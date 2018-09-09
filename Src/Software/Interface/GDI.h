#pragma once
#include "../Included.h"
#include "Window.h"

namespace Software 
{
	namespace Interface
	{

		#define RGBA(r,g,b,a) ((COLORREF)((((DWORD)(BYTE)(a))<<24) | RGB(r,g,b)))

		class GDI
		{
			enum Colors
			{
				Red = RGB(255, 0, 0),
				Green = RGB(0, 255, 0),
				Blue = RGB(255, 0, 42),
				White = RGB(255, 255, 255),
				Black = RGB(0, 0, 0),
				Grey = RGB(127, 127, 127),
				Dark_Grey = RGB(63, 63, 63),
				Light_Grey = RGB(190, 190, 190),
				Transparent = RGBA(0, 0, 0, 0),
				Text_Background = RGB(100, 100, 100),
				Text_Shadow = RGB(1, 1, 1)
			};

		protected:

			Interface::Window * Window;

			HFONT Font;

			HDC DeviceContextHandle;

		public:

			//Construct
			GDI(Interface::Window * Window);

			//Function to draw a line
			void DrawLine(float StartX, float StartY, float EndX, float EndY, COLORREF Color);

			//Function to draw a rectangle
			void DrawRectangle(HBRUSH Brush, int PositionX, int PositionY, int Width, int Height);

			//Function to draw a border
			void DrawBorderBox(HBRUSH Brush, int PositionX, int PositionY, int Width, int Height, int Thickness);

			//Function to draw a string
			void DrawString(int PositionX, int PositionY, COLORREF Color, const char * Text);

		};
	}
}
