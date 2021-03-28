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
//void Player::updateAnimation(const float& dt)
//{
//	if (this->attacking) //in caase attack anim is too big, values need to be adjusted here
//	{
//		///set origin depending on direction
//		/*if (this->sprite.getScale().x > 0.f) ///Facing left
//		{
//			this->sprite.setOrigin(0, 0.f);
//		}
//		else ///Facing right
//		{
//			this->sprite.setOrigin(500.f, 0.f);
//		}*/
//		///Animate and check for animation end
//		if (this->animationComponent->play("ATTACK", dt, true))//when attack animation is done, set attacking to false
//		{
//			this->attacking = false;
//
//			/*if (this->sprite.getScale().x > 0.f) ///Facing left
//			{
//				this->sprite.setOrigin(500.f, 0.f);
//			}
//			else ///Facing right
//			{
//				this->sprite.setOrigin(0.f, 0.f);
//			}*/
//		}
//	}
//
//	//we are defining what animation to see when player is moving in ? direction
//	if (this->movementComponent->getState(IDLE))
//		this->animationComponent->play("IDLE", dt);
//
//	else if (this->movementComponent->getState(MOVING_LEFT))
//	{
//		if (this->sprite.getScale().x > 0.f)
//		{
//			this->sprite.setOrigin(500.f, 0.f);
//			this->sprite.setScale(-1.f * PLAYER_SIZE_FACTOR, 1.f * PLAYER_SIZE_FACTOR);
//		}
//		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
//	}
//	else if (this->movementComponent->getState(MOVING_RIGHT))
//	{
//		if (this->sprite.getScale().x < 0.f)
//		{
//			this->sprite.setOrigin(0.f, 0.f);
//			this->sprite.setScale(1.f * PLAYER_SIZE_FACTOR, 1.f * PLAYER_SIZE_FACTOR);
//		}
//		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
//	}
//	else if (this->movementComponent->getState(MOVING_UP))
//	{
//		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
//	}
//	else if (this->movementComponent->getState(MOVING_DOWN))
//	{
//		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
//	}
//
//}

void Player::update(const float& dt)
{
	this->movementComponent->update(dt); //calculates velocity and MOVES the sprite

	this->updateAttack();

	this->updateAnimation(dt);

	this->hitboxComponent->update();

}