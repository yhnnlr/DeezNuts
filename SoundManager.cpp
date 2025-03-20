#include "SoundManager.h"

namespace Deeznuts
{
	SoundManager::SoundManager()
	{
		ALFWInit();

		if (!ALFWInitOpenAL())
		{
			System::Windows::Forms::MessageBox::Show("Failed to initialize OpenAL\n");
			ALFWShutdown();
			return;
		}
	}

	SoundManager::~SoundManager()
	{
		ALFWShutdownOpenAL();

		ALFWShutdown();
	}
}