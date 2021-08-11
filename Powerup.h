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

	void resetPowerup();
	void deletePowerup(GameObject* GO);

	void update(Game* g) override;
	void spawn(Game* g, int tex);

	const int maxSpawn = 1;
	int activeSpwn = 0;
	double delay = 8.0;

private:
	std::vector<GameObject*> activePowerup;
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

class PaddlePlusPowerup : public GameObject {
public:
	bool hit = false;
	double effect = 7.0;

	PaddlePlusPowerup(Game* g, glm::vec3 position, glm::vec3 scale, glm::vec3 velocity);

	void delayEffect(Game* g);
	void update(Game* g) override;
	void draw(Game* g) override;
};

class PaddleMinusPowerup : public GameObject {
public:
	bool hit = false;
	double effect = 7.0;

	PaddleMinusPowerup(Game* g, glm::vec3 position, glm::vec3 scale, glm::vec3 velocity);

	void delayEffect(Game* g);
	void update(Game* g) override;
	void draw(Game* g) override;
};