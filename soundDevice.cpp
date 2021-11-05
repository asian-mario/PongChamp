#include"soundDevice.h"
#include<stdio.h>


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

soundDevice::~soundDevice() {
	if (!alcMakeContextCurrent(nullptr))
		throw("ERROR: FAILED TO SET CONTEXT TO NULL");

	alcDestroyContext(se_ALCContext);
	if (se_ALCContext)
		throw("ERROR: FAILED TO UNSET CONTEXT DURING CLOSE");

	if (!alcCloseDevice(se_ALCDevice))
		throw("ERROR: FAILED TO CLOSE SOUND DEVICE");
}