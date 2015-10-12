// GameHighScore.h: Schnittstelle f�r die Klasse GameHighScore.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include "../All2DEngine/All2D/All2D_Sprites/UIElement.h"
#include "GameImageCloner.h"

#include <String>
#include "../All2DEngine/All2D/All2D_Base/ImageText.h"	// Hinzugef�gt von der Klassenansicht

using namespace std;

#define HIGH_SCORE_ENTRIES		10

class GameHighScore :
	public UIElement,
	public GameImageCloner
{
public:
	void insert(string strName, int iPts);
	int getPlace(int iPts);
	void getGFX(Image& imgGFX);
	void load();
	void save();
	bool paint(Image& backBuffer);
	GameHighScore();
	virtual ~GameHighScore();
private:
	ImageText TextFont;
	string strNames[HIGH_SCORE_ENTRIES];
	int		iPoints[HIGH_SCORE_ENTRIES];
};
