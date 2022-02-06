#include "Includes.h"

#include <thread>
#include <array>

using namespace hazedumper::netvars;
using namespace hazedumper::signatures;

using namespace hazedumper;

void printInstructions() { // instructions for the cheat CVO
	std::cout << "\nCS:GO External Instructions\n\n";
	Sleep(100);
	std::cout << "*Enemies will glow cyan.\n";
	Sleep(100);
	std::cout << "*Radar is toggled on.\n";
	Sleep(100);
	std::cout << "*Anti-Flash is toggled on.\n";
	Sleep(100);
	std::cout << "*Hold Spacebar to Bunnyhop.\n";
	Sleep(100);
	std::cout << "*Hold ALT to enable third-person.\n";
	Sleep(100);
	std::cout << "*Press F1 to enable Wide FOV.\n";
	Sleep(100);
	std::cout << "*Press F2 to disable Wide FOV.\n";
	Sleep(100);
	std::cout << "*Press F3 to enable no-scope while scoped in.\n";
	Sleep(100);
	std::cout << "*Press F4 to disable no-scope while scoped in.\n";
	Sleep(100);
}

int main() {
	handleWindow = FindWindowA(NULL, "Counter-Strike: Global Offensive - Direct3D 9");
	GetWindowThreadProcessId(handleWindow, &processId);
	handleProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, processId);
	moduleBase = GetModuleBaseAddress("client.dll");
	hdc = GetDC(handleWindow);

	ShowWindow(GetConsoleWindow(), SW_SHOW);
	system("Color 0B");

	// HWID checks
	if (hwidChecker() == true) {
		std::cout << "HWID verified\n";
		Sleep(2000);
	}
	else{
		std::cout << "HWID not verified\n";
		Sleep(10000);
	}
	// if CS:GO is running, then the cheat runs
	bool isRunning = true;
	if ((FindWindowA(NULL, "Counter-Strike: Global Offensive - Direct3D 9")) == NULL) { // checks if CS:GO is Running
		isRunning = false;
		std::cout << "CANT FIND CSGO\n";
		
	}
	else {
		isRunning = true;
		std::cout << "CS:GO IS RUNNING\n";
		std::cout << "LOADING CHEAT\n";
	}

	printInstructions();
	
	// while the hardware ID matches, run CS:GO
	while (hwidChecker() == true) {
		uintptr_t GlowManager = ReadMem<uintptr_t>(moduleBase + dwGlowObjectManager);
		for (auto Entity = 0u; Entity < 64; Entity++) { // checks the whole glow list 
			uintptr_t playerEntity = ReadMem<uintptr_t>(moduleBase + dwEntityList + Entity * 0x10);

			int GlowIndex = ReadMem<int>(playerEntity + m_iGlowIndex);
			int Health = ReadMem<int>(playerEntity + m_iHealth); if (Health < 1 || Health > 100) continue;
			bool Dormant = ReadMem<bool>(playerEntity + m_bDormant); if (Dormant) continue;

			int localPlayerHealth = ReadMem<int>(getLocalPlayer() + m_iHealth);

			int EntityTeam = ReadMem<int>(playerEntity + m_iTeamNum);
			int localTeam = ReadMem<int>(getLocalPlayer() + m_iTeamNum);

			bhopMechanic();
			antiFlash();
			wideFOV();
			literalNoScope();
			thirdPerson();

			if (localTeam != EntityTeam) { // if the entity team is not on my team
				radarAlwaysSeen(playerEntity);
				basicGlowEnemy(GlowManager, GlowIndex);
			}	
		}
	}
}