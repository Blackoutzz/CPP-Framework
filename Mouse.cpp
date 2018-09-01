#include "Mouse.h"
namespace Software
{
	namespace Hardware
	{
		Mouse::Mouse()
		{
			this->UpdatePositions();
		}

		void Mouse::LeftMouseButtonClick(int Speed)
		{
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			Sleep(Speed);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}

		void Mouse::RightMouseButtonClick(int Speed)
		{
			mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
			Sleep(Speed);
			mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
		}

		int Mouse::GetMousePositionX()
		{
			this->UpdatePositions();
			return this->Positions.PositionX;
		}

		int Mouse::GetMousePositionY()
		{
			this->UpdatePositions();
			return this->Positions.PositionY;
		}

		void Mouse::SetMousePositionX(int PositionX)
		{
			this->UpdatePositions();
			SetCursorPos(PositionX, this->Positions.PositionY);
		}

		void Mouse::SetMousePositionY(int PositionY)
		{
			this->UpdatePositions();
			SetCursorPos(this->Positions.PositionX, PositionY);
		}

		void Mouse::UpdatePositions()
		{
			GetCursorPos(&this->Cursor);
			this->Positions.PositionX = this->Cursor.x;
			this->Positions.PositionY = this->Cursor.y;
		}

		Vector2D Mouse::GetMousePositions()
		{
			this->UpdatePositions();
			return this->Positions;
		}

		void Mouse::SetMousePositions(int PositionX, int PositionY)
		{
			SetCursorPos(PositionX, PositionY);
		}

		Rect Mouse::GetMouseRect(int Size)
		{
			this->UpdatePositions();
			return Rect(this->Positions.PositionX, this->Positions.PositionY, 1 * Size, 2 * Size);
		}

		bool Mouse::IsPressedButton(int MouseButton)
		{
			//-13108 Unclicked
			INT keyState = GetAsyncKeyState(MouseButton);
			if (keyState != 0) {
				return true;
			}
			else {
				return false;
			}
		}
	}
}
