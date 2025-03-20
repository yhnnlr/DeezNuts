#ifndef BUTTON_H
#define BUTTON_H

namespace Deeznuts
{
	using namespace System;

	ref class CustomButton : System::Windows::Forms::Button
	{
	public:
		Drawing::Image^ idle;
		Drawing::Image^ hovered;
		Drawing::Image^ clicked;

		CustomButton(String^ name, System::Drawing::Size _size);

		System::Void Button_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
		System::Void Button_MouseEnter(System::Object^ sender, System::EventArgs^ e);
		System::Void Button_MouseLeave(System::Object^ sender, System::EventArgs^ e);
		System::Void Button_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
	};
}

#endif