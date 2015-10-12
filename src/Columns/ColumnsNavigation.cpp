// ColumnsNavigation.cpp: Implementierung der Klasse ColumnsNavigation.
//
//////////////////////////////////////////////////////////////////////

#include "ColumnsNavigation.h"
#include "ColumnsConstants.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

ColumnsNavigation::ColumnsNavigation() : xContainer("Menu")
{
	KbdNavigator.setMaxEntry(6);	// Six Menu entries..
	KbdNavigator.setMinEntry(1);
}

ColumnsNavigation::~ColumnsNavigation()
{
	blnGameRunning=false;
}

void ColumnsNavigation::getGFX(Image& imgGFXElements)
{
	GameImageCloner::getGFX(imgGFXElements);

	Image tmp;
	tmp.cloneImage(imgGFXElements);

	tmp.setSrcRect(Rect(0,272,160,31));
	btnContinue.cloneImage(tmp);
	btnContinue.setHoverImage(tmp);
	btnContinue.setHoverFlag(COLUMNS_NAVIGATION_HOVER,7);
	btnContinue.setHoverBlitMode(IMAGE_BLTMODE_ADD);
	btnContinue.setBlitMode(IMAGE_BLTMODE_HALF);
	btnContinue.setPosition(Rect(240,120,160,32));
	btnContinue.setSendFlag(MM_KEYDOWN,sf::Keyboard::Escape,0);
//	add(btnContinue);

	tmp.setSrcRect(Rect(224,320,160,32));
	btnStart.cloneImage(tmp);
	btnStart.setHoverImage(tmp);
	btnStart.setHoverFlag(COLUMNS_NAVIGATION_HOVER,1);
	btnStart.setHoverBlitMode(IMAGE_BLTMODE_ADD);
	btnStart.setBlitMode(IMAGE_BLTMODE_HALF);
	btnStart.setPosition(Rect(240,160,160,32));
	btnStart.setSendFlag(MM_START_REQUEST,0,0);
	add(btnStart);

	tmp.setSrcRect(Rect(224,416,160,32));
	btnScore.cloneImage(tmp);
	btnScore.setHoverImage(tmp);
	btnScore.setHoverFlag(COLUMNS_NAVIGATION_HOVER,2);
	btnScore.setHoverBlitMode(IMAGE_BLTMODE_ADD);
	btnScore.setBlitMode(IMAGE_BLTMODE_HALF);
	btnScore.setPosition(Rect(240,200,160,32));
	btnScore.setSendFlag(MM_HIGHSCORE,0,0);
	add(btnScore);

	tmp.setSrcRect(Rect(224,352,160,32));
	btnConfigs.cloneImage(tmp);
	btnConfigs.setHoverImage(tmp);
	btnConfigs.setHoverFlag(COLUMNS_NAVIGATION_HOVER,3);
	btnConfigs.setHoverBlitMode(IMAGE_BLTMODE_ADD);
	btnConfigs.setBlitMode(IMAGE_BLTMODE_HALF);
	btnConfigs.setPosition(Rect(240,240,160,32));
	btnConfigs.setSendFlag(MM_CONFIG,0,0);
	add(btnConfigs);

	tmp.setSrcRect(Rect(224,384,160,32));
	btnHelp.cloneImage(tmp);
	btnHelp.setHoverImage(tmp);
	btnHelp.setHoverFlag(COLUMNS_NAVIGATION_HOVER,4);
	btnHelp.setHoverBlitMode(IMAGE_BLTMODE_ADD);
	btnHelp.setBlitMode(IMAGE_BLTMODE_HALF);
	btnHelp.setPosition(Rect(272,280,160,32));
	btnHelp.setSendFlag(MM_HELP,0,0);
	add(btnHelp);

	tmp.setSrcRect(Rect(224,448,160,32));
	btnCredits.cloneImage(tmp);
	btnCredits.setHoverImage(tmp);
	btnCredits.setHoverFlag(COLUMNS_NAVIGATION_HOVER,5);
	btnCredits.setHoverBlitMode(IMAGE_BLTMODE_ADD);
	btnCredits.setBlitMode(IMAGE_BLTMODE_HALF);
	btnCredits.setPosition(Rect(240,320,160,32));
	btnCredits.setSendFlag(MM_CREDITS,0,0);
	add(btnCredits);

	tmp.setSrcRect(Rect(224,288,160,32));
	btnExit.cloneImage(tmp);
	btnExit.setHoverImage(tmp);
	btnExit.setHoverFlag(COLUMNS_NAVIGATION_HOVER,6);
	btnExit.setHoverBlitMode(IMAGE_BLTMODE_ADD);
	btnExit.setBlitMode(IMAGE_BLTMODE_HALF);
	btnExit.setPosition(Rect(272,360,160,32));
	btnExit.setSendFlag(MM_QUIT,0,0);
	add(btnExit);
}


void ColumnsNavigation::setActive(bool flag)
{
	blnIsActive=flag;
}

bool ColumnsNavigation::handleEvent(Event *evt)
{
	if (blnIsActive)
	{
		bool retVal=xContainer::handleEvent(evt);	// normally rout all events to the Buttons
		manageKeyPress(evt);	// For Keyboard control
		return retVal;
	}
	else
		return true;
}

void ColumnsNavigation::manageKeyPress(Event *evt)
{
	if (KbdNavigator.handleEvent(evt))
	{
		getMenuButton(KbdNavigator.getLastEntry()).setHoverStatus(false);
		getMenuButton(KbdNavigator.getActualEntry()).setHoverStatus(true);
	}

	switch(evt->Type)
	{
		case MM_KEYDOWN:
		{
			char a=(char)evt->wData;
			switch (a) {
				case sf::Keyboard::Return:
					menuSelect();
						break;
				default:
					break;
				}
			} break;
		case COLUMNS_NAVIGATION_HOVER:	// Wenn die Maus bewegt wird, muss der aktuelle(Mausgewaehlte Eintrag auch dem KeyboardNavigator mitgeteilt werden..)
			getMenuButton(KbdNavigator.getActualEntry()).setHoverStatus(false);
			KbdNavigator.setActualEntry(evt->wData);
		break;
	}
	if (evt->Type==MM_DROP)
		menuSelect();
}

void ColumnsNavigation::menuSelect()
{
	getMenuButton(KbdNavigator.getActualEntry()).fire();
}

UIHoverButton& ColumnsNavigation::getMenuButton(int index)
{
	switch(index)
	{
		case 1:
			return btnStart;
		case 2:
			return btnScore ;
		case 3:
			return btnConfigs ;
		case 4:
			return btnHelp;
		case 5:
			return btnCredits ;
		case 6:
			return btnExit;
		case 7:
			return btnContinue;
		default:
			return btnDummy;//	2DO: remove this ugly small hack..But what to return, if no reference is valid?
	}
}

void ColumnsNavigation::setGameStatus(bool blnGameRuns)
{
	blnGameRunning=blnGameRuns;
	if (blnGameRunning)
	{
		xContainer::remove(btnContinue);
		xContainer::add(btnContinue);
		KbdNavigator.setMaxEntry(7);	// Seven Menu entries..(Continue-Button is added)

	}else{
		xContainer::remove(btnContinue);
		KbdNavigator.setMaxEntry(6);	// Six Menu entries..

	}
}
