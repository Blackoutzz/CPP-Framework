#include "GDI.h"
namespace Software 
{
	namespace Interface
	{
		GDI::GDI(Interface::Window * Window)
		{
			this->Window = Window;
			this->DeviceContextHandle = this->Window->GetDeviceContext();
		}

		void GDI::DrawLine(float StartX, float StartY, float EndX, float EndY, COLORREF Color)
		{
			HPEN TargetPen = CreatePen(PS_SOLID, 2, Color);
			HPEN OurPen = (HPEN)SelectObject(this->DeviceContextHandle, TargetPen);
			MoveToEx(this->DeviceContextHandle, StartX, StartY, NULL);
			LineTo(this->DeviceContextHandle, EndX, EndY);
			DeleteObject(SelectObject(this->DeviceContextHandle, OurPen));
		}

		void GDI::DrawRectangle(HBRUSH Brush, int PositionX, int PositionY, int Width, int Height)
		{
			RECT OurRectangle = { PositionX, PositionY, PositionX + Width, PositionY + Height };
			FillRect(this->Window->GetDeviceContext(), &OurRectangle, Brush);
		}

		void GDI::DrawBorderBox(HBRUSH Brush, int PositionX, int PositionY, int Width, int Height, int Thickness)
		{
			this->DrawRectangle(Brush, PositionX, PositionY, Width, Thickness);
			this->DrawRectangle(Brush, PositionX, PositionY, Thickness, Height);
			this->DrawRectangle(Brush, (PositionX + Width), PositionY, Thickness, Height);
			this->DrawRectangle(Brush, PositionX, PositionY + Height, Width + Thickness, Thickness);
		}

		void GDI::DrawString(int PositionX, int PositionY, COLORREF Color, const char * Text)
		{
			SetTextAlign(this->DeviceContextHandle, TA_CENTER | TA_NOUPDATECP);
			SetBkColor(this->DeviceContextHandle, RGBA(0, 0, 0, 0));
			SetBkMode(this->DeviceContextHandle, TRANSPARENT);
			SetTextColor(this->DeviceContextHandle, Color);
			SelectObject(this->DeviceContextHandle, this->Font);
			TextOutA(this->DeviceContextHandle, PositionX, PositionY, Text, strlen(Text));
			DeleteObject(this->Font);
		}
	}

}
