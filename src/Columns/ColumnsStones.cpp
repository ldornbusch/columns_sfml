// ColumnsStones.cpp: Implementierung der Klasse ColumnsStones.
// The ColumnsStone Paints itself in an offscreenbuffer
// only if it is rotated, it will update this offscreenbuffer
// (blnOrderChanged is true, then)
// The ScreenCoords are held in the normal SpriteCoordinates
// The IndexCoords are held in indexPosition
// Both CoordinateSystems should not be touched from outside..
//////////////////////////////////////////////////////////////////////

#include "ColumnsStones.h"
#include "ColumnsConstants.h"
#include "SoundConstants.h"
#include "../All2DEngine/All2D/All2D_System.h"

#define SPRITE_SIZE		32
#define SPRITE_COLORS	 6
//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

ColumnsStones::ColumnsStones()
{
	blnOrderChanged=true;
	blnFallDown=false;
	resize(SPRITE_SIZE,SPRITE_SIZE*3);
	setOffset(0,96);	// pivot ist an der untersten kante...des untersten steines
	srand((unsigned)All2D_System::getTime());
	Positioner.setPosition(208,0,224,448);	// is too special we need a Rect to parametrize this
	Positioner.initGrid(0,0,SPRITE_SIZE,SPRITE_SIZE);			

	blnShowPreview=true;
	blnJoker=true;

	iNextUpperColor=rand()%SPRITE_COLORS+1;
	iNextCenterColor=rand()%SPRITE_COLORS+1;
	iNextLowerColor=rand()%SPRITE_COLORS+1;
	ptrGamePit=NULL;
	iButtonTime=0;
}

bool ColumnsStones::isJoker()
{
	return (iUpperColor==COLUMNS_JOKER);
}

ColumnsStones::~ColumnsStones()
{
	finish();
}

void ColumnsStones::rotateUp()
{
	int tmp=iUpperColor;
	iUpperColor=iCenterColor;
	iCenterColor=iLowerColor;
	iLowerColor=tmp;
	blnOrderChanged=true;
}

void ColumnsStones::rotateDown()
{
	int tmp=iLowerColor;
	iLowerColor=iCenterColor;
	iCenterColor=iUpperColor;
	iUpperColor=tmp;
	blnOrderChanged=true;
}

int ColumnsStones::getColor(int position)
{
	switch (position)
	{
	case UPPER_STONE:
		return iUpperColor;
	case CENTER_STONE:
		return iCenterColor;
	case LOWER_STONE:
		return iLowerColor;
	}
	return -1;
}
// initalizes the three stones
// and sets it at top of the Screen
void ColumnsStones::start()
{
	iUpperColor=iNextUpperColor;
	iCenterColor=iNextCenterColor;
	iLowerColor=iNextLowerColor;

	if ((rand()%75==1 && iLevel>5) && blnJoker)	
	{
		iNextUpperColor=COLUMNS_JOKER;
		iNextCenterColor=COLUMNS_JOKER;
		iNextLowerColor=COLUMNS_JOKER;
	}else{
		iNextUpperColor=rand()%SPRITE_COLORS+1;
		iNextCenterColor=rand()%SPRITE_COLORS+1;
		iNextLowerColor=rand()%SPRITE_COLORS+1;
	}

	setPosition(304,0);	// This must be removed too specialized
	iTargetXIndex=Positioner.getGridIndex(304,0).x;	// y muss ein legaler wert sein.. 

//	setPosition(3,-3);
//	iTargetXIndex=3;

	blnOrderChanged=true;
	blnFallDown=false;			// space is nich gedrückt

	stoneSlowCounter=All2D_System::getTime();
	bVisible=true;
}

