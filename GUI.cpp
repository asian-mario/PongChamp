#include "game.h"
#include "GUI.h"

//IMGUI
#include<imgui/imconfig.h>
#include<imgui/imgui.h>
#include<imgui/imgui_impl_glfw_gl3.h>
#include<imgui/imgui_internal.h>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>


#define VEC3_ZERO glm::vec3(0.0f)

void GUI::createDebugMenu( GOList* obj, string name, glm::vec3 orgPos, glm::vec3 orgRot, glm::vec3 orgScale) { //name has to match the same name in the GOList map
	{
		GameObject* objDebug = obj->GOList.at(name);
		ImGui::Begin(name.c_str());

		bool resetScale = false;
		bool resetPos = false;
		bool resetRot = false;

		ImGui::Text("Mesh Controls");
		ImGui::Dummy(ImVec2(0.0f, 5.0f));
		ImGui::SliderFloat("Scale X", &objDebug->scale.x, 0.0f, 200.0f);
		ImGui::SliderFloat("Scale Y", &objDebug->scale.y, 0.0f, 200.0f);
		ImGui::SliderFloat("Scale Z", &objDebug->scale.z, 0.0f, 200.0f);

		if (ImGui::Button("Reset Scale"))
			resetScale = true;

		if (resetScale == true) {
			objDebug->scale = orgScale;
		}

		ImGui::Dummy(ImVec2(0.0f, 5.0f));

		ImGui::SliderFloat("Translation X", &objDebug->position.x, -200.0f, 200.0f);
		ImGui::SliderFloat("Translation Y", &objDebug->position.y, -200.0f, 200.0f);
		ImGui::SliderFloat("Translation Z", &objDebug->position.z, -200.0f, 200.0f);
		if (ImGui::Button("Reset Position"))
			resetPos = true;

		if (resetPos == true) {
			objDebug->position = orgPos;
		}

		ImGui::Dummy(ImVec2(0.0f, 5.0f));

		ImGui::SliderFloat("Rotation X", &objDebug->rotation.x, -360.0f, 360.0f);
		ImGui::SliderFloat("Rotation Y", &objDebug->rotation.y, -360.0f, 360.0f);
		ImGui::SliderFloat("Rotation Z", &objDebug->rotation.z, -360.0f, 360.0f);
		if (ImGui::Button("Reset Rotation"))
			resetRot = true;

		if (resetRot == true) {
			objDebug->rotation = orgRot;
		}


		ImGui::Dummy(ImVec2(0.0f, 5.0f));
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

		ImGui::End();
	}
}

void GUI::createDebugMenu(Game* g) {
	static int control = 1;
	ImGui::Begin("Settings");
	if (ImGui::Button(g->pause ? "Play" : "Pause")) {
		g->pause = !g->pause;
		if (!g->pause) // if unpausing
			g->lastTime = glfwGetTime();
	}

	if (g->pause) {
		ImGui::Dummy(ImVec2(0.0f, 5.0f));

		ImGui::SliderInt("Frames", &control, 1, 120);
		ImGui::Dummy(ImVec2(0.0f, 5.0f));
		if (ImGui::Button("Framestep")) {
			g->lastTime = glfwGetTime();
			g->framestep = control;
		}
	}

	ImGui::End();
}

void GUI::onClickDebug(Game* g) {
	if (g->ScreenHandler[0]->screen == ScreenHandler::SCREENTYPE::GAME) {
		int state = glfwGetMouseButton(g->gameWindow, GLFW_MOUSE_BUTTON_LEFT);

		g->ScreenObject[0]->getCursorPosition(g);
		g->ScreenObject[0]->screenToWorldCord();


		if (state == GLFW_PRESS) {
			for (GameObject* o : g->gameObjects) {
				bool mouseIntersect = g->ScreenObject[0]->collisionBB(g, o);
				if (o->name != "") {
					if (mouseIntersect == true) {
						g->ScreenHandler[0]->renderDebugScreen = true;
						g->ScreenHandler[0]->currentDebugObj = o->name;
					}
				}
			}

		}
	}
}