#include "AudioDevice.h"
#include <AL/al.h>
#include <stdio.h>
#include <vector>

static AudioDevice* instance = nullptr;

AudioDevice* AudioDevice::get()
{
    init();
    return instance;
}

void AudioDevice::init()
{
    if (instance == nullptr)
    {
        instance = new AudioDevice();
    }
}

void AudioDevice::GetLocation(float& x, float& y, float& z)
{
    alGetListener3f(AL_POSITION, &x, &y, &z);
}

void AudioDevice::GetOrientation(float& ori)
{
    alGetListenerfv(AL_ORIENTATION, &ori);
}

float AudioDevice::GetGain()
{
    float curr_gain;
    alGetListenerf(AL_GAIN, &curr_gain);
    return curr_gain;
}

void AudioDevice::SetLocation(const float& x, const float& y, const float& z)
{
    alListener3f(AL_POSITION, x, y, z);
}

void AudioDevice::SetOrientation(const float& atx, const float& aty, const float& atz, const float& upx, const float& upy, const float& upz)
{
    std::vector<float> ori;
    ori.push_back(atx);
    ori.push_back(aty);
    ori.push_back(atz);
    ori.push_back(upx);
    ori.push_back(upy);
    ori.push_back(upz);
    alListenerfv(AL_ORIENTATION, ori.data());
}

void AudioDevice::SetGain(const float& val)
{

    float newVol = val;
    if (newVol < 0.f)
    {
        newVol = 0.f;
    }
    else if (newVol > 5.f)
    {
        newVol = 5.f;
    }
    alListenerf(AL_GAIN, newVol);
}

AudioDevice::AudioDevice()
{
    m_ALCDevice = alcOpenDevice(nullptr); // get default device
    if (!m_ALCDevice)
        throw("Failed to get audio device");

    m_ALCContext = alcCreateContext(m_ALCDevice, nullptr); // create context
    if (!m_ALCContext)
        throw("Failed to get audio context");

    if (!alcMakeContextCurrent(m_ALCContext)) //make context current
        throw("Failed to make context current");

    const ALCchar* name = nullptr;
    if (alcIsExtensionPresent(m_ALCDevice, "ALC_ENUMERATE_ALL_EXT"))
        name = alcGetString(m_ALCDevice, ALC_ALL_DEVICES_SPECIFIER);
    if (!name || alcGetError(m_ALCDevice) != AL_NO_ERROR)
        name = alcGetString(m_ALCDevice, ALC_DEVICE_SPECIFIER);
    //  printf("Opened \"$s\"\n", name);
    printf("Opened \"%s\"\n", name);

}

AudioDevice::~AudioDevice()
{

    alcMakeContextCurrent(nullptr);
    alcDestroyContext(m_ALCContext);
    alcCloseDevice(m_ALCDevice);

    /*if (!alcMakeContextCurrent(nullptr))
        throw("Failed to set context to nullptr");

    alcDestroyContext(m_ALCContext);
    if (m_ALCContext)
        throw("Failed to unset during close");

    if (!alcCloseDevice(m_ALCDevice))
        throw("Failed to close audio device");*/
}