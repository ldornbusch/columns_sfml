// ColumnsGameController.h: Schnittstelle für die Klasse BallerGameController.
// Handelt das Spiel als gesamtes:
// Start Bildschirm, Instruktions, HighScore usw
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BALLERGAMECONTROLLER_H__42480621_C0F3_11D5_B046_00E098802DF2__INCLUDED_)
#define AFX_BALLERGAMECONTROLLER_H__42480621_C0F3_11D5_B046_00E098802DF2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../All2DEngine/All2D/AppGameController.h"

#include "ColumnsGame.h"
#include "../game/GameHighScore.h"
#include "../game/GameInstructions.h"
#include "../All2DEngine/All2D/All2D_Base/ImageText.h"
#include "ColumnsNavigation.h"
#include "ColumnsMouseMover.h"
#include "ColumnsConfig.h"
#include "ColumnsNameEditor.h"
#include "ColumnsMorganeDefrag.h"
#include "..\GAME\GameMessageBox.h"	// Added by ClassView
#include "ColumnsBlase.h"	// Added by ClassView

class ColumnsGameController : public AppGameController
{
public:
	void paintBackGround(Image& backBuffer);
	int iAppOldState;
	void setLayerState(int iState);
	virtual bool paint(Image& backBuffer);
	virtual bool handleEvent(Event *evt);
	void init();
	ColumnsGameController();
	virtual ~ColumnsGameController();

private:
	ColumnsBlase* myBlase;
	GameMessageBox myMsgBox;
	//bool paintBoss(Image draw);
	Image imgBackground;
	int iAppState;
	int iLayerState;

	Image imgGFXElements;

	GameInstructions myInstructions;
	GameHighScore highScore;

	ColumnsMorganeDefrag bossScreen;
	ColumnsGame	myGame;
	ColumnsNavigation myMenu;
	ColumnsMouseMover myMouse;
	ColumnsConfig myConfig;
	ColumnsNameEditor myEditor;

};

#endif // !defined(AFX_BALLERGAMECONTROLLER_H__42480621_C0F3_11D5_B046_00E098802DF2__INCLUDED_)
