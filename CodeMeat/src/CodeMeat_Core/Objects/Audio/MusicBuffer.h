#pragma once
#include <al.h>
#include <sndfile.h>
#include "CodeMeat.h"

/*
The following code excerpt is from Openal-soft alext.h to allow the use of multi-channel audio;

all credit->https://github.com/kcat/openal-soft
*/
#ifndef AL_EXT_BFORMAT
#define AL_EXT_BFORMAT 1
/* Provides support for B-Format ambisonic buffers (first-order, FuMa scaling
 * and layout).
 *
 * BFORMAT2D_8: Unsigned 8-bit, 3-channel non-periphonic (WXY).
 * BFORMAT2D_16: Signed 16-bit, 3-channel non-periphonic (WXY).
 * BFORMAT2D_FLOAT32: 32-bit float, 3-channel non-periphonic (WXY).
 * BFORMAT3D_8: Unsigned 8-bit, 4-channel periphonic (WXYZ).
 * BFORMAT3D_16: Signed 16-bit, 4-channel periphonic (WXYZ).
 * BFORMAT3D_FLOAT32: 32-bit float, 4-channel periphonic (WXYZ).
 */
#define AL_FORMAT_BFORMAT2D_8                    0x20021
#define AL_FORMAT_BFORMAT2D_16                   0x20022
#define AL_FORMAT_BFORMAT2D_FLOAT32              0x20023
#define AL_FORMAT_BFORMAT3D_8                    0x20031
#define AL_FORMAT_BFORMAT3D_16                   0x20032
#define AL_FORMAT_BFORMAT3D_FLOAT32              0x20033
#endif

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
	//MusicBuffer();

private:
	ALuint src;
	static const int BUFFER_SAMPLES = 8192;
	static const int NUM_BUFFERS = 4;
	ALuint buffers[NUM_BUFFERS];
	SNDFILE* sndFile;
	SF_INFO sfinfo;
	short* membuf;
	ALenum format;

	//MusicBuffer(){}
	
};
