// ColumnsConfig.h: Schnittstelle f�r die Klasse ColumnsConfig.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include "..\GAME\KeyboardNavigator.h"	// Added by ClassView
#include "..\ALL2DENGINE\GUI\UIKeyRecorder.h"	// Hinzugef�gt von der Klassenansicht

#include "../All2DEngine/All2D/All2D_Base/ImageText.h"	// Hinzugef�gt von der Klassenansicht
#include "../ALL2DENGINE/ALL2D/ALL2D_BASE/xContainer.h"
#include "../game/GameImageCloner.h"
#include "..\ALL2DENGINE\GUI\UIButton.h"	// Hinzugef�gt von der Klassenansicht
#include "..\ALL2DENGINE\ALL2D\ALL2D_BASE\Image.h"	// Added by ClassView

class ColumnsConfig :
	public xContainer,
	public GameImageCloner
{
public:
	bool getSnowFlakes();
	virtual void init();
	void setVisible(bool blnFlag);
	virtual bool transformEvent(Event* evt);
	bool handleEvent(Event*evt);
	void getGFX(Image& imgGFX);
	bool paint(Image& backBuffer);
	ColumnsConfig();
	virtual ~ColumnsConfig();
	bool getPreview();
	bool getJoker();

private:
	bool blnInRecordMode;
	void menuSelect();
	KeyboardNavigator KbdNavigator;
	bool blnVisible;
	void save();
	void reset();
	void load();
	UIKeyRecorder dropKey;
	UIKeyRecorder upKey;
	UIKeyRecorder downKey;
	UIKeyRecorder leftKey;
	UIKeyRecorder rightKey;
	UIKeyRecorder bossKey;
	UIKeyRecorder pauseKey;
	UIButton btnFullScreen;
	UIButton btnShowFlakes;
	UIButton btnPreview;
	UIButton btnJoker;
	ImageText TextFont;
	bool blnPreview;
	bool blnJoker;
	bool blnShowFlakes;
	bool blnFullscreen;
};