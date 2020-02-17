// ColumnsConfig.cpp: Implementierung der Klasse ColumnsConfig.
//
//////////////////////////////////////////////////////////////////////


#include "ColumnsConfig.h"
#include "ColumnsConstants.h"
#include "../All2Dengine/All2D/All2D_Events/MessageManager.h"
#include "../All2Dengine/All2D/All2D_System.h"

#define COL1_XOFF 114
#define COL2_XOFF 310
#define ROW_YOFF	190
#define ROW_HIGH	22
#define ROW(x)		ROW_YOFF+x*ROW_HIGH

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////


ColumnsConfig::ColumnsConfig():xContainer("Configs")
{
	load();

	KbdNavigator.setMaxEntry(11);
	KbdNavigator.setMinEntry(1);

	btnPreview.setPosition(COL1_XOFF,ROW(8),328,ROW_HIGH-1);
	btnPreview.setSendFlag(MM_PREVIEW);
	add(btnPreview);

	btnJoker.setPosition(COL1_XOFF,ROW(9),328,ROW_HIGH-1);
	btnJoker.setSendFlag(MM_JOKER);
	add(btnJoker);

	btnShowFlakes.setPosition(COL1_XOFF,ROW(10),328,ROW_HIGH-1);
	btnShowFlakes.setSendFlag(MM_SNOW);
	add(btnShowFlakes);

	btnFullScreen.setPosition(COL1_XOFF,ROW(11),328,ROW_HIGH-1);
	btnFullScreen.setSendFlag(MM_FULLSCREEN);
	add(btnFullScreen);


	leftKey.setPosition(Rect(COL1_XOFF,ROW(0),520,ROW_HIGH-1));
	add(leftKey);

	rightKey.setPosition(Rect(COL1_XOFF,ROW(1),520,ROW_HIGH-1));
	add(rightKey);

	upKey.setPosition(Rect(COL1_XOFF,ROW(2),520,ROW_HIGH-1));
	add(upKey);

	downKey.setPosition(Rect(COL1_XOFF,ROW(3),520,ROW_HIGH-1));
	add(downKey);

	dropKey.setPosition(Rect(COL1_XOFF,ROW(4),520,ROW_HIGH-1));
	add(dropKey);

	bossKey.setPosition(Rect(COL1_XOFF,ROW(5),520,ROW_HIGH-1));
	add(bossKey);

	pauseKey.setPosition(Rect(COL1_XOFF,ROW(6),520,ROW_HIGH-1));
	add(pauseKey);

	blnVisible=false;
	blnInRecordMode=false;
}

ColumnsConfig::~ColumnsConfig()
{
	save();
}


void ColumnsConfig::getGFX(Image& imgGFX)
{
	GameImageCloner::getGFX(imgGFX);

	TextFont.cloneImage(imgGFX,Rect(224,208,80,64));
	TextFont.FontInit(16,16,10,"ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789:[]_@.-+*$%§!");

	MessageManager::handleEvent(new Event(MM_SETFULLSCREEN,(int)blnFullscreen,0));
	if (!blnPreview)
		MessageManager::handleEvent(new Event(MM_PREVIEW,0,0));
	if (!blnJoker)
		MessageManager::handleEvent(new Event(MM_JOKER,0,0));
	if (!blnShowFlakes)
		MessageManager::handleEvent(new Event(MM_SNOW,0,0));
}


/*----------------------------------- dbug --- 29.08.2002 00:59:34

	added macros to shortcut offset handling in text table printing

 --------------------------------------------------------------*/

#define SHOW_ROW(x,y,t,h)		TextFont.PrintAt(backBuffer,x,ROW(y),t,h)

