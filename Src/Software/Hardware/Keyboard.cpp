#include "Keyboard.h"
namespace Software 
{
	namespace Hardware
	{
		Keyboard::Keyboard()
		{
			//Nothing to do here.
		}

		void Keyboard::PressButton(int Button, int Speed)
		{
			keybd_event(Button, 0, 0, 0);
			Sleep(Speed);
			keybd_event(Button, 0, KEYEVENTF_KEYUP, 0);
		}

		bool Keyboard::IsPressedButton(int Button)
		{
			return GetAsyncKeyState(Button);
		}
	}
}