bool ColumnsStones::paint(Image& backBuffer)
{
	moveToTarget();
	if (blnOrderChanged)	// draw new Image of the Stone??
	{
		Image::clear();
		drawStone(UPPER_STONE,iUpperColor);
		drawStone(CENTER_STONE,iCenterColor);
		drawStone(LOWER_STONE,iLowerColor);
		blnOrderChanged=false;
	}

	// We will clip into the playfield by cloning the backBuffer.. too specialized
	imgClipImage.cloneImage(backBuffer,Rect(0,16,640,448));	// Clipping of upper Boarder..

	indexPosition=getGridPosition();


	// ToDo: Make too separate CordPairs: 1 Index, 1 Screencoords..
	calculateScreenCoord();
	if (bVisible){
			blit(imgClipImage, isJoker()? IMAGE_BLTMODE_ADD : IMAGE_BLTMODE_TRANS);
	}
	restoreIndexCoord();

	if (blnShowPreview)
	{
 		imgClipImage.cloneImage(backBuffer,Rect(176,16,32,96));	// Clipping of upper Boarder..
		//imgClipImage.clear();
		int iBltMode;
		if (iNextUpperColor!=COLUMNS_JOKER)
			iBltMode=IMAGE_BLTMODE_TRANS;
		else
			iBltMode=IMAGE_BLTMODE_ADD;
		
		drawStone(UPPER_STONE,iNextUpperColor,&imgClipImage,iBltMode);
		drawStone(CENTER_STONE,iNextCenterColor,&imgClipImage,iBltMode);
		drawStone(LOWER_STONE,iNextLowerColor,&imgClipImage,iBltMode);
	}

	return true;
}

void ColumnsStones::calculateScreenCoord()
{
	ScreenCoords=getPosition();

	int now=All2D_System::getTime();
	int tmp=now-getTime();

	float fac=(float)(tmp) / getFallTime(iLevel);
	int off=SPRITE_SIZE-1;
	if (fac<1.0)
		off=int(fac*SPRITE_SIZE);
	else
		off=SPRITE_SIZE;

	int iTmp=((indexPosition.y-3)*SPRITE_SIZE)+off;
	setPosition(getPosition().x1, iTmp);	
}
void ColumnsStones::restoreIndexCoord()
{
	setPosition(ScreenCoords.x1,ScreenCoords.y1,ScreenCoords.x2,ScreenCoords.y2);	
}

void ColumnsStones::drawStone(int iStonePosition, int iStoneColor, Image* dest, int bltMode)
{
	int y=0;
	switch (iStonePosition)
	{
		case UPPER_STONE:
			y=0;
		break;
		case CENTER_STONE:
			y=SPRITE_SIZE;
		break;
		case LOWER_STONE:
			y=SPRITE_SIZE*2;
		break;
	}
	if (dest==NULL)
		dest=(Image*)this;

	imgElements.setSrcRect(Rect((iStoneColor-1)*SPRITE_SIZE,0,SPRITE_SIZE,SPRITE_SIZE));
	imgElements.show(*dest,0,y, bltMode);

}

bool ColumnsStones::handleEvent(Event *evt)
{
	switch (evt->Type)
	{
		case MM_LEFT:
		{
			if (ptrGamePit)
				if (ptrGamePit->isFree(indexPosition.x-1,indexPosition.y))
				{
					// falls Stone noch zwischen den Grids, jump ansonsten smooth
					if (getPosition().x1==Positioner.getCoords(iTargetXIndex,0).x)
					{
						All2D_System::sound->playSample(SND_STONE_MOVE_LEFT);
						iTargetXIndex=indexPosition.x-1;
						iButtonTime=All2D_System::getTime();
					}
				}
		}			break;
		case MM_RIGHT:
		{
			if (ptrGamePit)
				if (ptrGamePit->isFree(indexPosition.x+1,indexPosition.y))
				{
					// falls Stone noch zwischen den Grids, jump ansonsten smooth
					if (getPosition().x1==Positioner.getCoords(iTargetXIndex,0).x)
					{
						iTargetXIndex=indexPosition.x+1;
						All2D_System::sound->playSample(SND_STONE_MOVE_RIGHT);
						iButtonTime=All2D_System::getTime();
					}
				}
		}			break;
		case MM_UP:
			All2D_System::sound->playSample(SND_STONE_ROTATE_UP);
			rotateUp();
			break;
		case MM_DOWN:
			All2D_System::sound->playSample(SND_STONE_ROTATE_DOWN);
			rotateDown();
			break;
		case MM_DROP:		// Game Logic Steering
				blnFallDown=true;
				All2D_System::sound->playSample(SND_STONE_DROP);
				setPosition(
					Positioner.getCoords(iTargetXIndex,0).x,
					getPosition().y1);
				break;
		default:
			break;
	}
	return true;
}


