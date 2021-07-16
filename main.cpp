#define _USE_MATH_DEFINES

#include<iostream>
#include<stdlib.h>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include"Mesh.h"
#include "ROML.h"
#include <chrono>
#include <cmath>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>

//IMGUI
#include<imgui/imconfig.h>
#include<imgui/imgui.h>
#include<imgui/imgui.cpp>
#include<imgui/imgui_demo.cpp>
#include<imgui/imgui_draw.cpp>
#include<imgui/imgui_impl_glfw_gl3.cpp>
#include<imgui/imgui_impl_glfw_gl3.h>
#include<imgui/imgui_internal.h>





using namespace std;

const unsigned int width = 1920;
const unsigned int height = 1080;

using seconds_t = std::chrono::seconds;

// return the same type as seconds.count() below does.
// note: C++14 makes this a lot easier.
decltype(seconds_t().count()) get_millis_since_epoch()
{
	// get the current time
	const auto now = chrono::system_clock::now();

	// transform the time into a duration since the epoch
	const auto epoch = now.time_since_epoch();

	// cast the duration into seconds
	const auto seconds = std::chrono::duration_cast<std::chrono::milliseconds>(epoch);

	// return the number of seconds
	return seconds.count();
}

bool circintersects(glm::vec3 circle, glm::vec3 rect, double circleRadius)
{
	return (pow(circleRadius, 2) - pow((rect.x - circle.x), 2)) >= 0;
}



