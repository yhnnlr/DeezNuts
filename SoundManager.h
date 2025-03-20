#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include "Framework.h"
#include "Sound.hpp"
#include "MyForm.h"

namespace Deeznuts
{

	ref class SoundManager
	{
	private:
		static SoundManager^ sm = gcnew SoundManager();
		SoundManager();

	public:
		static SoundManager^ Get()
		{
			return sm;
		}

		static Sound^ currentSound = nullptr;
		static SongComponent^ currentSongComponent = nullptr;

		static float volume = 0.5f;

		~SoundManager();

		static const char* ConvertSystemStringToChar(System::String^ managedString) {
			if (managedString == nullptr)
				return nullptr;

			const char* nativeString = (const char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(managedString)).ToPointer();
			return nativeString;
		}
	};
}

#endif // !SOUNDMANAGER_H
