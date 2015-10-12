#include "Columns/ColumnsGameController.h"
#include "All2DEngine/All2D/All2D_System.h"
#include "All2DEngine/All2D/All2D_HAL/All2DWin.h"

#define NAME    "All3DInterface"
#define TITLE   "DDraw to All3D Window/Screen"

LRESULT CALLBACK MainWndProc (HWND ,UINT,WPARAM ,LPARAM);
bool fullscreen = false;	// app is in fullscreen mode
All2DWin *myWin;					// Die Window-Klasse für DirectDraw Window

//
// initialize static system object
// ------------------------------------------------------
// get and set registry defaults if not present
//
bool initAll2D()
{
	All2D_System::fixedBits=16;
	All2D_System::fixedX=640;
	All2D_System::fixedY=480;
	All2D_System::WinTitle="WinterColumns by hexerei software creations (c) 2000-2003";

	myWin = new All2DWin();
	myWin->init();

	PicLoader::init();

	return true;
}

int main()
{
	int a=0;

	initAll2D();

	// constructor calls request loads
	ColumnsGameController Columns;

	/*
	 * load all buffered images and post progress
	 */

	int c=0;

	while (c>=0)
	{
		c=PicLoader::loadAllBitMaps();
	}

	/*
	 * init window and game controller and start main loop
	 */

	Columns.init();

	myWin->startApp(Columns);

	Columns.finish();			// drawableElement aufräumen

	delete myWin;

	return a;
}

