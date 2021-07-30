#pragma once

#include "GameObject.h"
#include "Barrier.h"
#include "shaderclass.h"
#include "Ball.h"
#include "Paddle.h"
#include "light.h"
#include "Camera.h"
#include"gameFont.h"
#include "font.h"
#include "Texture.h"
#include "Particles.h"
#include <vector>

class Game;
class Barrier;
class Shader;
class Ball;
class Paddle;
class Light;
class Camera;
class gameFont;
struct Font;
class Texture;
class GameObject;
class ParticleSystem;
struct GLFWwindow;

class Game {
	public:
		
		GLFWwindow* gameWindow;
		std::vector <Ball*> balls;
		std::vector <Paddle*> paddles;
		std::vector <Barrier*> barriers;
		std::vector <Shader*> shaders;
		std::vector <Light*> lights;
		std::vector <gameFont*> texts;
		std::vector <Font*> fonts;
		std::vector <Texture*> textures;

		std::vector <ParticleSystem*> particleSystems;

		std::vector <Camera*> cameras;
		std::vector <GameObject*> gameObjects;

		float lastTime;
		bool pause = false;
		int framestep = 0;

		Game();

		//--FRAME
		void update();
		void draw();

		//--UTILITY
		float deltaTime;
};

