#pragma once
#include<AL/al.h>

class soundSource{
public:
	soundSource();
	~soundSource();

	void Play(const ALuint buffer);

private:
	//audio settings
	float se_pitch = 1.0f;
	float se_gain = 1.0f;
	//'position' where sound is played, 3D audio
	float se_positions[3] = { 0,0,0 };
	//for moving sounds 
	float se_velocity[3] = { 0,0,0 };
	
	bool se_loopSound = false;
	//more sounds played = the more the int goes up
	ALuint se_buffer = 0;
	ALuint se_source;
};

