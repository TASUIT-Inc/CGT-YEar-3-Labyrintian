#include "AudioBuffer.h"
#include <inttypes.h>
#include "al.h"
#include "alc.h"
#include <sndfile.h>

AudioBuffer* AudioBuffer::get()
{
    static AudioBuffer* audioBuff = new AudioBuffer();
    return audioBuff;
}

ALuint AudioBuffer::addAudioFX(const char* filename)
{
    ALenum err, format;
    ALuint buffer;
    SNDFILE* sndfile;
    SF_INFO sfinfo;
    short* membuf;
    sf_count_t num_frames;
    ALsizei num_bytes;

    std::string FilePath = SFX_POOL_PATH + (std::string)filename;

    // Open the audio file
    sndfile = sf_open(FilePath.c_str(), SFM_READ, &sfinfo);
    if (!sndfile)
    {
        fprintf(stderr, "Could not open audio in %s: %s\n", FilePath.c_str(), sf_strerror(sndfile));
        return 0;
    }
    if (sfinfo.frames < 1 || sfinfo.frames >(sf_count_t)(INT_MAX / sizeof(short)) / sfinfo.channels)
    {
        fprintf(stderr, "Bad sample count in %s (%" PRId64 ")\n", FilePath.c_str(), sfinfo.frames);
        sf_close(sndfile);
        return 0;
    }

    // Get the sound format, and figure out the OpenAL format
    format = AL_NONE;
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
        if (sf_command(sndfile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT)
        {
            format = AL_FORMAT_BFORMAT2D_16;
        }
    }
    else if (sfinfo.channels == 4)
    {
        if (sf_command(sndfile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT)
            format = AL_FORMAT_BFORMAT3D_16;
    }
    if (!format)
    {
        fprintf(stderr, "Unsupported channel count: %d\n", sfinfo.channels);
        sf_close(sndfile);
        return 0;
    }

    // decode whole audio file into buffer
    membuf = static_cast<short*>(malloc((size_t)(sfinfo.frames * sfinfo.channels) * sizeof(short)));

    num_frames = sf_readf_short(sndfile, membuf, sfinfo.frames);
    if (num_frames < 1)
    {
        free(membuf);
        sf_close(sndfile);
        fprintf(stderr, "Failed to read samples in %s (%" PRId64 ")\n", FilePath.c_str(), num_frames);
        return 0;
    }

    num_bytes = (ALsizei)(num_frames * sfinfo.channels) * (ALsizei)sizeof(short);

    // Buffer audio data into new buffer obj, the free the data and close file
    buffer = 0;
    alGenBuffers(1, &buffer);
    alBufferData(buffer, format, membuf, num_bytes, sfinfo.samplerate);

    free(membuf);
    sf_close(sndfile);

    // check if error occured and clean up if so   
    err = alGetError();
    if (err != AL_NO_ERROR)
    {
        fprintf(stderr, "OpenAL Error: %s\n", alGetString(err));
        if (buffer && alIsBuffer(buffer))
        {
            alDeleteBuffers(1, &buffer);
        }
        return 0;
    }

    m_AudioFXBuffers.push_back(buffer);

    return buffer;
}

bool AudioBuffer::removeAudioFX(const ALuint& buffer)
{
    auto it = m_AudioFXBuffers.begin();
    while (it != m_AudioFXBuffers.end())
    {
        if (*it == buffer)
        {
            alDeleteBuffers(1, &*it);

            it = m_AudioFXBuffers.erase(it);

            return true;
        }
        else {
            ++it;
        }
    }
    return false;
}

AudioBuffer::AudioBuffer()
{
    m_AudioFXBuffers.clear();
}

AudioBuffer::~AudioBuffer()
{
    alDeleteBuffers(m_AudioFXBuffers.size(), m_AudioFXBuffers.data());

    m_AudioFXBuffers.clear();
}