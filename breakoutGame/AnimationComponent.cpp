#include "libs.h"
#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& textureSheet)
	:sprite(sprite), textureSheet(textureSheet), lastAnimation(NULL), priorityAnimation(NULL)
{
}

AnimationComponent::~AnimationComponent()
{
	for (auto& i : this->animations)
		delete i.second;
}
//Accessor

const bool& AnimationComponent::isDone(const std::string key)
{
	return this->animations[key]->isDone();
}


//Functions
void AnimationComponent::addAnimation(
	const std::string key,
	float animationTimer,
	int start_frame_x, int start_frame_y,
	int frames_x, int frames_y,
	int width, int  height)
{
	this->animations[key] = new Animation(this->sprite, this->textureSheet,
		animationTimer, start_frame_x, start_frame_y,
		frames_x, frames_y, width, height);
}

const bool& AnimationComponent::play(const std::string key, const float& dt, const bool priority)
{

	if (this->priorityAnimation)//if there is a priority animation
	{
		if (this->priorityAnimation == this->animations[key])
		{
			//resetting animation sequence every time another animation comes ( etc. idle -> moving )
			if (this->lastAnimation != this->animations[key])
			{
				if (this->lastAnimation == NULL)
				{
					this->lastAnimation = this->animations[key];
				}
				else
				{
					this->lastAnimation->reset();
					this->lastAnimation = this->animations[key];

				}
			}
			//if priority animation is done, remove it
			if (this->animations[key]->play(dt)) //WHEN play() returns done = true
			{
				this->priorityAnimation = NULL;
			}
		}
	}
	else //play animation if no other priority animation is set
	{
		//if this is priority animation,set it
		if (priority)
		{
			this->priorityAnimation = this->animations[key];
		}

		//resetting animation sequence every time another animation comes ( etc. idle -> moving )
		if (this->lastAnimation != this->animations[key])
		{
			if (this->lastAnimation == NULL)
			{
				this->lastAnimation = this->animations[key];
			}
			else
			{
				this->lastAnimation->reset();
				this->lastAnimation = this->animations[key];

			}
		}
		this->animations[key]->play(dt);
	}

	return this->animations[key]->isDone();
}

const bool& AnimationComponent::play(const std::string key, const float& dt, const float& modifier, const float& modifier_max, const bool priority)
{
	if (this->priorityAnimation)//if there is a priority animation
	{
		if (this->priorityAnimation == this->animations[key])
		{
			//resetting animation sequence every time another animation comes ( etc. idle -> moving )
			if (this->lastAnimation != this->animations[key])
			{
				if (this->lastAnimation == NULL)
				{
					this->lastAnimation = this->animations[key];
				}
				else
				{
					this->lastAnimation->reset();
					this->lastAnimation = this->animations[key];

				}
			}
			//if priority animation is done, remove it
			if (this->animations[key]->play(dt)) //WHEN play() returns done = true
			{
				this->priorityAnimation = NULL;
			}
		}
	}
	else //play animation if no other priority animation is set
	{
		//if this is priority animation,set it
		if (priority)
		{
			this->priorityAnimation = this->animations[key];
		}
		//resetting animation sequence every time another animation comes ( etc. idle -> moving )
		if (this->lastAnimation != this->animations[key])
		{
			if (this->lastAnimation == NULL)
			{
				this->lastAnimation = this->animations[key];
			}
			else
			{
				this->lastAnimation->reset();
				this->lastAnimation = this->animations[key];

			}
		}
		this->animations[key]->play(dt, abs(modifier / modifier_max));
	}

	return this->animations[key]->isDone();
}