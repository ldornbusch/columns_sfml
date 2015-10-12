// GamePit.h: Schnittstelle für die Klasse GamePit.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GAMEPIT_H__B8BDDAC9_B815_4E53_9D91_F58B2D3C1253__INCLUDED_)
#define AFX_GAMEPIT_H__B8BDDAC9_B815_4E53_9D91_F58B2D3C1253__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../All2DEngine/All2D/All2D_Sprites/UIElement.h"
#include "../All2DEngine/All2D/All2D_Base/Image.h"	// Hinzugefügt von der Klassenansicht

class GamePit  :	public UIElement
{
public:
	virtual void setStone(int x, int y, int value)=0;
	virtual bool isFree(int x, int y)=0;
	virtual void emptyPit()=0;
	GamePit();
	virtual ~GamePit();

};

#endif // !defined(AFX_GAMEPIT_H__B8BDDAC9_B815_4E53_9D91_F58B2D3C1253__INCLUDED_)
