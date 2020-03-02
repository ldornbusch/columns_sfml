// ColumnsGameController.cpp: Implementierung der Klasse ColumnsGameController.
// 020119 LDO: iLayerState darf nur durch die Function setLayerState gesetzt werden, da
//						 myMenu dementsprechend auf Active oder nicht gesetzt werden muss,
//						 damit die Buttons nicht im unsichtbaren Zustand die HandleEvents bekommen
// 020308 DAV: added standard sound engine
//////////////////////////////////////////////////////////////////////

#include <All2D/All2DEngine/All2D/All2D_System.h>
#include <All2D/All2DEngine/All2D/All2D_Events/MessageManager.h>
#include "ColumnsGameController.h"
#include "ColumnsConstants.h"
#define BLASEN_ANZAHL 55
#define BLASEN_ANZAHL_SMALL  40
//#define BLASEN_ANZAHL_MEDIUM 15	// Die Grossen sind dann BLASEN_ANZAHL-BLASEN_ANZAHL_SMALL-BLASEN_ANZAHL_MEDIUM
#define BLASEN_ANZAHL_MEDIUM 10	// Die Grossen sind dann BLASEN_ANZAHL-BLASEN_ANZAHL_SMALL-BLASEN_ANZAHL_MEDIUM
//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

ColumnsGameController::ColumnsGameController():imgBackground(510,300)
{
//	imgBackground(510,300);
	imgBackground.clear(0x050505);
	imgBackground.setOffset(0,0);
	iAppState=COLUMNS_APP_TITLE;
	iAppOldState=COLUMNS_APP_TITLE;

	myBlase=new ColumnsBlase[BLASEN_ANZAHL];
}

ColumnsGameController::~ColumnsGameController()
{
	delete[] myBlase;
}

void ColumnsGameController::init()
{
	AppGameController::init();

	// load samples
	All2D_System::sound->loadSample(SND_FILE_0);
	All2D_System::sound->loadSample(SND_FILE_1);
	All2D_System::sound->loadSample(SND_FILE_2);
	All2D_System::sound->loadSample(SND_FILE_3);
	All2D_System::sound->loadSample(SND_FILE_4);
	All2D_System::sound->loadSample(SND_FILE_5);
	All2D_System::sound->loadSample(SND_FILE_6);
	All2D_System::sound->loadSample(SND_FILE_7);
	All2D_System::sound->loadSample(SND_FILE_8);
	All2D_System::sound->loadSample(SND_FILE_9);
	All2D_System::sound->loadSample(SND_FILE_10);
	All2D_System::sound->loadSample(SND_FILE_11);
	All2D_System::sound->loadSample(SND_FILE_12);
	All2D_System::sound->loadSample(SND_FILE_13);
	All2D_System::sound->loadSample(SND_FILE_14);
	All2D_System::sound->loadSample(SND_FILE_15);
	All2D_System::sound->loadSample(SND_FILE_16);
	All2D_System::sound->loadSample(SND_FILE_17);

	// load the total ressource image
	imgGFXElements.loadImage("data/elements.png");
	Image imgTmp;
	imgTmp.loadImage("data/elements.jpg");
	imgTmp.show(imgGFXElements,0,480,IMAGE_BLTMODE_FAST);
	imgTmp.resize(0,0);// Speicher wieder freigeben

	// get graphics from resource image
	myGame.getGFX(imgGFXElements);
	myInstructions.getGFX(imgGFXElements);
	highScore.getGFX(imgGFXElements);
	bossScreen.getGFX(imgGFXElements);
	myMenu.getGFX(imgGFXElements);
	myMouse.getGFX(imgGFXElements);
	myConfig.getGFX(imgGFXElements);
	myMsgBox.getGFX(imgGFXElements);

	for (int x=0;x<BLASEN_ANZAHL;x++)
	{
		myBlase[x].setType(((x<BLASEN_ANZAHL_SMALL)?3:((x<(BLASEN_ANZAHL_SMALL+BLASEN_ANZAHL_MEDIUM)?2:1))));
		myBlase[x].getGFX(imgGFXElements);
	}
	myEditor.getGFX(imgGFXElements);
	myEditor.setActive(false);


	// add all elements
	add(myGame);
	add(myConfig);
	add(myInstructions);
	add(highScore);
	add(bossScreen);
	add(myMenu);
	add(myEditor);
	add(myMsgBox);	// Nach allen anderen, dann werden die Msgs nicht weiter durchgereicht... so dass die MsgBox die restlichen Teile blockiert
	add(myMouse);

	setLayerState(COLUMNS_LAYER_MENU);
}

