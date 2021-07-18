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
#include"Paddle.h"
#include"light.h"
#include"Ball.h"
#include"Barrier.h"
#include"GUI.h"
#include"GameObject.h"
#include"game.h"


//IMGUI
#include<imgui/imconfig.h>
#include<imgui/imgui.h>
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

	GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "OpenPong", NULL, NULL);
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
	Light directLight(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.5f, 1.5f));
	//--------------------------------------------MESH-----------------------------------------------------

	//--------------Paddle1---------------------------------
	Paddle paddle1(glm::vec3(-0.75f, 0.0f, 0.0f), glm::vec3(0.015f, 0.2f, 1.0f), Paddle::CONTROLTYPE::WASD);
	paddle1.mesh = Mesh(sqrverts, sqrinds, defaultTex);
	//--------------Paddle1---------------------------------

	//--------------Paddle2---------------------------------
	Paddle paddle2(glm::vec3(0.75f, 0.0f, 0.0f), glm::vec3(0.015f, 0.2f, 1.0f), Paddle::CONTROLTYPE::ARROW);
	paddle2.mesh = Mesh(sqrverts, sqrinds, defaultTex);
	//--------------Paddle2---------------------------------

	//--------------BarrierUp-------------------------------
	Barrier BarrierBU(glm::vec3(0.0f, 0.85f, 0.0f), glm::vec3(1.7f, 0.05f, 1.0f));
	BarrierBU.mesh = Mesh(sqrverts, sqrinds, defaultTex);
	//--------------BarrierUp-------------------------------

	//--------------BarrierDown-------------------------------
	Barrier BarrierBD(glm::vec3(0.0f, -0.85f, 0.0f), glm::vec3(1.7f, 0.05f, 1.0f));
	BarrierBD.mesh = Mesh(sqrverts, sqrinds, defaultTex);
	//--------------BarrierDown-------------------------------

	//--------------BALL--------------------------------------
	Ball ball1(glm::vec3(-0.02f, 0.0f, 0.0f), glm::vec3(0.096f, 0.191f, 1.0f), glm::vec3(-0.005f, 0.0f, 0.0f));
	ball1.mesh = Mesh(ballsverts, ballinds, ballTex);
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


			Game g();
			g.update();
			g.draw();

		

		//Exporting data & Render
		/*lightShader.Activate();
		glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
		glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), directLight.colorVec.x, directLight.colorVec.y, directLight.colorVec.z, directLight.colorVec.w);
		light.Draw(lightShader, camera);

		shaderProgram.Activate();
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(pad1Model));
		glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), directLight.colorVec.x, directLight.colorVec.y, directLight.colorVec.z, directLight.colorVec.w);
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), directLight.posVec.x, directLight.posVec.y, directLight.posVec.z);
		pad1.Draw(shaderProgram, camera);

		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(pad2Model));
		glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), directLight.colorVec.x, directLight.colorVec.y, directLight.colorVec.z, directLight.colorVec.w);
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), directLight.posVec.x, directLight.posVec.y, directLight.posVec.z);
		pad2.Draw(shaderProgram, camera);

		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(BUModel));
		glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), directLight.colorVec.x, directLight.colorVec.y, directLight.colorVec.z, directLight.colorVec.w);
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), directLight.posVec.x, directLight.posVec.y, directLight.posVec.z);
		barrierUp.Draw(shaderProgram, camera);

		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(BDModel));
		glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), directLight.colorVec.x, directLight.colorVec.y, directLight.colorVec.z, directLight.colorVec.w);
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), directLight.posVec.x, directLight.posVec.y, directLight.posVec.z);
		barrierDown.Draw(shaderProgram, camera);

		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(ballModel));
		glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), directLight.colorVec.x, directLight.colorVec.y, directLight.colorVec.z, directLight.colorVec.w);
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), directLight.posVec.x, directLight.posVec.y, directLight.posVec.z);
		ball.Draw(shaderProgram, camera);*/

		//---------------------------------------------------------------------------------------------------------------------------------
		//Updates and exports camera matrix to the vert shader
		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		//IMGUI
		ImGui_ImplGlfwGL3_NewFrame();


		//-------------------------------------COLLISION-----------------------------------------

		glm::vec3 padWorldPos = pad1Model * glm::vec4(paddle1.posVec, 1.0f);
		glm::vec3 pad2WorldPos = pad2Model * glm::vec4(paddle2.posVec, 1.0f);
		glm::vec3 ballWorldPos = ballModel * glm::vec4(ball1.posVec, 1.0f);
		//float rad = 0.0702019f;
		double rad = 0.00047;
		bool intersect = circintersects(ballWorldPos, padWorldPos, rad);
		bool intersect2 = circintersects(ballWorldPos, pad2WorldPos, rad);


		if (intersect) {
			ball1.speedVec.x = -ball1.speedVec.x;
			ball1.speedVec.y -= rand() / 10000000.0f + paddle1.velocity;
			
		}
		
		if (intersect2) {
			ball1.speedVec.x = -ball1.speedVec.x;
			ball1.speedVec.y -= rand() / 10000000.0f + paddle2.velocity;
		}
		if (ball1.posVec.y <= -0.8) {
			ball1.speedVec.y = -ball1.speedVec.y;
			paddle1.velocity = 0.0;
			paddle2.velocity = 0.0;
		}

		if (ball1.posVec.y >= 0.8) {
			ball1.speedVec.y = -ball1.speedVec.y;
			paddle1.velocity = 0.0;
			paddle2.velocity = 0.0;
		}


		//-------------------------------------COLLISION-----------------------------------------
		
		ball1.posVec.x += ball1.speedVec.x;
		ball1.posVec.y += ball1.speedVec.y;


	//---------------------------DEBUG----------------------------------
		GUI::createDebugMenu(paddle1);
		GUI::createDebugMenu(paddle2, "Debug Paddle 2");
		GUI::createDebugMenu(ball1);
		GUI::createDebugMenu(BarrierBU);
		GUI::createDebugMenu(BarrierBD, "Debug Barrier Bottom");
	//-------------------------------------DEBUG----------------------------------------------
		



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