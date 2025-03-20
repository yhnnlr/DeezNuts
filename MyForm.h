#pragma once
#include "CustomButton.h"
#include "SongComponent.h"
#include "Sound.hpp"
#include "Playlist.h"
#include <vector>

namespace Deeznuts {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Description résumée de MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void);
	private: System::Windows::Forms::PictureBox^ Title;
	private: System::Windows::Forms::Button^ ImportPlaylist;
	private: System::Windows::Forms::FlowLayoutPanel^ MenuButtons;
	private: System::Windows::Forms::Button^ SavePlaylist;
	private: System::Windows::Forms::Button^ AddFromFile;
	private: System::Windows::Forms::Button^ AddFromFolder;
	private: System::Windows::Forms::TrackBar^ volumeBar;

	public:
		Deeznuts::CustomButton^ playButton = gcnew CustomButton(gcnew String("PlayButton"), System::Drawing::Size(36, 36));
		Deeznuts::CustomButton^ pauseButton = gcnew CustomButton(gcnew String("PauseButton"), System::Drawing::Size(36, 36));
		Deeznuts::CustomButton^ nextSong = gcnew CustomButton(gcnew String("NextSong"), System::Drawing::Size(36, 36));
		Deeznuts::CustomButton^ previousSong = gcnew CustomButton(gcnew String("PreviousSong"), System::Drawing::Size(36, 36));
		Deeznuts::CustomButton^ stopSong = gcnew CustomButton(gcnew String("StopButton"), System::Drawing::Size(36, 36));
		Deeznuts::Playlist^ playlist = gcnew Playlist(this);
	private: System::Windows::Forms::PictureBox^ volumeLogo;

	public:

	public:
		Timer^ checkSoundTimer = gcnew Timer();
		Timer^ updateSoundTimer = gcnew Timer();

	protected:
		/// <summary>
		/// Nettoyage des ressources utilisées.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	public: System::Windows::Forms::FlowLayoutPanel^ controlPanel;
		  System::Windows::Forms::FlowLayoutPanel^ songList;
	private: System::ComponentModel::IContainer^ components;

