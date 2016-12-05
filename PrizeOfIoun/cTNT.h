#pragma once
/*
=================
cTNT.h
- Header file for class definition - SPECIFICATION
- Header file for the TNT class which is a child of cSprite class
=================
*/
#ifndef _CTNT_H
#define _CTNT_H
#include "cSprite.h"


class cTNT : public cSprite
{
private:
	SDL_Point tntVelocity;

public:
	cTNT();
	void update(double deltaTime);		// TNT update method
	void setTNTVelocity(SDL_Point tntVel);   // Sets the velocity for the TNT
	SDL_Point getTNTVelocity();				 // Gets the TNT velocity
};
#endif