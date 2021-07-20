#include "Ball.h"
#include<stdlib.h>
#include <cmath>

Ball::Ball(glm::vec3 pos, glm::vec3 scale, glm::vec3 velocity) {
	this->position = glm::vec3(pos);
	this->rotation = glm::vec3(0.0f);
	this->scale = glm::vec3(scale);
	this->velocity = glm::vec3(velocity);
}

bool Ball::circintersects(glm::vec3 circle, glm::vec3 rect, double circleRadius)
{
	double circleDistanceX = abs(circle.x - rect.x);
	double circleDistanceY = abs(circle.y - rect.y);


	double cornerDistance = pow((circleDistanceX - 0.0075 / 2), 2.0f) +
		pow((circleDistanceY - 0.2 / 2), 2.0f);
	return (pow(circleRadius, 2) - pow((rect.x - circle.x), 2)) >= 0 && (circle.y >= rect.y - 0.2) && (circle.y <= rect.y + 0.2) || cornerDistance <= pow(circleRadius, 2);
}


void Ball::update(Game* g) {
	//All the model matrices
	glm::mat4 padModel = g->paddles[0]->getModelMatrix();
	glm::mat4 pad2Model = g->paddles[1]->getModelMatrix();
	glm::mat4 ballModel = getModelMatrix();

	double control = 100000.0;
	double deltaTime = g->deltaTime();

	//Calculating worldpos
	glm::vec3 padWorldPos = g->paddles[0]->findWorldPos(padModel, g->paddles[0]->position);
	glm::vec3 pad2WorldPos = g->paddles[1]->findWorldPos(pad2Model, g->paddles[1]->position);
	glm::vec3 ballWorldPos = ballModel * glm::vec4(position, 1.0f);

	double rad = 0.003;

	bool intersect = circintersects(ballWorldPos, padWorldPos, rad);
	bool intersect2 = circintersects(ballWorldPos, pad2WorldPos, rad);

	if (intersect) {
		velocity.x = -velocity.x;
		velocity.y += -rand() / control + g->paddles[0]->velocity.y;

	}

	if (intersect2) {
		velocity.x = -velocity.x;
		velocity.y += rand() / control + g->paddles[1]->velocity.y;
	}
	if (position.y <= -0.8) {
		velocity.y = -velocity.y - 0.001f;
		g->paddles[0]->velocity.y = 0.0f;
		g->paddles[1]->velocity.y = 0.0f;
	}

	if (position.y >= 0.8) {
		velocity.y = -velocity.y - 0.001f;
		g->paddles[0]->velocity.y = 0.0f;
		g->paddles[1]->velocity.y = 0.0f;
	}


	//-------------------------------------COLLISION-----------------------------------------

	//------------------------NOT COLLISION (Very Descritive)--------------------------------
	position.x += velocity.x * deltaTime;
	position.y += velocity.y * deltaTime;


}
