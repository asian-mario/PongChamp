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
		ImGui::SliderFloat("Scale X", &pad.scaleVec.x, 0.0f, 10.0f);
		ImGui::SliderFloat("Scale Y", &pad.scaleVec.y, 0.0f, 10.0f);
		ImGui::SliderFloat("Scale Z", &pad.scaleVec.z, 0.0f, 10.0f);

		if (ImGui::Button("Reset Scale"))
			resetScale = true;

		if (resetScale == true) {
			pad.scaleVec.x = 0.015f;
			pad.scaleVec.y = 0.2f;
			pad.scaleVec.z = 1.0f;
		}

		ImGui::Dummy(ImVec2(0.0f, 5.0f));

		ImGui::SliderFloat("Translation X", &pad.posVec.x, -10.0f, 10.0f);
		ImGui::SliderFloat("Translation Y", &pad.posVec.y, -10.0f, 10.0f);
		ImGui::SliderFloat("Translation Z", &pad.posVec.z, -10.0f, 10.0f);
		if (ImGui::Button("Reset Position"))
			resetPos = true;

		if (resetPos == true) {
			pad.posVec = glm::vec3(-0.75f, 0.0f, 0.0f);
		}

		ImGui::Dummy(ImVec2(0.0f, 5.0f));

		ImGui::SliderFloat("Rotation X", &pad.rotVec.x, -90.0f, 90.0f);
		ImGui::SliderFloat("Rotation Y", &pad.rotVec.y, -90.0f, 90.0f);
		ImGui::SliderFloat("Rotation Z", &pad.rotVec.z, -90.0f, 90.0f);
		if (ImGui::Button("Reset Rotation"))
			resetRot = true;

		if (resetRot == true) {
			pad.rotVec = glm::vec3(0.0f, 0.0f, 0.0f);
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


		if (ImGui::Button("Reset Scale"))
			resetScale = true;

		if (resetScale == true) {
			ball.scaleVec = glm::vec3(0.096f, 0.191f, 1.0f);
		}

		ImGui::Dummy(ImVec2(0.0f, 5.0f));

		ImGui::SliderFloat("Translation X", &ball.posVec.x, -10.0f, 10.0f);
		ImGui::SliderFloat("Translation Y", &ball.posVec.y, -10.0f, 10.0f);
		ImGui::SliderFloat("Translation Z", &ball.posVec.z, -10.0f, 10.0f);
		if (ImGui::Button("Reset Position"))
			resetPos = true;

		if (resetPos == true) {
			ball.posVec = glm::vec3(0.0f, 0.0f, 0.0f);
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
	ImGui::SliderFloat("Scale X", &bar.scaleVec.x, 0.0f, 10.0f);
	ImGui::SliderFloat("Scale Y", &bar.scaleVec.y, 0.0f, 10.0f);
	ImGui::SliderFloat("Scale Z", &bar.scaleVec.z, 0.0f, 10.0f);

	if (ImGui::Button("Reset Scale"))
		resetScale = true;

	if (resetScale == true) {
		bar.scaleVec = glm::vec3(1.7f, 0.05f, 1.0f);
	}

	ImGui::Dummy(ImVec2(0.0f, 5.0f));

	ImGui::SliderFloat("Translation X", &bar.posVec.x, -10.0f, 10.0f);
	ImGui::SliderFloat("Translation Y", &bar.posVec.y, -10.0f, 10.0f);
	ImGui::SliderFloat("Translation Z", &bar.posVec.z, -10.0f, 10.0f);
	if (ImGui::Button("Reset Position"))
		resetPos = true;

	if (resetPos == true) {
		bar.posVec = glm::vec3(0.0f, 0.0f, 0.0f);
	}

	ImGui::Dummy(ImVec2(0.0f, 5.0f));

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

	ImGui::End();
	}
}