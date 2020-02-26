// ColumnsConfig.h: Schnittstelle für die Klasse ColumnsConfig.
//
//////////////////////////////////////////////////////////////////////
#pragma once


#include "../All2DEngine/All2D/All2D_Base/Image.h"	// Added by ClassView
#include "../All2DEngine/All2D/All2D_Base/ImageText.h"	// Hinzugefügt von der Klassenansicht
#include "../All2DEngine/All2D/All2D_Base/xContainer.h"
#include "../Game/GameImageCloner.h"
#include "../Game/KeyboardNavigator.h"	// Added by ClassView
#include "../All2DEngine/Gui/UIButton.h"	// Hinzugefügt von der Klassenansicht
#include "../All2DEngine/Gui/UIKeyRecorder.h"	// Hinzugefügt von der Klassenansicht

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
