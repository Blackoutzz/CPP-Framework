#pragma once
#include "Included.h"

namespace Software
{
	namespace Memory 
	{
		class Module
		{
			protected:

				DWORD EntryPoint;

				DWORD Size;

				string Name;

				string Path;

				DWORD ProcessId;

			public:

				Module(DWORD ProcessId, const char * ModuleName);

				DWORD GetEntryPointAddress();

				DWORD GetSize();

				string GetName();

				string GetPath();

				DWORD GetProcessId();

		};
	}
}
