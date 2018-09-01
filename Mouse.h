#pragma once
#include "Included.h"

namespace Software 
{
	namespace Hardware 
	{
		class Mouse
		{
			static enum buttons : int {
				Left_Mouse_Button = 0x01,
				Right_Mouse_Button = 0x02,
				Cancel_Button = 0x03,
				Middle_Mouse_Button = 0x04,
				Next_Mouse_Button = 0x05,
				Previous_Mouse_Button = 0x06
			};

		protected:

			POINT Cursor;

			Vector2D Positions;

			void UpdatePositions();

		public:

			Mouse();

			void SetMousePositions(int PositionX = 0, int PositionY = 0);

			void SetMousePositionX(int PositionX = 0);

			void SetMousePositionY(int PositionY = 0);

			int GetMousePositionX();

			int GetMousePositionY();

			Vector2D GetMousePositions();

			void LeftMouseButtonClick(int Speed = 0);

			void RightMouseButtonClick(int Speed = 0);

			Rect GetMouseRect(int Size = 1);

			bool IsPressedButton(int MouseButton);

		};
	}
}
