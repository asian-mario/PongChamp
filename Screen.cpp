#include "Screen.h"

void Screen::getCursorPosition(Game* g) {
	glfwGetCursorPos(g->gameWindow, &xpos, &ypos);
}

ScreenHandler::ScreenHandler(SCREENTYPE screen) {
	this->screen = screen;
}

void ScreenHandler::ScreenInit(Game* g) {
	if (screen == PAUSE) {
		Screen* crntMenu = new PauseMenu();

		g->ScreenObject.push_back(crntMenu);
	}

	if (screen == MAIN) {
		Screen* crntMenu = new MainMenu();

		g->ScreenObject.push_back(crntMenu);
	}

	if (screen == GAME) {
		Screen* crntMenu = new GameScene();

		g->ScreenObject.push_back(crntMenu);
	}
}

void ScreenHandler::ScreenSwitch(SCREENTYPE screen) {
	this->screen = screen;

	if (screen == PAUSE) {
		
	}

	if (screen == MAIN) {
		
	}

	if (screen == GAME) {
		
	}
}


void PauseMenu::drawScreen(Game* g) {
	g->shaders[2]->Activate();

	int w, h;
	glfwGetWindowSize(g->gameWindow, &w, &h);
	glm::mat4 orthoP = roml::createOrto(0.0f, (float)w, (float)h, 0.0f);
	glUniformMatrix4fv(glGetUniformLocation(g->shaders[2]->ID, "ModViewProj"), 1, GL_FALSE, &orthoP[0][0]);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

	g->fonts[1]->drawString(750.0f, 150.0f, "PAUSED", g->shaders[2]);
	g->fonts[1]->drawString(100.0f, 350.0f, "PLAY", g->shaders[2]);
}

void PauseMenu::updateScreen(Game* g) {
	int state = glfwGetMouseButton(g->gameWindow, GLFW_MOUSE_BUTTON_LEFT);

	if (glfwGetKey(g->gameWindow, GLFW_KEY_P) == GLFW_PRESS) {
		remove(g);
		g->ScreenHandler[0]->ScreenSwitch(ScreenHandler::SCREENTYPE::GAME);
		g->ScreenHandler[0]->ScreenInit(g);
	}

	if (state == GLFW_PRESS)
	{
		g->ScreenObject[0]->getCursorPosition(g);
		cout << g->ScreenObject[0]->ypos << endl;

		if (g->ScreenObject[0]->xpos <= 379.0 && g->ScreenObject[0]->xpos >= 96.0 && g->ScreenObject[0]->ypos >= 272.0 && g->ScreenObject[0]->ypos <= 357.0) {
			remove(g);
			g->ScreenHandler[0]->ScreenSwitch(ScreenHandler::SCREENTYPE::GAME);
			g->ScreenHandler[0]->ScreenInit(g);
		}
	}

		
	
}

void PauseMenu::remove(Game* g) {
	g->removeScreen(this);
}

void MainMenu::drawScreen(Game* g) {
	g->shaders[2]->Activate();

	int w, h;
	glfwGetWindowSize(g->gameWindow, &w, &h);
	glm::mat4 orthoP = roml::createOrto(0.0f, (float)w, (float)h, 0.0f);
	glUniformMatrix4fv(glGetUniformLocation(g->shaders[2]->ID, "ModViewProj"), 1, GL_FALSE, &orthoP[0][0]);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

	g->fonts[1]->drawString(800.0f, 150.0f, "PLApla", g->shaders[2]);
}

void MainMenu::remove(Game* g) {
	g->removeScreen(this);
}

void GameScene::drawScreen(Game* g) {
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

void GameScene::updateScreen(Game* g) {
	if (glfwGetKey(g->gameWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		remove(g);
		g->ScreenHandler[0]->ScreenSwitch(ScreenHandler::SCREENTYPE::PAUSE);
		g->ScreenHandler[0]->ScreenInit(g);
	}
}

void GameScene::remove(Game* g) {
	g->removeScreen(this);
}
