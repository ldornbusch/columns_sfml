// ColumnsNameEditor.h: Schnittstelle für die Klasse ColumnsNameEditor.
// This Class makes a cool Effect for typing your Highscore Name
//////////////////////////////////////////////////////////////////////
#pragma once

#include <String>

#include "../ALL2DENGINE\ALL2D\ALL2D_SPRITES\UIElement.h"
#include "../game/GameImageCloner.h"
#include "../All2DEngine/All2D/All2D_Base/ImageText.h"	// Hinzugefügt von der Klassenansicht

class ColumnsNameEditor :
	public UIElement,
	public GameImageCloner
{
public:
	void setActive(bool flag);
	void reset();
	string getName();
	int iActualChar;
	bool handleEvent(Event* evt);
	bool paint(Image& backBuffer);
	void getGFX(Image& imgGFX);
	ColumnsNameEditor();
	virtual ~ColumnsNameEditor();
private:
	bool blnActive;
	string strName;
	float fRotSpeed;
	ImageText TextFont;
};
