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
#include "Screen.h"
#include "GUI.h"
#include "GOList.h"
#include "soundDevice.h"
#include "soundBuffer.h"
#include "soundSource.h"
#include "musicBuffer.h"
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
class ScreenHandler;
class Screen;
class GUI;
class GOList;
class SoundList;
class soundDevice;
class soundBuffer;
class soundSource;
class musicBuffer;
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
		std::vector <Texture*> texWithBloom;
		std::vector <PowerupSpawn*> PowerupSpawner;
		std::vector <ScreenHandler*> ScreenHandler;
		std::vector <Screen*> ScreenObject;
		std::vector <GUI*> debugGUI;
		std::vector <GOList*> OBJList;

		//-----------------ROSE---------------------
		std::vector <soundDevice*> soundDevice;
		std::vector <soundBuffer*> soundBuffer;
		std::vector <soundSource*> soundSource;
		std::vector <SoundList> SoundList;
		//temporary on hold, issue with file reads
		std::vector <musicBuffer*> musictracks;

		std::vector <std::vector<GLuint>> indexVec;
		std::vector <std::vector<Texture>> texturesVec;
		std::vector <std::vector<Vertex>> vertVec;

		std::vector <ParticleSystem*> particleSystems;

		std::vector <Camera*> cameras;
		std::vector <GameObject*> gameObjects;

		//i am sorry
		std::vector <GLuint> FBOBuffers;
		float lastTime;
		bool pause = false;
		bool inDebugMode = true;
		bool postProcessingOn = true;
		int framestep = 0;

		int screenWidth = 1920;
		int screenHeight = 1080;

		Game();

		//--FRAME
		bool timer(int time);
		void update();
		void deleteObj(GameObject* GO);
		void draw();

		void drawScreen();
		void removeScreen(Screen* S);
		void updateScreen();

		//--UTILITY
		void slowMo(float time);
		float deltaTime;
		float gamma = 2.2f;

		//--SETTING
		//Screen Settings
		const char* settingType = "< VIDEO >";
		const char* resSetting = "< 1920 X 1080 >";

		enum RESID { HD, FHD, TWOK, FOURK };
		RESID resID = FHD;

		const char* debugSetting = "< ON ";
};

