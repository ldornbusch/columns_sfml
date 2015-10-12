// ColumnsNavigation.h: Schnittstelle für die Klasse ColumnsNavigation.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COLUMNSNAVIGATION_H__8EA2C376_6566_4132_805C_37F09AD1C8CB__INCLUDED_)
#define AFX_COLUMNSNAVIGATION_H__8EA2C376_6566_4132_805C_37F09AD1C8CB__INCLUDED_

#include "..\GAME\KeyboardNavigator.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../game/GameImageCloner.h"
#include "../All2DEngine/All2D/All2D_Base/xContainer.h"
#include "../All2DEngine/GUI/UIHoverButton.h"	// Hinzugefügt von der Klassenansicht

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

#endif // !defined(AFX_COLUMNSNAVIGATION_H__8EA2C376_6566_4132_805C_37F09AD1C8CB__INCLUDED_)
