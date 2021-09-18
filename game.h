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
#include "VBO.h"
#include "Powerup.h"
#include "Menu.h"
#include <vector>

class Game;
class Barrier;
class Shader;
class Ball;
class Paddle;
class Light;
class Camera;
class gameFont;
class miscFont;
struct Font;
class Texture;
class PowerupSpawn;
class GameObject;
class ParticleSystem;
class MenuHandler;
struct Vertex;
struct GLFWwindow;

class Game {
	public:
		
		GLFWwindow* gameWindow;
		std::vector <Ball*> balls;
		std::vector <Paddle*> paddles;
		std::vector <Barrier*> barriers;
		std::vector <Shader*> shaders;
		std::vector <Light*> lights;
		std::vector <miscFont*> miscfonts;
		std::vector <gameFont*> texts;
		std::vector <Font*> fonts;
		std::vector <Texture*> textures;
		std::vector <PowerupSpawn*> PowerupSpawner;
		std::vector <MenuHandler*> MenuHandler;

		std::vector <std::vector<GLuint>> indexVec;
		std::vector <std::vector<Texture>> texturesVec;
		std::vector <std::vector<Vertex>> vertVec;

		std::vector <ParticleSystem*> particleSystems;

		std::vector <Camera*> cameras;
		std::vector <GameObject*> gameObjects;

		float lastTime;
		bool debugPause = false;
		int framestep = 0;

		Game();

		//--FRAME
		bool timer(int time);
		void update();
		void deleteObj(GameObject* GO);
		void draw();
		void initScreen();

		//--UTILITY
		void slowMo(float time);
		float deltaTime;
};

