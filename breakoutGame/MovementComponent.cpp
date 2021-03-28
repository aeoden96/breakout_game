#include "libs.h"
#include "MovementComponent.h"


//Konstr/destr
MovementComponent::MovementComponent(
	sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration)
	:sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration)
{
	dirx = 1;
	diry = 1;
}


MovementComponent::~MovementComponent()
{
}
//Accesors
const float& MovementComponent::getMaxVelocity() const
{
	return this->maxVelocity;
}

const sf::Vector2f& MovementComponent::getVelocity() const
{
	return this->velocity;
}




//Functions
const bool MovementComponent::getState(const short unsigned state) const
{
	switch (state) {
	case IDLE:

		if (this->velocity.x == 0.f && this->velocity.y == 0.f)
			return true;

		break;
	case MOVING:

		if (this->velocity.x != 0.f || this->velocity.y != 0.f)
			return true;

		break;
	case MOVING_LEFT:

		if (this->velocity.x < 0.f)
			return true;

		break;
	case MOVING_RIGHT:

		if (this->velocity.x > 0.f)
			return true;

		break;
	case MOVING_UP:

		if (this->velocity.y < 0.f)
			return true;

		break;
	case MOVING_DOWN:

		if (this->velocity.y > 0.f)
			return true;

		break;

	}

	return false;
}


//sets directional velocity
void MovementComponent::move(const float dir_x, const float dir_y, const float& dt)
{
	/*accelerating a sprite until reaches maxVelocity*/


	//acceleraton
	this->velocity.x += this->acceleration * dir_x;

	this->velocity.y += this->acceleration * dir_y;

}
void MovementComponent::reflexion(const float& dt, bool horizontal)
{
	
	if (horizontal) {
		diry = -diry;
		this->velocity.y = -this->velocity.y;

	}
	else {
		dirx = -dirx;
		this->velocity.x = -this->velocity.x;

	}

	
	
	

}
void MovementComponent::move(const float& dt)
{
	/*accelerating a sprite until reaches maxVelocity*/


	//acceleraton
	this->velocity.x += this->acceleration * dirx;

	this->velocity.y += this->acceleration * diry;

}

void MovementComponent::update(const float& dt)
{
	/*
	Decelerates the sprite and controls max velocity.
	Moves the sprite.
	*/
	if (this->velocity.x > 0.f) //check for positive x 
	{
		//maxVelocity check x positive
		if (this->velocity.x > this->maxVelocity)
			this->velocity.x = this->maxVelocity;

		//Deceleration x positive
		this->velocity.x -= deceleration;
		if (this->velocity.x < 0.f)
			this->velocity.x = 0.f;

	}
	else if (this->velocity.x < 0.f)//check for negative x 
	{
		//maxVelocity check x negative
		if (this->velocity.x < -this->maxVelocity)
			this->velocity.x = -this->maxVelocity;
		//Deceleration x negative
		this->velocity.x += deceleration;
		if (this->velocity.x > 0.f)
			this->velocity.x = 0.f;
	}

	if (this->velocity.y > 0.f) //check for positive y 
	{
		//maxVelocity check y positive
		if (this->velocity.y > this->maxVelocity)
			this->velocity.y = this->maxVelocity;

		//Deceleration y positive
		this->velocity.y -= deceleration;
		if (this->velocity.y < 0.f)
			this->velocity.y = 0.f;

	}
	else if (this->velocity.y < 0.f)//check for negative y 
	{
		//maxVelocity check y negative
		if (this->velocity.y < -this->maxVelocity)
			this->velocity.y = -this->maxVelocity;
		//Deceleration y negative
		this->velocity.y += deceleration;
		if (this->velocity.y > 0.f)
			this->velocity.y = 0.f;
	}

	//final move
	this->sprite.move(this->velocity * dt);//uses velocity
}