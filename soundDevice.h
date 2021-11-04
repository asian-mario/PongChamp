#pragma once
#include<AL/alc.h>

class soundDevice {
public:
	static soundDevice* get();

private:
	soundDevice();
	~soundDevice();

	ALCdevice* p_ALCDevice;
	ALCcontext* p_ALCContext;
};