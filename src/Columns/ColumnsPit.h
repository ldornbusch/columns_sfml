// ColumnsPit.h: Schnittstelle für die Klasse ColumnsPit.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OLUMNSPIT_H__A76F7F37_3AD5_4D1E_90B5_BB3660ACB57D__INCLUDED_)
#define AFX_OLUMNSPIT_H__A76F7F37_3AD5_4D1E_90B5_BB3660ACB57D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../Game/GamePit.h"	// Hinzugefügt von der Klassenansicht
#include "ColumnsStones.h"
#include "../game/GameImageCloner.h"

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

#endif // !defined(AFX_OLUMNSPIT_H__A76F7F37_3AD5_4D1E_90B5_BB3660ACB57D__INCLUDED_)
