#pragma once

#include<glm/glm.hpp>
#include "GameObject.h"
#include "game.h"

class GameObject;
class Game;

class PowerupSpawn : public GameObject{
public:
	string powerups[3] = { "BallPlus", "PaddlePlus", "PaddleMinus" };
	string currentPowerup = powerups[rand() % 3];

	void update(Game* g) override;
	void spawn(Game* g, int tex);

	bool maxSpawn = false;


};

class BallPlusPowerup : public GameObject {
public:
	bool hit = false;
	double effect = 5.0;

	BallPlusPowerup(Game* g, glm::vec3 position, glm::vec3 scale, glm::vec3 velocity);

	void delayEffect(Game* g);
	void update(Game* g) override;
	void draw(Game* g) override;
};

