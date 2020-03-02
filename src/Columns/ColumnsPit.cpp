// ColumnsPit.cpp: Implementierung der Klasse ColumnsPit.
//
//////////////////////////////////////////////////////////////////////

#include <All2D/All2DEngine/All2D/All2D_System.h>
#include "ColumnsConstants.h"
#include "ColumnsPit.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

ColumnsPit::ColumnsPit()
{
}

ColumnsPit::~ColumnsPit()
{

}

bool ColumnsPit::paint(Image& backBuffer)
{
	for (int x=0; x<COL_PITWIDTH; x++)
		for (int y=COL_PITHEIGHT-1;y>2;y--)
		{
			int iStoneColor=abs(stones[y*COL_PITWIDTH+x] % 7);
			if (iStoneColor!=0)
			{
				imgElements.setSrcRect(Rect((iStoneColor-1)*32,0,32,32));
				imgElements.show(backBuffer,208+x*32,16+(y-3)*32);
			}
		}

	if (blnShowFlames)// 2Do: Use an AnimationObject...
	{
		static unsigned int now=0;
		static unsigned int fire=0;
		if (All2D_System::getTime()-now>30){
			if (++fire>6)
				fire=0;
			now=All2D_System::getTime();
		}

		imgElements.setSrcRect(Rect(fire*32,176,32,80));
		for (size_t x=0;x<vecFireStones.size();++x)
		{
			Point tmp=vecFireStones[x];
			imgElements.show(backBuffer,tmp.x*32+208,16+(tmp.y-3)*32-48,IMAGE_BLTMODE_ADD);
		}
		imgElements.setSrcRect(Rect(0,0,imgElements.getWidth(),imgElements.getHeight()));
	}
	return true;
}

void ColumnsPit::emptyPit()
{
	for (int x=0;x<(COL_PITWIDTH*COL_PITHEIGHT); x++)
		stones[x]=0;

	blnShowFlames=false;
}

void ColumnsPit::removeGaps()
{
	for (int x=0; x<COL_PITWIDTH ;x++)
	{
		for (int y=COL_PITHEIGHT-1; y>-1; y--)
		{
			int tmpCol=getStone(x,y);
			if (tmpCol==0 && y>0)
			{ // falls der Stone leer ist, muss die Reihe über ihm nach einem Stone abgesucht werden, der dann in das Loch gelegt wird
				for (int tmpY=y; tmpY>=0; tmpY-- )
				{
					if (getStone(x, tmpY)!=0)
					{
						setStone(x,y,getStone(x,tmpY));
						setStone(x,tmpY,0);
						break;
					}
				}
			}
		}
	}
}

int ColumnsPit::getStone(int x, int y)
{
	if (valid(x,y))
		return stones[y*COL_PITWIDTH+x];
	else
		return -1;
}

// This Routine can be asked, if a place in the
// Pit is free..(needed by FallingStone to check Collision)
bool ColumnsPit::isFree(int x, int y)
{
		int tmp=getStone(x,y);
		return (tmp==0);
}

// only a small checkRoutine...
bool ColumnsPit::valid(int x, int y)
{
	return  (x<COL_PITWIDTH && x>=0 && y<COL_PITHEIGHT && y>=0);
}

// Sucht jeden Stein ab, ob er Mitglied einer  3er Gruppe ist..
int ColumnsPit::searchSolution()
{
	vecFireStones.clear();
	for (int x=0; x<COL_PITWIDTH; x++)
		for (int y=0;y<COL_PITHEIGHT; y++)
		{
			if (checkAt(x,y))
			{
				vecTripleStones.insert(vecTripleStones.begin(), Point(x,y));
				vecFireStones.insert(vecFireStones.begin(), Point(x,y));
			}
		}

/*	for (x=0;x<vecTripleStones.size();x++)
	{
		Point tmp=vecTripleStones[x];
		setStone(tmp.x,tmp.y,0);
	}
*/
	return vecTripleStones.size();
}

// return: if some gaps occurs..
// clears all found stones which were presen in a 3er Group
bool ColumnsPit::deleteSolution()
{
	if (vecTripleStones.size()>0)
	{
		for (size_t x=0;x<vecTripleStones.size();x++)
		{
			Point tmp=vecTripleStones[x];
			setStone(tmp.x,tmp.y,0);
		}
		removeGaps();
		vecTripleStones.clear();
		return true;
	}
	return false;
}

// Untersucht den Stein an Position x/y, ob er Mitglied einer 3er Gruppe ist
bool ColumnsPit::checkAt(int x, int y)
{
	/* So werden die Nachbarpunkte gecheckt:
	   1 2 3
		 8 X 4
		 7 6 5
		 Wenn ein Punkt die gleiche Farbe hat, wird der nächste
		 in der gleichen Richtung gecheckt (CoordOffset*2) und der
		 gegenüberliegende (Cooroffset*(-1))
	*/
	int checkCoords[2*8]={-1,-1,	0, -1,	1, -1,
												 1, 0,	1,  1,	0,	1,
												-1, 1, -1,  0
	};
	bool retVal=false;
	int color=getStone(x,y);
	if (color>0)
	{
		for(int neighbor=0; neighbor<8; neighbor++)
		{
			int xOff=checkCoords[2*neighbor];
			int yOff=checkCoords[2*neighbor+1];
			if (getStone(x+xOff, y+yOff)==color)
			{	// Nachbar ist gleich -> 3. Stein finden...
				if ((getStone(x+2*xOff, y+2*yOff)==color) ||
						(getStone(x-xOff,y-yOff)==color))
				{	// 3. Stein gefunden !
					retVal=true;
					break;
				}
			}
		}
	}
	return retVal;
}


int ColumnsPit::searchJoker()
{
	int iJokerCol=-1;
	for (int x=0; x<COL_PITWIDTH; x++)
		for (int y=COL_PITHEIGHT-1;y>-1; y--)
		{
			if (getStone(x,y)==COLUMNS_JOKER)
			{
				iJokerCol=getStone(x,y+1);
				break;
			}
		}

	for (int x=0; x<COL_PITWIDTH; x++)
		for (int y=0;y<COL_PITHEIGHT; y++)
		{
			if (getStone(x,y)==iJokerCol)
				vecTripleStones.insert(vecTripleStones.begin(), Point(x,y));
			if (getStone(x,y)==COLUMNS_JOKER)
				setStone(x,y,0);// der Joker wird als Punkte nicht gezählt
		}
// Clear the Stones
	for (size_t x=0;x<vecTripleStones.size();x++)
	{
		Point tmp=vecTripleStones[x];
		setStone(tmp.x, tmp.y,0);
	}

	return vecTripleStones.size();
}

void ColumnsPit::setStone(int x, int y, int value)
{
	if (valid(x,y))
	{
		stones[y*COL_PITWIDTH+x]=value;
	}
}

void ColumnsPit::setFlames(bool blnFlag)
{
	blnShowFlames=blnFlag;
	if(!blnShowFlames)	// wenn Flames aus sind, Vector löschen
		vecFireStones.clear();
}
