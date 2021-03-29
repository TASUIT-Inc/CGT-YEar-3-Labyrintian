#pragma once
#include <alc.h>

#define SD_INIT AudioDevice::init();
#define LISTENER AudioDevice::get()

class AudioDevice
{
public:
	static AudioDevice* get();
	static void init();

	void GetLocation(float& x, float& y, float& z);
	void GetOrientation(float& ori);
	float GetGain();

	void SetLocation(const float& x, const float& y, const float& z);
	void SetOrientation(const float& atx, const float& aty, const float& atz,
		const float& upx, const float& upy, const float& upz);
	void SetGain(const float& val);



private:
	AudioDevice();
	~AudioDevice();

	ALCdevice* m_ALCDevice;
	ALCcontext* m_ALCContext;

};
