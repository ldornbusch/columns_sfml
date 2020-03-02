// ColumnsBlase.cpp: implementation of the ColumnsBlase class.
//
//////////////////////////////////////////////////////////////////////

#include <math.h>
#include <All2D/All2DEngine/All2D/All2D_System.h>
#include "ColumnsBlase.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ColumnsBlase::ColumnsBlase()
{
	iType=1;
	iStartTimer=0;
}

ColumnsBlase::~ColumnsBlase()
{

}
void ColumnsBlase::getGFX(Image& imgGFX)
{
	GameImageCloner::getGFX(imgGFX);
	initSize();
	imgElements.show(*this,0,0);
	setBlitMode(IMAGE_BLTMODE_ADD);
	setTarget(0,480+64);
	setVisible(true);
	setNewStart();
	setPosition(RECT_INVALID,rand()%480);
}

bool ColumnsBlase::paint(Image& backBuffer)
{
	if (!isVisible())
		check4NewRound();

	if (updatePosition()){
		setVisible(false);
	}

	static int alpha=0;

	int tmp=xCoordinate+iAmplitude*sin(double(++alpha)*dSwing);
	setPosition(tmp);
	return UIMovableSprite::paint(backBuffer);
}

void ColumnsBlase::check4NewRound()
{
	if (iStartTimer==0)
		iStartTimer=All2D_System::getTime()+(1000*(rand()%2));
	int a = (iStartTimer - All2D_System::getTime());
	if (a < 0)
	{
		iStartTimer=0;
		setPosition(00,-64);
		setTarget(00,480+64);
		setVisible(true);
		setNewStart();
	}
}

void ColumnsBlase::setType(int typ)
{
	iType=typ;
	initSize();
}

void ColumnsBlase::initSize()
{
	int size=64;
	switch (iType){
	case 1:
		size=64;
		imgElements.setSrcRect(Rect(112,416,size,size));
		break;
	case 2:
		size=32;
		imgElements.setSrcRect(Rect(176,416,size,size));
		break;
	case 3:
		size=16;
		imgElements.setSrcRect(Rect(176,448,size,size));
		break;
	default:
		break;
	}
	resize(size,size);
	setPosition(00,480,size,size);

}

void ColumnsBlase::setNewStart()
{
	setTime(25000-rand()%((iType==1)?9000 :(iType==2)?11000:16000));

	if (rand()%2==1)
		xCoordinate=(rand()%176)-32;
	else
		xCoordinate=(rand()%208)+448;

	dSwing=(double)((rand()%15)+15)/30000;
	iAmplitude=rand()%(8*(4-iType));

}
