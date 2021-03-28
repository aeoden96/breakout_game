#pragma once

#include "Entity.h"
class Player :
	public Entity
{
private:
	//Variables
	//bool attacking;
	const float PLAYER_SIZE_FACTOR = 0.5f;

	//Initializer funcions
	void initVariables();
	void initComponents();

public:
	Player(float x, float y, sf::Texture& textureSheet);
	virtual ~Player();

	//Functions
	void updateAnimation(const float& dt);
	void updateAttack();

	virtual void update(const float& dt);
};