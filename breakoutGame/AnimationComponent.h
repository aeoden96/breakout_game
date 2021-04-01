#pragma once
#include "libs.h"
class AnimationComponent
{
private:
	class Animation
	{
	public:
		//Variables
		sf::Sprite& sprite;
		sf::Texture& textureSheet;
		float animationTimer;
		int width;
		int height;
		float timer;
		bool done;
		sf::IntRect startRect;
		sf::IntRect currentRect;
		sf::IntRect endRect;

		Animation(sf::Sprite& sprite, sf::Texture& textureSheet,
			float animationTimer,
			int start_frame_x, int start_frame_y,
			int frames_x, int frames_y,
			int width, int  height)
			:sprite(sprite), textureSheet(textureSheet), timer(0.f), done(false),
			animationTimer(animationTimer), width(width), height(height)
		{

			this->timer = 0.f;
			//s lijeva slike pocne od <start_frame_x * width> npr od 0, ili od 1*width
			//od vrha slike pocne od <start_frame_y * height> npr od 0 ili od 1*height
			this->startRect = sf::IntRect(start_frame_x * width, start_frame_y * height, width, height);
			this->currentRect = this->startRect;
			this->endRect = sf::IntRect(frames_x * width, frames_y * height, width, height);

			this->sprite.setTexture(this->textureSheet, true);//in case of error,set true?
			this->sprite.setTextureRect(this->startRect);//we want to display just the part of the texture
		}
		//Accessors
		const bool& isDone()const {
			return this->done;
		}
		//Functions
		const bool& play(const float& dt)
		{
			this->timer += 100.f * dt;
			//update timer
			this->done = false;
			if (this->timer >= this->animationTimer)
			{
				//reset timer
				this->timer = 0.f;
				//Animate
				if (this->currentRect != this->endRect)
				{
					this->currentRect.left += this->width;
				}
				else //Reset
				{
					this->currentRect.left = this->startRect.left;
					this->done = true;
				}

				this->sprite.setTextureRect(this->currentRect);

			}

			return this->done;
		}

		const bool& play(const float& dt, float mod_percent)
		{
			if (mod_percent < 0.5f)
			{
				mod_percent = 0.5f;
			}
			this->done = false;
			this->timer += mod_percent * 100.f * dt;
			//update timer
			if (this->timer >= this->animationTimer)
			{
				//reset timer
				this->timer = 0.f;
				//Animate
				if (this->currentRect != this->endRect)
				{
					this->currentRect.left += this->width;
				}
				else //Reset
				{
					this->currentRect.left = this->startRect.left;
					this->done = true;
				}

				this->sprite.setTextureRect(this->currentRect);

			}
			return this->done;
		}

		void reset() {
			this->timer = this->animationTimer;
			this->currentRect = this->startRect;
		}
	};


	sf::Sprite& sprite;
	sf::Texture& textureSheet;
	std::map<std::string, Animation*> animations;
	Animation* lastAnimation;
	Animation* priorityAnimation;

public:
	AnimationComponent(sf::Sprite& sprite, sf::Texture& textureSheet);
	virtual ~AnimationComponent();
	//Accesors

	const bool& isDone(const std::string key);

	//Functions
	void addAnimation(const std::string key,
		float animationTimer,
		int start_frame_x, int start_frame_y,
		int frames_x, int frames_y,
		int width, int  height);

	/*void startAnimation(const std::string animation);
	void pauseAnimation(const std::string animation);
	void resetAnimation(const std::string animation);*/

	const bool& play(const std::string key, const float& dt, const bool priority = false);
	const bool& play(const std::string key, const float& dt, const float& modifier, const float& modifier_max, const bool priority = false);

};