#pragma once
#include <windows.h>
#include <iostream>
#include <TlHelp32.h>
#include <string>
#include <sstream>

namespace am {
	struct offset {
		int size;
		const int *offsets;

	};
	template<typename...T>
	offset offset_arr(const T& ...k) {
		int *to_populate = new int[sizeof...(k)]{ k... };
		return{ sizeof...(k), to_populate };
	}

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

		int FindMultiLevelPointer(DWORD base, am::offset o);

		void InitProcess(LPCSTR processName);

		~AccMem();
	};


}


