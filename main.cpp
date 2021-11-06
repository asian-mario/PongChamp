#define _USE_MATH_DEFINES

#include<iostream>
#include<stdlib.h>
#include <Windows.h>
#include <map>

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
#include"GOList.h"
#include"FBO.h"
#include"soundDevice.h"
#include"soundBuffer.h"
#include"soundSource.h"
#include"musicBuffer.h"

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

	float rectangleVertices[] =
	{
		// Coords    // texCoords
		 1.0f, -1.0f,  1.0f, 0.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		-1.0f,  1.0f,  0.0f, 1.0f,

		 1.0f,  1.0f,  1.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		-1.0f,  1.0f,  0.0f, 1.0f
	};

	//------------------------------------------------------------------------------------------------


	//------------------------------------------------------------------------------------------------
	Game g;
	auto monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	GOList ObjectList;
	g.OBJList.push_back(&ObjectList);

	soundDevice * sndDevice = soundDevice::get();
	g.soundDevice.push_back(sndDevice);

	//uint32_t = ALuint
	uint32_t sndHit = soundBuffer::get()->addSoundEffect("./Sounds/hit.wav");
	//this is fine for now. will make a map so it isnt as messy
	g.sounds.push_back(sndHit);

	uint32_t sndGoal = soundBuffer::get()->addSoundEffect("./Sounds/score.wav");
	g.sounds.push_back(sndGoal);

	uint32_t sndPowerup = soundBuffer::get()->addSoundEffect("./Sounds/powerup.wav");
	g.sounds.push_back(sndPowerup);


	soundSource crntSpeaker;
	g.soundSource.push_back(&crntSpeaker);

	musicBuffer bruhndertale("./Music/notUndertale.wav");

	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

	GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "PongChamp!", NULL, NULL);
	g.gameWindow = window;
	glfwSetWindowMonitor(window, NULL, 0, 0, mode->width, mode->height, mode->refreshRate);
	if (window == NULL) {
		cout << "Failed to create a window" << endl; //Just checking if the window failed to create
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window); //tells glfw to make the window to hold 'all' of opengl

	gladLoadGL(); //load the config for opengl

	glViewport(0, 0, g.screenWidth, g.screenHeight); //where we want the opengl to show stuff

	// Prepare framebuffer rectangle VBO and VAO
	GLuint rectVAO, rectVBO;
	glGenVertexArrays(1, &rectVAO);
	glGenBuffers(1, &rectVBO);
	glBindVertexArray(rectVAO);
	glBindBuffer(GL_ARRAY_BUFFER, rectVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleVertices), &rectangleVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	g.FBOBuffers.push_back(rectVAO);
	g.FBOBuffers.push_back(rectVBO);

	Texture textures[]{
		//----------TEXTURES-------------------------------
		Texture("white.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE)
		//-------------------------------------------------
	};
	g.textures.push_back(textures);
	g.texWithBloom.push_back(textures);

	Texture circle[]{
		Texture("ballAlt.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE)
	};
	g.textures.push_back(circle);
	g.texWithBloom.push_back(circle);

	Texture particle[]{
		Texture("particle.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE)
	};
	g.textures.push_back(particle);
	g.texWithBloom.push_back(particle);

	Texture particleBU[]{
		Texture("ParticleBU.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE)
	};
	g.textures.push_back(particleBU);
	g.texWithBloom.push_back(particleBU);

	Texture particleBD[]{
		Texture("particleBD.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE)
	};
	g.textures.push_back(particleBD);
	g.texWithBloom.push_back(particleBD);

	Texture barTex[]{
		Texture("barrier.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE)
	};
	g.textures.push_back(barTex);
	g.texWithBloom.push_back(barTex);

	Texture pad1Tex[]{
		Texture("paddleB.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE)
	};
	g.textures.push_back(pad1Tex);
	g.texWithBloom.push_back(pad1Tex);

	Texture pad2Tex[]{
		Texture("paddleP.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE)
	};
	g.textures.push_back(pad2Tex);
	g.texWithBloom.push_back(pad2Tex);

	Texture ballPlus[]{
		Texture("BallPlus.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE)
	};
	g.textures.push_back(ballPlus);

	Texture paddlePlus[]{
		Texture("PaddlePlus.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE)
	};
	g.textures.push_back(paddlePlus);

	Texture paddleMinus[]{
		Texture("PaddleMinus.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE)
	};
	g.textures.push_back(paddleMinus);

	Texture butterFingers[]{
		Texture("ButterFingers.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE)
	};
	g.textures.push_back(butterFingers);

	Texture ultraSmash[]{
		Texture("UltraSmash.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE)
	};
	g.textures.push_back(ultraSmash);

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
	Light directLight(glm::vec4(1.0f, 1.0f, 1.0f, 4.0f), glm::vec3(0.0f, 50.0f, 150.0f));
	directLight.mesh = Mesh(lightVerts, lightInd, defaultTex);
	g.lights.push_back(&directLight);
	g.gameObjects.push_back(&directLight);



	//------------------------------TEXT-------------------------------------------------------------------
	Shader fShader("font.vert", "font.frag");
	g.shaders.push_back(&fShader);

	Shader particleShader("particles.vert", "particles.frag");
	g.shaders.push_back(&particleShader);

	Shader framebufferProgram("framebuffer.vert", "framebuffer.frag");
	g.shaders.push_back(&framebufferProgram);

	g.shaders[4]->Activate();
	glUniform1i(glGetUniformLocation(g.shaders[4]->ID, "screenTexture"), 0);
	glUniform1i(glGetUniformLocation(g.shaders[4]->ID, "bloomTexture"), 1);
	glUniform1i(glGetUniformLocation(g.shaders[4]->ID, "gamma"), g.gamma);

	Shader blurProgram("framebuffer.vert", "blur.frag");
	g.shaders.push_back(&blurProgram);

	g.shaders[5]->Activate();
	glUniform1i(glGetUniformLocation(g.shaders[5]->ID, "screenTexture"), 0);
	//--------------------------------------------MESH-----------------------------------------------------

	//--------------Paddle1---------------------------------
	Paddle paddle1(glm::vec3(-0.85f, 0.0f, 0.0f) * 100.0f, glm::vec3(0.015f, 0.2f, 1.0f) * 100.0f, Paddle::CONTROLTYPE::WASD, glm::vec3(0.0f), "Paddle1");
	paddle1.mesh = Mesh(sqrverts, sqrinds, paddle1Tex);
	g.paddles.push_back(&paddle1);
	g.gameObjects.push_back(&paddle1);

	ObjectList.GOList.insert(pair<std::string, GameObject*>(paddle1.name, &paddle1));
	//--------------Paddle1---------------------------------

	//--------------Paddle2---------------------------------
	Paddle paddle2(glm::vec3(0.85f, 0.0f, 0.0f) * 100.0f, glm::vec3(0.015f, 0.2f, 1.0f) * 100.0f, Paddle::CONTROLTYPE::ARROW, glm::vec3(0.0f), "Paddle2");
	paddle2.mesh = Mesh(sqrverts, sqrinds, paddle2Tex);
	g.paddles.push_back(&paddle2);
	g.gameObjects.push_back(&paddle2);

	ObjectList.GOList.insert(pair<std::string, GameObject*>(paddle2.name, &paddle2));
	//--------------Paddle2---------------------------------

	//--------------BarrierUp-------------------------------
	Barrier BarrierBU(glm::vec3(0.0f, 1.02f, 0.0f) * 100.0f, glm::vec3(2.0f, 0.05f, 1.0f) * 100.0f, "BarrierUp");
	BarrierBU.mesh = Mesh(sqrverts, sqrinds, barrierTex);
	g.barriers.push_back(&BarrierBU);
	g.gameObjects.push_back(&BarrierBU);
	ObjectList.GOList.insert(pair<std::string, GameObject*>(BarrierBU.name, &BarrierBU));
	//--------------BarrierUp-------------------------------

	//--------------BarrierDown-------------------------------
	Barrier BarrierBD(glm::vec3(0.0f, -1.02f, 0.0f) * 100.0f, glm::vec3(2.0f, 0.05f, 1.0f) * 100.0f, "BarrierDown");
	BarrierBD.mesh = Mesh(sqrverts, sqrinds, barrierTex);
	g.barriers.push_back(&BarrierBD);
	g.gameObjects.push_back(&BarrierBD);
	ObjectList.GOList.insert(pair<std::string, GameObject*>(BarrierBD.name, &BarrierBD));
	//--------------BarrierDown-------------------------------

	Barrier BarrierER(glm::vec3(1.0f, 0.0f, 0.0f) * 100.0f, glm::vec3(0.0f, 2.0f, 1.0f) * 100.0f, "BarrierEnd");
	BarrierER.mesh = Mesh(sqrverts, sqrinds, defaultTex);
	g.barriers.push_back(&BarrierER);
	g.gameObjects.push_back(&BarrierER);
	ObjectList.GOList.insert(pair<std::string, GameObject*>(BarrierER.name, &BarrierER));
	//--------------BALL--------------------------------------
	Ball ball1("Ball1", glm::vec3(-0.02f, 0.0f, 0.0f) * 100.0f, glm::vec3(0.096f, 0.191f, 1.0f) * 100.0f, 2.5, glm::vec3(-65.0f, rand() / 10000.0f, 0.0f));
	ball1.mesh = Mesh(ballsverts, ballinds, ballTex);
	g.balls.push_back(&ball1);
	g.gameObjects.push_back(&ball1);
	ObjectList.GOList.insert(pair<std::string, GameObject*>(ball1.name, &ball1));
	//--------------BALL--------------------------------------

	//------------FRAME BUFFER TINGS-------------------
	FBO FBO(&g);

	FBO.PingPongBuffers(&g);
	//--------------------------------------------MESH-----------------------------------------------------


	glEnable(GL_MULTISAMPLE);

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

	ScreenHandler ScreenHandler;

	//Only one screen handler but im doing this so I can access its values in other files
	g.ScreenHandler.push_back(&ScreenHandler); 

	g.ScreenHandler[0]->ScreenSwitch(ScreenHandler::SCREENTYPE::GAME, &g);
	g.ScreenHandler[0]->ScreenInit(&g);
	//----------------------MENU HANDLER---------------------
	
	GUI DebugGUI;
	g.debugGUI.push_back(&DebugGUI);

	

	while (!glfwWindowShouldClose(window)) {

		//Framebuffer
		FBO.Bind();

		//glEnable(GL_FRAMEBUFFER_SRGB);
		glClearColor(pow(0.0f, g.gamma), pow(0.0f, g.gamma), pow(0.01f, g.gamma), 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		
		//IMGUI
		ImGui_ImplGlfwGL3_NewFrame();
		bruhndertale.Play();
		g.drawScreen();
		g.updateScreen();
		bruhndertale.updateBufferStream();
		//Error Checks For FBO
		/*auto fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (fboStatus != GL_FRAMEBUFFER_COMPLETE) {
			cout << "Error:" << fboStatus << endl;
		}*/


		FBO.ActivateBloom(&g);

		FBO.Unbind();

		//Draw the framebuffer rectangle
		g.shaders[4]->Activate();
		glBindVertexArray(rectVAO);
		FBO.drawRectangleScreen(&g);
		 
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
	framebufferProgram.Delete();
	blurProgram.Delete();
	//-----------------------------


	glfwDestroyWindow(window); //killing the window after we finish

	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate(); //terminating glfw after function

	return 0;
}