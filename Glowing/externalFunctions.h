#pragma once

using namespace hazedumper::netvars;
using namespace hazedumper::signatures;

using namespace hazedumper;

HWND handleWindow;
DWORD processId;
HANDLE handleProcess;
uintptr_t moduleBase;
HDC hdc;
uintptr_t engineModule;

uintptr_t GetModuleBaseAddress(const char* moduleName) {
	uintptr_t modBaseAddr = 0;
	HANDLE handleSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processId);
	if (handleSnapshot != INVALID_HANDLE_VALUE) {
		MODULEENTRY32 moduleEntry;
		moduleEntry.dwSize = sizeof(moduleEntry);
		if (Module32First(handleSnapshot, &moduleEntry)) {
			do {
				if (!strcmp(moduleEntry.szModule, moduleName)) {
					CloseHandle(handleSnapshot);
					return (uintptr_t)moduleEntry.modBaseAddr;
				}
			} while (Module32Next(handleSnapshot, &moduleEntry));
		}
	}
}

template<typename T> T RPM(SIZE_T address) { // read process memory
	T buffer;
	ReadProcessMemory(handleProcess, (LPCVOID)address, &buffer, sizeof(T), NULL);
	return buffer;
}

template<typename T> void WPM(SIZE_T address, T buffer) { // write process memory
	WriteProcessMemory(handleProcess, (LPVOID)address, &buffer, sizeof(buffer), NULL);
}