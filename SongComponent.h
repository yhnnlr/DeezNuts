#ifndef SONG_H
#define SONG_H

#include "Sound.hpp"

#include <msclr/marshal.h>

namespace Deeznuts
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	ref class MyForm;

	ref class SongComponent
	{
	public:
		SongComponent(MyForm^ _form, String^ _path);
		void SetPlaying(bool _state);

		Sound^ GetSound() { return localSound; }
		String^ GetPath() { return path; }

		void AddEqualizer() { if (!panel->Controls->Contains(equalizer)) panel->Controls->Add(equalizer); }
		void RemoveEqualizer() { if (panel->Controls->Contains(equalizer)) panel->Controls->Remove(equalizer); }

	private:
		MyForm^ form;

		Panel^ panel = gcnew Panel();

		Label^ songName = gcnew Label();
		Label^ artistName = gcnew Label();
		PictureBox^ equalizer = gcnew PictureBox();

		Button^ playButton = gcnew Button();
		Button^ deleteButton = gcnew Button();

		Sound^ localSound;

		String^ path;

		System::Void playButton_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void deleteButton_Click(System::Object^ sender, System::EventArgs^ e);

	};
}
#endif