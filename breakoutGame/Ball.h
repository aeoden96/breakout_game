#pragma once
#include "libs.h"
#include "Entity.h"
class Ball :
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
		Ball(float x, float y, sf::Texture& textureSheet);
		virtual ~Ball();

		//Functions
		void updateAnimation(const float& dt);
		void updateAttack();

		virtual void update(const float& dt);
	};