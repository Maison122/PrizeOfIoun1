#pragma once
/*
=================
cTextureMgr.h
- Header file for class definition - SPECIFICATION
- Header file for the cTextureManager class
=================
*/
#ifndef _CTEXTUREMANAGER_H
#define _CTEXTUREMANAGER_H
#include "GameConstants.h"
#include "cTexture.h"

class cTextureManager
{
private:
	static cTextureManager* pInstance;
	map<LPCSTR, cTexture*> textureList;
	SDL_Renderer* theSDLRenderer;

public:
	static cTextureManager* getInstance();
	cTextureManager();
	cTextureManager(SDL_Renderer* theRenderer);
	~cTextureManager();
	void addTexture(LPCSTR txtName, LPCSTR theFilename);		// add the texture for use.
	void addTexture(LPCSTR txtName, SDL_Texture* theTexture);		// add the texture for use.
	cTexture* getTexture(LPCSTR textureName);		// return the texture.
	void setRenderer(SDL_Renderer* ptheRenderer); // Set the renderer
	void deleteTextures();						// Delete all textures;
	void deleteTexture(LPCSTR txtName);						// Delete all textures;
};
#endif