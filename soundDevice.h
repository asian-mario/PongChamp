#pragma once
#include<AL/alc.h>

class soundDevice {
public:
	static soundDevice* get();

private:
	soundDevice();
	~soundDevice();

	ALCdevice* se_ALCDevice;
	ALCcontext* se_ALCContext;
};