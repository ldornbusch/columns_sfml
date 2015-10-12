// ColumnsStones.h: Schnittstelle für die Klasse ColumnsStones.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FALLINGSTONES_H__0E14D9BD_2FF0_4265_95EC_4F2771593FB0__INCLUDED_)
#define AFX_FALLINGSTONES_H__0E14D9BD_2FF0_4265_95EC_4F2771593FB0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../game/GameImageCloner.h"
#include "../Game/GameStone.h"
#include "../Game/GamePit.h"
#include "../All2DEngine/UTILS\Grid.h"	// Hinzugefügt von der Klassenansicht
#include "../All2DEngine/UTILS\Point.h"	// Hinzugefügt von der Klassenansicht
#include "../All2DEngine/All2D/All2D_Base/Image.h"	// Hinzugefügt von der Klassenansicht
#include "..\ALL2DENGINE\UTILS\POINT.H"	// Added by ClassView

#define	UPPER_STONE		0x0001
#define	CENTER_STONE	0x0002
#define	LOWER_STONE		0x0003

class ColumnsStones :	public GameStone  ,
						public GameImageCloner
{
public:
	int gameLogic(int iLevel);
	void setPit(GamePit* ptrPit);
	bool isJoker();
	int getFallTime(int iLev);
	void setJoker(bool blnFlag);
	void setPreview(bool blnFlag);
	int getTime();
	void moveDown();
	Point getGridPosition();
	bool handleEvent(Event* evt);
	bool paint(Image& backBuffer);
	void start();
	int getColor(int position=UPPER_STONE);
	void rotateDown();
	void rotateUp();
	ColumnsStones();
	virtual ~ColumnsStones();

	Point indexPosition;

private:
	int iButtonTime;
	void calculateScreenCoord();
	void restoreIndexCoord();
	void moveToTarget();
	void layDownStones();
	void drawStone(int iStonePosition, int iStoneColor, Image* dest=NULL, int bltMode=IMAGE_BLTMODE_TRANS);
	GamePit* ptrGamePit;
	Image imgClipImage;
	int stoneSlowCounter;
	Grid Positioner;		// Can transpose the ScreenCoords into PitArray-Indexes
	int iUpperColor;			// Color of the Stones
	int iCenterColor;
	int iLowerColor;
	int iNextUpperColor;			// Color of the next Stones
	int iNextCenterColor;
	int iNextLowerColor;
	bool blnFallDown;		// This is true when the Space button was pressed-> The stone is falling as fast as possible
	bool blnOrderChanged;	// has the Order changed? if so, the SpriteImage has to be repainted
	bool blnShowPreview;	// Preview allowed?
	bool blnJoker;			// Joker allowed?
	Rect ScreenCoords;
	int	 iTargetXIndex;			// The XCoord which has to be reached
	int  iXSpeed;			// The Offset which is added to the actual XCoord
	int  iLevel;			// The Offset which is added to the actual XCoord
};

#endif // !defined(AFX_FALLINGSTONES_H__0E14D9BD_2FF0_4265_95EC_4F2771593FB0__INCLUDED_)
