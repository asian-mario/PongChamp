#include"soundDevice.h"
#include<stdio.h>


soundDevice* soundDevice::get() {
	static soundDevice* snd_device = new soundDevice();
	return snd_device;
}

soundDevice::soundDevice() {
	//Gets default audio device
	p_ALCDevice = alcOpenDevice(nullptr); 
	if (!p_ALCDevice) 
		throw("ERROR: DEFAULT AUDIO DEVICE NOT FOUND");
	
	//Create audio context
	p_ALCContext = alcCreateContext(p_ALCDevice, nullptr);

	if (!p_ALCContext)
		throw("ERROR: FAILED TO SET SOUND CONTEXT");

	if (!alcMakeContextCurrent(p_ALCContext)) 
		throw("ERROR: FAILED MAKE CONTEXT CURRENT");


	const ALCchar* name = nullptr;
	if (alcIsExtensionPresent(p_ALCDevice, "ALC_ENUMERATE_ALL_EXT"))
		name = alcGetString(p_ALCDevice, ALC_ALL_DEVICES_SPECIFIER);
	
	if (!name == alcGetError(p_ALCDevice) != ALC_NO_ERROR)
		name = alcGetString(p_ALCDevice, ALC_DEVICE_SPECIFIER);

	printf("Opened \"%s\"\n", name);

}

soundDevice::~soundDevice() {
	if (!alcMakeContextCurrent(nullptr))
		throw("ERROR: FAILED TO SET CONTEXT TO NULL");

	alcDestroyContext(p_ALCContext);
	if (p_ALCContext)
		throw("ERROR: FAILED TO UNSET CONTEXT DURING CLOSE");

	if (!alcCloseDevice(p_ALCDevice))
		throw("ERROR: FAILED TO CLOSE SOUND DEVICE");
}