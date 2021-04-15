#pragma once
#include <AL/al.h>
class AudioSource
{
public:
	AudioSource();
	~AudioSource();

	void Play(const ALuint buffer_to_play);

private:
	ALuint src;
	float pitch = 1.f;
	float gain = 1.f;
	float positions[3] = { 0, 0, 0 };
	float vel[3] = { 0, 0, 0 };
	bool loopAudio = false;
	ALuint buffer = 0;
};

