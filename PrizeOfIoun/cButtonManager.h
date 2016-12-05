
/*
==========================================================================
cSoundManager.h
==========================================================================
*/

#ifndef _BUTTONMANAGER_H
#define _BUTTONMANAGER_H

// OpenGL Headers
#include "GameConstants.h"
#include "cButton.h"


using namespace std;

class cButtonManager

{
private:
	static cButtonManager* pInstance;

protected:
	cButtonManager();
	~cButtonManager();
	map <LPCSTR, cButton*> gameBtns;

public:
	void add(LPCSTR btnName, cButton* theBtn);
	cButton* getBtn(LPCSTR btnName);
	void deleteBtn();
	static cButtonManager* getInstance();
};
#endif
