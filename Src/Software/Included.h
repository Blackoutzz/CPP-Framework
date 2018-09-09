#pragma once
#define WIN32_LEAN_AND_MEAN
#define _MAIN_H

#pragma warning( disable : 4244 )
#pragma warning( disable : 4996 )
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dwmapi.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "Shlwapi.lib")
#pragma comment( lib, "gdiplus.lib" )

#include <d3dx9.h>	
#include <d3d9.h>	
#include <Windows.h>
#include <iostream>
#include <dwmapi.h>		
#include <ctime>
#include <math.h>
#include <vector>
#include <string>
#include <TlHelp32.h>		
#include <conio.h>
#include <gdiplus.h>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <Psapi.h>	
#include <process.h>
#include <Shlwapi.h>
#include <regex>
#include <string.h>
#include <tchar.h>
#include "Libraries/Game.h"
#include <cstdint>
#include <cstddef>
#include <atlbase.h>

using namespace Gdiplus;
using namespace std;