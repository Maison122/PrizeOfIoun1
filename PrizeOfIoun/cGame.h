#pragma once
#ifndef _GAME_H
#define _GAME_H

/*
==================================================================================
cGame.h
==================================================================================
*/

#include <SDL.h>

// Game specific includes
#include "PrizeOfIounGame.h"


using namespace std;

class cGame
{
public:
	cGame();

	void initialise(SDL_Window* theSDLWND, SDL_Renderer* theRenderer);
	void run(SDL_Window* theSDLWND, SDL_Renderer* theRenderer);
	void cleanUp(SDL_Window* theSDLWND);
	void render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer);
	void render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer, double rotAngle, SDL_Point* spriteCentre);
	void update();
	void update(double deltaTime);
	bool getInput(bool theLoop);
	double getElapsedSeconds();

	static cGame* getInstance();

private:

	static cGame* pInstance;
	// for framerates
	time_point< high_resolution_clock > m_lastTime;
	time_point< high_resolution_clock > m_CurrentTime;
	duration< double > deltaTime;
	bool loop;

// Sprites for displaying background and player textures
cSprite spriteBkgd;
cPlayer thePlayer;
cBoulder theBoulder;
cTNT theTNT;
cArrow theArrow;
// game related variables
vector<LPCSTR> textureName;
vector<LPCSTR> textName;
vector<LPCSTR> texturesToUse;
vector<cBoulder*> theBoulders;
vector<cTNT*> theTNTs;
vector<cArrow*> theArrows;
// Fonts to use
vector<LPCSTR> fontList;
vector<LPCSTR> fontsToUse;
// Text for Game
vector<LPCSTR> gameTextNames;
vector<LPCSTR> gameTextList;
// Game Sounds
vector<LPCSTR> soundList;
vector<soundType> soundTypes;
vector<LPCSTR> soundsToUse;
// Create vector array of button textures
vector<LPCSTR> btnNameList;
vector<LPCSTR> btnTexturesToUse;
vector<SDL_Point> btnPos;
vector <cButton> theButtons;
// Game objects
// Define the elements and there position in/on the array/map
int renderWidth, renderHeight;
int score;
string strScore;
gameState theGameState;
btnTypes theBtnType;
SDL_Rect pos;
FPoint scale;
SDL_Rect aRect;
SDL_Color aColour;
cTexture* tempTextTexture;
SDL_Point theAreaClicked;
};

#endif