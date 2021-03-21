#pragma once
#include <map>
#include <AL/al.h>
class AudioManager
{
	struct AudioSrc
	{
		ALuint src;
		float pitch = 1.f;
		float gain = 1.f;
		float positions[3] = { 0, 0, 0 };
		float vel[3] = { 0, 0, 0 };
		bool loopAudio = false;
		ALuint buffer = 0;
	};

	std::map<AudioSrc, const char*> audioLoader;

	AudioManager() {};
	~AudioManager() {};

	bool init();


};

