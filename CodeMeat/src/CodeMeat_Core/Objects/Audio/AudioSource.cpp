#include "AudioSource.h"
#include <iostream>
AudioSource::AudioSource()
{
	alGenSources(1, &src);
	//alSourcef(src, AL_PITCH, pitch);
	//alSourcef(src, AL_GAIN, gain);
	//alSource3f(src, AL_POSITION, positions[0], positions[1], positions[2]);
	//alSource3f(src, AL_VELOCITY, vel[0], vel[1], vel[2]);
	//alSourcei(src, AL_LOOPING, loopAudio);
	alSourcei(src, AL_BUFFER, buffer);
}

AudioSource::~AudioSource()
{
	alDeleteSources(1, &src);
}

void AudioSource::Play(const ALuint buffer_to_play)
{
	if (buffer_to_play != buffer)
	{
		buffer = buffer_to_play;
		alSourcei(src, AL_BUFFER, (ALint)buffer);
	}

	alSourcePlay(src);

	//ALint state = AL_PLAYING;
	//std::cout << "playing Sound\n";
	//while (state == AL_PLAYING && alGetError() == AL_NO_ERROR)
	//{
	//	//std::cout << "currently playing sound\n";
	//	alGetSourcei(src, AL_SOURCE_STATE, &state);
	//}
	//std::cout << "done playing sound\n";
}

void AudioSource::SetBufferToPlay(const ALuint& buffer_to_play)
{
	if (buffer_to_play != buffer)
	{
		buffer = buffer_to_play;
		alSourcei(src, AL_BUFFER, (ALint)buffer);
	}
}

void AudioSource::SetLooping(const bool& loop)
{
	alSourcei(src, AL_LOOPING, (ALint)loop);
}

bool AudioSource::isPlaying()
{
	ALint playState;
	alGetSourcei(src, AL_SOURCE_STATE, &playState);
	return (playState == AL_PLAYING);
}
