#pragma once


#include "HitboxComponent.h"
#include "MovementComponent.h"
//#include "AnimationComponent.h"

class Entity //EVERY ENITIY HAS ITS SPRITE
{
private:
	void initVariables();

protected:

	sf::Sprite sprite;

	//sf::RectangleShape shape; //placeholder


	HitboxComponent* hitboxComponent;
	MovementComponent* movementComponent;
	//AnimationComponent* animationComponent;

public:
	Entity();

	virtual ~Entity();
	//Component functions
	void setTexture(sf::Texture& texture);


	void createHitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height);
	void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
	//void createAnimationComponent(sf::Texture& textureSheet);

	//Functions
	virtual bool checkCollision(Entity* entity);
	bool checkCollision(sf::FloatRect rect);
	virtual void setPosition(const float x, const float y);
	sf::Vector2f  getPosition();
	//move fn. for entity
	virtual void move(const float x, const float y, const float& dt);
	void move(const float& dt);
	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget& target);
};
