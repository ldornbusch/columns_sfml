// ColumnsMorganeDefrag.h: interface for the ColumnsMorganeDefrag class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COLUMNSMORGANEDEFRAG_H__248FF8AB_16E3_43DE_86BF_F3848DD0BA0C__INCLUDED_)
#define AFX_COLUMNSMORGANEDEFRAG_H__248FF8AB_16E3_43DE_86BF_F3848DD0BA0C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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

#endif // !defined(AFX_COLUMNSMORGANEDEFRAG_H__248FF8AB_16E3_43DE_86BF_F3848DD0BA0C__INCLUDED_)
