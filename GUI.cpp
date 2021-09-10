#include "game.h"
#include "GUI.h"

//IMGUI
#include<imgui/imconfig.h>
#include<imgui/imgui.h>
#include<imgui/imgui_impl_glfw_gl3.h>
#include<imgui/imgui_internal.h>

void GUI::createDebugMenu(GameObject& obj, string name, glm::vec3 orgPos, glm::vec3 orgRot, glm::vec3 orgScale) {
	{
		ImGui::Begin(name.c_str());

		bool resetScale = false;
		bool resetPos = false;
		bool resetRot = false;

		ImGui::Text("Mesh Controls");
		ImGui::Dummy(ImVec2(0.0f, 5.0f));
		ImGui::SliderFloat("Scale X", &obj.scale.x, 0.0f, 200.0f);
		ImGui::SliderFloat("Scale Y", &obj.scale.y, 0.0f, 200.0f);
		ImGui::SliderFloat("Scale Z", &obj.scale.z, 0.0f, 200.0f);

		if (ImGui::Button("Reset Scale"))
			resetScale = true;

		if (resetScale == true) {
			obj.scale = orgScale;
		}

		ImGui::Dummy(ImVec2(0.0f, 5.0f));

		ImGui::SliderFloat("Translation X", &obj.position.x, -200.0f, 200.0f);
		ImGui::SliderFloat("Translation Y", &obj.position.y, -200.0f, 200.0f);
		ImGui::SliderFloat("Translation Z", &obj.position.z, -200.0f, 200.0f);
		if (ImGui::Button("Reset Position"))
			resetPos = true;

		if (resetPos == true) {
			obj.position = orgPos;
		}

		ImGui::Dummy(ImVec2(0.0f, 5.0f));

		ImGui::SliderFloat("Rotation X", &obj.rotation.x, -360.0f, 360.0f);
		ImGui::SliderFloat("Rotation Y", &obj.rotation.y, -360.0f, 360.0f);
		ImGui::SliderFloat("Rotation Z", &obj.rotation.z, -360.0f, 360.0f);
		if (ImGui::Button("Reset Rotation"))
			resetRot = true;

		if (resetRot == true) {
			obj.rotation = orgRot;
		}


		ImGui::Dummy(ImVec2(0.0f, 5.0f));
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

		ImGui::End();
	}
}

void GUI::createDebugMenu(Game* g) {
	static int control = 1;
	ImGui::Begin("Settings");
	if (ImGui::Button(g->debugPause ? "Play" : "Pause")) {
		g->debugPause = !g->debugPause;
		if (!g->debugPause) // if unpausing
			g->lastTime = glfwGetTime();
	}

	if (g->debugPause) {
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