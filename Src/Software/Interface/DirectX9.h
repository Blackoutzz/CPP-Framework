#pragma once
#include "../Included.h"
#include "Window.h"
#include "../Hardware/Mouse.h"

namespace Software 
{
	namespace Interface
	{
		class DirectX9 
		{

			protected:

				IDirect3D9Ex * Object;

				IDirect3DDevice9Ex* Device;

				D3DPRESENT_PARAMETERS Params;

				ID3DXLine* Line;

				ID3DXFont* Font;

				Interface::Window * Window;

				bool Initialized = false;

			public:


				enum Colors {
					Red = D3DCOLOR_ARGB(255, 255, 0, 0),
					Green = D3DCOLOR_ARGB(255, 0, 255, 0),
					Blue = D3DCOLOR_ARGB(255, 0, 42, 255),
					White = D3DCOLOR_ARGB(255, 255, 255, 255),
					Black = D3DCOLOR_ARGB(255, 0, 0, 0),
					Grey = D3DCOLOR_ARGB(255, 127, 127, 127),
					Dark_Grey = D3DCOLOR_ARGB(255, 63, 63, 63),
					Light_Grey = D3DCOLOR_ARGB(255, 190, 190, 190),
					Transparent = D3DCOLOR_ARGB(0, 0, 0, 0),
					Text_Background = D3DCOLOR_ARGB(255, 100, 100, 100),
					Text_Shadow = D3DCOLOR_ARGB(255, 1, 1, 1)
				};

				DirectX9(Interface::Window * Window);

				bool Init();

				void Render();

				void Reset();

				void DrawString(string String, int PositionX, int PositionY, D3DCOLOR Color);

				void DrawShadowString(string String, int PositionX, int PositionY, D3DCOLOR Color);

				void Gradient(int x, int y, int w, int h, int r, int g, int b, int a);

				void DrawLine(float StartingPositionX, float StartingPositionY, float EndingPositionX, float EndingPositionY, float Size, D3DCOLOR Color);

				void DrawCrosshair(float Size, D3DCOLOR Color);

				void DrawBox(float PositionX, float PositionY, float Width, float Height, D3DCOLOR Color);

				void DrawBorderedBox(float PositionX, float PositionY, float Width, float Height, D3DCOLOR Border, D3DCOLOR Background);

				D3DCOLOR GetHealthColor(int CurrentHealth);

				void DrawRectangle(int PositionX, int PositionY, int Width, int Height, D3DCOLOR Color);

				void DrawMouse(int Size, D3DCOLOR Color);

				Gdiplus::Rect GetMouseRect();

				void FillRGBA(float PositionX, float PositionY, float Width, float Height, int Red, int Green, int Blue, int Transparance);

				void FillColor(float PositionX, float PositionY, float Width, float Height, D3DCOLOR Color);

		};
	}
}
