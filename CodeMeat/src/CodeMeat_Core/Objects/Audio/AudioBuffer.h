#pragma once
#include <AL/al.h>
#include <vector>

#define SE_LOAD AudioBuffer::get()->addAudioFX
#define SE_UNLOAD AudioBuffer::get()->removeAudioFX
class AudioBuffer
{
public:
	static AudioBuffer* get();

	ALuint addAudioFX(const char* filename);
	bool removeAudioFX(const ALuint& buffer);

private:
	AudioBuffer();
	~AudioBuffer();

	std::vector<ALuint> m_AudioFXBuffers;
};