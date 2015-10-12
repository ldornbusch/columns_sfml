// olummsBackGround.cpp: Implementierung der Klasse ColummsBackGround.
//
//////////////////////////////////////////////////////////////////////

#include "ColumnsBackGround.h"
#include <math.h>
//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

ColumnsBackGround::ColumnsBackGround()
{

}

ColumnsBackGround::~ColumnsBackGround()
{
	imgOffBuffer.finish();
}

void ColumnsBackGround::getGFX(Image& imgGFX)
{
	GameImageCloner::getGFX(imgGFX);
	imgOffBuffer.resize(224,448*2);
	imgOffBuffer.clear(0x0f0f0f);
//	imgElements.setSrcRect(397,15,224,448);
//	imgElements.show(&imgOffBuffer,0,0,IMAGE_BLTMODE_FAST);
//	imgElements.show(&imgOffBuffer,0,448,IMAGE_BLTMODE_FAST);
}

bool ColumnsBackGround::paint(Image& backBuffer)
{
	static int  alpha=0;
//	alpha++;
	alpha=alpha%(448);

	imgOffBuffer.setSrcRect(Rect(0,alpha,224,448));
	imgOffBuffer.show(backBuffer,208,16, IMAGE_BLTMODE_HALF);
	return true;
}	
