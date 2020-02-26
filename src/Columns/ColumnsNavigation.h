// ColumnsNavigation.h: Schnittstelle f�r die Klasse ColumnsNavigation.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include "../Game/KeyboardNavigator.h"	// Added by ClassView
#include "../Game/GameImageCloner.h"
#include "../All2DEngine/All2D/All2D_Base/xContainer.h"
#include "../All2DEngine/Gui/UIHoverButton.h"	// Hinzugef�gt von der Klassenansicht

class ColumnsNavigation :
	public xContainer,
	public GameImageCloner
{
public:
	void setGameStatus(bool blnGameRuns);
	bool handleEvent(Event* evt);
	void setActive(bool flag);
	void getGFX(Image& imgGFXElements);
//	void menuUp();
//	void menuDown();
	void menuSelect();
	ColumnsNavigation();
	virtual ~ColumnsNavigation();

private:
	bool blnGameRunning;
	KeyboardNavigator KbdNavigator;
	UIHoverButton& getMenuButton(int index);
	void manageKeyPress(Event* evt);
//	int iActiveMenuEntry;
	bool blnIsActive;
	UIHoverButton btnDummy;
	UIHoverButton btnContinue;
	UIHoverButton btnStart;
	UIHoverButton btnHelp;
	UIHoverButton btnScore;
	UIHoverButton btnConfigs;
	UIHoverButton btnCredits;
	UIHoverButton btnExit;
};
