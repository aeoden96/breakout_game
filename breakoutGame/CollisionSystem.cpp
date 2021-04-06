#include "CollisionSystem.h"

CollisionSystem::CollisionSystem(
	Ball* ball,
	Player* player,
	BrickMap* brickMap, 
	ScoreSystem* scoreSystem,
	int screenW,
	int screenH) :
	ball(ball), 
	player(player), 
	brickMap(brickMap),
	scoreSystem(scoreSystem),
	screenW(screenW),
	screenH(screenH)
{}

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

	else if (player->getPosition().x + player->getOuterBounds().width > screenW) {
		player->setPosition(screenW - player->getOuterBounds().width, player->getPosition().y);
	}

}

void CollisionSystem::collision_wall_ball(const float& dt)
{
	//COLLISION BALL--WALLS 

	

	if (ball->getPosition().x < 0 ||
		ball->getPosition().x > screenW - this->ball->getOuterBounds().width ){
		ball->hit(dt, false);
	}

	if (ball->getPosition().y < 0) {
		ball->hit(dt, true);
	}

	//END

	if (ball->getPosition().y > screenH) {
		//this->endState();
		this->scoreSystem->ballLost();
	}
}

void CollisionSystem::collision_brick_ball(const float& dt)
{
	enum class hitType {NONE,FROM_SIDE, FROM_TOP_OR_BOTTOM, NEAR_EDGE };
	
	
	hitType hit = hitType::NONE;

	for (unsigned int x = 0; x < this->brickMap->maxSize.x; x++)
	{
		for (unsigned int y = 0; y < brickMap->maxSize.y; y++)
		{
			if (ball->checkCollision(this->brickMap->returnBrick(x, y)->returnPosition()))
			{
				sf::FloatRect brickPosition = this->brickMap->returnBrick(x, y)->returnPosition();
				//this->brickMap->returnBrick(x, y)->hit();
				this->brickMap->crackIt(x, y);
				this->scoreSystem->addPoints(this->brickMap->returnBrick(x, y)->getBrickType());
				//hit = FROM_TOP_OR_BOTTOM;

				//HIT FROM BELOW
				
				if (ball->getPosition().x > brickPosition.left) {
					hit = hitType::FROM_SIDE;
				}
				else if (ball->getPosition().x + ball->getOuterBounds().width < brickPosition.left + brickPosition.width){
					hit = hitType::FROM_SIDE;
				}
				if (ball->getPosition().x > brickPosition.left &&
					ball->getPosition().x + ball->getOuterBounds().width < brickPosition.left + brickPosition.width) {
					hit = hitType::FROM_TOP_OR_BOTTOM;
				}




			}
		}
	}
	
	//COLLISION BALL-- BRICK

	if (hit == hitType::FROM_TOP_OR_BOTTOM)
		ball->hit(dt, true);
	else if (hit == hitType::FROM_SIDE) {
		ball->hit(dt, false);
	}
}

void CollisionSystem::collision_ball_player(const float& dt)
{
	//COLLISION BALL--PLAYER

	if (player->checkCollision(ball)) {
		int ballCenter =static_cast<int>( ball->getOuterBounds().width / 2 + ball->getPosition().x );

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
