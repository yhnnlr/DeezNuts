#include "SongComponent.h"
#include "SoundManager.h"

namespace Deeznuts
{
	SongComponent::SongComponent(MyForm^ _form, String^ _path)
	{
		form = _form;
		path = _path;

		localSound = gcnew Sound();
		if (_path->EndsWith(".wav"))
		{
			if (!localSound->LoadWav(SoundManager::ConvertSystemStringToChar(_path))) return;
		}
		else if (_path->EndsWith(".ogg"))
		{
			if (!localSound->LoadOgg(SoundManager::ConvertSystemStringToChar(_path))) return;
		}

		panel->Size = System::Drawing::Size(488, 70);

		songName->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
		songName->ForeColor = System::Drawing::SystemColors::ControlLight;
		songName->Location = System::Drawing::Point(55, 12);
		songName->Margin = System::Windows::Forms::Padding(0);
		songName->Name = L"Song";
		songName->RightToLeft = System::Windows::Forms::RightToLeft::No;
		songName->Size = System::Drawing::Size(237, 25);
		songName->TabIndex = 0;
		songName->Text = localSound->GetTitle();

		artistName->AutoSize = true;
		artistName->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
		artistName->ForeColor = System::Drawing::SystemColors::ControlLight;
		artistName->Location = System::Drawing::Point(57, 37);
		artistName->Margin = System::Windows::Forms::Padding(0);
		artistName->Name = L"Artist";
		artistName->Size = System::Drawing::Size(53, 17);
		artistName->TabIndex = 1;
		artistName->Text = localSound->GetArtist();

		String^ path = System::IO::Path::GetDirectoryName(System::Reflection::Assembly::GetExecutingAssembly()->Location);
		path += "/Assets/";

		equalizer->BackColor = System::Drawing::Color::Transparent;
		equalizer->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
		equalizer->Image = System::Drawing::Image::FromFile(path + L"equalizer.gif");
		equalizer->Location = System::Drawing::Point(339, 21);
		equalizer->Name = L"Equalizer";
		equalizer->Size = System::Drawing::Size(25, 25);
		equalizer->TabIndex = 11;
		equalizer->TabStop = false;
		equalizer->SizeMode = PictureBoxSizeMode::Zoom;

		playButton->BackgroundImage = System::Drawing::Image::FromFile(path + L"play.png");
		playButton->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
		playButton->FlatAppearance->BorderSize = 0;
		playButton->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Transparent;
		playButton->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
		playButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		playButton->Location = System::Drawing::Point(0, 0);
		playButton->Name = L"PlayButton";
		playButton->Size = System::Drawing::Size(50, 67);
		playButton->TabIndex = 2;
		playButton->UseVisualStyleBackColor = true;
		playButton->Click += gcnew System::EventHandler(this, &Deeznuts::SongComponent::playButton_Click);

		deleteButton->BackgroundImage = System::Drawing::Image::FromFile(path + L"delete.png");
		deleteButton->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
		deleteButton->FlatAppearance->BorderSize = 0;
		deleteButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		deleteButton->Location = System::Drawing::Point(450, 22);
		deleteButton->Name = L"button2";
		deleteButton->Size = System::Drawing::Size(25, 27);
		deleteButton->TabIndex = 4;
		deleteButton->UseVisualStyleBackColor = true;
		deleteButton->Click += gcnew System::EventHandler(this, &Deeznuts::SongComponent::deleteButton_Click);

		panel->Controls->Add(songName);
		panel->Controls->Add(artistName);
		panel->Controls->Add(playButton);
		panel->Controls->Add(deleteButton);

		form->songList->Controls->Add(panel);
	}

	System::Void SongComponent::playButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		SoundManager^ sm = SoundManager::Get();

		if (sm->currentSongComponent)
		{
			sm->currentSongComponent->SetPlaying(false);
		}
		sm->currentSongComponent = this;

		if (SoundManager::Get()->currentSound != nullptr)
		{
			sm->currentSound->Stop();
		}
		sm->currentSound = localSound;

		form->playlist->PlaySong(sm->currentSound);

		form->controlPanel->Controls->Remove(form->playButton);
		form->controlPanel->Controls->Remove(form->nextSong);

		form->controlPanel->Controls->Add(form->pauseButton);
		form->controlPanel->Controls->Add(form->nextSong);
		SetPlaying(true);
	}

	System::Void SongComponent::deleteButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		SoundManager^ sm = SoundManager::Get();

		if (sm->currentSound == localSound && sm->currentSongComponent == this)
		{
			sm->currentSound = nullptr;
			sm->currentSongComponent = nullptr;

			form->controlPanel->Controls->Remove(form->pauseButton);
			form->controlPanel->Controls->Remove(form->nextSong);

			form->controlPanel->Controls->Add(form->playButton);
			form->controlPanel->Controls->Add(form->nextSong);
		}

		form->songList->Controls->Remove(panel);
		delete localSound;
		form->playlist->Remove(this);
	}

	void SongComponent::SetPlaying(bool _state)
	{
		if (_state)
		{
			songName->ForeColor = System::Drawing::Color::LimeGreen;
			artistName->ForeColor = System::Drawing::Color::LimeGreen;
			panel->Controls->Add(equalizer);
		}
		else
		{
			songName->ForeColor = System::Drawing::SystemColors::ControlLight;
			artistName->ForeColor = System::Drawing::SystemColors::ControlLight;
			panel->Controls->Remove(equalizer);
		}
	}
}