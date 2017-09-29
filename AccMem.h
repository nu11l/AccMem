#pragma once
#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <TlHelp32.h>
#include <string>
#include <sstream>
class AccMem
{
public:
	AccMem();
	HANDLE handle;
	DWORD processId;
	template <class dataTypeVar>
	dataTypeVar Read(DWORD address/*, dataTypeVar valueRead*/) {
		dataTypeVar valueRead;
		ReadProcessMemory(handle, (PBYTE*)address, &valueRead, sizeof(valueRead), 0);

		return valueRead;
	}
	//int Read(DWORD address, int valueRead);
	DWORD AccMem::Module(LPSTR ModuleName);

	template <class dataTypeVar>
	void Write(DWORD address, dataTypeVar newValue) {
		if (handle == NULL) {
			std::cout << "Process either does not exist or is not initalized." << std::endl;
		}
		WriteProcessMemory(handle, (LPVOID)address, &newValue, sizeof(newValue), 0);
	}
	void InitProcess(LPCSTR processName);
	~AccMem();
};

