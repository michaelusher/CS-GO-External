#pragma once

using namespace hazedumper::netvars;
using namespace hazedumper::signatures;

using namespace hazedumper;

HWND hwnd;
DWORD procId;
HANDLE hProcess;
uintptr_t moduleBase;
HDC hdc;
int closest;
uintptr_t engineModule;

uintptr_t GetModuleBaseAddress(const char* modName) {
	uintptr_t modBaseAddr = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
	if (hSnap != INVALID_HANDLE_VALUE) {
		MODULEENTRY32 moduleEntry;
		moduleEntry.dwSize = sizeof(moduleEntry);
		if (Module32First(hSnap, &moduleEntry)) {
			do {
				if (!strcmp(moduleEntry.szModule, modName)) {
					CloseHandle(hSnap);
					return (uintptr_t)moduleEntry.modBaseAddr;
				}
			} while (Module32Next(hSnap, &moduleEntry));
		}
	}
}

template<typename T> void WPM(T buffer, SIZE_T address) {
	WriteProcessMemory(hProcess, (LPVOID)address, &buffer, sizeof(buffer), NULL);
}

template<typename T> T RPM(SIZE_T address) {
	T buffer;
	ReadProcessMemory(hProcess, (LPCVOID)address, &buffer, sizeof(T), NULL);
	return buffer;
}

uintptr_t getLocalPlayer() {
	return RPM<uintptr_t>(moduleBase + dwLocalPlayer);
}

void bhopMechanic() {
	BYTE Flag = RPM<BYTE>(getLocalPlayer() + m_fFlags);
	if (GetKeyState(VK_CAPITAL) && Flag & (1 << 0)) { 
		WPM<DWORD>(0x06, moduleBase + dwForceJump);
	}
}

void antiFlash() {
	bool noFlash = true;
	if (getLocalPlayer && noFlash) { //flash bang will not blind player 
		long double duration = 0.001001;
		WPM<long double>(duration, getLocalPlayer() + m_flFlashDuration);
	}
}

void radarAlwaysSeen(uintptr_t entity) {
	bool enemySeen = true;
	if (getLocalPlayer && enemySeen) {
		WPM<bool>(enemySeen, entity + m_bSpotted);
	}
}