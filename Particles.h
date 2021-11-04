#pragma once

#include <vector>
#include "VAO.h"
#include "GameObject.h"
#include "game.h"
#include <glad/glad.h>
#include<glm/glm.hpp>

class GameObject;
class Shader;
class Game;
class Camera;
class Texture;




class Particle: public GameObject{
public:
	float life;
	Particle(glm::vec3 position, glm::vec3 velocity, glm::vec3 scale, glm::vec4 color, float life);
	void draw(Game* g, VAO* vao, Texture* texture, Camera* camera);
};

class ParticleSystem : public GameObject{
public:

	ParticleSystem(Texture* texture);
	void spawn(Game* g, glm::vec3 position, glm::vec3 velocity, glm::vec3 scale, glm::vec4 color, float life);

	void update(Game* g) override;

	

private:
	VAO particleVAO;

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	std::vector<Particle*> particles;
	unsigned int amount;
	Texture* texture;
	void init();
	void draw(Game* g);
};