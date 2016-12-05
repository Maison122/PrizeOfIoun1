/*
=================
cButtinManager.cpp
- CPP file for class definition - IMPLEMENTATION
- CPP file for the ButtonManager class
=================
*/
#include "cButtonManager.h"
cButtonManager* cButtonManager::pInstance = NULL;

/*
=================================================================================
Singleton Design Pattern
=================================================================================
*/
cButtonManager* cButtonManager::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new cButtonManager();
	}
	return cButtonManager::pInstance;
}

/*
=================
- Data constructor initializes the buttonManager object
- Is always called, thus ensures all buttonManager objects are in a consistent state.
=================
*/
cButtonManager::cButtonManager()
{

}

/*
=================
- Destructor.
=================
*/
cButtonManager::~cButtonManager()
{
	deleteBtn();
}

void cButtonManager::add(LPCSTR btnName, cButton* theBtn)
{
	if (!getBtn(btnName))
	{
		
		gameBtns.insert(make_pair(btnName, theBtn));
	}
}

void cButtonManager::deleteBtn()
{
	for (map<LPCSTR, cButton*>::iterator btn = gameBtns.begin(); btn != gameBtns.end(); ++btn)
	{
		delete btn->second;
	}
}

/*
=================
- return the texture.
=================
*/
cButton* cButtonManager::getBtn(LPCSTR btnName)        // return the texture.
{
	map<LPCSTR, cButton*>::iterator btn = gameBtns.find(btnName);
	if (btn != gameBtns.end())
	{
		return btn->second;
	}
	else
	{
		return NULL;
	}
}
