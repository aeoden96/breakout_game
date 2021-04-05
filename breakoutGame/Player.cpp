#include "libs.h"
#include "Player.h"

//Initializer funcions

void Player::initVariables()
{
	//this->attacking = false;
}

void Player::initComponents()
{

}

//Constructors/Destructors
Player::Player(float x, float y, sf::Texture& texture)
{
	this->initVariables();


	this->setPosition(x, y);

	this->createHitboxComponent(this->sprite, 22.f, 80.f, 590.f * 0.5f * 0.65f, 200.f * 0.5f * 0.73f);
	this->createMovementComponent(300.f, 15.f, 5.f);

	this->sprite.setScale(PLAYER_SIZE_FACTOR, PLAYER_SIZE_FACTOR);
	

	//this->createAnimationComponent(textureSheet);
	// 
	//this->animationComponent->addAnimation("IDLE", 10.f, 0, 0, 9, 0, 587, 707);
	//this->animationComponent->addAnimation("WALK", 7.f, 0, 1, 9, 1, 587, 707);
	//this->animationComponent->addAnimation("ATTACK", 7.f, 0, 2, 9, 2, 587, 707);


}


Player::~Player()
{
}

//Functions
void Player::updateAttack()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		//this->attacking = true;
	}
}
void Player::updateAnimation(const float& dt) {

}

void Player::update(const float& dt)
{
	this->movementComponent->update(dt); //calculates velocity and MOVES the sprite
	
	this->updateAttack();

	this->updateAnimation(dt);

	this->hitboxComponent->update();

}