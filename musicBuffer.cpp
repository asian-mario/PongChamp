#include "musicBuffer.h"
#include <cstddef>
#include <AL\alext.h>
#include <malloc.h>

void musicBuffer::Play() {
	ALsizei i;

	alGetError();

	//rewinds source position + clear buffer
	alSourceRewind(se_source);
	alSourcei(se_source, AL_BUFFER, 0);

	//fill the buffer up
	for (i = 0; i < num_buffers; i++) {
		sf_count_t slen = sf_readf_short(se_sndfile, se_membuf, b_samples);
		if (slen < 1) break;

		slen *= se_sfinfo.channels * (sf_count_t)sizeof(short);
		alBufferData(se_buffers[i], se_format, se_membuf, (ALsizei)slen, se_sfinfo.samplerate);

	}
	if (alGetError != AL_NO_ERROR) {
		throw("ERROR: Cannot buffer playback.");
	}

	//queue and start playback
	alSourceQueueBuffers(se_source, i, se_buffers);
	alSourcePlay(se_source);

	if (alGetError != AL_NO_ERROR) {
		throw("ERROR: Cannot start playback	");
	}

}

//refresh the buffers so they don't run out 
void musicBuffer::updateBufferStream() {
	ALint processed, state;

	alGetError();

	//check status of speakers
	alGetSourcei(se_source, AL_SOURCE_STATE, &state);
	//check amnt of buffers processed
	alGetSourcei(se_source, AL_BUFFERS_PROCESSED, &processed);

	if (alGetError() != AL_NO_ERROR) {
		throw("ERROR: Cannot check source/speaker state.");
	}

	while (processed > 0) {
		ALuint bufid;
		sf_count_t slen;

		alSourceUnqueueBuffers(se_source, 1, &bufid);

		//read the rest of the data, refill the buffers and re-queue
		slen = sf_readf_short(se_sndfile, se_membuf, b_samples);
		if (slen > 0) {
			alBufferData(bufid, se_format, se_membuf, (ALsizei)slen, se_sfinfo.samplerate);
		}


		if (alGetError != AL_NO_ERROR) {
			throw("ERROR: Cannot buffer playback.");
		}

	}

	//checking if source is underrun
	if (state != AL_PLAYING && state != AL_PAUSED){
		ALint queued;

		//if there isnt any buffers queued it means playback is done
		alGetSourcei(se_source, AL_BUFFERS_QUEUED, &queued);
		if (queued == 0)
			return;

		alSourcePlay(se_source);

		if (alGetError != AL_NO_ERROR) {
			throw("ERROR: Cannot restart music playback.");
		}
	}
}
musicBuffer::musicBuffer(const char* filename) {
	alGenSources(1, &se_source);
	//generates all the buffers (currently 4)
	alGenBuffers(num_buffers, se_buffers);

	std::size_t framesize;

	//using sndfile to read the soundtrack
	se_sndfile = sf_open(filename, SFM_READ, &se_sfinfo);

	//fun fact, when specifying paths with '\' instead of '/' a double slash is needed 
	if (!se_sndfile) {
		throw("ERROR: Soundtrack path is invalid.");
	}

	//get sound format then set OpenAL format
	if (se_sfinfo.channels == 1) {
		se_format = AL_FORMAT_MONO16;
	}
	else if (se_sfinfo.channels == 2) {
		se_format = AL_FORMAT_STEREO16;
	}
	else if (se_sfinfo.channels == 3) {
		if (sf_command(se_sndfile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT) {
			se_format = AL_FORMAT_BFORMAT2D_16;
		}
	}
	else if (se_sfinfo.channels == 4) {
		if (sf_command(se_sndfile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT) {
			se_format = AL_FORMAT_BFORMAT3D_16;
		}
	}

	if (!se_format) {
		sf_close(se_sndfile);
		se_sndfile = NULL;
		throw("ERROR: Unsupported channel count. Unable to figure format.");
	}

	//calculates audio frame size
	framesize = ((size_t)b_samples * (size_t)se_sfinfo.channels * sizeof(short));
	//allocate memory
	se_membuf = static_cast<short*>(malloc(framesize));
}

musicBuffer::~musicBuffer() {
	//bog standard
	alDeleteSources(1, &se_source);
	if (se_sndfile)
		sf_close(se_sndfile);

	se_sndfile = nullptr;
	free(se_membuf);

	alDeleteBuffers(num_buffers, se_buffers);
}