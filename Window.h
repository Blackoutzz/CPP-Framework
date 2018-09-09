#pragma once
#include "Included.h"

namespace Software
{
	namespace Interface 
	{
		class Window
		{
			public:

				Window(string Name);

				RECT GetRectangle();

				Vector2D GetPositions();

				int GetWidth();

				int GetHeight();

				string GetName();

				HWND GetHandle();

				HDC GetDeviceContext();

				bool IsActive();

				bool IsAlive();

				MARGINS GetMargin();

				void Destroy();

				bool IsFullScreen();

				void CreateNewWindow();

				bool ResizeToWindow(Window * Window);

				Rect GetNewRectangle();

			protected:

				bool Active;

				bool Alive;

				HDC DeviceContext;

				string Name;

				int Height;

				int Width;

				RECT Rectangle;

				Vector2D Positions;

				HWND Handle;

				MARGINS Margin;

				bool FullScreen;

		};
	}
}