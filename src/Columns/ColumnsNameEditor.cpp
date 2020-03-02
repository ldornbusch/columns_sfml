// olumnsNameEditor.cpp: Implementierung der Klasse ColumnsNameEditor.
//
//////////////////////////////////////////////////////////////////////

#include <math.h>
#include <All2D/All2DEngine/All2D/All2D_Events/MessageManager.h>
#include "ColumnsNameEditor.h"
#include "ColumnsConstants.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

ColumnsNameEditor::ColumnsNameEditor()
{
	reset();
}

ColumnsNameEditor::~ColumnsNameEditor()
{

}

void ColumnsNameEditor::getGFX(Image& imgGFX)
{
	GameImageCloner::getGFX(imgGFX);

	TextFont.cloneImage(imgGFX,Rect(224,208,80,64));
	TextFont.FontInit(16,16,10,"ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789:[]_@.-+*$%§!");
}

bool ColumnsNameEditor::paint(Image& backBuffer)
{
	if (blnActive)
	{
		const char* txt="ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789:[]_@.-+*$%§!";
//		backBuffer->clear();

		static float blob=0;	// für das blubbern der Buchstaben...
		blob+=0.07f;

		int len=strlen(txt);
		float rot=3.1415/2 - iActualChar*(2*3.1415/len);	// Ausgewählter Buchstabe ist GROSS

		int factor=TextFont.getFontWidth();

		for (int x=0; x<len; x++)
		{
			int xc=cos(2 * 3.1415 / len * x+rot)*310+312;
			int yc=sin(2 * 3.1415 / len * x+rot)*130+240;

			float scale=sin(2 * 3.1415 / len * x+rot)*0.75 +1.25;  // Perspektive

			float blobber=(sin(2 * 3.1415 / 12 * x+blob)*0.30+0.8);	// blubbern

			if (x!=iActualChar)
				TextFont.PrintAt(backBuffer, xc,yc-(scale*factor*blobber/2),txt+(len-1-x),IMAGE_BLTMODE_HALF,2,scale*factor, scale*factor*blobber);
			else
				TextFont.PrintAt(backBuffer, xc,yc-(scale*factor),txt+(len-1-x),IMAGE_BLTMODE_TRANS,2,2*scale*factor, 2*scale*factor);
		}
		float blobber=(sin(2 * 3.1415 / 12 * blob)*0.70+1.3)*factor;	// blubbern
		TextFont.PrintCenter(backBuffer, 210-blobber/2,strName.c_str(),IMAGE_BLTMODE_TRANS,-1,blobber, blobber);
	}
	return true;
}

bool ColumnsNameEditor::handleEvent(Event *evt)
{
	if (blnActive)
	{
		const char* txt="ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789:[]_@.-+*$%§!";
		int len=strlen(txt);
		switch(evt->Type){
			case MM_RIGHT:
				fRotSpeed=2 * 3.1415f / len;
				iActualChar--;
				break;
			case MM_LEFT:
				fRotSpeed=-2 * 3.1415f / len;
				iActualChar++;
				break;
			case MM_DROP:
				if (strName.length()<12)
				{
					switch (iActualChar)
					{
					case 0:		// End Button pressed
						MessageManager::handleEvent(new Event(MM_NAME_READY,0,0));
						break;
					case 1:		// Rubber pressed
						strName=strName.substr(0,strName.length()-1);
						break;
					default:
						strName+=txt[len-1-iActualChar];	// Normal Char
					}
				}else {
					strName=strName.substr(0,11);
				}

				break;
			default:
				fRotSpeed*=0.0;
		}
		if (iActualChar<0)
			iActualChar+=len;
		if (iActualChar>=len)
			iActualChar-=len;
	}
	return true;
}

string ColumnsNameEditor::getName()
{
	return strName;
}

void ColumnsNameEditor::reset()
{
	fRotSpeed=0.0f;
	iActualChar=48;
	strName="";
}

void ColumnsNameEditor::setActive(bool flag)
{
	blnActive=flag;
}
