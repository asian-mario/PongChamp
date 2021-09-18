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

	if (screen == GAME) {
		GameObject* crntMenu = new GameScreen();

		g.gameObjects.push_back(crntMenu);
	}
}

void MenuHandler::MenuSwitch(SCREENTYPE screen) {
	this->screen = screen;

	if (screen == PAUSE) {
		
	}

	if (screen == MAIN) {
		
	}

	if (screen == GAME) {
		
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

void GameScreen::screen(Game* g) {
	if (!g->debugPause || g->framestep > 0) {
		g->update();
		if (g->framestep > 0)
			g->framestep--;
	}

	//Exporting data & Render
	g->draw();
	//-----------------------------------------------------------------
	g->cameras[0]->updateMatrix(45.0f, 0.0f, 500.0f);

	//------------------------TEXT (NOTE: IMPLEMENT IN G.DRAW())----------------------------------------
	g->shaders[2]->Activate();



	int w, h;
	glfwGetWindowSize(g->gameWindow, &w, &h);
	glm::mat4 orthoP = roml::createOrto(0.0f, (float)w, (float)h, 0.0f);
	glUniformMatrix4fv(glGetUniformLocation(g->shaders[2]->ID, "ModViewProj"), 1, GL_FALSE, &orthoP[0][0]);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

	g->texts[0]->update(g, g->gameWindow);
	g->texts[1]->update(g, g->gameWindow);

	g->fonts[0]->drawString(g->texts[0]->pos.x, g->texts[0]->pos.y, g->texts[0]->text, g->shaders[2]);
	g->fonts[0]->drawString(g->texts[1]->pos.x, g->texts[1]->pos.y, g->texts[1]->text, g->shaders[2]);

	cout << g->balls[0]->limitSpeed << endl;
}

void GameScreen::remove(Game* g) {
	g->deleteObj(this);
}
