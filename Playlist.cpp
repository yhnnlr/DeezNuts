#include "Playlist.h"
#include "SoundManager.h"

#include <ctime>

namespace Deeznuts
{
	Playlist::Playlist(MyForm^ _form)
	{
		form = _form;
	}

	void Playlist::PlaySong(Sound^ _currentSong)
	{
		SoundManager^ sm = SoundManager::Get();

		for (int i = 0; i < playlist.Count; i++)
		{
			if (playlist[i]->GetSound() == _currentSong)
			{
				id = i;
			}
		}

		if (sm->currentSound != nullptr)
		{
			sm->currentSound->Stop();
		}

		sm->currentSongComponent->SetPlaying(false);

		sm->currentSongComponent = playlist[id];
		sm->currentSound = playlist[id]->GetSound();

		if (sm->currentSound->type == Sound::FileType::OGG)
		{
			sm->currentSound->LoadOgg(SoundManager::ConvertSystemStringToChar(sm->currentSongComponent->GetPath()));
		}

		sm->currentSound->UpdateVolume(sm->volume);
		sm->currentSound->Play();
		sm->currentSongComponent->SetPlaying(true); 
	}

	bool Playlist::PlayNextSong()
	{
		SoundManager^ sm = SoundManager::Get();

		if (sm->currentSound == nullptr) return false;

		id++;

		if (id >= playlist.Count)
		{
			id = 0;
		}

		PlaySong(playlist[id]->GetSound());

		return true;
	}

	bool Playlist::PlayPreviousSong()
	{
		SoundManager^ sm = SoundManager::Get();

		if (sm->currentSound == nullptr) return false;

		id--;

		if (id < 0)
		{
			id = playlist.Count - 1;
		}

		PlaySong(playlist[id]->GetSound());

		return true;
	}

	void Playlist::Import()
	{
		OpenFileDialog^ ofd = gcnew OpenFileDialog();

		ofd->Filter = "TXT Files (*.txt)|*.txt";
		ofd->Title = "Select a TXT File";

		if (ofd->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			String^ file = ofd->FileName;

			System::IO::StreamReader^ reader = gcnew System::IO::StreamReader(file);

			String^ line;
			while (line = reader->ReadLine())
			{
				if (line->EndsWith(".ogg") || line->EndsWith(".wav"))
					Add(gcnew Deeznuts::SongComponent(form, line));
			}

			reader->Close();
		}
	}

	void Playlist::Save()
	{
		SaveFileDialog^ sfd = gcnew SaveFileDialog();
		sfd->Filter = "TXT Files (*.txt)|*.txt";
		sfd->Title = "Save Playlist As";
		sfd->FileName = "New playlist";

		if (sfd->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			String^ file = sfd->FileName;
			System::IO::StreamWriter^ writer = gcnew System::IO::StreamWriter(file);

			for (int i = 0; i < playlist.Count; i++)
			{
				writer->WriteLine(playlist[i]->GetPath());
			}
			writer->Close();
		}
	}
}