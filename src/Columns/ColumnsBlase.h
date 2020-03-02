// ColumnsBlase.h: interface for the ColumnsBlase class.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include <All2D/All2DEngine/All2D/All2D_Sprites/UIMovableSprite.h>
#include "../Game/GameImageCloner.h"

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
