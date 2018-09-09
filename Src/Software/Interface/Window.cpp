#include "Window.h"

namespace Software 
{
	namespace Interface
	{
		Window::Window(const char * Name)
		{
			this->Name = Name;
			this->Margin = { 0, 22, 0, 0 };
			this->Handle = FindWindow(0, (LPSTR)this->Name.c_str());
		}

		bool Window::IsAlive()
		{
			if (this->Handle != NULL)
			{
				return true;
			}
			return false;
		}

		bool Window::IsActive()
		{
			if (GetForegroundWindow() == this->Handle) {
				return true;
			}
			return false;
		}

		string Window::GetName()
		{
			GetWindowText(this->Handle, (LPSTR)this->Name.c_str(), sizeof(this->Name));
			return this->Name;
		}

		MARGINS Window::GetMargin()
		{
			return this->Margin;
		}

		HWND Window::GetHandle()
		{
			return this->Handle;
		}

		Vector2D Window::GetPositions()
		{
			GetWindowRect(this->Handle, &this->Rectangle);
			this->Positions.PositionX = this->Rectangle.left;
			this->Positions.PositionY = this->Rectangle.top;
			return this->Positions;
		}

		RECT Window::GetRectangle()
		{
			GetWindowRect(this->Handle, &this->Rectangle);
			return this->Rectangle;
		}

		int Window::GetHeight()
		{
			GetWindowRect(this->Handle, &this->Rectangle);
			this->Height = this->Rectangle.bottom - this->Rectangle.top;
			return this->Height;
		}

		int Window::GetWidth()
		{
			GetWindowRect(this->Handle, &this->Rectangle);
			this->Width = this->Rectangle.right - this->Rectangle.left;
			return this->Width;
		}

		void Window::Destroy()
		{
			this->Alive = false;
			this->Active = false;
			DestroyWindow(this->Handle);
		}

		bool Window::IsFullScreen()
		{
			RECT desktop;
			HWND hDesktop = GetDesktopWindow();
			GetWindowRect(hDesktop, &desktop);
			int ScreenWith = desktop.right;
			int ScreenHeight = desktop.bottom;
			if (this->Width == ScreenWith
				&& this->Height == ScreenHeight) {
				this->FullScreen = true;
			}
			else {
				this->FullScreen = false;
			}
			return this->FullScreen;
		}

		void Window::CreateNewWindow()
		{
			this->Handle = CreateWindowEx(WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED, (LPCSTR)this->Name.c_str(), (LPCSTR)this->Name.c_str(), WS_POPUP, 0, 0, this->Width, this->Height, 0, 0, 0, 0);
			SetLayeredWindowAttributes(this->Handle, 0, 1.0f, LWA_ALPHA);
			SetLayeredWindowAttributes(this->Handle, 0, 255, LWA_COLORKEY);
			ShowWindow(this->Handle, SW_SHOW);
		}

		bool Window::ResizeToWindow(Window * Window)
		{
			if (this->Width != Window->Width
				|| this->Height != Window->Height
				|| this->Positions.PositionX != Window->GetPositions().PositionX
				|| this->Positions.PositionY != Window->GetPositions().PositionY
				|| this->Rectangle.bottom != Window->GetRectangle().bottom
				|| this->Rectangle.left != Window->GetRectangle().left
				|| this->Rectangle.top != Window->GetRectangle().top
				|| this->Rectangle.right != Window->GetRectangle().right)
			{
				this->Height = Window->GetHeight();
				this->Width = Window->GetWidth();
				this->Positions = Window->GetPositions();
				this->Margin = Window->GetMargin();
				this->Rectangle = Window->GetRectangle();
				MoveWindow(this->Handle, this->Rectangle.left, this->Rectangle.top, this->Width, this->Height, true);
				return true;
			}
			else {
				MoveWindow(this->Handle, this->Rectangle.left, this->Rectangle.top, this->Width, this->Height, true);
				return false;
			}

		}

		HDC Window::GetDeviceContext()
		{
			this->DeviceContext = GetWindowDC(this->Handle);
			return this->DeviceContext;
		}

		//GDI Rectangle
		Rect Window::GetNewRectangle()
		{
			GetWindowRect(this->Handle, &this->Rectangle);
			return Rect(this->Rectangle.left, this->Rectangle.top, this->GetWidth(), this->GetHeight());
		}

		bool Window::Screenshot()
		{
			HDC DeviceContext = this->GetDeviceContext();
			HDC CompatibleDeviceContext = CreateCompatibleDC(DeviceContext);
			HBITMAP BitmapHandle = CreateCompatibleBitmap(DeviceContext, this->GetWidth(), this->GetHeight()-22);
			HGDIOBJ GDIHandleObject = SelectObject(CompatibleDeviceContext, BitmapHandle);
			BitBlt(CompatibleDeviceContext, 0,-22, this->GetWidth()-4, this->GetHeight()+22, DeviceContext, 4, 4, SRCCOPY);
			SelectObject(CompatibleDeviceContext, GDIHandleObject);
			DeleteDC(CompatibleDeviceContext);
			ReleaseDC(this->Handle, DeviceContext);
			return this->SaveBitmapToFile(BitmapHandle);
		}

		bool Window::SaveBitmapToFile(HBITMAP BitmapHandle, const char * Filepath)
		{
			PICTDESC PictureDescription = { sizeof(PictureDescription), PICTYPE_BITMAP };
			PictureDescription.bmp.hbitmap = BitmapHandle;

			CComPtr<IPicture> Picture = NULL;
			CComPtr<IStream>  Stream = NULL;
			LONG Size = 0;

			BOOL ResourceAccess = FALSE;

			ResourceAccess = SUCCEEDED(CreateStreamOnHGlobal(NULL, TRUE, &Stream));
			ResourceAccess = SUCCEEDED(OleCreatePictureIndirect(&PictureDescription, IID_IPicture, TRUE, (void**)&Picture));
			ResourceAccess = SUCCEEDED(Picture->SaveAsFile(Stream, TRUE, &Size));

			if (ResourceAccess)
			{
				LARGE_INTEGER Offset = { 0 };
				Stream->Seek(Offset, STREAM_SEEK_SET, NULL);
				HANDLE FileHandle = CreateFile(Filepath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
				if (INVALID_HANDLE_VALUE != FileHandle)
				{
					DWORD Written = 0, Read = 0, Done = 0;
					BYTE  DataBuffer[4096];
					while (Done < Size)
					{
						if (SUCCEEDED(Stream->Read(DataBuffer, sizeof(DataBuffer), &Read)))
						{
							WriteFile(FileHandle, DataBuffer, Read, &Written, NULL);
							if (Written != Read) break;
							Done += Read;
						}
						else {
							break;
						}
					}
					_ASSERTE(Done == Size);
					CloseHandle(FileHandle);
					return true;
				}
			}
			return false;
		}

	}
}
