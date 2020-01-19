// ColumnsGame.cpp: Implementierung der Klasse ColumnsGame.
//
//////////////////////////////////////////////////////////////////////

#include "ColumnsGame.h"
#include "ColumnsConstants.h"
#include "../All2Dengine/All2D/All2D_Events/MessageManager.h"
#include <math.h>

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

ColumnsGame::ColumnsGame()
{
	iGameState=COLUMNS_GAME_OUT;
}

ColumnsGame::~ColumnsGame()
{
}

void ColumnsGame::getGFX(Image& imgGFXElements)
{
	GameImageCloner::getGFX(imgGFXElements);
	PlayField.getGFX(imgGFXElements);
	Pit.getGFX(imgGFXElements);
	activeStone.getGFX(imgGFXElements);
	activeStone.setPit(&Pit);
	ScoreFont.cloneImage(imgGFXElements,Rect(224,112,80,96));
	ScoreFont.FontInit(32,32,5,"0123456789x ");
	reset();
	iGameState=COLUMNS_GAME_OUT;
}

void ColumnsGame::reset()
{
	Pit.emptyPit();
	activeStone.start();
	iLevel=0;
	advanceLevel();
	iOldGameState=iGameState=COLUMNS_STONE_MOVE;
	iPoints=0;
	iAddPoints=0;
	iAddMultiplier=0;
	blnRunAdd=false;
}

bool ColumnsGame::paint(Image& backBuffer)
{
	PlayField.paint(backBuffer);

	if(iGameState!=COLUMNS_GAME_PAUSE){
		gameLogic();
		Pit.paint(backBuffer);
		activeStone.paint(backBuffer);
	}	else {
		static float iRadius=30.0f;		// Display Pause Logo
		static int a=0;
		int iRotSpeed=3;
		int xc=sin(a*(3.14f/180.0f))*iRadius;
		int yh=cos(a*(3.14f/180.0f))*50;
		a+=iRotSpeed;
		imgElements.setSrcRect(Rect(0,304,128,32));
		imgElements.show(backBuffer, 230+xc,225-abs(yh/2),165,yh,IMAGE_BLTMODE_ADD);
	}

	if (iGameState==COLUMNS_GAME_OVER)
	{
		static float iRadius=30.0f;		// Display Game Over Logo
		static int a=0;
		int iRotSpeed=3;
		int xc=sin(a*(3.14f/180.0f))*iRadius;
		int yh=cos(a*(3.14f/180.0f))*50;
		a+=iRotSpeed;
		iRadius-=iRotSpeed*(30.0f/720.0f);
		imgElements.setSrcRect(Rect(225,5,165,50));
		imgElements.show(backBuffer, 230+xc,225-abs(yh/2),165,yh,IMAGE_BLTMODE_ADD);
		if (a>720)
		{
			a=0;
			iRadius=30.0f;
			iGameState=COLUMNS_GAME_OUT;
		}
	}
	// Displaying Score...
	displayScore(backBuffer);
	return true;
}

int ColumnsGame::gameLogic()
{
// Here will be the Logic of the game: Stone Moving, and inserting into the Pit..
	unsigned int now=All2D_System::getTime();
	static unsigned int iReactionTime=0;		// How long to wait before next removing/searching..is at beginning 0, when gaps found it will be set to 500 ms
	static unsigned int iExplosionBrake=0;	// Timer for removing Gaps / Stones
	static int iCalculatedPoints=0;
	switch (iGameState)
	{
		case COLUMNS_REMOVE_JOKER:
		{
			if ((now-iExplosionBrake)>iReactionTime)
			{
				int iTmp=Pit.searchJoker();	// How many stones have to be removed?
				iCalculatedPoints+=(iTmp*10);
				iAddPoints+=(iTmp*10);	//damit man den Bonus auch schon hochzählen sieht...

				if (iTmp>0)						// if there are some stones, remove Gaps in next loop..
				{
					All2D_System::sound->playSample(SND_JOKER_MATCH);
					iAddMultiplier=0;
					iGameState=COLUMNS_REMOVE_GAP;
				} else
				{
					activeStone.start();		// neuer Stein..
					iGameState=COLUMNS_STONE_MOVE;
				}
				iExplosionBrake=now;
			}
		}
		break;
		case COLUMNS_REMOVE_STONE:
		{
			if ((now-iExplosionBrake)>iReactionTime)
			{
				int iTmp=Pit.searchSolution();	// How many stones have to be removed?
				iCalculatedPoints+=(iTmp*10);
				iAddPoints+=(iTmp*10);	//damit man den Bonus auch schon hochzählen sieht...

				if (iTmp>0)
				{						// if there are some stones, remove Gaps in next loop..
					static int iMatchSound=0;
					if (++iMatchSound>6) iMatchSound=0;
					switch (iMatchSound) {
						case 1:
							All2D_System::sound->playSample(SND_STONE_MATCH_2);
							break;
						case 2:
							All2D_System::sound->playSample(SND_STONE_MATCH_3);
							break;
						case 3:
							All2D_System::sound->playSample(SND_STONE_MATCH_4);
							break;
						case 4:
							All2D_System::sound->playSample(SND_STONE_MATCH_5);
							break;
						case 5:
							All2D_System::sound->playSample(SND_STONE_MATCH_6);
							break;
						case 6:
							All2D_System::sound->playSample(SND_STONE_MATCH_7);
							break;
						default:
							All2D_System::sound->playSample(SND_STONE_MATCH);
							break;
					}
					Pit.setFlames(true);
					iGameState=COLUMNS_REMOVE_GAP;

				}else{							// Keine 3er Gruppen mehr gefunden....

					activeStone.start();		// neuer Stein..
					iGameState=COLUMNS_STONE_MOVE;

					iReactionTime=0;			// WarteZeit wieder auf 0

					iAddPoints+=(iAddMultiplier-1)*iCalculatedPoints;	// Bonus ausrechnen (einmal ist der Bonus ja schon oben addiert worden..

					iAddMultiplier=0;
					iCalculatedPoints=0;	// for next Stone
					if (iAddPoints>0)
						blnRunAdd=true;

					Pit.setFlames(false);
				}
				iExplosionBrake=now;
			} else {
				Pit.setFlames(false);
			}
			break;
		}
		case COLUMNS_REMOVE_GAP:
		{
			if ((now-iExplosionBrake)>COLUMNS_REACTIONTIME)		// Wait 500 ms
			{
				if (Pit.deleteSolution())
				{
					iAddMultiplier++;
					iGameState=COLUMNS_REMOVE_STONE;	// look in the Pit if there are more stones to find...
					iReactionTime=COLUMNS_REACTIONTIME;					// warteZeit auf 500 ms
				}
				iExplosionBrake=now;
				//All2D_System::sound->playSample(SND_REMOVE_GAP);
			}
			break;
		}
		case COLUMNS_STONE_MOVE:
		{
			unsigned int  test=All2D_System::getTime();
			if (test>iLevelTime)
				advanceLevel();

			iGameState=activeStone.gameLogic(iLevel);
			if ( iGameState==COLUMNS_GAME_OVER ) {
				All2D_System::sound->playSample(SND_GAME_OVER);
				iPoints+=iAddPoints;
				iAddPoints=0;
			}
		}
	}
	if ( blnRunAdd && iCalculatedPoints%10 == 0)
		All2D_System::sound->playSample(SND_ADD_POINT);

	return iPoints;
}