bool ColumnsConfig::paint(Image& backBuffer)
{
	int normal=IMAGE_BLTMODE_HALF;
	int high=IMAGE_BLTMODE_ADD;
	int hover=IMAGE_BLTMODE_TRANS;
	int ihigh=KbdNavigator.getActualEntry();

	blnFullscreen=All2D_System::fullScreen;

	TextFont.PrintCenter(backBuffer, 160,"CONFIGURATIONS",normal);


	SHOW_ROW(COL1_XOFF,0,"MOVE LEFT  :",leftKey.getActive()?high:(ihigh==1)?hover:normal);
	SHOW_ROW(COL2_XOFF,0,leftKey.KeyName.c_str(),(ihigh==1)?hover:normal);

	SHOW_ROW(COL1_XOFF,1,"MOVE RIGHT :",rightKey.getActive()?high:(ihigh==2)?hover:normal);
	SHOW_ROW(COL2_XOFF,1,rightKey.KeyName.c_str(),(ihigh==2)?hover:normal);

	SHOW_ROW(COL1_XOFF,2,"ROTATE UP  :",upKey.getActive()?high:(ihigh==3)?hover:normal);
	SHOW_ROW(COL2_XOFF,2,upKey.KeyName.c_str(),(ihigh==3)?hover:normal);

	SHOW_ROW(COL1_XOFF,3,"ROTATE DOWN:",downKey.getActive()?high:(ihigh==4)?hover:normal);
	SHOW_ROW(COL2_XOFF,3,downKey.KeyName.c_str(),(ihigh==4)?hover:normal);

	SHOW_ROW(COL1_XOFF,4,"DROP STONE :",dropKey.getActive()?high:(ihigh==5)?hover:normal);
	SHOW_ROW(COL2_XOFF,4,dropKey.KeyName.c_str(),(ihigh==5)?hover:normal);

	SHOW_ROW(COL1_XOFF,5,"BOSSKEY    :",bossKey.getActive()?high:(ihigh==6)?hover:normal);
	SHOW_ROW(COL2_XOFF,5,bossKey.KeyName.c_str(),(ihigh==6)?hover:normal);

	SHOW_ROW(COL1_XOFF,6,"PAUSEKEY   :",pauseKey.getActive()?high:(ihigh==7)?hover:normal);
	SHOW_ROW(COL2_XOFF,6,pauseKey.KeyName.c_str(),(ihigh==7)?hover:normal);


	SHOW_ROW(COL1_XOFF,8,"PREVIEW    :",(ihigh==8)?hover:normal);
	SHOW_ROW(COL2_XOFF,8,blnPreview?" ON":" OFF",(ihigh==8)?hover:normal);

	SHOW_ROW(COL1_XOFF,9,"JOKER      :",(ihigh==9)?hover:normal);
	SHOW_ROW(COL2_XOFF,9,blnJoker?" ON":" OFF",(ihigh==9)?hover:normal);

	SHOW_ROW(COL1_XOFF,10,"SNOWFLAKES :",(ihigh==10)?hover:normal);
	SHOW_ROW(COL2_XOFF,10,blnShowFlakes?" ON":" OFF",(ihigh==10)?hover:normal);

	SHOW_ROW(COL1_XOFF,11,"FULLSCREEN :",(ihigh==11)?hover:normal);
	SHOW_ROW(COL2_XOFF,11,blnFullscreen?" ON":" OFF",(ihigh==11)?hover:normal);

	return xContainer::paint(backBuffer);
}

bool ColumnsConfig::handleEvent(Event *evt)
{
	if (blnVisible){
		switch(evt->Type)
		{
			case MM_CHANGE_FULLSCREEN:
				blnFullscreen=evt->wData;
				break;
			case MM_FULLSCREEN:
				blnFullscreen=!blnFullscreen;
				MessageManager::handleEvent(new Event(MM_SETFULLSCREEN,(int)blnFullscreen,0));
				break;
			case MM_SNOW:
				blnShowFlakes=!blnShowFlakes;
				break;
			case MM_PREVIEW:
				blnPreview=!blnPreview;
				break;
			case MM_JOKER:
				blnJoker=!blnJoker;
				break;
			case MM_MOUSEMOVE:	// ein bisschen frickelei fuer den HoverFX.. da hier keine richtigen Buttons benutzt wurden..
				{
					Rect UIArea=Rect(60,ROW_YOFF,540,ROW_YOFF+260);
					Point actCoords=All2D_System::extractMouseCoords(evt);
					if (UIArea.isInside(actCoords.x,actCoords.y))
					{
						int i = 0;

						if ( actCoords.y < ROW(7))
							i = ((actCoords.y-ROW_YOFF)/ROW_HIGH) + 1;
						else if ( actCoords.y > ROW(8) )
							i = ((actCoords.y-ROW_YOFF)/ROW_HIGH);
						//	i = ((actCoords.y - ROW(8))/ROW_HIGH) + 7;

						//int i = ((actCoords.y-UIArea.y1)/ROW_HIGH) - 1;
						//int i = ((actCoords.y-ROW_YOFF)/ROW_HIGH) + 1;

						//if ( i<=12 && (i<8||i>8) )
						//if ( i > 9 ) i++;
							KbdNavigator.setActualEntry(i);
						//else
						//	KbdNavigator.setActualEntry(0);

					}else{
						KbdNavigator.setActualEntry(0);	// No one highlighted..
					}
					break;
				}
			case MM_KEYRECORDERACTIVE:
				blnInRecordMode=evt->wData;
				break;
			case MM_KEYDOWN:
				{
				char a=(char)evt->wData;
				switch (a) {
					case VK_RETURN:
						menuSelect();
						evt->Type=MM_NO_EVENT;// Damit das Keydown-Event nicht von jemand anderem nochmals behandelt wird..(direkt aufgenommen z.B)
							break;
					default:
						break;
					}
				}break;
		}

		if (evt->Type==MM_DROP)
			menuSelect();

		if (!blnInRecordMode)
			KbdNavigator.handleEvent(evt);
		return xContainer::handleEvent(evt);
	}
	else
		return true;
}

