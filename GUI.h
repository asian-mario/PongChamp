#pragma once



#include <cmath>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>
#include"Paddle.h"
#include"Ball.h"
#include"Barrier.h"
#include"GOList.h"

class Game;

class GUI {
public:
	static void createDebugMenu(GOList* obj, string name, glm::vec3 orgScale, glm::vec3 orgRot, glm::vec3 orgPos);
	static void createDebugMenu(Game* g);

	void onClickDebug(Game* g);

};

