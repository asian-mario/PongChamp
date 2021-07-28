#include"gameFont.h"
#include "Ball.h"
#include<stdlib.h>
#include <cmath>

Ball::Ball(glm::vec3 position, glm::vec3 scale, glm::vec3 velocity) {
	this->position = glm::vec3(position);
	this->rotation = glm::vec3(0.0f);
	this->scale = glm::vec3(scale);
	this->velocity = glm::vec3(velocity);
}

bool Ball::circintersects(glm::vec3 circle, glm::vec3 rect, double circleRadius)
{
	double circleDistanceX = abs(circle.x - rect.x);
	double circleDistanceY = abs(circle.y - rect.y);


	double cornerDistance = pow((circleDistanceX - 0.75 / 2), 2.0f) + pow((circleDistanceY - 20.0 / 2), 2.0f);
	return (pow(circleRadius, 2) - pow((rect.x - circle.x), 2)) >= 0 && (circle.y >= rect.y - 18.0) && (circle.y <= rect.y + 18.0) || cornerDistance <= pow(circleRadius, 2);
}

bool Ball::boundsCheck(glm::vec3 position, glm::vec3 velocity, float bounds) {
	if (position.x >= bounds) {
		return true;
	}

}
bool Ball::boundsCheckL(glm::vec3 position, glm::vec3 velocity, float bounds) {
	if (position.x <= bounds) {
		return true;
	}

}



void Ball::update(Game* g) {
	//--------------BOUNDS CHECK----------------------
	bool checkRight = boundsCheck(g->balls[0]->position, g->balls[0]->velocity, 1.0f * 100.0f);
	bool checkLeft = boundsCheckL(g->balls[0]->position, g->balls[0]->velocity, -1.0f * 100.0f);

	if (checkRight == true) {
		position = glm::vec3(0.0f);
		velocity = glm::vec3(-60.0f, -rand() / control, 0.0f);
		if (g->texts[0]->score < 6) {
			g->texts[0]->score++;
		}
	}

	if (checkLeft == true) {
		position = glm::vec3(0.0f);
		velocity = glm::vec3(60.0f, rand() / control, 0.0f);
		if (g->texts[1]->score < 5) {
			g->texts[1]->score++;
		}
	}

	//--------------INTERSECTION-----------------------


	double deltaTime = g->deltaTime();

	double rad = 3.0;

	bool intersect = circintersects(g->balls[0]->position, g->paddles[0]->position, rad);
	bool intersect2 = circintersects(g->balls[0]->position, g->paddles[1]->position, rad);

	if (intersect) {
		velocity.x = -velocity.x;
		velocity.y += g->paddles[0]->velocity.y;
	}

	if (intersect2) {
		velocity.x = -velocity.x;
		velocity.y += g->paddles[1]->velocity.y;
	}

	if (position.y > 95.0f) {
		velocity.y = -velocity.y;
		velocity.y = velocity.y;
	}

	if (position.y < -95.0f) {
		velocity.y = -velocity.y;
	}

	//Speed control
	if (roml::magnitude(velocity) >= 500.0f) {
		float mag = roml::magnitude(velocity);
		velocity = velocity * (500.0f / mag);
	}


	//-------------------------------------COLLISION-----------------------------------------

	//------------------------NOT COLLISION (Very Descriptive)--------------------------------
	position += velocity * (float) deltaTime;
	//--------------INTERSECTION-----------------------


}
