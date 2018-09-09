#pragma once
#include "Included.h"
#include "Module.h"

namespace Software 
{
	class Process
	{
		protected:

			DWORD Id = 0;

			string Name;

			bool Running;

		public:

			Process(const char * ProcessName);

			Process(DWORD ProcessId);

			~Process();

			bool IsRunning();

			Memory::Module * GetModuleByName(TCHAR * ModuleName);

			DWORD GetId();

			string GetName();

			template <typename Data>
			Data ReadExternalMemory(DWORD Address);

			template <typename Data>
			Data ReadInternalMemory(DWORD Address);

			template <typename Data>
			bool WriteExternalMemory(DWORD Address, Data Value);

			template <typename Data>
			bool WriteInternalMemory(DWORD Address, Data Value);

	};
}
