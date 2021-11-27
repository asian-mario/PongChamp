#pragma once
#include<AL/alc.h>

class soundDevice {
public:
	static soundDevice* get();

	void getLocation(float x, float y, float z);
	void getOrientation(float orientation);
	float getGain();

	void setAttunation(int key);
	void setLocation(float x, float y, float z);
	void setOrientation(
		float atx, float aty, float atz,
		float upx, float upy, float upz
	);
	void setGain(float value);

private:
	soundDevice();
	~soundDevice();

	ALCdevice* se_ALCDevice;
	ALCcontext* se_ALCContext;
};