#include "MusicBuffer.h"
#include <iostream>
#include <AL/alext.h>

void MusicBuffer::Play()
{
	ALsizei i;

	//clear any al errors
	alGetError();

	// rewind the source position and clear the buffer queue
	alSourceRewind(src);
	alSourcei(src, AL_BUFFER, 0);

	// fill the buffer queue
	for (i = 0; i < NUM_BUFFERS; i++)
	{
		// get some data to give to the buffer
		sf_count_t slen = sf_readf_short(sndFile, membuf, BUFFER_SAMPLES);
		if (slen < 1) break;

		slen *= sfinfo.channels * (sf_count_t)sizeof(short);
		alBufferData(buffers[i], format, membuf, (ALsizei)slen, sfinfo.samplerate);
	}
	if (alGetError() != AL_NO_ERROR)
	{
		throw("Error buffering for playback");
	}

	//now queue and start playback
	alSourceQueueBuffers(src, i, buffers);
	alSourcePlay(src);
	if (alGetError() != AL_NO_ERROR)
	{
		throw("Error starting playback");
	}
}

void MusicBuffer::Pause()
{
	alSourcePause(src);
}

void MusicBuffer::Stop()
{
	alSourceStop(src);
}

void MusicBuffer::Resume()
{
	alSourcePlay(src);
}

void MusicBuffer::UpdateBufferStream()
{
	ALint processed, state;

	//clear errors
	alGetError();

	//get relevant source info
	alGetSourcei(src, AL_SOURCE_STATE, &state);
	alGetSourcei(src, AL_BUFFERS_PROCESSED, &processed);

	if (alGetError() != AL_NO_ERROR)
	{
		throw("error checking music source state");
	}

	//unqueue and handle each processed buffer
	while (processed > 0)
	{
		ALuint bufferID;
		sf_count_t slen;

		alSourceUnqueueBuffers(src, 1, &bufferID);
		processed--;

		//read the next chunk of data, refill the buffer, and queue it back on the siyrce
		slen = sf_readf_short(sndFile, membuf, BUFFER_SAMPLES);
		if (slen > 0)
		{
			slen *= sfinfo.channels * (sf_count_t)sizeof(short);
			alBufferData(bufferID, format, membuf, (ALsizei)slen, sfinfo.samplerate);
			alSourceQueueBuffers(src, 1, &bufferID);
		}

		if (alGetError() != AL_NO_ERROR)
		{
			throw("Error buffering music data");
		}
	}

	// make sure the source hasnt underrun
	if (state != AL_PLAYING && state != AL_PAUSED)
	{
		ALint queued;

		// if no buffers are queued, playback is finished
		alGetSourcei(src, AL_BUFFERS_QUEUED, &queued);

		if (queued == 0)
		{
			return;
		}

		alSourcePlay(src);
		//alSourcei(src, AL_LOOPING, 1);
		if (alGetError() != AL_NO_ERROR)
		{
			throw("error restarting music playback");
		}
	}


}

ALint MusicBuffer::GetSource()
{
	return src;
}

bool MusicBuffer::isPlaying()
{
	ALint state;
	alGetSourcei(src, AL_SOURCE_STATE, &state);
	return (state == AL_PLAYING);
}

void MusicBuffer::isLooping(const bool& loop)
{
	alSourcei(src, AL_LOOPING, (ALint)loop);
}

MusicBuffer::MusicBuffer(const char* filename)
{
	alGenSources(1, &src);
	alGenBuffers(NUM_BUFFERS, buffers);

	std::size_t frame_size;

	sndFile = sf_open(filename, SFM_READ, &sfinfo);
	if (!sndFile)
	{
		throw("Could not open music file -- check path");
	}

	// get the sound format
	if (sfinfo.channels == 1)
	{
		format = AL_FORMAT_MONO16;
	}
	else if (sfinfo.channels == 2)
	{
		format = AL_FORMAT_STEREO16;
	}
	else if (sfinfo.channels == 3)
	{
		if (sf_command(sndFile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT)
		{
			format = AL_FORMAT_BFORMAT2D_16;
		}
	}
	else if (sfinfo.channels == 4)
	{
		if (sf_command(sndFile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT)
		{
			format = AL_FORMAT_BFORMAT3D_16;
		}
	}
	if (!format)
	{
		sf_close(sndFile);
		sndFile = NULL;
		throw("Unsupported channel coount from file");
	}

	frame_size = ((size_t)BUFFER_SAMPLES * (size_t)sfinfo.channels) * sizeof(short);
	membuf = static_cast<short*>(malloc(frame_size));
}

MusicBuffer::~MusicBuffer()
{
	alDeleteSources(1, &src);
	sf_close(sndFile);

	sndFile = nullptr;

	free(membuf);

	alDeleteBuffers(NUM_BUFFERS, buffers);
}