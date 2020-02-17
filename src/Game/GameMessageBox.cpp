// GameMessageClass.cpp: implementation of the GameMessageClass class.
//
//////////////////////////////////////////////////////////////////////

#include "GameMessageBox.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GameMessageBox::GameMessageBox(): xContainer("MessageBox"),evtYes(0,0,0)
{
	isVisible=true;
	KbdNavigator.setMaxEntry(1);
	KbdNavigator.setMaxEntry(2);
	KbdNavigator.setMenuDirection(false);
}

GameMessageBox::~GameMessageBox()
{

}

string GameMessageBox::getMessage()
{
	return strMessage;
}

void GameMessageBox::setMessage(string strText)
{
	strMessage=strText;
	int lenx=(strText.length())*TextFont.getFontWidth()+2*10+5;
	int leny=7*TextFont.getFontHeight();
	if (lenx<(2*10+5+btnYes.getWidth()+btnNo.getWidth()))	// mindestbreite: so breit wie die Buttons+rand(10 px)!
		lenx=2*10+5+btnYes.getWidth()+btnNo.getWidth();
	if (lenx>620)// 2DO: WordWrap!
	{
//		strMessage.substr();
	}
	imgBackground.resize(lenx,leny);
	imgBackground.clear(0x2C4EB9);
	//imgBackground.clear(0xFF8080);
}

Event GameMessageBox::getEvent()
{
	return evtYes;
}

void GameMessageBox::setYesEvent(Event evt)
{
	evtYes=evt;
	btnYes.setSendFlag(evt.Type, evt.wData, evt.lData);
}

bool GameMessageBox::paint(Image& imgBackBuffer)
{
	int x1=(imgBackBuffer.getWidth()-imgBackground.getWidth())/2;
	int y1=(imgBackBuffer.getHeight()-imgBackground.getHeight())/2;
	imgBackground.show(imgBackBuffer,
					  x1,
					  y1,
					  IMAGE_BLTMODE_HALF);
	TextFont.PrintCenter(imgBackBuffer,y1+2*TextFont.getFontHeight(),strMessage.c_str());

	btnYes.setPosition(Rect(x1+10,y1+imgBackground.getHeight()-btnYes.getHeight()-10,btnYes.getWidth(),btnYes.getHeight()));
	btnNo.setPosition(Rect(x1+imgBackground.getWidth()-btnNo.getWidth()-10,
					   y1+imgBackground.getHeight()-btnNo.getHeight()-10,btnNo.getWidth(),btnNo.getHeight()));
	xContainer::paint(imgBackBuffer);

	return true;
}

bool GameMessageBox::handleEvent(Event *evt)
{
	if (isVisible)
	{
		if (KbdNavigator.handleEvent(evt))
		{
			getMenuButton(KbdNavigator.getLastEntry()).setHoverStatus(false);
			getMenuButton(KbdNavigator.getActualEntry()).setHoverStatus(true);
		}

		xContainer::handleEvent(evt);

		if (evt->Type==MM_NAVIGATION_HOVER){
			// Wenn die Maus bewegt wird, muss der aktuelle(Mausgewaehlte Eintrag auch dem KeyboardNavigator mitgeteilt werden..)
			getMenuButton(KbdNavigator.getActualEntry()).setHoverStatus(false);
			KbdNavigator.setActualEntry(evt->wData);
		}
		if (evt->Type==MM_FIRE||(evt->Type==MM_KEYDOWN && evt->wData==sf::Keyboard::Return))
			menuSelect();


	}return (!isVisible);		// Stoppt nach diesem xElement, das HandleRouting, falls die MsgBox sichtbar ist
}

void GameMessageBox::menuSelect()
{
	getMenuButton(KbdNavigator.getActualEntry()).fire();
}

UIHoverButton& GameMessageBox::getMenuButton(int index)
{
	switch(index)
	{
		case 1:
			return btnYes;
		case 2:
		default:
			return btnNo;
	}
}

void GameMessageBox::getGFX(Image& imgGFX)
{

	Image tmp;
	tmp.cloneImage(imgGFX);

	TextFont.cloneImage(imgGFX,Rect(224,208,80,64));
	TextFont.FontInit(16,16,10,"ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789:[]_@.-+*$%§!");

	tmp.setSrcRect(Rect(112,368,80,32));
	btnYes.cloneImage(tmp);
	btnYes.setHoverImage(tmp);
	btnYes.setHoverBlitMode(IMAGE_BLTMODE_ADD);
	btnYes.setHoverFlag(MM_NAVIGATION_HOVER,1);
	btnYes.setBlitMode(IMAGE_BLTMODE_HALF);
	btnYes.setPosition(Rect(240,120,80,32));
	btnYes.setSendFlag(0,0,0);
	add(btnYes);

	tmp.setSrcRect(Rect(112,336,55,32));
	btnNo.cloneImage(tmp);
	btnNo.setHoverImage(tmp);
	btnNo.setHoverBlitMode(IMAGE_BLTMODE_ADD);
	btnYes.setHoverFlag(MM_NAVIGATION_HOVER,2);
	btnNo.setBlitMode(IMAGE_BLTMODE_HALF);
	btnNo.setPosition(Rect(240,160,55,32));
	btnNo.setSendFlag(MM_KEYDOWN,sf::Keyboard::Escape,0);
	add(btnNo);

	setMessage("ARE YOU SURE?");	// 2DO: FontExtension..

}

void GameMessageBox::setVisible(bool blnFlag)
{
	isVisible=blnFlag;
}
