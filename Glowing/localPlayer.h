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

template<typename T> void WPM(T buffer, SIZE_T address) { // write process memory
	WriteProcessMemory(hProcess, (LPVOID)address, &buffer, sizeof(buffer), NULL);
}

template<typename T> T RPM(SIZE_T address) { // read process memory
	T buffer;
	ReadProcessMemory(hProcess, (LPCVOID)address, &buffer, sizeof(T), NULL);
	return buffer;
}

uintptr_t getLocalPlayer() {
	return RPM<uintptr_t>(moduleBase + dwLocalPlayer);
}

void bhopMechanic() {
	BYTE Flag = RPM<BYTE>(getLocalPlayer() + m_fFlags);
	if (GetAsyncKeyState(VK_SPACE) && Flag & (1 << 0)) {
		WPM<DWORD>(0x06, moduleBase + dwForceJump); // if the player is on the ground, then force jump to bhop
	}
}

void antiFlash() {
	bool noFlash = true;
	if (noFlash) { // flash bang will not blind player 
		long double duration = 0;
		WPM<long double>(duration, getLocalPlayer() + m_flFlashDuration); // flash duration is consistenly set to 0
	}
}

void radarAlwaysSeen(uintptr_t entity) {
	bool enemySeen = true;
	if (getLocalPlayer && enemySeen) {
		WPM<bool>(enemySeen, entity + m_bSpotted); // set radar to enemies are always seen
	}
}

void triggerbot(uintptr_t entity){
	int id = RPM<int>(getLocalPlayer() + m_iCrosshairId); // id of all players
	if ((GetKeyState(VK_CAPITAL))) {
		if ((id > 0 && id < 64)) { // if a player is in the crosshair of local player
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0); // left click simulated
			Sleep(1);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
	}
}