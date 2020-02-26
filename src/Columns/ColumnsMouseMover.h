// ColumnsMouseMover.h: Schnittstelle für die Klasse ColumnsMouseMover.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include "../All2DEngine/Gui/MouseMover.h"
#include "../Game/GameImageCloner.h"

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
