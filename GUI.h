#pragma once



#include <cmath>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>
#include"Paddle.h"
#include"Ball.h"
#include"Barrier.h"


class GUI {
public:
	static void createDebugMenu(Paddle pad, string name = "Debug Paddle");
	static void createDebugMenu(Ball ball, string name = "Debug Ball");
	static void createDebugMenu(Barrier bar, string name = "Debug Barrier");

	GUI() = delete;
};

