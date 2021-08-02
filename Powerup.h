#pragma once

#include<glm/glm.hpp>
#include "GameObject.h"
#include "game.h"

class GameObject;
class Game;

class PowerupSpawn : public GameObject {
public:


	PowerupSpawn();
	void update(Game* g) override;

	bool maxSpawn = false;

	//Powerup Functions
	

};

class Powerup : public GameObject {
	Powerup(glm::vec3 position, glm::vec3 scale, glm::vec3 velocity);
};

class BallPlus : public Powerup {
	BallPlus(Game* g);
};