#pragma once
#ifndef GUI_CLASS_H
#define GUI_CLASS_H


#include <cmath>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>
#include"Paddle.h"
#include"light.h"
#include"Ball.h"
#include"Barrier.h"


static class GUI {
public:
	static void createDebugMenu(Paddle pad);
	static void createDebugMenu(Ball ball);
	static void createDebugMenu(Barrier bar);
};
#endif 
