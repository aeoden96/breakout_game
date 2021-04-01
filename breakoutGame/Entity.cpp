#include "libs.h"
#include "Entity.h"

void Entity::initVariables()
{

	this->hitboxComponent = NULL;
	this->movementComponent = NULL;
	//this->animationComponent = NULL;
}

Entity::Entity()
{
	this->initVariables();
}


Entity::~Entity()
{
	delete this->hitboxComponent;
	delete this->movementComponent;
	//delete this->animationComponent;
}

//Component functions
void Entity::setTexture(sf::Texture& texture)
{

	this->sprite.setTexture(texture);


}

void Entity::createHitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height)
{
	this->hitboxComponent = new HitboxComponent(sprite, offset_x, offset_y, width, height);
}

void Entity::createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration)
{
	this->movementComponent = new MovementComponent(this->sprite, maxVelocity, acceleration, deceleration);
}
/*
void Entity::createAnimationComponent(sf::Texture& textureSheet)
{
	this->animationComponent = new AnimationComponent(this->sprite, textureSheet);
}*/


bool Entity::checkCollision(Entity* entity)
{
	return (this->hitboxComponent->checkIntersect(entity->sprite.getGlobalBounds()));
}

bool Entity::checkCollision(sf::FloatRect rect)
{
	return (this->hitboxComponent->checkIntersect(rect));
}

//Functions
void Entity::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);

}
sf::Vector2f Entity::getPosition()
{
	return sprite.getPosition();
	
}
sf::FloatRect Entity::getOuterBounds()
{
	return this->sprite.getGlobalBounds();
}
void Entity::stopVelocity(char axis)
{
	if (axis == 'x') {
		this->movementComponent->stopVelocityX();
	}
	else if (axis == 'y') {
		this->movementComponent->stopVelocityY();

	}
	else {
		this->movementComponent->stopVelocity();

	}
}
void Entity::move(const float dir_x, const float dir_y, const float& dt)
{
	if (this->movementComponent)
	{
		this->movementComponent->move(dir_x, dir_y, dt);//sets velocity
	}

}

void Entity::move(const float& dt)
{
	if (this->movementComponent)
	{
		this->movementComponent->move(dt);//sets velocity
	}

}

void Entity::update(const float& dt)
{
}

void Entity::render(sf::RenderTarget& target)
{

	target.draw(this->sprite);

	if (this->hitboxComponent)
		this->hitboxComponent->render(target);

}