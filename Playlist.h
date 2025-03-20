#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "SongComponent.h"

namespace Deeznuts
{
	ref class Playlist
	{

	public:
		Playlist::Playlist(MyForm^ _form);

		void PlaySong(Sound^ _currentSong);
		bool PlayNextSong();
		bool PlayPreviousSong();

		void Add(SongComponent^ _song) { playlist.Add(_song); }
		void Remove(SongComponent^ _song) { playlist.Remove(_song); }

		void Import();
		void Save();

	private:

		System::Collections::Generic::List<SongComponent^> playlist;

		MyForm^ form;
		int id;
	};
}

#endif
