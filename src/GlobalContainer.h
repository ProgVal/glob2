/*
  Copyright (C) 2001, 2002, 2003 Stephane Magnenat & Luc-Olivier de Charrière
  for any question or comment contact us at nct@ysagoon.com or nuage@ysagoon.com

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/

#ifndef __GLOBALCONTAINER_H
#define __GLOBALCONTAINER_H

#include "GAG.h"
#include "StringTable.h"
#include "BuildingType.h"
#include <string>

class Settings : public base::Object
{
protected:
	CLASSDEF(Settings)
		BASECLASS(base::Object)
	MEMBERS
		ITEM(std::string, username)
		ITEM(int, screenWidth)
		ITEM(int, screenHeight)
		ITEM(Uint32, screenFlags)
		ITEM(Uint32, optionFlags)
		ITEM(Uint32, graphicType)
		ITEM(Uint32, defaultLanguage)
	CLASSEND;

public:
	Settings();
};

class FileManager;
class LogFileManager;

class GlobalContainer
{
public:
	enum { USERNAME_MAX_LENGTH=32 };
	enum { OPTION_LOW_SPEED_GFX=0x1 };

private:
	void initProgressBar(void);
	void updateLoadProgressBar(int value);

	//! user preferences
	base::Ptr<Settings> settings;
	const char *userName;

public:
	GlobalContainer(void);
	virtual ~GlobalContainer(void);

	void parseArgs(int argc, char *argv[]);
	void load(void);

	void pushUserName(const char *name);
	void popUserName();
	void setUserName(const char *name);
	const char *getUsername(void) { return userName; }
	Uint32 getGfxFlags() { return settings->screenFlags; }
	Uint32 getOptionFlags() { return settings->screenFlags; }

public:
	FileManager *fileManager;
	LogFileManager *logFileManager;
	
	GraphicContext *gfx;
	Sprite *terrain;
	Sprite *terrainShader;
	Sprite *terrainBlack;
	Sprite *ressources;
	Sprite *units;
	Sprite *buildings;
	Sprite *unitmini;
	Sprite *gamegui;
	Font *menuFont;
	Font *standardFont;
	Font *littleFont;

	StringTable texts;

	BuildingsTypes buildingsTypes;
	
	bool hostServer;
	char hostServerMapName[32];
};

extern GlobalContainer *globalContainer;

#endif 

