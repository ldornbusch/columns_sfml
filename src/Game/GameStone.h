// GameStone.h: Schnittstelle f�r die Klasse GameStone.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GAMESTONE_H__883B7575_4175_437A_B424_8A0ADB15E063__INCLUDED_)
#define AFX_GAMESTONE_H__883B7575_4175_437A_B424_8A0ADB15E063__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "../All2DEngine/All2D/All2D_Sprites/UISprite.h"	// Hinzugef�gt von der Klassenansicht

class GameStone  :	public UISprite  
{
public:
	GameStone();
	virtual ~GameStone();

};

#endif // !defined(AFX_GAMESTONE_H__883B7575_4175_437A_B424_8A0ADB15E063__INCLUDED_)
