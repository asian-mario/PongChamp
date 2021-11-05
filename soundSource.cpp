#include "soundSource.h"

soundSource::soundSource() {
	//setting all values
	alGenSources(1, &se_source);
	alSourcef(se_source, AL_PITCH, se_pitch);
	alSourcef(se_source, AL_GAIN, se_gain);

	alSource3f(se_source, AL_POSITION, se_positions[0], se_positions[1], se_positions[2]);
	alSource3f(se_source, AL_VELOCITY, se_velocity[0], se_velocity[1], se_velocity[2]);

	alSourcei(se_source, AL_LOOPING, se_loopSound);
	alSourcei(se_source, AL_BUFFER, se_buffer);
}

soundSource::~soundSource() {
	alDeleteSources(1, &se_source);
}

void soundSource::Play(const ALuint buffer) {
	//sets the sound buffer to the given sound
	if (buffer != se_buffer) {
		se_buffer = buffer;
		alSourcei(se_source, AL_BUFFER, (ALint)se_buffer);

	}

	//plays sound
	alSourcePlay(se_source);  
}