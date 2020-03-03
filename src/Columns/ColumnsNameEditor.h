// ColumnsNameEditor.h: Schnittstelle f�r die Klasse ColumnsNameEditor.
// This Class makes a cool Effect for typing your Highscore Name
//////////////////////////////////////////////////////////////////////
#pragma once

#include <string>

#include <All2D/All2DEngine/All2D/All2D_Sprites/UIElement.h>
#include <All2D/All2DEngine/All2D/All2D_Base/ImageText.h>
#include "../Game/GameImageCloner.h"

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
