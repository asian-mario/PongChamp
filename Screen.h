#pragma once

#include "GameObject.h"
#include "game.h"
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class Game;


class Screen {
public:
	virtual void drawScreen(Game* g){}
	virtual void updateScreen(Game* g){}
};

class ScreenHandler : public Screen {
public:
	enum SCREENTYPE { GAME, PAUSE, MAIN };
	SCREENTYPE screen;
	ScreenHandler(SCREENTYPE screen);

	void MenuInit(Game* g);
	void MenuSwitch(SCREENTYPE screen);
};

class PauseMenu : public Screen {
public:
	void drawScreen(Game* g) override;
	//void menuUpdate(Game* g) override;
	void remove(Game* g);
};

class MainMenu : public Screen {
public:
	void drawScreen(Game* g) override;
	//void menuUpdate(Game* g) override;
	void remove(Game* g);
};

class GameScene : public Screen {
public:
	void drawScreen(Game* g) override;
	//void menuUpdate(Game* g) override;
	void remove(Game* g);
};