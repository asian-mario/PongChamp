#define _USE_MATH_DEFINES

#include<iostream>
#include<stdlib.h>
#include <Windows.h>

#include<glad/glad.h>
#include<stb/stb_image.h>
#include "ROML.h"
#include"GameObject.h"
#include"game.h"
#include"Mesh.h"
#include"Paddle.h"
#include"light.h"
#include"Ball.h"
#include"Barrier.h"
#include"GUI.h"
#include"font.h"
#include"gameFont.h"

#include <chrono>
#include <cmath>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>



//IMGUI
#include<imgui/imconfig.h>
#include<imgui/imgui.h>
#include<imgui/imgui_impl_glfw_gl3.h>
#include<imgui/imgui_internal.h>


#define VEC3_ZERO glm::vec3(0.0f)

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
	Game g;
	auto monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

	GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "OpenPong", NULL, NULL);
	g.gameWindow = window;
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
	g.shaders.push_back(&shaderProgram);
	
	
	

	Shader lightShader("light.vert", "light.frag");
	//GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale"); //get uniform reference value (stored in uniID)
	

	//-----------------------------Lights------------------------------------------------------------------
	std::vector <Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
	std::vector <GLuint> lightInd(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));
	g.shaders.push_back(&lightShader);

	//-----------------------------Lights------------------------------------------------------------------
	Light directLight(glm::vec4(10.0f, 10.0f, 10.0f, 10.0f) * 100.0f, glm::vec3(0.0f, 0.5f, 1.5f));
	directLight.mesh = Mesh(lightVerts, lightInd, defaultTex);
	g.lights.push_back(&directLight);
	g.gameObjects.push_back(&directLight);

	//------------------------------TEXT-------------------------------------------------------------------
	Shader fShader("font.vert", "font.frag");
	g.shaders.push_back(&fShader);


	//--------------------------------------------MESH-----------------------------------------------------

	//--------------Paddle1---------------------------------
	Paddle paddle1(glm::vec3(-0.85f, 0.0f, 0.0f) * 100.0f, glm::vec3(0.015f, 0.2f, 0.0f) * 100.0f, Paddle::CONTROLTYPE::WASD, glm::vec3(0.0f));
	paddle1.mesh = Mesh(sqrverts, sqrinds, defaultTex);
	g.paddles.push_back(&paddle1);
	g.gameObjects.push_back(&paddle1);
	//--------------Paddle1---------------------------------

	//--------------Paddle2---------------------------------
	Paddle paddle2(glm::vec3(0.85f, 0.0f, 0.0f) * 100.0f, glm::vec3(0.015f, 0.2f, 0.0f) * 100.0f, Paddle::CONTROLTYPE::ARROW, glm::vec3(0.0f));
	paddle2.mesh = Mesh(sqrverts, sqrinds, defaultTex);
	g.paddles.push_back(&paddle2);
	g.gameObjects.push_back(&paddle2);
	//--------------Paddle2---------------------------------

	//--------------BarrierUp-------------------------------
	Barrier BarrierBU(glm::vec3(0.0f, 1.02f, 0.0f) * 100.0f, glm::vec3(2.0f, 0.05f, 1.0f) * 100.0f);
	BarrierBU.mesh = Mesh(sqrverts, sqrinds, defaultTex);
	g.barriers.push_back(&BarrierBU);
	g.gameObjects.push_back(&BarrierBU);
	//--------------BarrierUp-------------------------------

	//--------------BarrierDown-------------------------------
	Barrier BarrierBD(glm::vec3(0.0f, -1.02f, 0.0f) * 100.0f, glm::vec3(2.0f, 0.05f, 1.0f) * 100.0f);
	BarrierBD.mesh = Mesh(sqrverts, sqrinds, defaultTex);
	g.barriers.push_back(&BarrierBD);
	g.gameObjects.push_back(&BarrierBD);
	//--------------BarrierDown-------------------------------

	//--------------BALL--------------------------------------
	Ball ball1(glm::vec3(-0.02f, 0.0f, 0.0f) * 100.0f, glm::vec3(0.096f, 0.191f, 1.0f) * 100.0f, glm::vec3(-65.0f, rand() / 10000.0f, 0.0f));
	ball1.mesh = Mesh(ballsverts, ballinds, ballTex);
	g.balls.push_back(&ball1);
	g.gameObjects.push_back(&ball1);
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

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 10.0f));
	g.cameras.push_back(&camera);
	g.gameObjects.push_back(&camera);

	//---------------------------TEXT----------------------------
	Font font;
	font.initFont("chargen.ttf");
	g.fonts.push_back(&font);

	gameFont score1(glm::vec3(200.0f, 150.0f, 0.0f));
	g.texts.push_back(&score1);

	gameFont score2(glm::vec3(1650.0f, 150.0f, 0.0f));
	g.texts.push_back(&score2);


	//---------------------------TEXT----------------------------

	while (!glfwWindowShouldClose(window)) {

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if (!g.pause || g.framestep > 0) {
			g.update();
			g.framestep--;
		}

		
		
		//Exporting data & Render
		g.draw();
		//---------------------------------------------------------------------------------------------------------------------------------
		//Updates and exports camera matrix to the vert shader
		camera.updateMatrix(45.0f, 0.0f, 500.0f);

		//------------------------TEXT (NOTE: IMPLEMENT IN G.DRAW())----------------------------------------
		fShader.Activate();


		int w, h;
		glfwGetWindowSize(window, &w, &h);
		glm::mat4 orthoP = roml::createOrto(0.0f, (float)w, (float)h, 0.0f);
		glUniformMatrix4fv(glGetUniformLocation(fShader.ID, "ModViewProj"), 1, GL_FALSE, &orthoP[0][0]);
		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);

		score1.update(&g, window);
		score2.update(&g, window);

		font.drawString(g.texts[0]->pos.x, g.texts[0]->pos.y, g.texts[0]->text, &fShader);
		font.drawString(g.texts[1]->pos.x, g.texts[1]->pos.y, g.texts[1]->text, &fShader);


		

		//------------------------TEXT (NOTE: IMPLEMENT IN G.DRAW())----------------------------------------

		//IMGUI
		ImGui_ImplGlfwGL3_NewFrame();


		//---------------------------DEBUG----------------------------------
		GUI::createDebugMenu(paddle1, "Debug Paddle 1", glm::vec3(-0.75f, 0.0f, 0.0f), VEC3_ZERO, glm::vec3(0.015f, 0.2f, 1.0f));
		GUI::createDebugMenu(paddle2, "Debug Paddle 2", glm::vec3(0.75f, 0.0f, 0.0f), VEC3_ZERO, glm::vec3(0.015f, 0.2f, 1.0f));
		GUI::createDebugMenu(ball1, "Debug Ball", glm::vec3(-0.02f, 0.0f, 0.0f), VEC3_ZERO, glm::vec3(0.096f, 0.191f, 1.0f));
		GUI::createDebugMenu(BarrierBU, "Debug Barrier Up", glm::vec3(0.0f, 0.85f, 0.0f), VEC3_ZERO, glm::vec3(1.7f, 0.05f, 1.0f));
		GUI::createDebugMenu(BarrierBD, "Debug Barrier Bottom", glm::vec3(0.0f, -0.85f, 0.0f), VEC3_ZERO, glm::vec3(1.7f, 0.05f, 1.0f));
		GUI::createDebugMenu(camera, "Camera", glm::vec3(0.0f, -0.85f, 0.0f), VEC3_ZERO, glm::vec3(1.7f, 0.05f, 1.0f));
		GUI::createDebugMenu(&g);
		//-------------------------------------DEBUG----------------------------------------------




		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents(); //this is to make the window actually, respond.


	}
	

	//------Delete-----------------
	shaderProgram.Delete();
	lightShader.Delete();
	fShader.Delete();
	//-----------------------------


	glfwDestroyWindow(window); //killing the window after we finish

	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate(); //terminating glfw after function
	return 0;
}