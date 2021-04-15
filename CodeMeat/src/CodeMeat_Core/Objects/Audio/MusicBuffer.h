#pragma once
#include <AL/al.h>
#include <sndfile.h>

class MusicBuffer
{
public:
	void Play();
	void Pause();
	void Stop();
	void Resume();

	void UpdateBufferStream();

	ALint GetSource();

	bool isPlaying();
	void isLooping(const bool& loop);

	MusicBuffer(const char* filename);
	~MusicBuffer();

private:
	ALuint src;
	static const int BUFFER_SAMPLES = 8192;
	static const int NUM_BUFFERS = 4;
	ALuint buffers[NUM_BUFFERS];
	SNDFILE* sndFile;
	SF_INFO sfinfo;
	short* membuf;
	ALenum format;


	MusicBuffer() = delete;
};
