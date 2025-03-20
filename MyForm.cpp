#include "MyForm.h"
#include "Sound.hpp"
#include "SoundManager.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace Deeznuts;

[STAThreadAttribute]
void Main(array<String^>^ args)
{
	SoundManager::Get();

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew MyForm());
}

MyForm::MyForm(void)
{
	InitializeComponent();
	InitializeCustomComponents();

	this->MaximizeBox = false;

	// center control buttons
	int totalButtonWidth = 0;
	for (int i = 0; i < controlPanel->Controls->Count; i++)
	{
		totalButtonWidth += controlPanel->Controls[i]->Width;
	}

	int panelWidth = controlPanel->ClientSize.Width;
	int horizontalPadding = (panelWidth - totalButtonWidth) / 2 - 36;
	controlPanel->Padding = System::Windows::Forms::Padding(horizontalPadding, 0, horizontalPadding, 0);
}

void MyForm::InitializeCustomComponents()
{
	pauseButton->Click += gcnew System::EventHandler(this, &Deeznuts::MyForm::Button_Pause);
	playButton->Click += gcnew System::EventHandler(this, &Deeznuts::MyForm::Button_Play);
	previousSong->Click += gcnew System::EventHandler(this, &Deeznuts::MyForm::Button_Previous);
	nextSong->Click += gcnew System::EventHandler(this, &Deeznuts::MyForm::Button_Next);
	stopSong->Click += gcnew System::EventHandler(this, &Deeznuts::MyForm::Button_Stop);

	controlPanel->Controls->Add(stopSong);
	controlPanel->Controls->Add(previousSong);
	controlPanel->Controls->Add(playButton);
	controlPanel->Controls->Add(nextSong);

	volumeLogo->SizeMode = PictureBoxSizeMode::Zoom;

	volumeBar->Value = 50.f;

	checkSoundTimer->Start();
	checkSoundTimer->Interval = 100; // Vérification toutes les 100 ms
	checkSoundTimer->Tick += gcnew EventHandler(this, &Deeznuts::MyForm::OnCheckSoundTimerTick);

	updateSoundTimer->Start();
	updateSoundTimer->Interval = 1;
	updateSoundTimer->Tick += gcnew EventHandler(this, &Deeznuts::MyForm::OnUpdateSoundTimerTick);
}

System::Void MyForm::ImportPlaylist_Click(System::Object^ sender, System::EventArgs^ e)
{
	playlist->Import();
}

System::Void MyForm::SavePlaylist_Click(System::Object^ sender, System::EventArgs^ e)
{
	playlist->Save();
}

System::Void MyForm::AddFromFile_Click(System::Object^ sender, System::EventArgs^ e)
{
	OpenFileDialog^ ofd = gcnew OpenFileDialog();

	ofd->Filter = "Audio Files (*.wav;*.ogg)|*.wav;*.ogg";
	ofd->Title = "Select an Audio File";

	if (ofd->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		String^ file = ofd->FileName;
		playlist->Add(gcnew Deeznuts::SongComponent(this, file));
	}
}

System::Void MyForm::AddFromFolder_Click(System::Object^ sender, System::EventArgs^ e)
{
	FolderBrowserDialog^ fbd = gcnew FolderBrowserDialog();

	fbd->Description = "Sélectionnez un dossier contenant des fichiers audio";

	if (fbd->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		String^ selectedFolder = fbd->SelectedPath;

		array<String^>^ files = System::IO::Directory::GetFiles(selectedFolder);
		for each (String ^ file in files)
		{
			if (file->EndsWith(".wav") || file->EndsWith(".ogg"))
			{
				playlist->Add(gcnew Deeznuts::SongComponent(this, file));
			}
		}
	}
}

System::Void  MyForm::volumeBar_Scroll(System::Object^ sender, System::EventArgs^ e)
{
	SoundManager^ sm = SoundManager::Get();

	sm->volume = volumeBar->Value / 100.f;

	if (!sm->currentSound) return;

	sm->currentSound->UpdateVolume(sm->volume);
}

System::Void MyForm::Button_Pause(System::Object^ sender, System::EventArgs^ e)
{
	SoundManager^ sm = SoundManager::Get();
	if (!sm->currentSound) return;

	sm->currentSound->Pause();

	controlPanel->Controls->Remove(pauseButton);
	controlPanel->Controls->Remove(nextSong);

	controlPanel->Controls->Add(playButton);
	controlPanel->Controls->Add(nextSong);

	sm->currentSongComponent->RemoveEqualizer();
}

System::Void MyForm::Button_Play(System::Object^ sender, System::EventArgs^ e)
{
	SoundManager^ sm = SoundManager::Get();

	if (!sm->currentSound) return;

	sm->currentSound->Play();

	controlPanel->Controls->Remove(playButton);
	controlPanel->Controls->Remove(nextSong);

	controlPanel->Controls->Add(pauseButton);
	controlPanel->Controls->Add(nextSong);

	sm->currentSongComponent->AddEqualizer();
}

System::Void MyForm::Button_Previous(System::Object^ sender, System::EventArgs^ e)
{
	if (!playlist->PlayPreviousSong()) return;
	if (!controlPanel->Controls->Contains(playButton)) return;

	controlPanel->Controls->Remove(playButton);
	controlPanel->Controls->Remove(nextSong);

	controlPanel->Controls->Add(pauseButton);
	controlPanel->Controls->Add(nextSong);
}

System::Void MyForm::Button_Next(System::Object^ sender, System::EventArgs^ e)
{
	if (!playlist->PlayNextSong()) return;
	if (!controlPanel->Controls->Contains(playButton)) return;

	controlPanel->Controls->Remove(playButton);
	controlPanel->Controls->Remove(nextSong);

	controlPanel->Controls->Add(pauseButton);
	controlPanel->Controls->Add(nextSong);
}

System::Void MyForm::Button_Stop(System::Object^ sender, System::EventArgs^ e)
{
	SoundManager^ sm = SoundManager::Get();

	if (!sm->currentSound) return;

	sm->currentSound->Stop();
	sm->currentSongComponent->SetPlaying(false);

	sm->currentSound = nullptr;
	sm->currentSongComponent = nullptr;

	controlPanel->Controls->Remove(pauseButton);
	controlPanel->Controls->Remove(nextSong);

	controlPanel->Controls->Add(playButton);
	controlPanel->Controls->Add(nextSong);
}

System::Void MyForm::OnCheckSoundTimerTick(System::Object^ sender, System::EventArgs^ e)
{
	SoundManager^ sm = SoundManager::Get();

	if (sm->currentSound == nullptr) return;

	if (*sm->currentSound->GetState() == AL_STOPPED)
	{
		playlist->PlayNextSong();
	}
}

System::Void MyForm::OnUpdateSoundTimerTick(System::Object^ sender, System::EventArgs^ e)
{
	SoundManager^ sm = SoundManager::Get();

	if (sm->currentSound == nullptr || controlPanel->Contains(playButton)) return;

	sm->currentSound->Update();
}