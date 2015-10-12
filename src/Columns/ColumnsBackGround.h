// olummsBackGround.h: Schnittstelle für die Klasse ColummsBackGround.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include "../All2DEngine/All2D/All2D_Sprites/UISprite.h"
#include "../All2DEngine/All2D/All2D_Base/Image.h"	// Hinzugefügt von der Klassenansicht
#include "../game/GameImageCloner.h"

class ColumnsBackGround :	public UISprite  ,
							public  GameImageCloner
{
public:
	void getGFX(Image& imgGFX);
	bool paint(Image& backBuffer);
	ColumnsBackGround();
	virtual ~ColumnsBackGround();

private:
	Image imgOffBuffer;
};
