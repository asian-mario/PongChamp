#include "GUI.h"

//IMGUI
#include<imgui/imconfig.h>
#include<imgui/imgui.h>
#include<imgui/imgui_impl_glfw_gl3.h>
#include<imgui/imgui_internal.h>

void GUI::createDebugMenu(Paddle pad, string name) {
	{
		ImGui::Begin(name.c_str());

		bool resetScale = false;
		bool resetPos = false;
		bool resetRot = false;

		ImGui::Text("Mesh Controls");
		ImGui::Dummy(ImVec2(0.0f, 5.0f));
		ImGui::SliderFloat("Scale X", &pad.scale.x, 0.0f, 10.0f);
		ImGui::SliderFloat("Scale Y", &pad.scale.y, 0.0f, 10.0f);
		ImGui::SliderFloat("Scale Z", &pad.scale.z, 0.0f, 10.0f);

		if (ImGui::Button("Reset Scale"))
			resetScale = true;

		if (resetScale == true) {
			pad.scale.x = 0.015f;
			pad.scale.y = 0.2f;
			pad.scale.z = 1.0f;
		}

		ImGui::Dummy(ImVec2(0.0f, 5.0f));

		ImGui::SliderFloat("Translation X", &pad.position.x, -10.0f, 10.0f);
		ImGui::SliderFloat("Translation Y", &pad.position.y, -10.0f, 10.0f);
		ImGui::SliderFloat("Translation Z", &pad.position.z, -10.0f, 10.0f);
		if (ImGui::Button("Reset Position"))
			resetPos = true;

		if (resetPos == true) {
			pad.position = glm::vec3(-0.75f, 0.0f, 0.0f);
		}

		ImGui::Dummy(ImVec2(0.0f, 5.0f));

		ImGui::SliderFloat("Rotation X", &pad.rotation.x, -90.0f, 90.0f);
		ImGui::SliderFloat("Rotation Y", &pad.rotation.y, -90.0f, 90.0f);
		ImGui::SliderFloat("Rotation Z", &pad.rotation.z, -90.0f, 90.0f);
		if (ImGui::Button("Reset Rotation"))
			resetRot = true;

		if (resetRot == true) {
			pad.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
		}


		ImGui::Dummy(ImVec2(0.0f, 5.0f));
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

		ImGui::End();
	}
}

void GUI::createDebugMenu(Ball ball, string name) {
	{
		ImGui::Begin(name.c_str());

		bool resetScale = false;
		bool resetPos = false;

		ImGui::Dummy(ImVec2(0.0f, 5.0f));
		ImGui::SliderFloat("Scale X", &ball.scale.x, 0.0f, 10.0f);
		ImGui::SliderFloat("Scale Y", &ball.scale.y, 0.0f, 10.0f);
		ImGui::SliderFloat("Scale Z", &ball.scale.z, 0.0f, 10.0f);
		if (ImGui::Button("Reset Scale"))
			resetScale = true;

		if (resetScale == true) {
			ball.scale = glm::vec3(0.096f, 0.191f, 1.0f);
		}

		ImGui::Dummy(ImVec2(0.0f, 5.0f));

		ImGui::SliderFloat("Translation X", &ball.position.x, -10.0f, 10.0f);
		ImGui::SliderFloat("Translation Y", &ball.position.y, -10.0f, 10.0f);
		ImGui::SliderFloat("Translation Z", &ball.position.z, -10.0f, 10.0f);
		if (ImGui::Button("Reset Position"))
			resetPos = true;

		if (resetPos == true) {
			ball.position = glm::vec3(0.0f, 0.0f, 0.0f);
		}


		ImGui::Dummy(ImVec2(0.0f, 5.0f));

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}
}

void GUI::createDebugMenu(Barrier bar, string name) {
	{
	ImGui::Begin(name.c_str());

	bool resetScale = false;
	bool resetPos = false;
	ImGui::Text("Barrier");
	ImGui::Dummy(ImVec2(0.0f, 5.0f));
	ImGui::SliderFloat("Scale X", &bar.scale.x, 0.0f, 10.0f);
	ImGui::SliderFloat("Scale Y", &bar.scale.y, 0.0f, 10.0f);
	ImGui::SliderFloat("Scale Z", &bar.scale.z, 0.0f, 10.0f);

	if (ImGui::Button("Reset Scale"))
		resetScale = true;

	if (resetScale == true) {
		bar.scale = glm::vec3(1.7f, 0.05f, 1.0f);
	}

	ImGui::Dummy(ImVec2(0.0f, 5.0f));

	ImGui::SliderFloat("Translation X", &bar.position.x, -10.0f, 10.0f);
	ImGui::SliderFloat("Translation Y", &bar.position.y, -10.0f, 10.0f);
	ImGui::SliderFloat("Translation Z", &bar.position.z, -10.0f, 10.0f);
	if (ImGui::Button("Reset Position"))
		resetPos = true;

	if (resetPos == true) {
		bar.position = glm::vec3(0.0f, 0.0f, 0.0f);
	}

	ImGui::Dummy(ImVec2(0.0f, 5.0f));

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

	ImGui::End();
	}
}