bool ColumnsGame::handleEvent(Event *evt)
{
	if (iGameState!=COLUMNS_GAME_OUT)
	{
		switch (evt->Type)
		{
			case MM_KEYDOWN:
			{
				char a=(char)evt->wData;
				switch (a) {
					case sf::Keyboard::F2:
						reset();
						break;
					default:
						if (iGameState==COLUMNS_GAME_OVER)
							iGameState=COLUMNS_GAME_OUT;
					break;
				}

			}
			break;
			case MM_LBUTTONDOWN:
			case MM_RBUTTONDOWN:
				if (iGameState==COLUMNS_GAME_OVER)
					iGameState=COLUMNS_GAME_OUT;
				break;
			case MM_DROP:
				break;

		}
		if (iGameState!=COLUMNS_GAME_PAUSE)
			activeStone.handleEvent(evt);
	}
	return true;
}

void ColumnsGame::displayScore(Image& backBuffer)
{
	char strTemp[20];
	wsprintf(strTemp,"%07d", iPoints);
	ScoreFont.PrintAt(backBuffer,208,17,strTemp,IMAGE_BLTMODE_HALF);
	if (iAddPoints>0)
	{
		wsprintf(strTemp,"%03d", iAddPoints);
		ScoreFont.PrintAt(backBuffer,336,49,strTemp,IMAGE_BLTMODE_HALF);
	}

	if (iAddMultiplier>1)
	{
		wsprintf(strTemp,"x%d", iAddMultiplier);
		ScoreFont.PrintAt(backBuffer,432,49,strTemp,IMAGE_BLTMODE_HALF);
	}

	int xs=64;
	int counter=All2D_System::getTime();
	xs = 64 + sin((double)counter*0.006)*10-10;
	imgElements.setSrcRect(Rect(112,416,64,64));
	imgElements.show(backBuffer,464,32-xs/2,64,xs,IMAGE_BLTMODE_TRANS);


	wsprintf(strTemp,"%d", iLevel);
	if ((iLevel)<10)
		ScoreFont.PrintAt(backBuffer,479,17,strTemp,IMAGE_BLTMODE_ADD);
	else
		ScoreFont.PrintAt(backBuffer,463,17,strTemp,IMAGE_BLTMODE_ADD);

	if (iAddPoints>0 && blnRunAdd)
	{
		iAddPoints--;
		iPoints++;
		if (iAddPoints==0)
			blnRunAdd=false;
	}
}

int ColumnsGame::getGameState()
{	return iGameState;}
int ColumnsGame::getPoints()
{	return iPoints;}

void ColumnsGame::pause(bool blnPause)
{
	if (iGameState==COLUMNS_GAME_OUT)
		return;
	static int iPauseTimer=0;	// Time measured in pause Mode..
	static bool blnPauseModeEntered=false;
	if (iGameState!=COLUMNS_GAME_PAUSE && blnPause)
	{
		iOldGameState=iGameState;
		iGameState=COLUMNS_GAME_PAUSE;
		iPauseTimer=All2D_System::getTime();
		blnPauseModeEntered=true;
		All2D_System::sound->playSample(SND_TOGGLE);
	}	else {
		if (!blnPause)
			iGameState=iOldGameState;

		if (blnPauseModeEntered)	// So, no illegal Time is calculated..if time is not started..
		{
			iLevelTime+=(All2D_System::getTime()-iPauseTimer);
			blnPauseModeEntered=false;
		}

	}
}

void ColumnsGame::setPreview(bool blnFlag)
{
	All2D_System::sound->playSample(SND_TOGGLE);
	activeStone.setPreview(blnFlag);
}

void ColumnsGame::setJoker(bool blnFlag)
{
	All2D_System::sound->playSample(SND_TOGGLE);
	activeStone.setJoker(blnFlag);
}

void ColumnsGame::advanceLevel()
{
	iLevel++;
	iLevelTime=All2D_System::getTime()+60*1000; // 1 min. für jedes Level..
}
