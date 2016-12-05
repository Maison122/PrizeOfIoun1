#pragma once
/*
=================
cArrow.h
- Header file for class definition - SPECIFICATION
- Header file for the Arrow class which is a child of cSprite class
=================
*/
#ifndef _CArrow_H
#define _CARROW_H
#include "cSprite.h"


class cArrow : public cSprite
{
private:
	SDL_Point arrowVelocity;

public:
	cArrow();
	void update(double deltaTime);		// Arrow update method
	void setArrowVelocity(SDL_Point arrowVel);   // Sets the velocity for the Arrow
	SDL_Point getArrowVelocity();				 // Gets the Arrow velocity
};
#endif