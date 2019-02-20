#pragma once
#include "stdafx.h"

namespace MEMORY {
	extern HANDLE hProcess;
	extern DWORD PID;

	bool Attach(const char* processName, DWORD rights);
	SMODULE GetModule(const char* moduleName);

	template <typename T>
	T Read(DWORD address) {
		T buffer;
		ReadProcessMemory(hProcess, (LPCVOID)address, &buffer, sizeof(T), NULL);
		return buffer;
	}

	template <typename T>
	bool ReadSize(DWORD addy, T* buffer, SIZE_T size = sizeof(T)) {
		return ReadProcessMemory(hProcess, (LPCVOID)addy, buffer, size, NULL);
	}

	template <typename T>
	bool Write(DWORD address, T buffer) {
		return WriteProcessMemory(hProcess, (LPVOID)address, (LPCVOID)&buffer, sizeof(T), NULL);
	}

	template <typename T>
	bool WriteSize(DWORD addy, T buffer, SIZE_T size = sizeof(T)) {
		return WriteProcessMemory(hProcess, (LPVOID)addy, (LPCVOID)&buffer, size, NULL);
	}
}