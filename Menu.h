#pragma once

#include "GameObject.h"
#include "game.h"
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class GameObject;
class Game;

class MenuHandler : public GameObject {
	enum SCREENTYPE { GAME, PAUSE, MAIN };
	SCREENTYPE screen;

	MenuHandler(SCREENTYPE screen);

	void MenuInit(Game g);
	void MenuSwitch(SCREENTYPE screen);
};

class PauseMenu : public GameObject {

	PauseMenu();

	
};