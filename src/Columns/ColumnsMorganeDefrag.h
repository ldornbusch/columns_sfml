// ColumnsMorganeDefrag.h: interface for the ColumnsMorganeDefrag class.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include "../Game/GameBossScreen.h"
#include "../All2DEngine/All2D/All2D_System.h"

class ColumnsMorganeDefrag : public GameBossScreen
{
public:
	void change();
	void changeCol();
	void getGFX(Image& imgGFX);
	bool paint(Image& backBuffer);
	ColumnsMorganeDefrag();
	virtual ~ColumnsMorganeDefrag();
private:
	int iDefragAreaOffset;
	int iBlock[3520];
};
