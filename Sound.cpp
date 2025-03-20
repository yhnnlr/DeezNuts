#include "Sound.hpp"

#include <stdlib.h>
#include <fstream>
#include <vector>


bool Sound::LoadWav(const char* _path)
{
	// Generate an AL Buffer
	alGenBuffers(1, uiBuffer);

	// Load Wave file into OpenAL Buffer
	if (!ALFWLoadWaveToBuffer(_path, *uiBuffer))
	{
		System::Windows::Forms::MessageBox::Show("Failed to load " + gcnew System::String(_path));
		return false;
	}

	// Generate a Source to playback the Buffer
	alGenSources(1, uiSource);

	// Attach Source to Buffer
	alSourcei(*uiSource, AL_BUFFER, *uiBuffer);

	title = System::IO::Path::GetFileName(gcnew System::String(_path));
	artist = gcnew System::String("Unknown");

	type = FileType::WAV;
	return true;
}

bool Sound::LoadOgg(const char* _path)
{
	uiBuffers = new ALuint[NUMBUFFERS];

	InitVorbisFile();
	if (!g_bVorbisInit)
	{
		System::Windows::Forms::MessageBox::Show("Failed to init");
		ShutdownVorbisFile();
		return false;
	}

	sCallbacks->read_func = wrapper->ov_read_func;
	sCallbacks->seek_func = wrapper->ov_seek_func;
	sCallbacks->close_func = wrapper->ov_close_func;
	sCallbacks->tell_func = wrapper->ov_tell_func;

	FILE* pOggVorbisFile = fopen(_path, "rb");
	if (!pOggVorbisFile)
	{
		System::Windows::Forms::MessageBox::Show("Failed to load " + gcnew System::String(_path));
		ShutdownVorbisFile();
		return false;
	}

	if (fn_ov_open_callbacks(pOggVorbisFile, sOggVorbisFile, NULL, 0, *sCallbacks) != 0)
	{
		System::Windows::Forms::MessageBox::Show("Failed to open OggVorbis stream.");
		fclose(pOggVorbisFile);
		ShutdownVorbisFile();
		return false;
	}

	psVorbisInfo = fn_ov_info(sOggVorbisFile, -1);
	if (!psVorbisInfo)
	{
		System::Windows::Forms::MessageBox::Show("Failed to retrieve OggVorbis file info.");
		fn_ov_clear(sOggVorbisFile);
		fclose(pOggVorbisFile);
		ShutdownVorbisFile();
		return false;
	}

	ulFrequency = psVorbisInfo->rate;
	ulChannels = psVorbisInfo->channels;
	ulFormat = (ulChannels == 1) ? AL_FORMAT_MONO16 :
		(ulChannels == 2) ? AL_FORMAT_STEREO16 : 0;

	if (ulFormat == 0)
	{
		System::Windows::Forms::MessageBox::Show("Unsupported channel count.");
		fn_ov_clear(sOggVorbisFile);
		fclose(pOggVorbisFile);
		ShutdownVorbisFile();
		return false;
	}

	ulBufferSize = ulFrequency * ulChannels * sizeof(short) / 4;
	ulBufferSize -= ulBufferSize % (ulChannels * sizeof(short));

	pDecodeBuffer = (char*)malloc(ulBufferSize);
	if (!pDecodeBuffer)
	{
		System::Windows::Forms::MessageBox::Show("Failed to allocate decode buffer.");
		fn_ov_clear(sOggVorbisFile);
		fclose(pOggVorbisFile);
		ShutdownVorbisFile();
		return false;
	}

	alGenBuffers(NUMBUFFERS, uiBuffers);
	alGenSources(1, uiSource);

	for (int i = 0; i < NUMBUFFERS; ++i)
	{
		ulBytesWritten = DecodeOggVorbis(sOggVorbisFile, pDecodeBuffer, ulBufferSize, ulChannels);
		if (ulBytesWritten > 0)
		{
			alBufferData(uiBuffers[i], ulFormat, pDecodeBuffer, ulBytesWritten, ulFrequency);
			alSourceQueueBuffers(*uiSource, 1, &uiBuffers[i]);
		}
	}

	vorbis_comment* comment = fn_ov_comment(sOggVorbisFile, -1);

	if (comment->comments >= 2)
	{
		title = gcnew System::String(comment->user_comments[0]);
		title = title->Substring(title->IndexOf('=') + 1);

		artist = gcnew System::String(comment->user_comments[1]);
		artist = artist->Substring(artist->IndexOf('=') + 1);
	}

	*iTotalBuffersProcessed = 0;
	type = FileType::OGG;
	return true;
}

