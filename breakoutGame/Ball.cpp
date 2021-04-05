#include "libs.h"
#include "Ball.h"

//Initializer funcions

void Ball::initVariables()
{
	//this->attacking = false;
}

void Ball::initComponents()
{

}

//Constructors/Destructors
Ball::Ball(float x, float y, sf::Texture& texture)
{
	this->initVariables();


	this->setPosition(x, y);

	this->createHitboxComponent(this->sprite, 0.f, 0.f, 80.f * 0.5f * 0.65f, 80.f * 0.5f * 0.73f);
	this->createMovementComponent(300.f, 15.f, 5.f);

	this->sprite.setScale(PLAYER_SIZE_FACTOR, PLAYER_SIZE_FACTOR);

	//this->createAnimationComponent(textureSheet);
	// 
	//this->animationComponent->addAnimation("IDLE", 10.f, 0, 0, 9, 0, 587, 707);
	//this->animationComponent->addAnimation("WALK", 7.f, 0, 1, 9, 1, 587, 707);
	//this->animationComponent->addAnimation("ATTACK", 7.f, 0, 2, 9, 2, 587, 707);


}


Ball::~Ball()
{
}

//Functions
void Ball::updateAttack()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		//this->attacking = true;
	}
}
void Ball::hit(const float& dt,bool horizontal)
{
	this->movementComponent->reflexion(dt, horizontal);
}
void Ball::updateAnimation(const float& dt) {

}


void Ball::update(const float& dt)
{
	this->movementComponent->update(dt); //calculates velocity and MOVES the sprite

	this->updateAttack();

	this->updateAnimation(dt);

	this->hitboxComponent->update();

}