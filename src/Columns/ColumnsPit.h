// ColumnsPit.h: Schnittstelle für die Klasse ColumnsPit.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include "../Game/GamePit.h"	// Hinzugefügt von der Klassenansicht
#include "../Game/GameImageCloner.h"
#include "ColumnsStones.h"

#define COL_PITWIDTH	 7
#define COL_PITHEIGHT	17

class ColumnsPit :	public GamePit,
					public GameImageCloner
{
public:
	void setFlames(bool blnFlag);
	void setStone(int x, int y, int value);
	int searchJoker();
	bool deleteSolution();
	int searchSolution();
	bool isFree(int x, int y);
	void emptyPit();
	bool paint(Image& backBuffer);
	ColumnsPit();
	virtual ~ColumnsPit();

private:
	int getStone(int x, int y);
	bool checkAt(int x,int y);
	bool valid(int x, int y);
	void removeGaps();
	bool blnShowFlames;
	vector<Point>	vecTripleStones;
	vector<Point>	vecFireStones;
	int stones[COL_PITWIDTH*COL_PITHEIGHT];	// The Stones laying in the Pit 7 each row numberation: 0  1  2  3  4  5  6
																		//		7  8  9 10 11 12 13  (y*7 + x)
};
