#pragma once
#ifndef GAME_CLASS_H
#define GAME_CLASS_H

#include <vector>
#include "GameObject.h"
#include "Paddle.h"
#include "Barrier.h"
#include "Ball.h"
#include "shaderclass.h"
#include "Camera.h"
#include "light.h"

class Game {
	public:
		
		GLFWwindow* gameWindow;
		std::vector <Ball*> balls;
		std::vector <Paddle*> paddles;
		std::vector <Barrier*> barriers;
		std::vector <Shader*> shaders;
		std::vector <Light*> lights;

		std::vector <Camera*> cameras;
		std::vector <GameObject*> gameObjects;

		double lastTime;

		Game() = default;

		//--FRAME
		void update();
		void draw();

		//--UTILITY
		double deltaTime();
};

#endif // !GAME_CLASS_H
