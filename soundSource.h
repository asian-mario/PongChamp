#pragma once
#include<AL/al.h>

class soundSource{
public:
	soundSource();
	~soundSource();

	void Play(const ALuint buffer);
	void Stop();
	void Pause();
	void Resume();

	/*void SetBufferToPlay(const ALuint& buffer_to_play);
	void SetLooping(const bool& loop);*/
	void setPosition(const float& x, const float& y, const float& z);


private:
	//more sounds played = the more the int goes up
	ALuint se_buffer = 0;
	ALuint se_source;
};

