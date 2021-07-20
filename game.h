#pragma once

#include "GameObject.h"
#include "Barrier.h"
#include "shaderclass.h"
#include "Ball.h"
#include "Paddle.h"
#include "light.h"
#include "Camera.h"
#include <vector>

class Game;
class Barrier;
class Shader;
class Ball;
class Paddle;
class Light;
class Camera;
class GameObject;
struct GLFWwindow;

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

		Game();

		//--FRAME
		void update();
		void draw();

		//--UTILITY
		double deltaTime();
};

