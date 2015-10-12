// GameMessageClass.h: interface for the GameMessageClass class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GAMEMESSAGECLASS_H__BC0A37C1_D9E7_475F_8BA5_AB72CDF11687__INCLUDED_)
#define AFX_GAMEMESSAGECLASS_H__BC0A37C1_D9E7_475F_8BA5_AB72CDF11687__INCLUDED_

#include "..\ALL2DENGINE\ALL2D\ALL2D_BASE\Image.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../All2DEngine/All2D/All2D_Base/xContainer.h"
#include "GameImageCloner.h"
#include "..\ALL2DENGINE\GUI\UIHoverButton.h"	// Added by ClassView
#include "..\ALL2DENGINE\ALL2D\ALL2D_EVENTS\Event.h"	// Added by ClassView
#include "..\ALL2DENGINE\ALL2D\ALL2D_BASE\ImageText.h"	// Added by ClassView
#include "KeyboardNavigator.h"	// Added by ClassView

class GameMessageBox : 
	public xContainer, 
	public GameImageCloner  
{
public:
	void setVisible(bool blnFlag);
	void getGFX(Image& imgGFX);
	bool handleEvent(Event* evt);
	bool paint(Image& imgBackBuffer);
	void setYesEvent(Event);
	Event getEvent();
	void setMessage(string strText);
	string getMessage();
	GameMessageBox();
	virtual ~GameMessageBox();

private:
	void menuSelect();
	UIHoverButton& getMenuButton(int index);
	KeyboardNavigator KbdNavigator;
	Image imgBackground;
	ImageText TextFont;
	bool isVisible;
	Event evtYes;
	UIHoverButton btnNo;
	UIHoverButton btnYes;
	string strMessage;
};

#endif // !defined(AFX_GAMEMESSAGECLASS_H__BC0A37C1_D9E7_475F_8BA5_AB72CDF11687__INCLUDED_)
