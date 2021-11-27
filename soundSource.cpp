#include "soundSource.h"


soundSource::soundSource() {
	//setting all values
	alGenSources(1, &se_source);
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

void soundSource::Pause()
{
	alSourcePause(se_source);
}

void soundSource::Stop()
{
	alSourceStop(se_source);
}

void soundSource::Resume()
{
	alSourcePlay(se_source);
}

void soundSource::setPosition(const float& x, const float& y, const float& z)
{
	alSource3f(se_source, AL_POSITION, x, y, z);
}
