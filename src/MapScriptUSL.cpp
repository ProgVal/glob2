/*
  Copyright (C) 2008 Bradley Arsenault

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/


#include <Toolkit.h>
#include <FileManager.h>
using namespace GAGCore;

#include "MapScriptUSL.h"

#include "error.h"

#include "Stream.h"
#include <iostream>
#include <sstream>
#include <memory>

using namespace std;

MapScriptUSL::MapScriptUSL()
{
	
}


MapScriptUSL::~MapScriptUSL()
{
	
}


void MapScriptUSL::encodeData(GAGCore::OutputStream* stream) const
{
	stream->writeEnterSection("MapScriptUSL");
	// TODO: serialize state
	stream->writeLeaveSection();
}



void MapScriptUSL::decodeData(GAGCore::InputStream* stream, Uint32 versionMinor)
{
	stream->readEnterSection("MapScriptUSL");
	// TODO: deserialize state if version do match
	stream->readLeaveSection();
}


bool MapScriptUSL::compileCode(const std::string& code)
{
	usl = Usl();
	
	try
	{
		if (Toolkit::getFileManager()->initDirectoryListing("data/usl/Language/Runtime", "usl"))
		{
			const char* fileName;
			while ((fileName = Toolkit::getFileManager()->getNextDirectoryEntry()) != NULL)
			{
				std::string fullFileName = string("data/usl/Language/Runtime") + DIR_SEPARATOR + fileName;
				auto_ptr<ifstream> file(Toolkit::getFileManager()->openIFStream(fullFileName));
				if (file.get())
				{
					cerr << "* Loading " << fullFileName << endl;
					usl.includeScript(fileName, *file.get());
				}
				else
				{
					cerr << "* Failed to load " << fullFileName << endl;
				}
			}
		}
		else
		{
			cerr << "MapScriptUSL::compileCode(): Cannot open Runtime directory" << endl;
			return false;
		}
	}
	catch(Exception& e)
	{
		cerr << "MapScriptUSL::compileCode(): Error in usl runtime file " << e.position << " : " << e.what() << endl;
		return false;
	}
	
	try
	{
		istringstream codeStream(code);
		usl.createThread("<mapscript>", codeStream);
	}
	catch(Exception& e)
	{
		error = MapScriptError(e.position.line, e.position.column, e.what());
		return false;
	}
	
	return true;
}

const MapScriptError& MapScriptUSL::getError() const
{
	return error;
}


void MapScriptUSL::syncStep(GameGUI *gui)
{
	const size_t stepsMax = 10000;
	size_t stepsCount = usl.run(stepsMax);
	cerr << "* USL executed " << stepsCount << " steps" << endl;
}
