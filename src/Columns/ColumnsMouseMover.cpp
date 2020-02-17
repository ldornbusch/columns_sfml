// ColumnsMouseMover.cpp: Implementierung der Klasse ColumnsMouseMover.
//
//////////////////////////////////////////////////////////////////////

#include "ColumnsMouseMover.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

ColumnsMouseMover::ColumnsMouseMover()
{

}

ColumnsMouseMover::~ColumnsMouseMover()
{

}

void ColumnsMouseMover::getGFX(Image& imgGFX)
{
	GameImageCloner::getGFX(imgGFX);
	MouseMover::init();
	Image temp;
	temp.cloneImage(imgElements,Rect(0,335,104,140));
	MouseMover::cloneImage(temp);
	MouseMover::setOffset(89,5);
	//MouseMover::setBlitMode(IMAGE_BLTMODE_TRANS);
	MouseMover::setBlitMode(IMAGE_BLTMODE_ADD);
	MouseMover::setPriority(10);
}

void ColumnsMouseMover::setVisible(bool blnFlag)
{
	blnVisible=blnFlag;
}

bool ColumnsMouseMover::paint(Image& backBuffer)
{
	bool retVal=true;
	if (blnVisible)
		retVal=MouseMover::paint(backBuffer);
	return retVal;
}
