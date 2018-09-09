#pragma once
#include "../Included.h"

class VirtualMethodTable
{
	protected:
		
		uintptr_t * Table;
		
		uint32_t MethodCount = 0;

		uintptr_t * OriginalTable = nullptr;

		uintptr_t** ModdedTable = nullptr;

	public:

		VirtualMethodTable(void* VMT);
		
		~VirtualMethodTable();

		void HookVitualMethod(void * Method, size_t MethodIndex);

		void ReplaceVMT();

		void RevertVMT();

		template<typename Method>
		Method GetOriginalMethod(size_t MethodIndex);

};
