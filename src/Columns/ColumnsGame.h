// ColumnsGame.h: Schnittstelle für die Klasse ColumnsGame.
// Enthält die gesamte Funktionalität und GameLogik
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COLUMNSGAME_H__2F4361A4_EE7F_11D5_B047_00E098802DF2__INCLUDED_)
#define AFX_COLUMNSGAME_H__2F4361A4_EE7F_11D5_B047_00E098802DF2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../game/GameImageCloner.h"
#include "../All2DEngine/All2D/All2D_Sprites/UIElement.h"
#include "../All2DEngine/All2D/All2D_System.h"


#include "ColumnsBackGround.h"	// Hinzugefügt von der Klassenansicht
#include "ColumnsStones.h"
#include "ColumnsPit.h"
#include "../All2DEngine/All2D/All2D_Base/ImageText.h"	// Hinzugefügt von der Klassenansicht

// sound engine
// initialization is in game controller init
#include "SoundConstants.h"
//#include "../sound/SoundFactory.h"
//static SoundEngine *sound;

class ColumnsGame :
	public UIElement,
	public GameImageCloner
{
public:
	void setPreview(bool blnFlag);
	void setJoker(bool blnFlag);
	void pause(bool blnRun);
	int getPoints();
	int getGameState();
	void getGFX(Image& imgGFXElements);
	bool handleEvent(Event* evt);
	int gameLogic();
	void reset();
	virtual bool paint(Image& backBuffer);
	ColumnsGame();
	virtual ~ColumnsGame();
private:
	void displayScore(Image& backBuffer);
	void advanceLevel();
	bool blnFallDown;
	int iAddMultiplier;
	bool blnRunAdd;
	int iAddPoints;
	int iGameState;
	int iOldGameState;
	int iPoints;
	int iLevel;
	long iLevelTime;
	ImageText ScoreFont;
	ColumnsStones activeStone;
	ColumnsPit Pit;
	ColumnsBackGround PlayField;
};

#endif // !defined(AFX_COLUMNSGAME_H__2F4361A4_EE7F_11D5_B047_00E098802DF2__INCLUDED_)
