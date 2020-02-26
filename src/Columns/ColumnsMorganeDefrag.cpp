// ColumnsMorganeDefrag.cpp: implementation of the ColumnsMorganeDefrag class.
//
//////////////////////////////////////////////////////////////////////

#include "ColumnsMorganeDefrag.h"
#include "time.h"
static int cols[]={0x0000,0xf800,0xffc0,0x07c0,0x07ff,0x001f,0xf91f,0xffff,0xffff};

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ColumnsMorganeDefrag::ColumnsMorganeDefrag() : GameBossScreen()
{
	srand((unsigned int)time(NULL));
	//imgFrameBuffer.resize(640,480);
}

ColumnsMorganeDefrag::~ColumnsMorganeDefrag()
{
	//imgFrameBuffer.finish();
}

void ColumnsMorganeDefrag::getGFX(Image& imgGFX)
{
	GameImageCloner::getGFX(imgGFX);

	int yOffset,yLines;

	if (All2D_System::fullScreen) {
		iDefragAreaOffset=28;
		yOffset=395;
		yLines=38;
		imgElements.setSrcRect(Rect(0,960,640,56));
		imgElements.show(imgFrameBuffer,0,0,IMAGE_BLTMODE_FAST);
		imgElements.setSrcRect(Rect(0,1016,640,2));
		for (int i=0; i<170; ++i )
			imgElements.show(imgFrameBuffer,0,56+(i*2),IMAGE_BLTMODE_FAST);
	} else {
		iDefragAreaOffset=5;
		yOffset=389;
		yLines=40;
		imgElements.setSrcRect(Rect(0,981,640,35));
		imgElements.show(imgFrameBuffer,0,0,IMAGE_BLTMODE_FAST);
		imgElements.setSrcRect(Rect(0,1016,640,2));
		for (int i=0; i<180; ++i )
			imgElements.show(imgFrameBuffer,0,35+(i*2),IMAGE_BLTMODE_FAST);
	}
	imgElements.setSrcRect(Rect(0,1019,640,85));
	imgElements.show(imgFrameBuffer,0,yOffset,IMAGE_BLTMODE_FAST);


	// loop rows
	for ( int y=0; y<yLines; ++y ) {
		// loop columns
		for ( int x=0; x<88; ++x ) {

			int pix = y*88+x;		// box offset
			int pcol=8;				// default box color white
			// set color depending on current pixel
			if (pix>2101) pcol=4*((rand()%2)+1);
			else if (pix<=300) 	pcol=5; // defragmented block
			else if (pix>300&&pix<2101) pcol=8;

			// paint filled box
			iBlock[pix]=pcol;

			if (pcol!=8) {
				imgFrameBuffer.box(5+7*x,iDefragAreaOffset+10*y,
								   5,8,0,cols[pcol]);
								   //5+7*x+5,iDefragAreaOffset+10*y+8,0,cols[pcol]);
			}
		}
	}
}

bool ColumnsMorganeDefrag::paint(Image& backBuffer)
{
	static int j=416;
	static int iLastTic=0;
	static int d=1970;
	static int defragoffset=0;
	static int fragoffset=0;
	unsigned int tics=All2D_System::getTime();
  // erster farbwechsel
	if(tics-iLastTic>400&&tics-iLastTic<1000){
		for (int x=0;x<defragoffset;x++)		// oberer Block..
		{
			iBlock[j-defragoffset+x]=4;
		}
		for (int x=0;x<fragoffset;x++)		// unterer Block
		{
			iBlock[d-fragoffset+x]=(iBlock[d-fragoffset+x]!=8)?3:8;
		}

	}
	// zweiter farbwechsel
	if(tics-iLastTic>1000&&tics-iLastTic<1200){
		for (int x=0;x<defragoffset;x++)
		{
			iBlock[j-defragoffset+x]=5;
		}
		for (int x=0;x<fragoffset;x++)		// unterer Block
		{
			iBlock[d-fragoffset+x]=8;
		}

	}
	// letzter farbwechsel
	if (tics-iLastTic>1200){
		iLastTic=tics;
		int newBlocks=rand()%10+1;
		int x=0,counter=0;
		for (;counter<newBlocks;x++)
		{
			if (iBlock[x+d]!=8)
				counter++;

//			iBlock[x+d]=8;
		}

		fragoffset=x;
		defragoffset=counter;

		for (x=0;x<j;x++)
		{
			iBlock[x]=5;
		}
		for (x=0;x<defragoffset;x++)
		{
			iBlock[x+j]=1;
		}

		d+=fragoffset;
		j+=defragoffset;

	}

// Malen des Arrays
	for ( int y=3; y<35; ++y ) {// loop rows
		for ( int x=0; x<88; ++x ) {		// loop columns
		   	int pix = y*88+x;		//  box offset
			if (iBlock[pix]==8) {
				imgFrameBuffer.box(5+7*x  ,iDefragAreaOffset+10*y,
								   5,8,
								  // 5+7*x+5,iDefragAreaOffset+10*y+8,
								   cols[8],
								   cols[8]);
			}else {
				imgFrameBuffer.box(5+7*x  ,iDefragAreaOffset+10*y,
								   5,8,
								   //5+7*x+5,iDefragAreaOffset+10*y+8,
								   0,
								   cols[iBlock[pix]]);
			}
		}
	}
	imgFrameBuffer.show(backBuffer,0,0,IMAGE_BLTMODE_FAST);
	return true;
}



