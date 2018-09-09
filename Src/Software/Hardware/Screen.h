#pragma once
#include "../Included.h"

namespace Software
{
	namespace Hardware
	{
		class Screen 
		{
			protected:

				int Width = 0;

				int Height = 0;
				
				bool SaveBitmapToFile(HBITMAP BitmapHandle, const char * Filepath = "Screenshots/Screenshot.bmp");

			public:

				Screen();

				int static GetHeight();

				int static GetWidth();

				bool Screenshot();
		};
	}
}