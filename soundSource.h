#pragma once
#include<AL/al.h>

class soundSource{
public:
	soundSource();
	~soundSource();

	void Play(const ALuint buffer);

private:
	float se_pitch = 1.0f;
	float se_gain = 1.0f;
	float se_positions[3] = { 0,0,0 };
	float se_velocity[3] = { 0,0,0 };
	
	bool se_loopSound = false;
	ALuint se_buffer = 0;
	ALuint se_source;
};

