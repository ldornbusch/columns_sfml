// ColumnsMouseMover.h: Schnittstelle für die Klasse ColumnsMouseMover.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COLUMNSMOUSEMOVER_H__E7E361AC_8D0F_46C9_934B_E95D8FEE7077__INCLUDED_)
#define AFX_COLUMNSMOUSEMOVER_H__E7E361AC_8D0F_46C9_934B_E95D8FEE7077__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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

#endif // !defined(AFX_COLUMNSMOUSEMOVER_H__E7E361AC_8D0F_46C9_934B_E95D8FEE7077__INCLUDED_)
