#include "stdafx.h"
#include "AccMem.h"


AccMem::AccMem()
{
}

/*int AccMem::Read(DWORD address, int valueRead) {
	ReadProcessMemory(handle, (PBYTE*)address, &valueRead, sizeof(valueRead), 0);

	return valueRead;
}*/

/*void AccMem::Write(DWORD address, LPCVOID newValue) {
	if (handle == NULL) {
		std::cout << "Process either does not exist or is not initalized." << std::endl;
	}
	WriteProcessMemory(handle, (LPVOID)address, &newValue, sizeof(newValue), 0);
}*/

void AccMem::InitProcess(LPCSTR processName) {
	HWND hwnd = FindWindowA(NULL, processName);
	if (hwnd == NULL) {
		std::cout << "Process does not exist. Process name should be equal to the name of the window." << std::endl;
		Sleep(10000);
		exit(-1);
	}
	else {
		GetWindowThreadProcessId(hwnd, &processId);
		handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
	}

}

DWORD AccMem::Module(LPSTR ModuleName) {


	HANDLE hModule = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, processId);
	MODULEENTRY32 mEntry;
	mEntry.dwSize = sizeof(mEntry);


	do
		if (!strcmp(mEntry.szModule, ModuleName))
		{
			CloseHandle(hModule);
			return (DWORD)mEntry.modBaseAddr;
		}
	while (Module32Next(hModule, &mEntry));

	std::cout << "\nMODULE: Process Platform Invalid\n";
	return 0;
}

AccMem::~AccMem()
{
}
