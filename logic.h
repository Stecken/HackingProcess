#ifndef LOGIC_H_

#include <Windows.h> // fica aqui, se n dá erro esse CARALHO
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <memoryapi.h>
#include <memory.h>
#include <vector>
#include <TlHelp32.h>
#include <SDKDDKVer.h>
#include <tchar.h>

DWORD GetProcId(const wchar_t* procName);
uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* modName);
uintptr_t FindDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets);

#endif // !LOGIC_H_