void ColumnsGameController::paintBackGround(Image& backBuffer)
{
		imgGFXElements.setSrcRect(Rect(0,480,640,960));
		imgGFXElements.show(backBuffer,0,0,IMAGE_BLTMODE_FAST);
		if (iAppState!=COLUMNS_APP_GAME )
		{
			imgGFXElements.setSrcRect(Rect(0,1104,352,146));
			imgGFXElements.show(backBuffer,148,0,IMAGE_BLTMODE_TRANS);
		}
		imgGFXElements.setSrcRect(Rect(0,0,backBuffer.getWidth(),backBuffer.getHeight()));
}

bool ColumnsGameController::paint(Image& backBuffer)
{
	bool isExit=false;

	if (iAppState!=COLUMNS_APP_BOSS)
		myMouse.paint(backBuffer);

	switch(iAppState)
	{
	case COLUMNS_APP_TITLE:
	{
		paintBackGround(backBuffer);
		if (myConfig.getSnowFlakes())
		{
			for (int x=0;x<BLASEN_ANZAHL;x++)
				myBlase[x].paint(backBuffer);
		}
		break;
	}
	case COLUMNS_APP_BOSS:
		bossScreen.paint(backBuffer);
		break;
	case COLUMNS_APP_GAME:
	{
		paintBackGround(backBuffer);
		if (myConfig.getSnowFlakes())
		{
			for (int x=0;x<BLASEN_ANZAHL;x++)
				myBlase[x].paint(backBuffer);
		}

		myGame.paint(backBuffer);
		if(myGame.getGameState()==COLUMNS_GAME_OUT)
		{
			if (highScore.getPlace(myGame.getPoints())>-1)
			{
				iAppState=COLUMNS_APP_HIGH_SCORE;
				myEditor.setActive(true);
				myEditor.reset();
			} else {
				myEditor.setActive(false);
				iAppState=COLUMNS_APP_TITLE;
			}
		}
		break;
	}
	case COLUMNS_APP_HIGH_SCORE:
	{
		paintBackGround(backBuffer);
		if (myConfig.getSnowFlakes())
		{
			for (int x=0;x<BLASEN_ANZAHL;x++)
				myBlase[x].paint(backBuffer);
		}
		myEditor.paint(backBuffer);
		break;
	}
	case COLUMNS_END:
		static unsigned int iEndCount=0;
		if (iEndCount==0)
			iEndCount=All2D_System::getTime();
		if (All2D_System::getTime()-iEndCount>1200)
			isExit=true;
		else
			paintBackGround(backBuffer);
		break;
	}

	if (iAppState!=COLUMNS_APP_BOSS)
	{

		switch(iLayerState)
		{
		case COLUMNS_LAYER_INSTRUCTIONS:
			imgBackground.show(backBuffer,60,150,520,300,IMAGE_BLTMODE_HALF);
			myInstructions.setCredit(false);
			myInstructions.paint(backBuffer);
			break;
		case COLUMNS_LAYER_CONFIG:
			imgBackground.show(backBuffer,60,150,520,310,IMAGE_BLTMODE_HALF);
			myConfig.paint(backBuffer);
			break;
		case COLUMNS_LAYER_CREDITS:
			imgBackground.show(backBuffer,60,150,520,300,IMAGE_BLTMODE_HALF);
			myInstructions.setCredit(true);
			myInstructions.paint(backBuffer);
			break;
		case COLUMNS_LAYER_HIGH_SCORE:
			//imgBackground.show(backBuffer,60,95,520,410,IMAGE_BLTMODE_HALF);
			highScore.paint(backBuffer);
			break;
		case COLUMNS_LAYER_MENU:
			if (myGame.getGameState()!=COLUMNS_GAME_OUT)	// Wenn im spiel, platz fuer Continue Button lassen..
				imgBackground.show(backBuffer,180,110,280,320,IMAGE_BLTMODE_HALF);
			else
				imgBackground.show(backBuffer,180,150,280,260,IMAGE_BLTMODE_HALF);
			myMenu.paint(backBuffer);// ShowMenu...
			break;
		case COLUMNS_LAYER_MSGBOX:
			myMsgBox.paint(backBuffer);
			break;
		default:
			break;
		}

	}
	return (!isExit);
}

