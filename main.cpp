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
#include"Particles.h"
#include"Powerup.h"
#include"Screen.h"

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
	srand(time(NULL));

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Specifying OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //Using core porfile (just modern libraries)


	//Face normals are perpendicular to a surface of one triangle while vertex normals are projected from each vertex
	//Face normals = flat shading, vertex normals = smooth shading. we're gonna use face normals

	//Had to remake this whole thing 
	Vertex vertices[] =
	{//     CO-ORDINATES                     /        COLOURS               /         TEXTURE CO-ORDS  /                NORMALS   //
		Vertex{glm::vec3(-0.5f, -0.5f, 0.0f),  glm::vec3(1.0f, 1.0f, 1.0f),  glm::vec3(0.0f, -1.0f, 0.0f),          glm::vec2(0.0f, 0.0f)},
		Vertex{glm::vec3(-0.5f, 0.5f, 0.0f),  glm::vec3(1.0f, 1.0f, 1.0f),   glm::vec3(0.0f, -1.0f, 0.0f),        glm::vec2(0.0f, 1.0f)},
		Vertex{glm::vec3(0.5f, 0.5f, 0.0f),   glm::vec3(1.0f, 1.0f, 1.0f),   glm::vec3(0.0f, -1.0f, 0.0f),        glm::vec2(1.0f, 1.0f)},
		Vertex{glm::vec3(0.5f, -0.5f, 0.0f),    glm::vec3(1.0f, 1.0f, 1.0f),    glm::vec3(0.0f, -1.0f, 0.0f),       glm::vec2(1.0f, 0.0f)}

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
		Texture("white.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE)
		//-------------------------------------------------
	};
	g.textures.push_back(textures);

	Texture circle[]{
		Texture("ballAlt.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE)
	};
	g.textures.push_back(circle);

	Texture particle[]{
		Texture("particle.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE)
	};
	g.textures.push_back(particle);

	Texture particleBU[]{
		Texture("ParticleBU.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE)
	};
	g.textures.push_back(particleBU);

	Texture particleBD[]{
		Texture("particleBD.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE)
	};
	g.textures.push_back(particleBD);

	Texture barTex[]{
		Texture("barrier.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE)
	};

	Texture pad1Tex[]{
		Texture("paddleB.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE)
	};

	Texture pad2Tex[]{
		Texture("paddleP.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE)
	};

	Texture ballPlus[]{
		Texture("BallPlus.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE)
	};

	Texture paddlePlus[]{
		Texture("PaddlePlus.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE)
	};

	Texture paddleMinus[]{
		Texture("PaddleMinus.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE)
	};

	Texture butterFingers[]{
		Texture("ButterFingers.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE)
	};

	Texture ultraSmash[]{
		Texture("UltraSmash.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE)
	};

	//Creates shadeprogram from default.vert and default.frag
	Shader shaderProgram("Default.vert", "default.frag");

	std::vector <Vertex> sqrverts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	g.vertVec.push_back(sqrverts);

	std::vector <GLuint> sqrinds(indices, indices + sizeof(indices) / sizeof(GLuint));
	g.indexVec.push_back(sqrinds);

	std::vector <Texture> defaultTex(textures, textures + sizeof(textures) / sizeof(Texture));
	g.texturesVec.push_back(defaultTex);

	std::vector <Vertex> ballsverts(ballvert, ballvert + sizeof(ballvert) / sizeof(Vertex));
	g.vertVec.push_back(ballsverts);

	std::vector <GLuint> ballinds(ballindices, ballindices + sizeof(ballindices) / sizeof(GLuint));
	g.indexVec.push_back(ballinds);

	std::vector <Texture> ballTex(circle, circle + sizeof(circle) / sizeof(Texture));
	g.texturesVec.push_back(ballTex);

	std::vector <Texture> particleTex(particle, particle + sizeof(particle) / sizeof(Texture));
	g.texturesVec.push_back(particleTex);

	std::vector <Texture> paddle1Tex(pad1Tex, pad1Tex + sizeof(pad1Tex) / sizeof(Texture));
	g.texturesVec.push_back(paddle1Tex);

	std::vector <Texture> paddle2Tex(pad2Tex, pad2Tex + sizeof(pad2Tex) / sizeof(Texture));
	g.texturesVec.push_back(paddle2Tex);

	std::vector <Texture> barrierTex(barTex, barTex + sizeof(barTex) / sizeof(barTex));
	g.texturesVec.push_back(barrierTex);

	std::vector <Texture> ballplusTex(ballPlus, ballPlus + sizeof(ballPlus) / sizeof(Texture));
	g.texturesVec.push_back(ballplusTex);

	std::vector <Texture> paddleplusTex(paddlePlus, paddlePlus + sizeof(paddlePlus) / sizeof(Texture));
	g.texturesVec.push_back(paddleplusTex);

	std::vector <Texture> paddleminusTex(paddleMinus, paddleMinus + sizeof(paddleMinus) / sizeof(Texture));
	g.texturesVec.push_back(paddleminusTex);

	std::vector <Texture> butterfingersTex(butterFingers, butterFingers + sizeof(butterFingers) / sizeof(Texture));
	g.texturesVec.push_back(butterfingersTex);

	std::vector <Texture> ultrasmashTex(ultraSmash, ultraSmash + sizeof(ultraSmash) / sizeof(Texture));
	g.texturesVec.push_back(ultrasmashTex);

	g.shaders.push_back(&shaderProgram);
	
	
	

	Shader lightShader("light.vert", "light.frag");
	//GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale"); //get uniform reference value (stored in uniID)
	

	//-----------------------------Lights------------------------------------------------------------------
	std::vector <Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
	std::vector <GLuint> lightInd(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));
	g.shaders.push_back(&lightShader);

	//-----------------------------Lights------------------------------------------------------------------
	Light directLight(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 50.0f, 150.0f));
	directLight.mesh = Mesh(lightVerts, lightInd, defaultTex);
	g.lights.push_back(&directLight);
	g.gameObjects.push_back(&directLight);



	//------------------------------TEXT-------------------------------------------------------------------
	Shader fShader("font.vert", "font.frag");
	g.shaders.push_back(&fShader);

	Shader particleShader("particles.vert", "particles.frag");
	g.shaders.push_back(&particleShader);


	//--------------------------------------------MESH-----------------------------------------------------

	//--------------Paddle1---------------------------------
	Paddle paddle1(glm::vec3(-0.85f, 0.0f, 0.0f) * 100.0f, glm::vec3(0.015f, 0.2f, 0.0f) * 100.0f, Paddle::CONTROLTYPE::WASD, glm::vec3(0.0f));
	paddle1.mesh = Mesh(sqrverts, sqrinds, paddle1Tex);
	g.paddles.push_back(&paddle1);
	g.gameObjects.push_back(&paddle1);
	//--------------Paddle1---------------------------------

	//--------------Paddle2---------------------------------
	Paddle paddle2(glm::vec3(0.85f, 0.0f, 0.0f) * 100.0f, glm::vec3(0.015f, 0.2f, 0.0f) * 100.0f, Paddle::CONTROLTYPE::ARROW, glm::vec3(0.0f));
	paddle2.mesh = Mesh(sqrverts, sqrinds, paddle2Tex);
	g.paddles.push_back(&paddle2);
	g.gameObjects.push_back(&paddle2);
	//--------------Paddle2---------------------------------

	//--------------BarrierUp-------------------------------
	Barrier BarrierBU(glm::vec3(0.0f, 1.02f, 0.0f) * 100.0f, glm::vec3(2.0f, 0.05f, 1.0f) * 100.0f);
	BarrierBU.mesh = Mesh(sqrverts, sqrinds, barrierTex);
	g.barriers.push_back(&BarrierBU);
	g.gameObjects.push_back(&BarrierBU);
	//--------------BarrierUp-------------------------------

	//--------------BarrierDown-------------------------------
	Barrier BarrierBD(glm::vec3(0.0f, -1.02f, 0.0f) * 100.0f, glm::vec3(2.0f, 0.05f, 1.0f) * 100.0f);
	BarrierBD.mesh = Mesh(sqrverts, sqrinds, barrierTex);
	g.barriers.push_back(&BarrierBD);
	g.gameObjects.push_back(&BarrierBD);
	//--------------BarrierDown-------------------------------

	Barrier BarrierER(glm::vec3(1.0f, 0.0f, 0.0f) * 100.0f, glm::vec3(0.0f, 2.0f, 0.0f) * 100.0f);
	BarrierER.mesh = Mesh(sqrverts, sqrinds, defaultTex);
	g.barriers.push_back(&BarrierER);
	g.gameObjects.push_back(&BarrierER);

	//--------------BALL--------------------------------------
	Ball ball1(glm::vec3(-0.02f, 0.0f, 0.0f) * 100.0f, glm::vec3(0.096f, 0.191f, 1.0f) * 100.0f, 2.5, glm::vec3(-65.0f, rand() / 10000.0f, 0.0f));
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

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 100.0f));
	g.cameras.push_back(&camera);
	g.gameObjects.push_back(&camera);

	//---------------------------TEXT----------------------------
	Font font;
	font.initFont("NexaBold.ttf");
	g.fonts.push_back(&font);

	Font font2;
	font2.initFont("chargen.ttf"); //Temporary Fix, still trying a multitude of solutions.
	g.fonts.push_back(&font2);

	gameFont score1(glm::vec3(200.0f, 150.0f, 0.0f));
	g.texts.push_back(&score1);

	gameFont score2(glm::vec3(1650.0f, 150.0f, 0.0f));
	g.texts.push_back(&score2);

	miscFont miscFont;
	g.miscfonts.push_back(&miscFont);

	//---------------------------TEXT----------------------------

	//----------------------PARTICLE SYSTEM---------------------
	ParticleSystem PS(g.textures[2]);
	g.particleSystems.push_back(&PS);

	ParticleSystem BPS(g.textures[3]);
	g.particleSystems.push_back(&BPS);

	ParticleSystem BDPS(g.textures[4]);
	g.particleSystems.push_back(&BDPS);

	
	ParticleSystem EPS(g.textures[2]);
	g.particleSystems.push_back(&EPS);
	//----------------------PARTICLE SYSTEM---------------------

	PowerupSpawn PowerS;
	g.PowerupSpawner.push_back(&PowerS);
	g.gameObjects.push_back(&PowerS);

	//----------------------PARTICLE SYSTEM---------------------

	ScreenHandler MenuHandler(ScreenHandler::SCREENTYPE::MAIN);
	MenuHandler.MenuInit(&g);
	//----------------------MENU HANDLER---------------------

	while (!glfwWindowShouldClose(window)) {

		glClearColor(0.0f, 0.0f, 0.01f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		g.drawScreen();


		//IMGUI
		ImGui_ImplGlfwGL3_NewFrame();


		//---------------------------DEBUG----------------------------------
		GUI::createDebugMenu(paddle1, "Debug Paddle 1", glm::vec3(-0.75f, 0.0f, 0.0f), VEC3_ZERO, glm::vec3(0.015f, 0.2f, 1.0f));
		GUI::createDebugMenu(paddle2, "Debug Paddle 2", glm::vec3(0.75f, 0.0f, 0.0f), VEC3_ZERO, glm::vec3(0.015f, 0.2f, 1.0f));
		GUI::createDebugMenu(ball1, "Debug Ball", glm::vec3(-0.02f, 0.0f, 0.0f), VEC3_ZERO, glm::vec3(0.096f, 0.191f, 1.0f));
		GUI::createDebugMenu(BarrierBU, "Debug Barrier Up", glm::vec3(0.0f, 0.85f, 0.0f), VEC3_ZERO, glm::vec3(1.7f, 0.05f, 1.0f));
		GUI::createDebugMenu(BarrierBD, "Debug Barrier Bottom", glm::vec3(0.0f, -0.85f, 0.0f), VEC3_ZERO, glm::vec3(1.7f, 0.05f, 1.0f));
		GUI::createDebugMenu(camera, "Camera", glm::vec3(0.0f, -0.85f, 0.0f), VEC3_ZERO, glm::vec3(1.7f, 0.05f, 1.0f));
		GUI::createDebugMenu(directLight, "Light", VEC3_ZERO, VEC3_ZERO, VEC3_ZERO);
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
	particleShader.Delete();
	//-----------------------------


	glfwDestroyWindow(window); //killing the window after we finish

	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate(); //terminating glfw after function
	return 0;
}