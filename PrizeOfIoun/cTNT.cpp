/*
=================
cTNT.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cTNT.h"

/*
=================================================================
Defualt Constructor
=================================================================
*/
cTNT::cTNT() : cSprite()
{
	this->tntVelocity = { 0.0, 0.0 };
}
/*
=================================================================
Update the sprite position
=================================================================
*/

void cTNT::update(double deltaTime)
{

	FPoint direction = { 0.0, 0.0 };
	direction.X = (sin((this->getSpriteRotAngle())*PI / 180));
	direction.Y = -(cos((this->getSpriteRotAngle())*PI / 180));

	direction.X *= this->getSpriteTranslation().x;
	direction.Y *= this->getSpriteTranslation().y;

	this->tntVelocity.x = this->tntVelocity.x + direction.X;
	this->tntVelocity.y = this->tntVelocity.y + direction.Y;

	SDL_Rect currentSpritePos = this->getSpritePos();
	currentSpritePos.x += this->tntVelocity.x * deltaTime;
	currentSpritePos.y += this->tntVelocity.y * deltaTime;

	this->setSpritePos({ currentSpritePos.x, currentSpritePos.y });

	cout << "TNT position - x: " << this->getSpritePos().x << " y: " << this->getSpritePos().y << " deltaTime: " << deltaTime << endl;

	this->setBoundingRect(this->getSpritePos());

}
/*
=================================================================
Sets the velocity for the TNT
=================================================================
*/
void cTNT::setTNTVelocity(SDL_Point tntVel)
{
	this->tntVelocity = tntVel;
}
/*
=================================================================
Gets the TNT velocity
=================================================================
*/
SDL_Point cTNT::getTNTVelocity()
{
	return this->tntVelocity;
}
