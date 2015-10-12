// olummsBackGround.h: Schnittstelle für die Klasse ColummsBackGround.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OLUMMSBACKGROUND_H__B05D2183_83B7_4434_B011_C2C0E67F53C9__INCLUDED_)
#define AFX_OLUMMSBACKGROUND_H__B05D2183_83B7_4434_B011_C2C0E67F53C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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

#endif // !defined(AFX_OLUMMSBACKGROUND_H__B05D2183_83B7_4434_B011_C2C0E67F53C9__INCLUDED_)
