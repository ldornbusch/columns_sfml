// ColumnsMorganeDefrag.h: interface for the ColumnsMorganeDefrag class.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include "..\GAME\GameBossScreen.h"
#include "..\ALL2DENGINE\ALL2D\All2D_System.h"

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
