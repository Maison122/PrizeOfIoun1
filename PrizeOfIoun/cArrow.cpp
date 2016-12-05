/*
=================
cArrow.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cArrow.h"

/*
=================================================================
Defualt Constructor
=================================================================
*/
cArrow::cArrow() : cSprite()
{
	this->arrowVelocity = { 0.0, 0.0 };
}
/*
=================================================================
Update the sprite position
=================================================================
*/

void cArrow::update(double deltaTime)
{

	FPoint direction = { 0.0, 0.0 };
	direction.X = (sin((this->getSpriteRotAngle())*PI / 180));
	direction.Y = -(cos((this->getSpriteRotAngle())*PI / 180));

	direction.X *= this->getSpriteTranslation().x;
	direction.Y *= this->getSpriteTranslation().y;

	this->arrowVelocity.x = this->arrowVelocity.x + direction.X;
	this->arrowVelocity.y = this->arrowVelocity.y + direction.Y;

	SDL_Rect currentSpritePos = this->getSpritePos();
	currentSpritePos.x += this->arrowVelocity.x * deltaTime;
	currentSpritePos.y += this->arrowVelocity.y * deltaTime;

	this->setSpritePos({ currentSpritePos.x, currentSpritePos.y });

	cout << "Arrow position - x: " << this->getSpritePos().x << " y: " << this->getSpritePos().y << " deltaTime: " << deltaTime << endl;

	this->setBoundingRect(this->getSpritePos());

}
/*
=================================================================
Sets the velocity for the Arrow
=================================================================
*/
void cArrow::setArrowVelocity(SDL_Point tntVel)
{
	this->arrowVelocity = tntVel;
}
/*
=================================================================
Gets the Arrow velocity
=================================================================
*/
SDL_Point cArrow::getArrowVelocity()
{
	return this->arrowVelocity;
}
