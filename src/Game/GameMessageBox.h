// GameMessageClass.h: interface for the GameMessageClass class.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include "../All2DEngine/All2D/All2D_Events/Event.h"	// Added by ClassView
#include "../All2DEngine/All2D/All2D_Base/ImageText.h"	// Added by ClassView
#include "../All2DEngine/All2D/All2D_Base/Image.h"	// Added by ClassView
#include "../All2DEngine/All2D/All2D_Base/xContainer.h"
#include "../All2DEngine/Gui/UIHoverButton.h"	// Added by ClassView
#include "KeyboardNavigator.h"	// Added by ClassView
#include "GameImageCloner.h"

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
