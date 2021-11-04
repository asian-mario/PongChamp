#pragma once
#include<AL/al.h>

class soundBuffer{
public:
	static soundBuffer* get();

	ALuint addSoundEffect(const char* filename);
	bool removeSoundEffect(const ALuint& buffer);
};

