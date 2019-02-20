#include "stdafx.h"

HANDLE MEMORY::hProcess;
DWORD MEMORY::PID;

bool MEMORY::Attach(const char* processName, DWORD rights) {
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);

	if (!Process32First(hProcessSnap, &pe32)) {
		return false;
	}
	do {
		if (!strcmp(pe32.szExeFile, processName)) {
			PID = pe32.th32ProcessID;
			CloseHandle(hProcessSnap);
			hProcess = OpenProcess(rights, false, PID);
			return true;
		}

	} while (Process32Next(hProcessSnap, &pe32));

	CloseHandle(hProcessSnap);
	return false;
}

SMODULE MEMORY::GetModule(const char* moduleName) {
	HANDLE hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE32 | TH32CS_SNAPMODULE, PID);
	MODULEENTRY32 me32;
	me32.dwSize = sizeof(MODULEENTRY32);

	if (!Module32First(hModuleSnap, &me32)) {
		return { (DWORD)false, (DWORD)false };
	}
	do {
		if (!strcmp(me32.szModule, moduleName)) {
			CloseHandle(hModuleSnap);
			return { (DWORD)me32.hModule, me32.modBaseSize };
		}
	} while (Module32Next(hModuleSnap, &me32));
	CloseHandle(hModuleSnap);
	return { (DWORD)false, (DWORD)false };
}