#pragma region OGG
void Sound::InitVorbisFile()
{
	if (g_bVorbisInit)
		return;

	// Try and load Vorbis DLLs (VorbisFile.dll will load ogg.dll and vorbis.dll)
	g_hVorbisFileDLL = LoadLibrary(L"vorbisfile.dll");
	if (g_hVorbisFileDLL)
	{
		fn_ov_clear = (LPOVCLEAR)GetProcAddress(g_hVorbisFileDLL, "ov_clear");
		fn_ov_read = (LPOVREAD)GetProcAddress(g_hVorbisFileDLL, "ov_read");
		fn_ov_pcm_total = (LPOVPCMTOTAL)GetProcAddress(g_hVorbisFileDLL, "ov_pcm_total");
		fn_ov_info = (LPOVINFO)GetProcAddress(g_hVorbisFileDLL, "ov_info");
		fn_ov_comment = (LPOVCOMMENT)GetProcAddress(g_hVorbisFileDLL, "ov_comment");
		fn_ov_open_callbacks = (LPOVOPENCALLBACKS)GetProcAddress(g_hVorbisFileDLL, "ov_open_callbacks");

		if (fn_ov_clear && fn_ov_read && fn_ov_pcm_total && fn_ov_info &&
			fn_ov_comment && fn_ov_open_callbacks)
		{
			g_bVorbisInit = true;
		}
	}
}

void Sound::ShutdownVorbisFile()
{
	if (g_hVorbisFileDLL)
	{
		FreeLibrary(g_hVorbisFileDLL);
		g_hVorbisFileDLL = NULL;
	}
	g_bVorbisInit = false;
}

unsigned long Sound::DecodeOggVorbis(OggVorbis_File* psOggVorbisFile, char* pDecodeBuffer, unsigned long ulBufferSize, unsigned long ulChannels)
{
	int current_section;
	long lDecodeSize;
	unsigned long ulSamples;
	short* pSamples;

	unsigned long ulBytesDone = 0;
	while (1)
	{
		lDecodeSize = fn_ov_read(psOggVorbisFile, pDecodeBuffer + ulBytesDone, ulBufferSize - ulBytesDone, 0, 2, 1, &current_section);
		if (lDecodeSize > 0)
		{
			ulBytesDone += lDecodeSize;

			if (ulBytesDone >= ulBufferSize)
				break;
		}
		else
		{
			break;
		}
	}

	// Mono, Stereo and 4-Channel files decode into the same channel order as WAVEFORMATEXTENSIBLE,
	// however 6-Channels files need to be re-ordered
	if (ulChannels == 6)
	{
		pSamples = (short*)pDecodeBuffer;
		for (ulSamples = 0; ulSamples < (ulBufferSize >> 1); ulSamples += 6)
		{
			// WAVEFORMATEXTENSIBLE Order : FL, FR, FC, LFE, RL, RR
			// OggVorbis Order            : FL, FC, FR,  RL, RR, LFE
			Swap(pSamples[ulSamples + 1], pSamples[ulSamples + 2]);
			Swap(pSamples[ulSamples + 3], pSamples[ulSamples + 5]);
			Swap(pSamples[ulSamples + 4], pSamples[ulSamples + 5]);
		}
	}

	return ulBytesDone;
}

void Sound::Swap(short& s1, short& s2)
{
	short sTemp = s1;
	s1 = s2;
	s2 = sTemp;
}

void Sound::Update()
{
	if (type != FileType::OGG) return;

	// récupère tt les buffers déjà processed
	alGetSourcei(*uiSource, AL_BUFFERS_PROCESSED, iBuffersProcessed);

	while (*iBuffersProcessed > 0)
	{
		// vide la queue
		ALuint buffer;
		alSourceUnqueueBuffers(*uiSource, 1, &buffer);

		// décode la prochaine partie du son (de taille ulBuffserSize)
		ulBytesWritten = DecodeOggVorbis(sOggVorbisFile, pDecodeBuffer, ulBufferSize, ulChannels);
		if (ulBytesWritten > 0)
		{
			// ajoute un nouveau buffer qui contient la suite du son à la queue
			alBufferData(buffer, ulFormat, pDecodeBuffer, ulBytesWritten, ulFrequency);
			alSourceQueueBuffers(*uiSource, 1, &buffer);
		}

		(*iBuffersProcessed)--;
	}

	// là c'est un edge case, si ton son est terminé on vérifie si t'as pas eu des pertes audio dans le fichier.
	// Si t'en as eu alors le son s'est stoppé, mais il reste des buffers dans la queue.
	// On cherche si il en reste, si oui alors on relance le son depuis le prochain buffer non endommagé, sinon c'est que le son est juste fini
	alGetSourcei(*uiSource, AL_SOURCE_STATE, iState);
	if (*iState != AL_PLAYING)
	{
		ALint queued;
		alGetSourcei(*uiSource, AL_BUFFERS_QUEUED, &queued);

		if (queued > 0)
		{
			alSourcePlay(*uiSource);
		}
	}
}
#pragma endregion