#pragma once

#include<glm/glm.hpp>
#include "GameObject.h"
#include "game.h"

class GameObject;
class Game;

class Powerup : public GameObject {
public:


	Powerup(glm::vec3 position, glm::vec3 scale, glm::vec3 velocity);
	void update(Game* g) override;

	bool maxSpawn = false;

	//Powerup Functions
	void BallPlus(Game* g);

};

