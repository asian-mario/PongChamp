#include"gameFont.h"
#include "Ball.h"
#include<stdlib.h>
#include <cmath>

Ball::Ball(std::string name, glm::vec3 position, glm::vec3 scale, double rad, glm::vec3 velocity) {
	this->position = glm::vec3(position);
	this->rotation = glm::vec3(0.0f);
	this->scale = glm::vec3(scale);
	this->velocity = glm::vec3(velocity);
	this->rad = rad;
	this->name = name;
	this->boundingBox = createBoundingBox();
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

	if (limitSpeed == true) {
		

		if (g->balls[0]->position.x <= -25.0f) {
			color = glm::vec4(0.66f, 0.66f, 0.992f, 1.0f);
		}

		if (g->balls[0]->position.x >= -24.9f && g->balls[0]->position.x <= 20.0f) {
			color = glm::vec4(0.46f, 0.46f, 0.956f, 1.0f);
		}

		if (g->balls[0]->position.x >= 20.1f && g->balls[0]->position.x <= 40.0f) {
			color = glm::vec4(0.48f, 0.125f, 0.76f, 1.0f);
		}

		if (g->balls[0]->position.x >= 40.1f) {
			color = glm::vec4(0.6f, 0.17f, 0.93f, 1.0f);
		}
	}
	
	if (limitSpeed == false) {
		color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	}
	


	g->particleSystems[0]->spawn(g, g->balls[0]->position, g->balls[0]->velocity, glm::vec3(1.0f), color, 0.5f);

	//--------------BOUNDS CHECK----------------------
	bool checkRight = boundsCheck(g->balls[0]->position, g->balls[0]->velocity, 1.0f * 100.0f);
	bool checkLeft = boundsCheckL(g->balls[0]->position, g->balls[0]->velocity, -1.0f * 100.0f);

	if (checkRight == true) {
		g->soundSource[0]->Play(g->SoundList[0]->SoundList["Goal"]);

		for (int i = 0; i < 25; i++) {
			g->particleSystems[3]->spawn(g, glm::vec3(g->barriers[2]->position.x, g->balls[0]->position.y, g->barriers[0]->position.z), glm::vec3(rand() / 200.0f, rand() / 100.0f, 0.0f), glm::vec3(3.0f), color, 2.0f);
		}
		
		position = glm::vec3(0.0f);

		if (g->texts[0]->score < 5) {
			velocity = glm::vec3(-60.0f, -rand() / control, 0.0f);
			g->texts[0]->score++;
		}

		
	}

	if (checkLeft == true) {
		g->soundSource[0]->Play(g->SoundList[0]->SoundList["Goal"]);

		for (int i = 0; i < 25; i++) {
			g->particleSystems[3]->spawn(g, glm::vec3(-g->barriers[2]->position.x, g->balls[0]->position.y, -g->barriers[0]->position.z), glm::vec3(-rand() / 200.0f, rand() / 100.0f, 0.0f), glm::vec3(3.0f), color, 2.0f);

		}

		//At zero it causes weird bounding box issues
		position = glm::vec3(0.01f);

		if (g->texts[1]->score < 5) {
			velocity = glm::vec3(60.0f, rand() / control, 0.0f);
			g->texts[1]->score++;
		}
	}

	//--------------INTERSECTION-----------------------


	double deltaTime = g->deltaTime;


	bool intersect = circintersects(g->balls[0]->position, g->paddles[0]->position, rad, g->paddles[0]->width, g->paddles[0]->height);
	bool intersect2 = circintersects(g->balls[0]->position, g->paddles[1]->position, rad, g->paddles[1]->width, g->paddles[1]->height);

	//---------TODO: FIX LIMITS AAAAAAAAAAAA------------
	if (intersect) {
		g->soundSource[0]->Play(g->SoundList[0]->SoundList["Hit"]);

		g->barriers[0]->barrierHit, g->barriers[1]->barrierHit = false;

		velocity.x = -velocity.x;
		velocity.y += g->paddles[0]->velocity.y * decreaseVal;

		g->paddles[1]->lastHit = false;
		g->paddles[0]->lastHit = true;
	}

	if (intersect2) {
		g->soundSource[0]->Play(g->SoundList[0]->SoundList["Hit"]);

		g->barriers[0]->barrierHit, g->barriers[1]->barrierHit = false;

		velocity.x = -velocity.x;
		velocity.y += (g->paddles[1]->velocity.y) * decreaseVal;

		g->paddles[0]->lastHit = false;
		g->paddles[1]->lastHit = true;
	}

	if (position.y >= 98.0f) {
		g->soundSource[0]->Play(g->SoundList[0]->SoundList["Hit"]);

		g->barriers[0]->barrierHit = true;
		g->barriers[1]->barrierHit = false;

		velocity.y = -velocity.y * 0.9;

		g->particleSystems[1]->spawn(g, glm::vec3(g->balls[0]->position.x, g->barriers[0]->position.y - 10.5f, g->barriers[0]->position.z), glm::vec3(0.0f, 25.0f, 0.0f), glm::vec3(20.0f), color, 1.5f);
	}

	if (position.y <= -98.0f) {
		g->soundSource[0]->Play(g->SoundList[0]->SoundList["Hit"]);

		g->barriers[0]->barrierHit = false;
		g->barriers[1]->barrierHit = true;

		velocity.y = -velocity.y * 0.9;

		g->particleSystems[2]->spawn(g, glm::vec3(g->balls[0]->position.x, g->barriers[1]->position.y, g->barriers[1]->position.z), glm::vec3(0.0f, -25.0f, 0.0f), glm::vec3(20.0f), color, 1.5f);
	}

	if (limitSpeed == true) {
		//Speed control
		if (roml::magnitude(velocity) >= 600.0f) {
			float mag = roml::magnitude(velocity);
			velocity = velocity * (500.0f / mag);
		}


	}


	//-------------------------------------COLLISION-----------------------------------------

	//------------------------NOT COLLISION (Very Descriptive)--------------------------------
	position += velocity * (float) deltaTime;
	//--------------INTERSECTION-----------------------

	

	if (velocity.y >= 250.0f && g->barriers[0]->barrierHit == false && g->barriers[1]->barrierHit == false)
		g->miscfonts[0]->smashDraw(g);
	

}
