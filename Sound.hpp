#pragma once

#include "Framework.h"
#include "Vorbis\vorbisfile.h"

#define NUMBUFFERS              (4)
#define	SERVICE_UPDATE_PERIOD	(20)

class OggVorbisWrapper
{
public:
	static size_t ov_read_func(void* ptr, size_t size, size_t nmemb, void* datasource) {
		return fread(ptr, size, nmemb, (FILE*)datasource);
	}

	static int ov_seek_func(void* datasource, ogg_int64_t offset, int whence) {
		return fseek((FILE*)datasource, (long)offset, whence);
	}

	static int ov_close_func(void* datasource) {
		return fclose((FILE*)datasource);
	}

	static long ov_tell_func(void* datasource) {
		return ftell((FILE*)datasource);
	}
};

ref class Sound
{
public:
	Sound()
	{
		uiBuffer = new ALuint();
		uiSource = new ALuint();
		iState = new ALint();
	}

	~Sound()
	{
		alSourceStop(*uiSource);
		alDeleteSources(1, uiSource);
		alDeleteBuffers(1, uiBuffer);

		delete wrapper;
		wrapper = nullptr;
	}

	bool LoadWav(const char* _path);
	bool LoadOgg(const char* _path);
	void Update();

	const ALint* GetState()
	{
		alGetSourcei(*uiSource, AL_SOURCE_STATE, iState);
		return iState;
	}

	void Play() { alSourcePlay(*uiSource); }
	void Stop() { alSourceStop(*uiSource); }
	void Pause() { alSourcePause(*uiSource); }

	System::String^ GetTitle() { return title; }
	System::String^ GetArtist() { return artist; }

	void UpdateVolume(float _volume)
	{
		alSourcef(*uiSource, AL_GAIN, _volume);
	}

	enum class FileType
	{
		WAV,
		OGG
	};

	FileType type;

private:

	System::String^ title = gcnew System::String("");
	System::String^ artist = gcnew System::String("");

	// General
	ALuint* uiBuffer;
	ALuint* uiSource;
	ALint* iState;

	// OGG
	ALuint* uiBuffers;
	ALint iLoop;
	ALint* iBuffersProcessed = new ALint();
	ALint* iTotalBuffersProcessed = new ALint();
	ALint* iQueuedBuffers = new ALint();
	unsigned long	ulFrequency = 0;
	unsigned long	ulFormat = 0;
	unsigned long	ulChannels = 0;
	unsigned long	ulBufferSize;
	unsigned long	ulBytesWritten;
	char* pDecodeBuffer;

	HINSTANCE g_hVorbisFileDLL = NULL;

	// Functions
	void InitVorbisFile();
	void ShutdownVorbisFile();
	unsigned long DecodeOggVorbis(OggVorbis_File* psOggVorbisFile, char* pDecodeBuffer, unsigned long ulBufferSize, unsigned long ulChannels);
	void Swap(short& s1, short& s2);

	OggVorbisWrapper* wrapper = new OggVorbisWrapper();

	// Function pointers
	typedef int (*LPOVCLEAR)(OggVorbis_File* vf);
	typedef long (*LPOVREAD)(OggVorbis_File* vf, char* buffer, int length, int bigendianp, int word, int sgned, int* bitstream);
	typedef ogg_int64_t(*LPOVPCMTOTAL)(OggVorbis_File* vf, int i);
	typedef vorbis_info* (*LPOVINFO)(OggVorbis_File* vf, int link);
	typedef vorbis_comment* (*LPOVCOMMENT)(OggVorbis_File* vf, int link);
	typedef int (*LPOVOPENCALLBACKS)(void* datasource, OggVorbis_File* vf, char* initial, long ibytes, ov_callbacks callbacks);

	// Variables
	LPOVCLEAR			fn_ov_clear = NULL;
	LPOVREAD			fn_ov_read = NULL;
	LPOVPCMTOTAL		fn_ov_pcm_total = NULL;
	LPOVINFO			fn_ov_info = NULL;
	LPOVCOMMENT			fn_ov_comment = NULL;
	LPOVOPENCALLBACKS	fn_ov_open_callbacks = NULL;

	ov_callbacks* sCallbacks = new ov_callbacks();
	OggVorbis_File* sOggVorbisFile = new OggVorbis_File();
	vorbis_info* psVorbisInfo = new vorbis_info();

	bool g_bVorbisInit = false;
};