int main() {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Specifying OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //Using core porfile (just modern libraries)

	//Face normals are perpendicular to a surface of one triangle while vertex normals are projected from each vertex
	//Face normals = flat shading, vertex normals = smooth shading. we're gonna use face normals

	//Had to remake this whole thing 
	Vertex vertices[] =
	{//     CO-ORDINATES                     /        COLOURS               /         TEXTURE CO-ORDS  /                NORMALS   //
		Vertex{glm::vec3(-0.5f, -0.5f, 0.0f),  glm::vec3(1.0f, 1.0f, 1.0f),  glm::vec3(0.0f, -1.0f, 0.0f),          glm::vec2(0.0f, 0.0f)},
		Vertex{glm::vec3(-0.5f, 0.5f, 0.0f),  glm::vec3(1.0f, 1.0f, 1.0f),   glm::vec3(0.0f, -1.0f, 0.0f),        glm::vec2(0.0f, 5.0f)},
		Vertex{glm::vec3(0.5f, 0.5f, 0.0f),   glm::vec3(1.0f, 1.0f, 1.0f),   glm::vec3(0.0f, -1.0f, 0.0f),        glm::vec2(5.0f, 5.0f)},
		Vertex{glm::vec3(0.5f, -0.5f, 0.0f),    glm::vec3(1.0f, 1.0f, 1.0f),    glm::vec3(0.0f, -1.0f, 0.0f),       glm::vec2(5.0f, 0.0f)}

	};

	//index buffer
	GLuint indices[] = {
		0, 2 ,1,
		0, 3, 2 

	};
	Vertex ballvert[] =
	{//     CO-ORDINATES                     /        COLOURS               /         TEXTURE CO-ORDS  /                NORMALS   //
		Vertex{glm::vec3(-0.1f, -0.1f, 0.0f),  glm::vec3(1.0f, 1.0f, 1.0f),  glm::vec3(0.0f, -1.0f, 0.0f),          glm::vec2(0.0f, 0.0f)},
		Vertex{glm::vec3(-0.1f, 0.1f, 0.0f),  glm::vec3(1.0f, 1.0f, 1.0f),   glm::vec3(0.0f, -1.0f, 0.0f),        glm::vec2(0.0f, 1.0f)},
		Vertex{glm::vec3(0.1f, 0.1f, 0.0f),   glm::vec3(1.0f, 1.0f, 1.0f),   glm::vec3(0.0f, -1.0f, 0.0f),        glm::vec2(1.0f, 1.0f)},
		Vertex{glm::vec3(0.1f, -0.1f, 0.0f),    glm::vec3(1.0f, 1.0f, 1.0f),    glm::vec3(0.0f, -1.0f, 0.0f),       glm::vec2(1.0f, 0.0f)}

	};

	//index buffer
	GLuint ballindices[] = {
		0, 2 ,1,
		0, 3, 2

	};



	//Making a cube that will be our light source
	Vertex lightVertices[] = {
		//   COORDINATES  //
		Vertex{glm::vec3(-0.1f, -0.1f, 0.1f)},
		Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
		Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},
		Vertex{glm::vec3(0.1f, -0.1f, 0.1f)},
		Vertex{glm::vec3(-0.1f, 0.1f, 0.1f)},
		Vertex{glm::vec3(-0.1f, 0.1f, -0.1f)},
		Vertex{glm::vec3(0.1f, 0.1f, -0.1f)},
		Vertex{glm::vec3(0.1f, 0.1f, 0.1f)}

	};

	GLuint lightIndices[] = {
		0, 1, 2,
		0, 2, 3,
		0, 4, 7,
		0, 7, 3,
		3, 7, 6,
		3, 6, 2,
		2, 6, 5,
		2, 5, 1,
		1, 5, 4,
		1, 4, 0,
		4, 5, 6,
		4, 6, 7
	};

	//------------------------------------------------------------------------------------------------

	auto monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

	GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "My Title", NULL, NULL);
	glfwSetWindowMonitor(window, NULL, 0, 0, mode->width, mode->height, mode->refreshRate);
	if (window == NULL) {
		cout << "Failed to create a window" << endl; //Just checking if the window failed to create
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window); //tells glfw to make the window to hold 'all' of opengl

	gladLoadGL(); //load the config for opengl

	glViewport(0, 0, width, height); //where we want the opengl to show stuff


	Texture textures[]{
		//----------TEXTURES-------------------------------
		Texture("white.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
		Texture("white.png", "specular", 1, GL_RED, GL_UNSIGNED_BYTE)
		//-------------------------------------------------
	};

	Texture circle[]{
		Texture("circle.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE)
	};


	//Creates shadeprogram from default.vert and default.frag
	Shader shaderProgram("Default.vert", "default.frag");
	std::vector <Vertex> sqrverts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	std::vector <GLuint> sqrinds(indices, indices + sizeof(indices) / sizeof(GLuint));
	std::vector <Texture> defaultTex(textures, textures + sizeof(textures) / sizeof(Texture));
	std::vector <Vertex> ballsverts(ballvert, ballvert + sizeof(ballvert) / sizeof(Vertex));
	std::vector <GLuint> ballinds(ballindices, ballindices + sizeof(ballindices) / sizeof(GLuint));
	std::vector <Texture> ballTex(circle, circle + sizeof(circle) / sizeof(Texture));
	Mesh pad1(sqrverts, sqrinds, defaultTex);
	Mesh pad2(sqrverts, sqrinds, defaultTex);
	Mesh barrierUp(sqrverts, sqrinds, defaultTex);
	Mesh barrierDown(sqrverts, sqrinds, defaultTex);
	Mesh ball(ballsverts, ballinds, ballTex);

	Shader lightShader("light.vert", "light.frag");
	//GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale"); //get uniform reference value (stored in uniID)
	GLuint timeID = glGetUniformLocation(shaderProgram.ID, "time");

	//-----------------------------Lights------------------------------------------------------------------
	std::vector <Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
	std::vector <GLuint> lightInd(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));
	Mesh light(lightVerts, lightInd, defaultTex); //The tex is just a placeholder
	//-----------------------------Lights------------------------------------------------------------------

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.0f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);

	//--------------------------------------------MESH-----------------------------------------------------

	//--------------Paddle1---------------------------------
	glm::vec3 scalepad = glm::vec3(0.015f, 0.2f, 1.0f);
	glm::vec3 rotpad = glm::vec3(0.0f, 0.0f, 0.0f);

	glm::vec3 padPos = glm::vec3(-0.75f, 0.0f, 0.0f); //X, Y, Z
	glm::mat4 padModel = glm::mat4(1.0f);

	//--------------Paddle1---------------------------------

	//--------------Paddle2---------------------------------
	glm::vec3 scalepad2 = glm::vec3(0.015f, 0.2f, 1.0f);
	glm::vec3 rotpad2 = glm::vec3(0.0f, 0.0f, 0.0f);

	glm::vec3 padPos2 = glm::vec3(0.75f, 0.0f, 0.0f); //X, Y, Z
	glm::mat4 padModel2 = glm::mat4(1.0f);
	//--------------Paddle2---------------------------------

	//--------------BarrierUp-------------------------------
	glm::vec3 scaleBU = glm::vec3(1.7f, 0.05f, 1.0f);

	glm::vec3 posBU = glm::vec3(0.0f, 0.85f, 0.0f); //X, Y, Z
	glm::mat4 modelBU = glm::mat4(1.0f);
	//--------------BarrierUp-------------------------------

	//--------------BarrierDown-------------------------------
	glm::vec3 scaleBD = glm::vec3(1.7f, 0.05f, 1.0f);

	glm::vec3 posBD = glm::vec3(0.0f, -0.85f, 0.0f); //X, Y, Z
	glm::mat4 modelBD = glm::mat4(1.0f);
	//--------------BarrierDown-------------------------------

	//--------------BALL--------------------------------------
	glm::vec3 scaleC = glm::vec3(0.096f, 0.191f, 1.0f);

	glm::vec3 posC = glm::vec3(-0.02f, 0.0f, 0.0f); //X, Y, Z
	glm::mat4 modelC = glm::mat4(1.0f);

	glm::vec3 ballSpeedVec = glm::vec3(0.0f);
	ballSpeedVec.x = -0.005f;
	//--------------BALL--------------------------------------

	//--------------------------------------------MESH-----------------------------------------------------

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
	glClear(GL_COLOR_BUFFER_BIT); //le execute with the color buffer
	glfwSwapBuffers(window);

	glEnable(GL_DEPTH_TEST); //fixes depth issues

	//GUI
	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(window, true);

	ImGui::StyleColorsDark();


	
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	while (!glfwWindowShouldClose(window)) {

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//---------------------------------------------------------------------------------------------------------------------------------
		lightModel = roml::translate(lightModel, lightPos);

		//-----------------------Paddle1 Control-----------------------------
		glm::mat4 Loc = roml::translate(glm::mat4(1.0f), padPos);
		glm::mat4 Soc = roml::scale(glm::mat4(1.0f), scalepad);

		glm::mat4 rotX = roml::rotate(glm::mat4(1.0f), roml::radians(rotpad.x), 'X');
		glm::mat4 rotY = roml::rotate(glm::mat4(1.0f), roml::radians(rotpad.y), 'Y');
		glm::mat4 rotZ = roml::rotate(glm::mat4(1.0f), roml::radians(rotpad.z), 'Z');
		glm::mat4 Rot = rotZ * rotY * rotX;
		padModel = Loc * Rot * Soc;
		//-----------------------Paddle1 Control-----------------------------

		//-----------------------Paddle2 Control----------------------------
		glm::mat4 Loc2 = roml::translate(glm::mat4(1.0f), padPos2);
		glm::mat4 Soc2 = roml::scale(glm::mat4(1.0f), scalepad2);

		glm::mat4 rotX2 = roml::rotate(glm::mat4(1.0f), roml::radians(rotpad2.x), 'X');
		glm::mat4 rotY2 = roml::rotate(glm::mat4(1.0f), roml::radians(rotpad2.y), 'Y');
		glm::mat4 rotZ2 = roml::rotate(glm::mat4(1.0f), roml::radians(rotpad2.z), 'Z');
		glm::mat4 Rot2 = rotZ2 * rotY2 * rotX2;
		padModel2 = Loc2 * Rot2 * Soc2;
		//-----------------------Paddle2 Control----------------------------

		//-----------------------BarrierUp Control--------------------------
		glm::mat4 LocB = roml::translate(glm::mat4(1.0f), posBU);
		glm::mat4 SocB = roml::scale(glm::mat4(1.0f), scaleBU);

		modelBU = LocB * SocB;
		//-----------------------BarrierUp Control--------------------------

		//-----------------------BarrierDown Control--------------------------
		glm::mat4 LocB2 = roml::translate(glm::mat4(1.0f), posBD);
		glm::mat4 SocB2 = roml::scale(glm::mat4(1.0f), scaleBD);

		modelBD = LocB2 * SocB2;
		//-----------------------BarrierUp Control--------------------------


		//-----------------------Ball--------------------------
		glm::mat4 LocBall = roml::translate(glm::mat4(1.0f), posC);
		glm::mat4 SocBall = roml::scale(glm::mat4(1.0f), scaleC);

		modelC = LocBall * SocBall;
		//-----------------------Ball--------------------------

		//Exporting data & Render
		lightShader.Activate();
		glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
		glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);

		shaderProgram.Activate();
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(padModel));
		glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		pad1.Draw(shaderProgram, camera);

		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(padModel2));
		glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		pad2.Draw(shaderProgram, camera);

		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelBU));
		glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		barrierUp.Draw(shaderProgram, camera);

		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelBD));
		glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		barrierDown.Draw(shaderProgram, camera);

		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelC));
		glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		ball.Draw(shaderProgram, camera);

		//---------------------------------------------------------------------------------------------------------------------------------
		//Updates and exports camera matrix to the vert shader
		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		//IMGUI
		ImGui_ImplGlfwGL3_NewFrame();

		//---------------DRAW------------------
		light.Draw(lightShader, camera);
		//---------------DRAW------------------

		//-------------------------------------COLLISION-----------------------------------------

		glm::vec3 padWorldPos = padModel * glm::vec4(padPos, 1.0f);
		glm::vec3 ballWorldPos = modelC * glm::vec4(posC, 1.0f);
		//float rad = 0.0702019f;
		float rad = 0.0004f;
		bool intersect = circintersects(ballWorldPos, padWorldPos, rad);

		

		if (intersect) {
			ballSpeedVec.x = -ballSpeedVec.x;
		}
		
		
		//-------------------------------------COLLISION-----------------------------------------
		
		posC += ballSpeedVec;


	//---------------------------DEBUG----------------------------------
		{
			ImGui::Begin("Debug Paddle 1");

			bool resetScale = false;
			bool resetPos = false;
			bool resetRot = false;
			ImGui::Text("Mesh Controls");
			ImGui::Dummy(ImVec2(0.0f, 5.0f));
			ImGui::SliderFloat("Scale X", &scalepad.x, 0.0f, 10.0f);
			ImGui::SliderFloat("Scale Y", &scalepad.y, 0.0f, 10.0f);
			ImGui::SliderFloat("Scale Z", &scalepad.z, 0.0f, 10.0f);

			if (ImGui::Button("Reset Scale"))
				resetScale = true;

			if (resetScale == true) {
				scalepad.x = 0.015f;
				scalepad.y = 0.2f;
				scalepad.z = 1.0f;
			}

			ImGui::Dummy(ImVec2(0.0f, 5.0f));

			ImGui::SliderFloat("Translation X", &padPos.x, -10.0f, 10.0f);
			ImGui::SliderFloat("Translation Y", &padPos.y, -10.0f, 10.0f);
			ImGui::SliderFloat("Translation Z", &padPos.z, -10.0f, 10.0f);
			if (ImGui::Button("Reset Position"))
				resetPos = true;

			if (resetPos == true) {
				padPos = glm::vec3(-0.75f, 0.0f, 0.0f);
			}

			ImGui::Dummy(ImVec2(0.0f, 5.0f));

			ImGui::SliderFloat("Rotation X", &rotpad.x, -90.0f, 90.0f);
			ImGui::SliderFloat("Rotation Y", &rotpad.y, -90.0f, 90.0f);
			ImGui::SliderFloat("Rotation Z", &rotpad.z, -90.0f, 90.0f);
			if (ImGui::Button("Reset Rotation"))
				resetRot = true;

			if (resetRot == true) {
				rotpad = glm::vec3(0.0f, 0.0f, 0.0f);
			}


			ImGui::Dummy(ImVec2(0.0f, 5.0f));
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

			ImGui::End();
		}

		{
			ImGui::Begin("Debug Paddle 2");

			bool resetScale = false;
			bool resetPos = false;
			bool resetRot = false;
			ImGui::Text("Mesh Controls");
			ImGui::Dummy(ImVec2(0.0f, 5.0f));
			ImGui::SliderFloat("Scale X", &scalepad2.x, 0.0f, 10.0f);
			ImGui::SliderFloat("Scale Y", &scalepad2.y, 0.0f, 10.0f);
			ImGui::SliderFloat("Scale Z", &scalepad2.z, 0.0f, 10.0f);

			if (ImGui::Button("Reset Scale"))
				resetScale = true;

			if (resetScale == true) {
				scalepad2.x = 0.015f;
				scalepad2.y = 0.2f;
				scalepad2.z = 1.0f;
			}

			ImGui::Dummy(ImVec2(0.0f, 5.0f));

			ImGui::SliderFloat("Translation X", &padPos2.x, -10.0f, 10.0f);
			ImGui::SliderFloat("Translation Y", &padPos2.y, -10.0f, 10.0f);
			ImGui::SliderFloat("Translation Z", &padPos2.z, -10.0f, 10.0f);
			if (ImGui::Button("Reset Position"))
				resetPos = true;

			if (resetPos == true) {
				padPos = glm::vec3(0.75f, 0.0f, 0.0f);
			}

			ImGui::Dummy(ImVec2(0.0f, 5.0f));

			ImGui::SliderFloat("Rotation X", &rotpad2.x, -90.0f, 90.0f);
			ImGui::SliderFloat("Rotation Y", &rotpad2.y, -90.0f, 90.0f);
			ImGui::SliderFloat("Rotation Z", &rotpad2.z, -90.0f, 90.0f);
			if (ImGui::Button("Reset Rotation"))
				resetRot = true;

			if (resetRot == true) {
				rotpad2 = glm::vec3(0.0f, 0.0f, 0.0f);
			}


			ImGui::Dummy(ImVec2(0.0f, 5.0f));
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

			ImGui::End();
		}

		{
			ImGui::Begin("Debug Barrier Up");

			bool resetScale = false;
			bool resetPos = false;
			ImGui::Text("Barrier");
			ImGui::Dummy(ImVec2(0.0f, 5.0f));
			ImGui::SliderFloat("Scale X", &scaleBU.x, 0.0f, 10.0f);
			ImGui::SliderFloat("Scale Y", &scaleBU.y, 0.0f, 10.0f);
			ImGui::SliderFloat("Scale Z", &scaleBU.z, 0.0f, 10.0f);

			if (ImGui::Button("Reset Scale"))
				resetScale = true;

			if (resetScale == true) {
				scaleBU = glm::vec3(1.7f, 0.05f, 1.0f);
			}

			ImGui::Dummy(ImVec2(0.0f, 5.0f));

			ImGui::SliderFloat("Translation X", &posBU.x, -10.0f, 10.0f);
			ImGui::SliderFloat("Translation Y", &posBU.y, -10.0f, 10.0f);
			ImGui::SliderFloat("Translation Z", &posBU.z, -10.0f, 10.0f);
			if (ImGui::Button("Reset Position"))
				resetPos = true;

			if (resetPos == true) {
				posBU = glm::vec3(0.0f, 0.0f, 0.0f);
			}

			ImGui::Dummy(ImVec2(0.0f, 5.0f));

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

			ImGui::End();
		}
		{
			ImGui::Begin("Debug Ball");

			bool resetScale = false;
			bool resetPos = false;
			bool intersect = circintersects(ballWorldPos, padWorldPos, rad);
			ImGui::Text("Ball");
			ImGui::Dummy(ImVec2(0.0f, 5.0f));
			ImGui::SliderFloat("Scale X", &scaleC.x, 0.0f, 10.0f);
			ImGui::SliderFloat("Scale Y", &scaleC.y, 0.0f, 10.0f);
			ImGui::SliderFloat("Scale Z", &scaleC.z, 0.0f, 10.0f);

			if (ImGui::Button("Reset Scale"))
				resetScale = true;

			if (resetScale == true) {
				scaleC = glm::vec3(0.096f, 0.191f, 1.0f);
			}

			ImGui::Dummy(ImVec2(0.0f, 5.0f));

			ImGui::SliderFloat("Translation X", &posC.x, -10.0f, 10.0f);
			ImGui::SliderFloat("Translation Y", &posC.y, -10.0f, 10.0f);
			ImGui::SliderFloat("Translation Z", &posC.z, -10.0f, 10.0f);
			if (ImGui::Button("Reset Position"))
				resetPos = true;

			if (resetPos == true) {
				posC = glm::vec3(0.0f, 0.0f, 0.0f);
			}

			ImGui::Dummy(ImVec2(0.0f, 5.0f));
			if (intersect == true) {
				ImGui::Text("Intersect: TRUE");
			}
			else if (intersect == false) {
				ImGui::Text("Intersect: FALSE");
			}

			ImGui::Dummy(ImVec2(0.0f, 5.0f));

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}
		//-------------------------------------DEBUG----------------------------------------------
		

		//-----------------------------------PAD 1 CONTROLS--------------------------------------
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			padPos.y += 0.01f;
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			padPos.y -= 0.01f;
		}
		//-----------------------------------PAD 1 CONTROLS--------------------------------------

		//-----------------------------------PAD 2 CONTROLS--------------------------------------
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
			padPos2.y += 0.01f;
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
			padPos2.y -= 0.01f;
		}
		//-----------------------------------PAD 2 CONTROLS--------------------------------------

		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents(); //this is to make the window actually, respond.
	}

	//------Delete-----------------
	shaderProgram.Delete();
	lightShader.Delete();
	//-----------------------------


	glfwDestroyWindow(window); //killing the window after we finish

	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate(); //terminating glfw after function
	return 0;
}