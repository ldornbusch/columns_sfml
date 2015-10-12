// ColumnsBlase.h: interface for the ColumnsBlase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COLUMNSBLASE_H__8EE41C0C_B785_4F90_829E_CCF08DFDED67__INCLUDED_)
#define AFX_COLUMNSBLASE_H__8EE41C0C_B785_4F90_829E_CCF08DFDED67__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\GAME\GameImageCloner.h"
#include "..\ALL2DENGINE\ALL2D\ALL2D_SPRITES\UIMovableSprite.h"

class ColumnsBlase : 
	public UIMovableSprite, 
	public GameImageCloner  
{
public:
	void setType(int typ);
	int iType;
	void check4NewRound();
	void getGFX(Image& imgGFX);
	bool paint(Image& backBuffer);
	ColumnsBlase();
	virtual ~ColumnsBlase();

private:
	int iStartTimer;
	int iAmplitude;
	double dSwing;
	void setNewStart();
	void initSize();
	int xCoordinate;
};
#endif 

