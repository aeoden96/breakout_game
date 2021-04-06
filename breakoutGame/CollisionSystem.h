#pragma once
#include"Ball.h"
#include "Player.h"
#include "BrickMap.h"
#include "ScoreSystem.h"

class CollisionSystem
{
	Ball* ball;
	Player* player;
	BrickMap* brickMap;
	ScoreSystem* scoreSystem;
	int screenW, screenH;
public:
	CollisionSystem(
		Ball* ball,
		Player* player,
		BrickMap* brickMap,
		ScoreSystem* scoreSystem,
		int screenW,int screenH);
	~CollisionSystem();
	void collision_wall_player(const float& dt);
	void collision_wall_ball(const float& dt);
	void collision_brick_ball(const float& dt);
	void collision_ball_player(const float& dt);
	void update(const float& dt);
};

