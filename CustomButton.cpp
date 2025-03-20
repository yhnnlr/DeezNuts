#include "CustomButton.h"

namespace Deeznuts
{
	CustomButton::CustomButton(String^ _name, System::Drawing::Size _size)
	{
		String^ path = System::IO::Path::GetDirectoryName(System::Reflection::Assembly::GetExecutingAssembly()->Location);
		path += "/Assets/";

		idle = Drawing::Image::FromFile(path + _name + "/Idle.png");
		hovered = Drawing::Image::FromFile(path + _name + "/Hovered.png");
		clicked = Drawing::Image::FromFile(path + _name + "/Clicked.png");

		BackColor = System::Drawing::Color::Transparent;
		BackgroundImage = idle;
		BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
		FlatAppearance->BorderSize = 0;
		FlatAppearance->MouseDownBackColor = System::Drawing::Color::Transparent;
		FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
		FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		ForeColor = System::Drawing::SystemColors::ControlText;
		Name = L"playButton";
		Size = _size;
		TabIndex = 1;
		UseVisualStyleBackColor = false;

		MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Deeznuts::CustomButton::Button_MouseDown);
		MouseEnter += gcnew System::EventHandler(this, &Deeznuts::CustomButton::Button_MouseEnter);
		MouseLeave += gcnew System::EventHandler(this, &Deeznuts::CustomButton::Button_MouseLeave);
		MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Deeznuts::CustomButton::Button_MouseUp);
	}

	System::Void CustomButton::Button_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
		BackgroundImage = clicked;
	};

	System::Void CustomButton::Button_MouseEnter(System::Object^ sender, System::EventArgs^ e)
	{
		BackgroundImage = hovered;
	};

	System::Void CustomButton::Button_MouseLeave(System::Object^ sender, System::EventArgs^ e)
	{
		BackgroundImage = idle;
	};

	System::Void CustomButton::Button_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
		BackgroundImage = idle;
	};
}