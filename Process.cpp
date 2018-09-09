#include "Process.h"

namespace Software
{

	Process::Process(const char * ProcessName)
	{
		string TargetProcessName = ProcessName;
		HANDLE ProcessHandle;
		DWORD Processes[1024], CountNeeded, CountProcesses;
		unsigned int i;
		if (!EnumProcesses(Processes, sizeof(Processes), &CountNeeded)) return;
		CountProcesses = CountNeeded / sizeof(DWORD);
		for (i = 0; i < CountProcesses; i++)
		{
			if (Processes[i] != 0)
			{
				TCHAR NewProcessName[MAX_PATH];
				ProcessHandle = OpenProcess(PROCESS_ALL_ACCESS | PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, Processes[i]);
				if (ProcessHandle)
				{
					HMODULE ModuleHandle;
					DWORD CountNeeded;
					if (EnumProcessModules(ProcessHandle, &ModuleHandle, sizeof(ProcessHandle), &CountNeeded))
					{
						GetModuleBaseName(ProcessHandle, ModuleHandle, NewProcessName, sizeof(NewProcessName) / sizeof(TCHAR));
						string SelectedProcessName = NewProcessName;
						if(strcmp(TargetProcessName.c_str(),SelectedProcessName.c_str()) == 0)
						{
							this->Id = Processes[i];
							this->Name = SelectedProcessName;
							CloseHandle(ProcessHandle);
							return;
						} 
					}
				}
				CloseHandle(ProcessHandle);
			}
		}
	}

	Process::Process(DWORD ProcessId)
	{
		TCHAR NewProcessName[MAX_PATH] = TEXT("unknown");
		HANDLE ProcessHandle;
		ProcessHandle = OpenProcess(PROCESS_ALL_ACCESS | PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, ProcessId);

		if (ProcessHandle)
		{
			HMODULE ModuleHandle;
			DWORD CountNeeded;
			if (EnumProcessModules(ProcessHandle, &ModuleHandle, sizeof(ProcessHandle), &CountNeeded))
			{
				GetModuleBaseName(ProcessHandle, ModuleHandle, NewProcessName, sizeof(NewProcessName) / sizeof(TCHAR));
				this->Id = ProcessId;
				this->Name = NewProcessName;
			}
			CloseHandle(ProcessHandle);
		}
	}

	Process::~Process()
	{

	}

	DWORD Process::GetId()
	{
		return this->Id;
	}

	string Process::GetName()
	{
		return this->Name;
	}

	bool Process::IsRunning()
	{
		if (this->Id >= 1)
		{
			HANDLE ProcessHandle;
			ProcessHandle = OpenProcess(PROCESS_ALL_ACCESS | PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, this->Id);
			if (ProcessHandle)
			{
				CloseHandle(ProcessHandle);
				return true;
			}
		}
		return false;
	}

	Memory::Module * Process::GetModuleByName(TCHAR * ModuleName)
	{
		HANDLE ProcessHandle;
		HMODULE ModulesHandle[1024];
		DWORD CountNeeded;
		unsigned int i;
		if (this->Id >= 1)
		{
			ProcessHandle = OpenProcess(PROCESS_ALL_ACCESS | PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, this->Id);
			if (EnumProcessModules(ProcessHandle, ModulesHandle, sizeof(ModulesHandle), &CountNeeded))
			{
				for (i = 0; i < (CountNeeded / sizeof(HMODULE)); i++)
				{
					TCHAR NewModuleName[MAX_PATH];
					if (GetModuleBaseName(ProcessHandle, ModulesHandle[i], NewModuleName, sizeof(NewModuleName) / sizeof(TCHAR)))
					{
						if (NewModuleName == ModuleName)
						{
							CloseHandle(ProcessHandle);
							return new Software::Memory::Module(this->Id, ModuleName);
						}
					}

				}
			}
		}
		return nullptr;
	}

	template <typename Data>
	Data Process::ReadExternalMemory(DWORD Address)
	{
		if (this->Id >= 1)
		{
			HANDLE ProcessHandle;
			ProcessHandle = OpenProcess(PROCESS_ALL_ACCESS | PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, this->Id);
			if (ProcessHandle)
			{
				Data Buffer;
				ReadProcessMemory(ProcessHandle, (PVOID*)Address, &Buffer, sizeof(Data), NULL);
				CloseHandle(ProcessHandle);
				return Buffer;
			}
		}
	}

	template <typename Data>
	Data Process::ReadInternalMemory(DWORD Address)
	{
		return *(Data*)(Address);
	}

	template <typename Data>
	bool Process::WriteExternalMemory(DWORD Address, Data Value)
	{
		if (this->Id >= 1)
		{
			HANDLE ProcessHandle;
			ProcessHandle = OpenProcess(PROCESS_ALL_ACCESS | PROCESS_VM_WRITE, FALSE, this->Id);
			if (ProcessHandle)
			{
				if (WriteProcessMemory(ProcessHandle, (PVOID*)Address, &Value, sizeof(Data), NULL))
				{
					CloseHandle(ProcessHandle);
					return true;
				} else {
					CloseHandle(ProcessHandle);
					return false;
				}
			}
		}
		
	}

	template <typename Data>
	bool Process::WriteInternalMemory(DWORD Address, Data Value)
	{
		Data * Pointer = (Data*)Address; 
		*Pointer = Value; 
		return true;
	}
}
