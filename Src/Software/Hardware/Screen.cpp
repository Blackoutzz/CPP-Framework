#include "Screen.h"

namespace Software
{
	namespace Hardware
	{
		
		Screen::Screen()
		{
		
		}

		int Screen::GetHeight()
		{
			return GetSystemMetrics(SM_CYSCREEN);
		}

		int Screen::GetWidth()
		{
			return GetSystemMetrics(SM_CXSCREEN);
		}

		bool Screen::Screenshot()
		{
			HDC DeviceContext = GetDC(NULL);
			HDC CompatibleDeviceContext = CreateCompatibleDC(DeviceContext);
			HBITMAP BitmapHandle = CreateCompatibleBitmap(DeviceContext, Screen::GetWidth(), Screen::GetHeight());
			HGDIOBJ GDIHandleObject = SelectObject(CompatibleDeviceContext, BitmapHandle);
			BitBlt(CompatibleDeviceContext, 0, 0, Screen::GetWidth(), Screen::GetHeight(), DeviceContext, 0, 0, SRCCOPY);
			SelectObject(CompatibleDeviceContext, GDIHandleObject);
			DeleteDC(CompatibleDeviceContext);
			ReleaseDC(NULL, DeviceContext);
			return this->SaveBitmapToFile(BitmapHandle);
		}

		bool Screen::SaveBitmapToFile(HBITMAP BitmapHandle, const char * Filepath)
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
							WriteFile(FileHandle,DataBuffer, Read, &Written, NULL);
							if (Written != Read) break;
							Done += Read;
						} else {
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