#pragma once
#define WIN32_LEAN_AND_MEAN   //Enleve lentete windows au fichier
#define _MAIN_H

#pragma warning( disable : 4244 ) //remove the incoming warns
#pragma warning( disable : 4996 ) //remove the incoming warns
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dwmapi.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "Detours.lib")
#pragma comment(lib, "Shlwapi.lib")
#pragma comment( lib, "gdiplus.lib" )

#include <d3dx9.h>		// DirectX
#include <d3d9.h>		// DirectX
#include <Windows.h>	//WindowsAPi
#include <iostream>		//IO
#include <dwmapi.h>		
#include <ctime>		//Clock & Time Library
#include <detours.h>	//Detour Microsoft Library
#include <math.h>		//Math Library
#include <vector>		//Math Vector Library
#include <string>		//Strings
#include <TlHelp32.h>	//Win32 Helper Library			
#include <conio.h>		//IO		
#include <gdiplus.h>	//GDI Microsoft Drawing Library	
#include <stdio.h>		//standard IO
#include <stdlib.h>
#include <sstream>		//String Stream
#include <Psapi.h>	
#include <process.h>	//Process Library
#include <Shlwapi.h>
#include <regex>
#include <string.h>
#include <tchar.h>
#include "game.h"

using namespace Gdiplus;
using namespace std;