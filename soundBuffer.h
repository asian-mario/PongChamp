#pragma once
#include<AL/al.h>
#include <vector>

class soundBuffer{
public:
	static soundBuffer* get();

	ALuint addSoundEffect(const char* filename);
	bool removeSoundEffect(const ALuint& buffer);

private:
	soundBuffer();
	~soundBuffer();

	//every initialized sound goes here
	std::vector<ALuint> p_soundEffectBuffers;
};

