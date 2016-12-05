#pragma once
/*
== == == == == == == == =
cFontManager.h
- Header file for class definition - SPECIFICATION
- Header file for the InputManager class
== == == == == == == == =
*/
#ifndef _CFONTManager_H
#define _CFONTManager_H
#include "GameConstants.h"
#include "cFont.h"

class cFontManager
{
private:

	static cFontManager* pInstance;
	map<LPCSTR, cFont*> fontList;

public:
	static cFontManager* getInstance();

	cFontManager();								// Constructor
	~cFontManager();							// Destructor.
	bool initFontLib();						// Initialise the SDL ttf library
	void addFont(LPCSTR fontName, LPCSTR fileName, int fontSize);  // add font to the Font collection
	cFont* getFont(LPCSTR fontName);				// return the font for use
	void deleteFont();								// delete font.

};

#endif