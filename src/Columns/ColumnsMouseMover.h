// ColumnsMouseMover.h: Schnittstelle für die Klasse ColumnsMouseMover.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include "..\ALL2DENGINE\GUI\MouseMover.h"
#include "../game/GameImageCloner.h"

class ColumnsMouseMover :	public MouseMover  ,
							public  GameImageCloner
{
public:
	bool paint(Image& backBuffer);
	void setVisible(bool blnFlag);
	void getGFX(Image& imgGFX);
	ColumnsMouseMover();
	virtual ~ColumnsMouseMover();

private:
	bool blnVisible;
};
