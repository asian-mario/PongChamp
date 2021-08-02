#include"gameFont.h"
#include "Ball.h"
#include<stdlib.h>
#include <cmath>

Ball::Ball(glm::vec3 position, glm::vec3 scale, double rad, glm::vec3 velocity) {
	this->position = glm::vec3(position);
	this->rotation = glm::vec3(0.0f);
	this->scale = glm::vec3(scale);
	this->velocity = glm::vec3(velocity);
	this->rad = rad;
}

bool Ball::circintersects(glm::vec3 circle, glm::vec3 rect, double circleRadius, double width, double height)
{
	double circleDistanceX = abs(circle.x - rect.x);
	double circleDistanceY = abs(circle.y - rect.y);


	double cornerDistance = pow((circleDistanceX - width / 2), 2.0f) + pow((circleDistanceY - height / 2), 2.0f);
	return (pow(circleRadius, 2) - pow((rect.x - circle.x), 2)) >= 0 && (circle.y >= rect.y - height) && (circle.y <= rect.y + height) || cornerDistance <= pow(circleRadius, 2);
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

	g->particleSystems[0]->spawn(g, g->balls[0]->position, g->balls[0]->velocity, glm::vec3(1.0f), glm::vec4(1.0f), 0.5f);

	//--------------BOUNDS CHECK----------------------
	bool checkRight = boundsCheck(g->balls[0]->position, g->balls[0]->velocity, 1.0f * 100.0f);
	bool checkLeft = boundsCheckL(g->balls[0]->position, g->balls[0]->velocity, -1.0f * 100.0f);

	if (checkRight == true) {
		for (int i = 0; i < 25; i++) {
			g->particleSystems[3]->spawn(g, glm::vec3(g->barriers[2]->position.x, g->balls[0]->position.y, g->barriers[0]->position.z), glm::vec3(50.0f, rand() / 200.0f, 0.0f), glm::vec3(3.0f), glm::vec4(1.0f), 2.0f);
		}
		
		position = glm::vec3(0.0f);
		velocity = glm::vec3(-60.0f, -rand() / control, 0.0f);
		if (g->texts[0]->score < 6) {
			g->texts[0]->score++;
			
		}

		
	}

	if (checkLeft == true) {
		for (int i = 0; i < 25; i++) {
			g->particleSystems[3]->spawn(g, glm::vec3(-g->barriers[2]->position.x, g->balls[0]->position.y, -g->barriers[0]->position.z), glm::vec3(-50.0f, rand() / 200.0f, 0.0f), glm::vec3(3.0f), glm::vec4(1.0f), 2.0f);

		}

		position = glm::vec3(0.0f);
		velocity = glm::vec3(60.0f, rand() / control, 0.0f);
		if (g->texts[1]->score < 5) {
			g->texts[1]->score++;
		}
	}

	//--------------INTERSECTION-----------------------


	double deltaTime = g->deltaTime;


	bool intersect = circintersects(g->balls[0]->position, g->paddles[0]->position, rad, 1.5, 20.0);
	bool intersect2 = circintersects(g->balls[0]->position, g->paddles[1]->position, rad, 1.5, 20.0);

	if (intersect) {
		velocity.x = -velocity.x;
		velocity.y += g->paddles[0]->velocity.y;

		g->paddles[1]->lastHit = false;
		g->paddles[0]->lastHit = true;
	}

	if (intersect2) {
		velocity.x = -velocity.x;
		velocity.y += g->paddles[1]->velocity.y;

		g->paddles[0]->lastHit = false;
		g->paddles[1]->lastHit = true;
	}

	if (position.y > 96.5f) {
		velocity.y = -velocity.y;

		g->particleSystems[1]->spawn(g, glm::vec3(g->balls[0]->position.x, g->barriers[0]->position.y - 10.5f, g->barriers[0]->position.z), glm::vec3(0.0f, 25.0f, 0.0f), glm::vec3(20.0f), glm::vec4(1.0f), 1.5f);
	}

	if (position.y < -96.5f) {
		velocity.y = -velocity.y;

		g->particleSystems[2]->spawn(g, glm::vec3(g->balls[0]->position.x, g->barriers[1]->position.y, g->barriers[1]->position.z), glm::vec3(0.0f, -25.0f, 0.0f), glm::vec3(20.0f), glm::vec4(1.0f), 1.5f);
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

	if (velocity.y >= 350.0f) {
		velocity.y = velocity.y - 60.0f;
	}
}