void ColumnsConfig::menuSelect()
{
	switch (KbdNavigator.getActualEntry())
	{
	case 1:
		leftKey.fire();
		break;
	case 2:
		rightKey.fire();
		break;
	case 3:
		upKey.fire();
		break;
	case 4:
		downKey.fire();
		break;
	case 5:
		dropKey.fire();
		break;
	case 6:
		bossKey.fire();
		break;
	case 7:
		pauseKey.fire();
		break;
	case 8:
		btnPreview.fire();
		break;
	case 9:
		btnJoker.fire();
		break;
	case 10:
		btnShowFlakes.fire();
		break;
	case 11:
		btnFullScreen.fire();
		break;
	}
}
//sets up Basic configurations
void ColumnsConfig::reset()
{
	blnFullscreen=true;
	blnPreview=true;
	blnJoker=true;
	blnShowFlakes=true;

	Event tmp(MM_KEYDOWN,sf::Keyboard::Up,0);
	upKey.setRecordedKey(&tmp);

	tmp=Event(MM_KEYDOWN,sf::Keyboard::Down,0);
	downKey.setRecordedKey(&tmp);

	tmp=Event(MM_KEYDOWN,sf::Keyboard::Left,0);
	leftKey.setRecordedKey(&tmp);

	tmp=Event(MM_KEYDOWN,sf::Keyboard::Right,0);
	rightKey.setRecordedKey(&tmp);

	tmp=Event(MM_KEYDOWN,sf::Keyboard::Space,0);
	dropKey.setRecordedKey(&tmp);

	tmp=Event(MM_KEYDOWN,sf::Keyboard::F7,0);
	bossKey.setRecordedKey(&tmp);

	tmp=Event(MM_KEYDOWN,sf::Keyboard::P,0);
	pauseKey.setRecordedKey(&tmp);
}

// loads the configParameters and sets it
void ColumnsConfig::load()
{
	reset();
	FILE* fConf=fopen("data\\set.bin","rb");
	if (fConf){
		int i;
		fscanf(fConf,"%d\n",&i);
		blnFullscreen=(i==1)?true:false;

		fscanf(fConf,"%d\n",&i);
		blnPreview=(i==1)?true:false;

		fscanf(fConf,"%d\n",&i);
		blnJoker=(i==1)?true:false;

		fscanf(fConf,"%d\n",&i);
		blnShowFlakes=(i==1)?true:false;

		Event tmp(0,0,0);
		int t,w;
		fscanf(fConf,"%d %d\n", &t, &w);
		tmp=Event(t,w,0);
		leftKey.setRecordedKey(&tmp);

		fscanf(fConf,"%d %d\n", &t, &w);
		tmp=Event(t,w,0);
		rightKey.setRecordedKey(&tmp);

		fscanf(fConf,"%d %d\n", &t, &w);
		tmp=Event(t,w,0);
		upKey.setRecordedKey(&tmp);

		fscanf(fConf,"%d %d\n", &t, &w);
		tmp=Event(t,w,0);
		downKey.setRecordedKey(&tmp);

		fscanf(fConf,"%d %d\n", &t, &w);
		tmp=Event(t,w,0);
		dropKey.setRecordedKey(&tmp);

		fscanf(fConf,"%d %d\n", &t, &w);
		tmp=Event(t,w,0);
		bossKey.setRecordedKey(&tmp);

		fscanf(fConf,"%d %d\n", &t, &w);
		tmp=Event(t,w,0);
		pauseKey.setRecordedKey(&tmp);

		fclose(fConf);
	}
}

