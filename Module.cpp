#include "Module.h"

namespace Software 
{
	namespace Memory 
	{
		Module::Module(DWORD ParentProcessId, const char * ModuleName)
		{
			string TargetModuleName = ModuleName;
			this->Name = string("Unknown Module Name");
			this->Path = string("Unknown Module Path");
			MODULEENTRY32 Entry;
			ZeroMemory(&Entry, sizeof(MODULEENTRY32));
			Entry.dwSize = sizeof(MODULEENTRY32);
			HANDLE Snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE32 | TH32CS_SNAPMODULE, ParentProcessId);
			if (Module32First(Snapshot, &Entry))
			{
				do
				{
					string NewModuleName = Entry.szModule;
					if (strcmp(TargetModuleName.c_str(),NewModuleName.c_str()) == 0)
					{
						CloseHandle(Snapshot);
						this->EntryPoint = (DWORD)Entry.modBaseAddr;
						this->Path = string(Entry.szExePath);
						this->Size = Entry.dwSize;
						this->Name = string(Entry.szModule);
						return;
					}
				} while (Module32Next(Snapshot, &Entry));
			}
			CloseHandle(Snapshot);
		}

		DWORD Module::GetProcessId()
		{
			return this->ProcessId;
		}

		DWORD Module::GetEntryPointAddress()
		{
			return this->EntryPoint;
		}

		DWORD Module::GetSize()
		{
			return this->Size;
		}

		string Module::GetPath()
		{
			return this->Path;
		}

		string Module::GetName()
		{
			return this->Name;
		}

	}
}
