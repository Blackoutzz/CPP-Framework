#include "VMT.h"

VirtualMethodTable::VirtualMethodTable(void * VMT)
{
	this->ModdedTable = reinterpret_cast<uintptr_t**>(VMT);
	this->OriginalTable = *this->ModdedTable;
	while (reinterpret_cast<uintptr_t*>(*this->ModdedTable)[this->MethodCount]) this->MethodCount++;
	this->Table = new uintptr_t[sizeof(uintptr_t) * this->MethodCount];
	memcpy(this->Table, this->OriginalTable, sizeof(uintptr_t) * this->MethodCount);
}

VirtualMethodTable::~VirtualMethodTable()
{
	this->RevertVMT();
}

void VirtualMethodTable::HookVitualMethod(void * Method, size_t MethodIndex)
{
	this->Table[MethodIndex] = reinterpret_cast<uintptr_t>(Method);
}

void VirtualMethodTable::ReplaceVMT()
{
	*this->ModdedTable = this->Table;
}

void VirtualMethodTable::RevertVMT()
{
	*this->ModdedTable = this->OriginalTable;
}

template<typename Method>
Method VirtualMethodTable::GetOriginalMethod(size_t MethodIndex)
{
	return reinterpret_cast<Method>(this->OriginalTable[MethodIndex]);
}