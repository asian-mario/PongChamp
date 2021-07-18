#pragma once
#include <vector>
#include "Paddle.h"
#include "Barrier.h"
#include "Ball.h"
class Game {
public:
	std::vector<Paddle> paddles;
	std::vector<Barrier> barriers;
	std::vector<Ball> balls;
	std::vector<GameObject> gameObjects;

	Game();

	void update();
};