/*
    Copyright (C) 2001, 2002 Stephane Magnenat & Luc-Olivier de Charriere
    for any question or comment contact us at nct@ysagoon.com

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*/

#ifndef __GAME_GUI_H
#define __GAME_GUI_H

#include "Header.h"
#include "Order.h"
#include "Game.h"
#include "GameGUIDialog.h"
#include <queue>

#define MAX_UNIT_WORKING 20
#define MAX_EXPLO_FLAG_RANGE 20
#define MAX_WAR_FLAG_RANGE 8
#define MAX_RATIO_RANGE 16

class GameGUI
{
public:
	GameGUI();
	~GameGUI();
	// this handle mouse, keyboard and window resize inputs
	void step(void);
	// get order from gui, return NullOrder if 
	Order *getOrder(void);
	int getViewportX() { return viewportX; }
	int getViewportY() { return viewportY; }
	
	void draw(void);
	void drawAll(int team);
	void executeOrder(Order *order);

	void load(SDL_RWops *stream);
	void save(SDL_RWops *stream);

	void processEvent(SDL_Event *event);
	bool processGameMenu(SDL_Event *event);
	void handleRightClick(void);
	void handleKey(SDL_keysym keySym, bool pressed);
	void handleMouseMotion(int mx, int my, int button);
	void handleMapClick(int mx, int my, int button);
	void handleMenuClick(int mx, int my, int button);

public:
	Game game;
	bool isRunning;
	//bool showExtendedInformation;
	bool drawHealthFoodBar, drawPathLines;
	int localPlayer, localTeam;
	int viewportX, viewportY;

private:
	void viewportFromMxMY(int mx, int my);
	void drawScrollBox(int x, int y, int value, int valueLocal, int act, int max);
	void drawButton(int x, int y, const char *caption);
	void drawTextCenter(int x, int y, const char *caption, int i=-1);
	void checkValidSelection(void);
	void statStep(void);
	void iterateSelection(void);
	void centerViewportOnSelection(void);
	void drawOverlayInfos(void);
	void drawInGameMenu(void);
	bool hasLocalTeamWon(void);

private:
	enum DisplayMode
	{
		BUILDING_AND_FLAG,
		BUILDING_SELECTION_VIEW,
		UNIT_SELECTION_VIEW,
		STAT_VIEW,
	};

	enum StatMode
	{
		STAT_TEXT=0,
		STAT_GRAPH=1,
		NB_STAT_MODE=2
	};

	DisplayMode displayMode;
	Building *selBuild;
	Unit *selUnit;
	Sint32 selectionUID;
	bool needRedraw;
	int typeToBuild;

	TeamStat stats[128];
	int statsPtr;
	StatMode statMode;

	Uint32 chatMask;

	SDLBitmapFont *font;

	std::queue<Order *> orderQueue;

	int mouseX, mouseY;
	int viewportSpeedX[8], viewportSpeedY[8];
	
	// statistics related:
	enum
	{
		nbRecentFreeUnits=32
	};
	int recentFreeUnits[nbRecentFreeUnits];
	int recentFreeUnitsIt;

	// menu related functions
	enum
	{
		IGM_NONE=0,
		IGM_MAIN,
		IGM_SAVE,
		IGM_ALLIANCE8
	} inGameMenu;
	InGameScreen *gameMenuScreen;

	// message related functions : FIXME : move this to a class
public :
	enum {
		MAX_MESSAGE_SIZE = 64
	}; // avoid network overflow
private :
	typedef struct
	{
		int showTicks;
		char text[MAX_MESSAGE_SIZE+BasePlayer::MAX_NAME_LENGTH+4];
	} Message;
	std::list<Message> messagesList;
	enum {
		DEFAULT_MESSAGE_SHOW_TICKS = 100
	};
	bool typingMessage;
	char typedMessage[MAX_MESSAGE_SIZE];
	int typedChar;
};

#endif