int ColumnsStones::gameLogic(int iLevel)
{
	int retVal=COLUMNS_STONE_MOVE;	// default;
	if (!ptrGamePit)			// nur für alle Fälle wg. Pointers..
		return retVal;

	int now=All2D_System::getTime();
	int tmp=now-getTime();
	if (tmp>getFallTime(iLevel)||blnFallDown)
	{
		if (ptrGamePit->isFree(indexPosition.x, indexPosition.y+1))	// ist der naechste Frei??
		{
			moveDown();
		} else {
			if (isJoker())
			{
				layDownStones();
				retVal=COLUMNS_REMOVE_JOKER;
			}else{
				layDownStones();
				retVal=COLUMNS_REMOVE_STONE;
			}
			if (indexPosition.x==3 && (indexPosition.y-3)<3 &&!ptrGamePit->isFree(3,3))	// bis oben aufgefüllt?
				retVal=COLUMNS_GAME_OVER;
		}

	} 
	return retVal;
}

// Here the stones will be dropped...and inserted into the Pit
void ColumnsStones::layDownStones()
{
	int pts=0, multiplier=0;

	if (!ptrGamePit)
		return;
	if (ptrGamePit->isFree(indexPosition.x, indexPosition.y))
	{
		if (indexPosition.y-2>=0)
			ptrGamePit->setStone(indexPosition.x,indexPosition.y-2,getColor(UPPER_STONE));
		if ((indexPosition.y-1)>=0)
			ptrGamePit->setStone(indexPosition.x,indexPosition.y-1,getColor(CENTER_STONE));
		if ((indexPosition.y-0)>=0)
			ptrGamePit->setStone(indexPosition.x,indexPosition.y-0,getColor(LOWER_STONE));
	}
	setVisible(false);
}

// DANGER !!
// Diese Funktion macht Annahmen über die Position des Pits(y=16) und das PitArray +3 ist nur da, weil 3 Zeilen nicht sichtbar sind..
// Variablen/Constanten fuer PitWidth/PitHeight einfuehren!
Point ColumnsStones::getGridPosition()// Brauche ich bald nicht mehr!!, wenn indexPosition und ScreenPosition voellig getrennt sind
{
	int tmp=0;
	tmp=Positioner.getGridPosition(getPosition().x1, getPosition().y1);
	return (Point(tmp%7, (tmp/7)+3));
}

// 2Do: Time, not Framebased...2Do: iTargetXIndex.. durch indexPosition.x ersetzen und screen und intern trennen...
void ColumnsStones::moveToTarget()
{
	int iTargetXCoord=Positioner.getCoords(iTargetXIndex,0).x;// y kann einfach =0, da .y nicht benoetigt wird

	int actXCoord=getPosition().x1;

	if(actXCoord!=iTargetXCoord)
	{
		if (actXCoord<iTargetXCoord)
			actXCoord+=8;
		if (actXCoord>iTargetXCoord)
			actXCoord-=8;
		setPosition(actXCoord);
	}
}


void ColumnsStones::moveDown()
{
	setPosition(getPosition().x1, getPosition().y1+SPRITE_SIZE);

	// indexPosition.y++;	// bald nur noch diese Function...

	stoneSlowCounter=All2D_System::getTime();
}

int ColumnsStones::getTime()
{
	return stoneSlowCounter;
}

void ColumnsStones::setPit(GamePit *ptrPit)
{
	ptrGamePit=ptrPit;
}

void ColumnsStones::setPreview(bool blnFlag)
{
	blnShowPreview=blnFlag;
}

void ColumnsStones::setJoker(bool blnFlag)
{
	blnJoker=blnFlag;
}

int ColumnsStones::getFallTime(int iLev)
{
	iLevel=iLev;
	int retVal=1000;
	if (iLev<12)			// Level 1-11 : each Level 50 ms faster
	{
		retVal=1000-iLev*50;
	} else if (iLev<22)		// Level 12-21 : each Level 25 ms faster
	{
		retVal=500-(iLev-11)*25;
	} else if(iLev<37)		// Level 22-36 : each Level 10 ms faster
	{
		retVal=250-(iLev-21)*10;
	} else if(iLev<51)		// Level 37-50 : each Level 5 ms faster
	{
		retVal=100-(iLev-36)*5;
	} else					// Level 50-: 5 steps per Second
	{
		retVal=20;
	}
	return retVal;
}