#pragma region Windows Form Designer generated code
		   /// <summary>
		   /// Méthode requise pour la prise en charge du concepteur - ne modifiez pas
		   /// le contenu de cette méthode avec l'éditeur de code.
		   /// </summary>
		   void InitializeComponent(void)
		   {
			   System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			   this->controlPanel = (gcnew System::Windows::Forms::FlowLayoutPanel());
			   this->songList = (gcnew System::Windows::Forms::FlowLayoutPanel());
			   this->Title = (gcnew System::Windows::Forms::PictureBox());
			   this->ImportPlaylist = (gcnew System::Windows::Forms::Button());
			   this->MenuButtons = (gcnew System::Windows::Forms::FlowLayoutPanel());
			   this->SavePlaylist = (gcnew System::Windows::Forms::Button());
			   this->AddFromFile = (gcnew System::Windows::Forms::Button());
			   this->AddFromFolder = (gcnew System::Windows::Forms::Button());
			   this->volumeBar = (gcnew System::Windows::Forms::TrackBar());
			   this->volumeLogo = (gcnew System::Windows::Forms::PictureBox());
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Title))->BeginInit();
			   this->MenuButtons->SuspendLayout();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->volumeBar))->BeginInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->volumeLogo))->BeginInit();
			   this->SuspendLayout();
			   // 
			   // controlPanel
			   // 
			   this->controlPanel->Location = System::Drawing::Point(0, 437);
			   this->controlPanel->Name = L"controlPanel";
			   this->controlPanel->Size = System::Drawing::Size(935, 47);
			   this->controlPanel->TabIndex = 1;
			   this->controlPanel->WrapContents = false;
			   // 
			   // songList
			   // 
			   this->songList->AutoScroll = true;
			   this->songList->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			   this->songList->FlowDirection = System::Windows::Forms::FlowDirection::TopDown;
			   this->songList->Location = System::Drawing::Point(402, 113);
			   this->songList->Name = L"songList";
			   this->songList->Size = System::Drawing::Size(522, 282);
			   this->songList->TabIndex = 2;
			   this->songList->WrapContents = false;
			   // 
			   // Title
			   // 
			   this->Title->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Title.Image")));
			   this->Title->Location = System::Drawing::Point(3, 12);
			   this->Title->Name = L"Title";
			   this->Title->Size = System::Drawing::Size(932, 75);
			   this->Title->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			   this->Title->TabIndex = 3;
			   this->Title->TabStop = false;
			   // 
			   // ImportPlaylist
			   // 
			   this->ImportPlaylist->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ImportPlaylist.BackgroundImage")));
			   this->ImportPlaylist->FlatAppearance->BorderSize = 0;
			   this->ImportPlaylist->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Black;
			   this->ImportPlaylist->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				   static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			   this->ImportPlaylist->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			   this->ImportPlaylist->Location = System::Drawing::Point(0, 0);
			   this->ImportPlaylist->Margin = System::Windows::Forms::Padding(0);
			   this->ImportPlaylist->Name = L"ImportPlaylist";
			   this->ImportPlaylist->Size = System::Drawing::Size(282, 70);
			   this->ImportPlaylist->TabIndex = 5;
			   this->ImportPlaylist->UseVisualStyleBackColor = true;
			   this->ImportPlaylist->Click += gcnew System::EventHandler(this, &MyForm::ImportPlaylist_Click);
			   // 
			   // MenuButtons
			   // 
			   this->MenuButtons->Controls->Add(this->ImportPlaylist);
			   this->MenuButtons->Controls->Add(this->SavePlaylist);
			   this->MenuButtons->Controls->Add(this->AddFromFile);
			   this->MenuButtons->Controls->Add(this->AddFromFolder);
			   this->MenuButtons->Location = System::Drawing::Point(45, 113);
			   this->MenuButtons->Margin = System::Windows::Forms::Padding(0);
			   this->MenuButtons->Name = L"MenuButtons";
			   this->MenuButtons->Size = System::Drawing::Size(311, 282);
			   this->MenuButtons->TabIndex = 8;
			   // 
			   // SavePlaylist
			   // 
			   this->SavePlaylist->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"SavePlaylist.BackgroundImage")));
			   this->SavePlaylist->FlatAppearance->BorderSize = 0;
			   this->SavePlaylist->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Black;
			   this->SavePlaylist->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				   static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			   this->SavePlaylist->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			   this->SavePlaylist->Location = System::Drawing::Point(0, 70);
			   this->SavePlaylist->Margin = System::Windows::Forms::Padding(0);
			   this->SavePlaylist->Name = L"SavePlaylist";
			   this->SavePlaylist->Size = System::Drawing::Size(282, 70);
			   this->SavePlaylist->TabIndex = 6;
			   this->SavePlaylist->UseVisualStyleBackColor = true;
			   this->SavePlaylist->Click += gcnew System::EventHandler(this, &MyForm::SavePlaylist_Click);
			   // 
			   // AddFromFile
			   // 
			   this->AddFromFile->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"AddFromFile.BackgroundImage")));
			   this->AddFromFile->FlatAppearance->BorderSize = 0;
			   this->AddFromFile->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Black;
			   this->AddFromFile->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				   static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			   this->AddFromFile->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			   this->AddFromFile->Location = System::Drawing::Point(0, 140);
			   this->AddFromFile->Margin = System::Windows::Forms::Padding(0);
			   this->AddFromFile->Name = L"AddFromFile";
			   this->AddFromFile->Size = System::Drawing::Size(282, 70);
			   this->AddFromFile->TabIndex = 7;
			   this->AddFromFile->UseVisualStyleBackColor = true;
			   this->AddFromFile->Click += gcnew System::EventHandler(this, &MyForm::AddFromFile_Click);
			   // 
			   // AddFromFolder
			   // 
			   this->AddFromFolder->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"AddFromFolder.BackgroundImage")));
			   this->AddFromFolder->FlatAppearance->BorderSize = 0;
			   this->AddFromFolder->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Black;
			   this->AddFromFolder->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				   static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			   this->AddFromFolder->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			   this->AddFromFolder->Location = System::Drawing::Point(0, 210);
			   this->AddFromFolder->Margin = System::Windows::Forms::Padding(0);
			   this->AddFromFolder->Name = L"AddFromFolder";
			   this->AddFromFolder->Size = System::Drawing::Size(282, 70);
			   this->AddFromFolder->TabIndex = 8;
			   this->AddFromFolder->UseVisualStyleBackColor = true;
			   this->AddFromFolder->Click += gcnew System::EventHandler(this, &MyForm::AddFromFolder_Click);
			   // 
			   // volumeBar
			   // 
			   this->volumeBar->LargeChange = 0;
			   this->volumeBar->Location = System::Drawing::Point(831, 465);
			   this->volumeBar->Maximum = 100;
			   this->volumeBar->Name = L"volumeBar";
			   this->volumeBar->RightToLeft = System::Windows::Forms::RightToLeft::No;
			   this->volumeBar->Size = System::Drawing::Size(104, 45);
			   this->volumeBar->TabIndex = 10;
			   this->volumeBar->TickStyle = System::Windows::Forms::TickStyle::None;
			   this->volumeBar->Value = 50;
			   this->volumeBar->Scroll += gcnew System::EventHandler(this, &MyForm::volumeBar_Scroll);
			   // 
			   // volumeLogo
			   // 
			   this->volumeLogo->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"volumeLogo.Image")));
			   this->volumeLogo->Location = System::Drawing::Point(808, 465);
			   this->volumeLogo->Name = L"volumeLogo";
			   this->volumeLogo->Size = System::Drawing::Size(20, 20);
			   this->volumeLogo->TabIndex = 11;
			   this->volumeLogo->TabStop = false;
			   // 
			   // MyForm
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(16)), static_cast<System::Int32>(static_cast<System::Byte>(16)),
				   static_cast<System::Int32>(static_cast<System::Byte>(16)));
			   this->ClientSize = System::Drawing::Size(936, 496);
			   this->Controls->Add(this->volumeLogo);
			   this->Controls->Add(this->volumeBar);
			   this->Controls->Add(this->MenuButtons);
			   this->Controls->Add(this->Title);
			   this->Controls->Add(this->songList);
			   this->Controls->Add(this->controlPanel);
			   this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			   this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			   this->Name = L"MyForm";
			   this->Text = L"Deeznuts";
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Title))->EndInit();
			   this->MenuButtons->ResumeLayout(false);
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->volumeBar))->EndInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->volumeLogo))->EndInit();
			   this->ResumeLayout(false);
			   this->PerformLayout();

		   }

		   void InitializeCustomComponents();

#pragma endregion

	private: System::Void ImportPlaylist_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void SavePlaylist_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void AddFromFile_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void AddFromFolder_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void volumeBar_Scroll(System::Object^ sender, System::EventArgs^ e);
	private: System::Void Button_Play(System::Object^ sender, System::EventArgs^ e);
	private: System::Void Button_Pause(System::Object^ sender, System::EventArgs^ e);
	private: System::Void Button_Next(System::Object^ sender, System::EventArgs^ e);
	private: System::Void Button_Previous(System::Object^ sender, System::EventArgs^ e);
	private: System::Void Button_Stop(System::Object^ sender, System::EventArgs^ e);
	private: System::Void OnCheckSoundTimerTick(System::Object^ sender, System::EventArgs^ e);
	private: System::Void OnUpdateSoundTimerTick(System::Object^ sender, System::EventArgs^ e);
	};
}