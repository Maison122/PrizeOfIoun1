#pragma once
/*
=================
cBoulder.h
- Header file for class definition - SPECIFICATION
- Header file for the Player class which is a child of cSprite class
=================
*/
#ifndef _CBOULDER_H
#define _CBOULDER_H
#include "cSprite.h"

class cBoulder : public cSprite
{
private:
	SDL_Point boulderVelocity;

public:
	cBoulder();
	void update(double deltaTime);		// Player update method
	void setBoulderVelocity(SDL_Point asteroidVel);   // Sets the velocity for the boulder
	SDL_Point getBoulderVelocity();				 // Gets the boulder velocity
};
#endif