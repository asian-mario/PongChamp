#pragma once
#include <vector>
#include "Paddle.h"
#include "Barrier.h"
#include "Ball.h"
#include "GameObject.h"
class Game {
	public:

		std::vector <Ball*> balls;
		std::vector <Paddle*> paddles;
		std::vector <Barrier*> barriers;


		GLFWwindow* gameWindow;
		std::vector <GameObject*> gameObjects;

		double lastTime;

		Game(GLFWwindow* gameWindow);

		//--FRAME
		void update();
		void draw();

		//--UTILITY
		double deltaTime();
};