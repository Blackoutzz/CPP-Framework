#include "DirectX9.h"

namespace Software
{
	namespace Interface
	{

		DirectX9::DirectX9(Interface::Window * Window)
		{
			this->Window = Window;
			this->Font = 0;
			this->Object = 0;
			this->Device = 0;
			this->Line = 0;
		}

		bool DirectX9::Init()
		{
			if (!this->Initialized)
			{
				//Trying to initialize our Directx Device
				if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &this->Object))) return false;
				ZeroMemory(&this->Params, sizeof(this->Params));
				this->Params.Windowed = TRUE;
				this->Params.SwapEffect = D3DSWAPEFFECT_DISCARD;
				this->Params.hDeviceWindow = this->Window->GetHandle();
				this->Params.MultiSampleQuality = D3DMULTISAMPLE_NONE;
				this->Params.BackBufferFormat = D3DFMT_A8R8G8B8;
				this->Params.BackBufferWidth = this->Window->GetWidth();
				this->Params.BackBufferHeight = this->Window->GetHeight();
				this->Params.EnableAutoDepthStencil = TRUE;
				this->Params.AutoDepthStencilFormat = D3DFMT_D16;
				if (FAILED(this->Object->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, this->Window->GetHandle(), D3DCREATE_HARDWARE_VERTEXPROCESSING, &this->Params, 0, &this->Device))) return false;
				if (!this->Line) D3DXCreateLine(this->Device, &this->Line);
				if (!this->Font) D3DXCreateFont(this->Device, 18, 0, 0, 0, false, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Calibri", &this->Font);
				this->Initialized = true;
				return true;
			}
		}

		void DirectX9::Render()
		{
			if (this->Initialized)
			{
				this->Device->Clear(0, 0, D3DCLEAR_TARGET, this->Transparent, 1.0f, 0);
				this->Device->BeginScene();
				this->Device->EndScene();
				this->Device->PresentEx(0, 0, 0, 0, 0);
			}
		}

		void DirectX9::DrawString(string String, int PositionX, int PositionY, D3DCOLOR Color)
		{
			RECT ShadowPos;
			ShadowPos.left = PositionX + 1;
			ShadowPos.top = PositionY + 1;
			RECT FontPos;
			FontPos.left = PositionX;
			FontPos.top = PositionY;
			this->Font->DrawTextA(0, (char*)String.c_str(), strlen((char*)String.c_str()), &ShadowPos, DT_NOCLIP, this->Text_Background);
			this->Font->DrawTextA(0, (char*)String.c_str(), strlen((char*)String.c_str()), &FontPos, DT_NOCLIP, Color);
		}

		void DirectX9::DrawShadowString(string String, int PositionX, int PositionY, D3DCOLOR Color)
		{
			RECT Font;
			RECT Fonts;
			RECT Fonts1;
			RECT Fonts2;
			RECT Fonts3;
			Font.left = PositionX;
			Font.top = PositionY;
			Fonts.left = PositionX + 1;
			Fonts.top = PositionY;
			Fonts1.left = PositionX - 1;
			Fonts1.top = PositionY;
			Fonts2.left = PositionX;
			Fonts2.top = PositionY + 1;
			Fonts3.left = PositionX;
			Fonts3.top = PositionY - 1;
			this->Font->DrawTextA(0, (char*)String.c_str(), strlen((char*)String.c_str()), &Fonts3, DT_NOCLIP, this->Text_Shadow);
			this->Font->DrawTextA(0, (char*)String.c_str(), strlen((char*)String.c_str()), &Fonts2, DT_NOCLIP, this->Text_Shadow);
			this->Font->DrawTextA(0, (char*)String.c_str(), strlen((char*)String.c_str()), &Fonts1, DT_NOCLIP, this->Text_Shadow);
			this->Font->DrawTextA(0, (char*)String.c_str(), strlen((char*)String.c_str()), &Fonts, DT_NOCLIP, this->Text_Shadow);
			this->Font->DrawTextA(0, (char*)String.c_str(), strlen((char*)String.c_str()), &Font, DT_NOCLIP, Color);
		}

		void DirectX9::Gradient(int x, int y, int w, int h, int r, int g, int b, int a)
		{
			int iColorr, iColorg, iColorb;
			for (int i = 1; i < h; i++)
			{
				iColorr = (int)((float)i / h * r);
				iColorg = (int)((float)i / h * g);
				iColorb = (int)((float)i / h * b);
				this->FillRGBA(x, y + i, w, 1, r - iColorr, g - iColorg, b - iColorb, a);
			}
		}

		void DirectX9::DrawLine(float StartingPositionX, float StartingPositionY, float EndingPositionX, float EndingPositionY, float Size, D3DCOLOR Color)
		{
			D3DXVECTOR2 dLine[2];
			dLine[0].x = StartingPositionX;
			dLine[0].y = StartingPositionY;
			dLine[1].x = EndingPositionX;
			dLine[1].y = EndingPositionY;
			this->Line->Begin();
			this->Line->SetWidth(Size);
			this->Line->Draw(dLine, 2, Color);
			this->Line->End();
		}

		void DirectX9::DrawCrosshair(float Size, D3DCOLOR Color)
		{
			int TopScreen = 12;
			float Width = (float)this->Window->GetWidth() / 2 - 1;
			float Height = (float)this->Window->GetHeight() / 2 - 1;
			Size = Size * 2;
			//Vertical Line bottom
			this->FillColor(Width, Height + TopScreen, 2, Size, Color);
			//Horizontal Line
			this->FillColor(Width, Height + TopScreen, Size, 2, Color);
			//Vertical Line top
			this->FillColor(Width, Height + TopScreen - Size + 2, 2, Size, Color);
			//Horizontal Line
			this->FillColor(Width - Size + 2, Height + TopScreen, Size, 2, Color);
		}

		void DirectX9::DrawBox(float PositionX, float PositionY, float Width, float Height, D3DCOLOR Color)
		{
			this->FillColor(PositionX, PositionY, Width, Height, Color);
		}

		void DirectX9::DrawBorderedBox(float PositionX, float PositionY, float Width, float Height, D3DCOLOR Border, D3DCOLOR Background)
		{
			D3DXVECTOR2 points[5];
			points[0] = D3DXVECTOR2(PositionX, PositionY);
			points[1] = D3DXVECTOR2(PositionX + Width, PositionY);
			points[2] = D3DXVECTOR2(PositionX + Width, PositionY + Height);
			points[3] = D3DXVECTOR2(PositionX, PositionY + Height);
			points[4] = D3DXVECTOR2(PositionX, PositionY);
			this->Line->Begin();
			this->Line->SetWidth(2);
			this->Line->Draw(points, 5, Border);
			this->Line->End();
			this->FillColor(PositionX + 1, PositionY + 1, Width - 1, Height - 1, Background);
		}

		void DirectX9::DrawRectangle(int PositionX, int PositionY, int Width, int Height, D3DCOLOR Color)
		{
			D3DRECT TargetRectangle = { PositionX, PositionY, PositionX + Width, PositionY + Height };
			this->Device->Clear(1, &TargetRectangle, D3DCLEAR_TARGET | D3DCLEAR_TARGET, Color, 0, 0);
		}

		void DirectX9::DrawMouse(int Size, D3DCOLOR Color)
		{
			Rect MouseRect = this->GetMouseRect();
			this->DrawRectangle(MouseRect.X, MouseRect.Y, Size, Size, Color);
		}

		Gdiplus::Rect DirectX9::GetMouseRect()
		{
			Hardware::Mouse * Mouse = new Hardware::Mouse();
			Gdiplus::Rect MouseRect = Mouse->GetMouseRect();
			return Gdiplus::Rect(MouseRect.X - this->Window->GetPositions().PositionX, MouseRect.Y - this->Window->GetPositions().PositionY, 2, 2);
		}

		D3DCOLOR DirectX9::GetHealthColor(int CurrentHealth)
		{
			if (CurrentHealth > 89 && CurrentHealth <= 100)
				return D3DCOLOR_ARGB(255, 0, 255, 0);
			else if (CurrentHealth > 79 && CurrentHealth < 90)
				return D3DCOLOR_ARGB(255, 0, 255, 155);
			else if (CurrentHealth > 69 && CurrentHealth < 80)
				return D3DCOLOR_ARGB(255, 255, 255, 0);
			else if (CurrentHealth > 59 && CurrentHealth < 70)
				return D3DCOLOR_ARGB(255, 255, 205, 0);
			else if (CurrentHealth > 49 && CurrentHealth < 60)
				return D3DCOLOR_ARGB(255, 255, 170, 0);
			else if (CurrentHealth > 39 && CurrentHealth < 50)
				return D3DCOLOR_ARGB(255, 255, 128, 0);
			else if (CurrentHealth > 29 && CurrentHealth < 40)
				return D3DCOLOR_ARGB(255, 255, 97, 0);
			else if (CurrentHealth > 19 && CurrentHealth < 30)
				return D3DCOLOR_ARGB(255, 255, 58, 0);
			else if (CurrentHealth > 9 && CurrentHealth < 20)
				return D3DCOLOR_ARGB(255, 255, 0, 66);
			else if (CurrentHealth > 1 && CurrentHealth < 9)
				return D3DCOLOR_ARGB(255, 255, 0, 0);
			return D3DCOLOR_ARGB(255, 255, 0, 0);
		}

		void DirectX9::FillRGBA(float PositionX, float PositionY, float Width, float Height, int Red, int Green, int Blue, int Transparance)
		{
			D3DXVECTOR2 vLine[2];
			vLine[0].x = PositionX + Width / 2;
			vLine[0].y = PositionY;
			vLine[1].x = PositionX + Width / 2;
			vLine[1].y = PositionY + Height;
			this->Line->Begin();
			this->Line->SetWidth(Width);
			this->Line->Draw(vLine, 2, D3DCOLOR_RGBA(Red, Green, Blue, Transparance));
			this->Line->End();
		}

		void DirectX9::FillColor(float PositionX, float PositionY, float Width, float Height, D3DCOLOR Color)
		{
			D3DRECT TargetRectangle = { PositionX, PositionY, PositionX + Width, PositionY + Height };
			this->Device->Clear(1, &TargetRectangle, D3DCLEAR_TARGET | D3DCLEAR_TARGET, Color, 0, 0);
		}

		void DirectX9::Reset()
		{
			if (this->Initialized)
			{
				this->Params.BackBufferWidth = this->Window->GetWidth();
				this->Params.BackBufferHeight = this->Window->GetHeight();
				this->Params.Windowed = TRUE;
				this->Params.SwapEffect = D3DSWAPEFFECT_DISCARD;
				this->Device->Reset(&this->Params);
			}
		}
	}

}
