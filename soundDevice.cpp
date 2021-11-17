#include"soundDevice.h"
#include<vector>
#include<stdio.h>
#include<iostream>

#include<inttypes.h>
#include<AL/alext.h>

using namespace std;

soundDevice* soundDevice::get() {
	static soundDevice* snd_device = new soundDevice();
	return snd_device;
}

soundDevice::soundDevice() {
	//nullptr = default audio device
	se_ALCDevice = alcOpenDevice(nullptr); 
	if (!se_ALCDevice) 
		throw("ERROR: DEFAULT AUDIO DEVICE NOT FOUND");
	
	//Create audio context
	se_ALCContext = alcCreateContext(se_ALCDevice, nullptr);

	if (!se_ALCContext)
		throw("ERROR: FAILED TO SET SOUND CONTEXT");

	if (!alcMakeContextCurrent(se_ALCContext)) 
		throw("ERROR: FAILED MAKE CONTEXT CURRENT");


	const ALCchar* name = nullptr;
	if (alcIsExtensionPresent(se_ALCDevice, "ALC_ENUMERATE_ALL_EXT"))
		name = alcGetString(se_ALCDevice, ALC_ALL_DEVICES_SPECIFIER);
	
	if (!name == alcGetError(se_ALCDevice) != ALC_NO_ERROR)
		name = alcGetString(se_ALCDevice, ALC_DEVICE_SPECIFIER);

	printf("Opened \"%s\"\n", name);

}



//outputs the current position of the listener (speaker, headphones etc.)
void soundDevice::getLocation(float x, float y, float z) {
	alGetListener3f(AL_POSITION, &x, &y, &z);
}

//outputs the current orientation of the listener
void soundDevice::getOrientation(float orientation) {
	alGetListenerfv(AL_ORIENTATION, &orientation);
}

//gives value of current audio gain on the listener
float soundDevice::getGain() {
	float crntGain;

	alGetListenerf(AL_GAIN, &crntGain);
	return crntGain;
}

//sets a new location value for listener
void soundDevice::setLocation(float x, float y, float z) {
	alListener3f(AL_POSITION, x, y, z);
}

//sets a new orientation value for listener
void soundDevice::setOrientation(float atx, float aty, float atz,
	float upx, float upy, float upz) {
	
	std::vector<float> orientation;

	//add info to the orientation vector
	orientation.push_back(atx);
	orientation.push_back(aty);
	orientation.push_back(atz);
	orientation.push_back(upx);
	orientation.push_back(upy);
	orientation.push_back(upz);

	alListenerfv(AL_ORIENTATION, orientation.data());
}

//sets new gain value for listener
void soundDevice::setGain(float value) {

	//clamp between 0 - 5 because i dont like blown speakers
	float newVolume = value;
	if (newVolume < 0.0f) {
		newVolume = 0.0f;
		cout << "ERROR: GAIN MINIMUM LIMIT REACHED" << endl;
	}
	else if (newVolume > 5.0f) {
		newVolume = 5.0f;
		cout << "ERROR: GAIN MAXIMUM LIMIT REACHED" << endl;
	}
}


soundDevice::~soundDevice() {
	if (!alcMakeContextCurrent(nullptr))
		throw("ERROR: FAILED TO SET CONTEXT TO NULL");

	alcDestroyContext(se_ALCContext);
	if (se_ALCContext)
		throw("ERROR: FAILED TO UNSET CONTEXT DURING CLOSE");

	if (!alcCloseDevice(se_ALCDevice))
		throw("ERROR: FAILED TO CLOSE SOUND DEVICE");
}