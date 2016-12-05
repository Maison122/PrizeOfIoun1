/*
=================
cBoulder.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cBoulder.h"

/*
=================================================================
Defualt Constructor
=================================================================
*/
cBoulder::cBoulder() : cSprite()
{
	this->boulderVelocity = { 0.0, 0.0 };
}
/*
=================================================================
Update the sprite position
=================================================================
*/

void cBoulder::update(double deltaTime)
{

	this->setSpriteRotAngle(this->getSpriteRotAngle() + (5.0f * deltaTime));
	if (this->getSpriteRotAngle() > 360)
	{
		this->setSpriteRotAngle(this->getSpriteRotAngle() - 360);
	}

	SDL_Rect currentSpritePos = this->getSpritePos();
	currentSpritePos.x += this->getSpriteTranslation().x * deltaTime * 10;
	currentSpritePos.y += this->getSpriteTranslation().y * deltaTime * 10;

	this->setSpritePos({ currentSpritePos.x, currentSpritePos.y });
	cout << "Asteroid position - x: " << this->getSpritePos().x << " y: " << this->getSpritePos().y << " deltaTime: " << deltaTime << endl;
	this->setBoundingRect(this->getSpritePos());
}
/*
=================================================================
Sets the velocity for the Boulder
=================================================================
*/
void cBoulder::setBoulderVelocity(SDL_Point BoulderVel)
{
	boulderVelocity = BoulderVel;
}
/*
=================================================================
Gets the Boulder velocity
=================================================================
*/
SDL_Point cBoulder::getBoulderVelocity()
{
	return boulderVelocity;
}
