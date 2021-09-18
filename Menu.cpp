#include "Menu.h"

MenuHandler::MenuHandler(SCREENTYPE screen) {
	this->screen = screen;
}

void MenuHandler::MenuInit(Game g) {
	if (screen == PAUSE) {
		GameObject* crntMenu = new PauseMenu();

		g.gameObjects.push_back(crntMenu);
	}

	if (screen == MAIN) {
		GameObject* crntMenu = new MainMenu();

		g.gameObjects.push_back(crntMenu);
	}
}

void MenuHandler::MenuSwitch(SCREENTYPE screen) {
	this->screen = screen;

	if (screen == PAUSE) {
		cout << "Switch Screen to PAUSE" << endl;
	}

	if (screen == MAIN) {
		cout << "Switch Screen to MAIN" << endl;
	}

	if (screen == GAME) {
		cout << "Switch Screen to GAME" << endl;
	}
}

void PauseMenu::screen(Game* g) {
	g->fonts[1]->drawString(800.0f, 150.0f, "PAUSED", g->shaders[2]);
}

void PauseMenu::remove(Game* g) {
	g->deleteObj(this);
}

void MainMenu::screen(Game* g) {
	g->fonts[1]->drawString(800.0f, 150.0f, "PongChamp!", g->shaders[2]);
}

void MainMenu::remove(Game* g) {
	g->deleteObj(this);
}
