#include "CollisionSystem.h"

CollisionSystem::CollisionSystem(
	Ball* ball,
	Player* player,
	BrickMap* brickMap, 
	ScoreSystem* scoreSystem) :
	ball(ball), 
	player(player), 
	brickMap(brickMap),
	scoreSystem(scoreSystem){}

CollisionSystem::~CollisionSystem()
{
}

void CollisionSystem::collision_wall_player(const float& dt)
{
	//COLLISION PLAYER--WALLS 
	if (player->getPosition().x < 0) {
		player->setPosition(0.f, player->getPosition().y);
		player->stopVelocity('x');
	}

	else if (player->getPosition().x + player->getOuterBounds().width > 1920) {
		player->setPosition(1920 - player->getOuterBounds().width, player->getPosition().y);
	}

}

void CollisionSystem::collision_wall_ball(const float& dt)
{
	//COLLISION BALL--WALLS 

	if (ball->getPosition().x < 0 ||
		ball->getPosition().x > 1920 - 50) {
		ball->hit(dt, false);
	}

	if (ball->getPosition().y < 0) {
		ball->hit(dt, true);
	}

	//END

	if (ball->getPosition().y > 1080) {
		//this->endState();
		this->scoreSystem->ballLost();
	}
}

void CollisionSystem::collision_brick_ball(const float& dt)
{
	int side = 0;
	for (size_t x = 0; x < this->brickMap->maxSize.x; x++)
	{
		for (size_t y = 0; y < brickMap->maxSize.y; y++)
		{
			if (ball->checkCollision(this->brickMap->returnBrick(x,y)->returnPosition()))
			{
				//this->brickMap->returnBrick(x, y)->hit();
				this->brickMap->crackIt(x, y);
				this->scoreSystem->addPoints(this->brickMap->returnBrick(x, y)->getBrickType());
				side = 1;
			}
		}
	}
	
	//COLLISION BALL-- BRICK

	if (side == 1)
		ball->hit(dt, true);
}

void CollisionSystem::collision_ball_player(const float& dt)
{
	//COLLISION BALL--PLAYER

	if (player->checkCollision(ball)) {
		int ballCenter = ball->getOuterBounds().width / 2 + ball->getPosition().x;

		if (ballCenter < player->getPosition().x ||
			ballCenter> player->getPosition().x + player->getOuterBounds().width) {
			ball->hit(dt, false);
			
		}
		else {
			ball->hit(dt, true);

		}
	}
}

void CollisionSystem::update(const float& dt)
{
	this->collision_wall_player(dt);
	this->collision_ball_player(dt);
	this->collision_wall_ball(dt);
	this->collision_brick_ball(dt);
}