// saves the ConfigParameters
void ColumnsConfig::save()
{
	FILE* fConf=fopen("data\\set.bin","wb");
	fprintf(fConf,"%d\n",blnFullscreen?1:0);
	fprintf(fConf,"%d\n",blnPreview?1:0);
	fprintf(fConf,"%d\n",blnJoker?1:0);
	fprintf(fConf,"%d\n",blnShowFlakes?1:0);

	fprintf(fConf,"%d %d\n",leftKey.getRecordedKey()->Type,
													leftKey.getRecordedKey()->wData);
	fprintf(fConf,"%d %d\n",rightKey.getRecordedKey()->Type,
													rightKey.getRecordedKey()->wData);
	fprintf(fConf,"%d %d\n",upKey.getRecordedKey()->Type,
													upKey.getRecordedKey()->wData);
	fprintf(fConf,"%d %d\n",downKey.getRecordedKey()->Type,
													downKey.getRecordedKey()->wData);
	fprintf(fConf,"%d %d\n",dropKey.getRecordedKey()->Type,
													dropKey.getRecordedKey()->wData);
	fprintf(fConf,"%d %d\n",bossKey.getRecordedKey()->Type,
													bossKey.getRecordedKey()->wData);
	fprintf(fConf,"%d %d\n",pauseKey.getRecordedKey()->Type,
													pauseKey.getRecordedKey()->wData);
	fclose(fConf);
}

// This method checks, if any GameKey is meant by
// this message and transforms it via the Mapping
// returns:
// If Class is in RecordMode(any KeyRecorder waits on its signal, the event will not be transformed,
// instead each KeyRecorder checks, if it owns this event and is not active, to delete the stored event,
// so no event can be associated on more than 1 keyrecorder
// (true) if a transform occurs
// (false) if Event is unchanged
bool ColumnsConfig::transformEvent(Event *evt)
{
	unsigned int oldType=evt->Type;

	if (!blnInRecordMode)
	{
		if (leftKey.isPressedKey(evt))
			evt->Type=MM_LEFT;
		if (rightKey.isPressedKey(evt))
			evt->Type=MM_RIGHT;
		if (upKey.isPressedKey(evt))
			evt->Type=MM_UP;
		if (downKey.isPressedKey(evt))
			evt->Type=MM_DOWN;
		if (dropKey.isPressedKey(evt))
			evt->Type=MM_DROP;
		if (bossKey.isPressedKey(evt))
			evt->Type=MM_BOSS;
		if (pauseKey.isPressedKey(evt))
			evt->Type=MM_PAUSE;
	}else{	// Falls der Event schon einer (anderen) Taste zugewiesen war wird er auf der alten taste gelöscht/kein transform, damit die neue Taste das Event aufnehmen kann
		// Die Tasten CURSOR, und RETURN funktionieren *immer* auf Standard weise
		// können nicht anderen Events zugewiesen werden..
		if (evt->Type==MM_KEYDOWN)
		{
			if (evt->wData==sf::Keyboard::Return && !dropKey.getActive())
				evt->Type = MM_NO_EVENT;
			if (evt->wData==sf::Keyboard::Left && !leftKey.getActive())
				evt->Type = MM_NO_EVENT;
			if (evt->wData==sf::Keyboard::Right && !rightKey.getActive())
				evt->Type = MM_NO_EVENT;
			if (evt->wData==sf::Keyboard::Up && !upKey.getActive())
				evt->Type = MM_NO_EVENT;
			if (evt->wData==sf::Keyboard::Down && !downKey.getActive())
				evt->Type = MM_NO_EVENT;
		}
		if (!leftKey.getActive() && leftKey.isPressedKey(evt))
			leftKey.deleteKey();
		if (!rightKey.getActive() && rightKey.isPressedKey(evt))
			rightKey.deleteKey();
		if (!upKey.getActive() && upKey.isPressedKey(evt))
			upKey.deleteKey();
		if (!downKey.getActive() && downKey.isPressedKey(evt))
			downKey.deleteKey();
		if (!dropKey.getActive() && dropKey.isPressedKey(evt))
			dropKey.deleteKey();
		if (!bossKey.getActive() && bossKey.isPressedKey(evt))
			bossKey.deleteKey();
		if (!pauseKey.getActive() && pauseKey.isPressedKey(evt))
			pauseKey.deleteKey();
	}

	return (oldType!=evt->Type);
}

void ColumnsConfig::setVisible(bool blnFlag)
{
	init();
	blnVisible=blnFlag;
}

bool ColumnsConfig::getPreview()
{
	return blnPreview;
}

bool ColumnsConfig::getJoker()
{
	return blnJoker;
}
bool ColumnsConfig::getSnowFlakes()
{
	return blnShowFlakes;
}

void ColumnsConfig::init()	// jedesmal wenn der Dialog angezeigt oder verlassen werden soll, muessen alle RecKey inaktiviert werden(wg. TransformEvent())
{
	blnInRecordMode=false;
	leftKey.setActive(false);
	rightKey.setActive(false);
	upKey.setActive(false);
	downKey.setActive(false);
	dropKey.setActive(false);
	bossKey.setActive(false);
	pauseKey.setActive(false);
	KbdNavigator.setActualEntry(0);// kein eintrag vorselectiert..
}