bool ColumnsGameController::handleEvent(Event *evt)
{
	myConfig.transformEvent(evt);
	if (iAppState!=COLUMNS_APP_BOSS)
	{
		switch (evt->Type)
		{
		case MM_KEYDOWN:
		{
			char a=(char)evt->wData;
			switch (a) {
				case sf::Keyboard::BackSpace:
				case sf::Keyboard::Escape:
						All2D_System::sound->playSample(SND_ESCAPE);
						if (iLayerState==COLUMNS_LAYER_MENU)
							setLayerState(COLUMNS_NO_LAYER);
						else
							setLayerState(COLUMNS_LAYER_MENU);
						break;
				case sf::Keyboard::F12:
						All2D_System::sound->playSample(SND_QUIT);
						iAppState=COLUMNS_END;
						break;
					default:
						break;
				}
			} break;
			case MM_PREVIEW:	// sets the preview-State for the Stones in Game
			{
				myGame.setPreview(!myConfig.getPreview());
			}	break;
			case MM_JOKER:	// sets the preview-State for the Stones in Game
			{
				myGame.setJoker(!myConfig.getJoker());
			}	break;
			case MM_PAUSE:
				{	static bool blnPauseMode=true;
					if (iLayerState==COLUMNS_NO_LAYER)	// Nur wenn keine Layer da sind, kann man die Pause de/aktivieren
					{
						myGame.pause(blnPauseMode);
						blnPauseMode=!blnPauseMode;
					}
				} break;
			case MM_BOSS:
				All2D_System::sound->playSample(SND_TOGGLE);
						iAppOldState=iAppState;
						iAppState=COLUMNS_APP_BOSS;
						break;
			case MM_HELP:
				All2D_System::sound->playSample(SND_HELP);
					setLayerState(COLUMNS_LAYER_INSTRUCTIONS);
					break;
			case MM_START_REQUEST:
					if (myGame.getGameState()!=COLUMNS_GAME_OUT)
					{
						myMsgBox.setMessage("DO YOU WANT TO RESTART THE GAME?");
						myMsgBox.setYesEvent(Event(MM_START,0,0));
						setLayerState(COLUMNS_LAYER_MSGBOX);
					} else {
						MessageManager::handleEvent(new Event(MM_START,0,0));
					}
					break;
			case MM_START:
//					imgFrameBuffer.clear();
					myGame.reset();
					iAppState=COLUMNS_APP_GAME;
					All2D_System::sound->playSample(SND_STARTGAME);
					setLayerState(COLUMNS_NO_LAYER);
					break;
			case MM_HIGHSCORE:
					All2D_System::sound->playSample(SND_HIGHSCORE);
					setLayerState(COLUMNS_LAYER_HIGH_SCORE);
					break;
			case MM_CONFIG:
					All2D_System::sound->playSample(SND_CONFIG);
					setLayerState(COLUMNS_LAYER_CONFIG);
					break;
			case MM_CREDITS:
					All2D_System::sound->playSample(SND_CREDITS);
					setLayerState(COLUMNS_LAYER_CREDITS);
					break;
			case MM_QUIT:
					All2D_System::sound->playSample(SND_CREDITS);
					if (myGame.getGameState()!=COLUMNS_GAME_OUT)
					{
						myMsgBox.setMessage("ARE YOU SURE TO QUIT?");
						myMsgBox.setYesEvent(Event(MM_KEYDOWN,sf::Keyboard::F12,0));
						setLayerState(COLUMNS_LAYER_MSGBOX);
					} else {
						MessageManager::handleEvent(new Event(MM_KEYDOWN,sf::Keyboard::F12,0));
					}
					break;
			case MM_NAME_READY:
					All2D_System::sound->playSample(SND_NAMEREADY);
				myEditor.setActive(false);
				highScore.insert(myEditor.getName(),myGame.getPoints());
				iAppState=COLUMNS_APP_TITLE;
				break;
		default:
				break;
		}

		return xContainer::handleEvent(evt);
	} else
	{
		switch (evt->Type)	// When in Bosskey-Mode only handle Bosskey
		{
			case MM_BOSS:
			iAppState=iAppOldState;
			default:
				break;
		}
		return true;
	}
}

void ColumnsGameController::setLayerState(int iState)
{
	iLayerState=iState;
	if (iState==COLUMNS_LAYER_MENU)
	{
		myMenu.setActive(true);
		myMenu.setGameStatus(myGame.getGameState()!=COLUMNS_GAME_OUT);
	}else{
		myMenu.setActive(false);
	}

	if (iState==COLUMNS_LAYER_CONFIG)
		myConfig.setVisible(true);
	else
		myConfig.setVisible(false);

	if (iState==COLUMNS_LAYER_MSGBOX)
		myMsgBox.setVisible(true);	// Aktivate MsgBox
	else
		myMsgBox.setVisible(false);	// Deaktivate It


	if(iLayerState==COLUMNS_NO_LAYER)
	{
		myGame.pause(false);
		myMouse.setVisible(false);
	}
	else
	{
		myGame.pause(true);
		myMouse.setVisible(true);
	}
}
