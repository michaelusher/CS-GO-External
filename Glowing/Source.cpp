#include "Includes.h"


using namespace hazedumper::netvars;
using namespace hazedumper::signatures;

using namespace hazedumper;


void printInstructions() {
	system("Color 0B");

	std::cout << "COOL VIBES ONLY! V5 (CVO)\n\n";
	Sleep(100);
	std::cout << "Instructions\n";
	Sleep(100);
	std::cout << "*Enemies will glow cyan.\n";
	Sleep(100);
	std::cout << "*Anti-Flash and Radar are toggled on.\n";
	Sleep(100);
	std::cout << "*To toggle bunnyhop, hold spacebar.\n";
	Sleep(5000);
}

int main() {
	handleWindow = FindWindowA(NULL, "Counter-Strike: Global Offensive");
	GetWindowThreadProcessId(handleWindow, &processId);
	handleProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, processId);
	moduleBase = GetModuleBaseAddress("client.dll");
	hdc = GetDC(handleWindow);

	ShowWindow(GetConsoleWindow(), SW_SHOW);
	printInstructions();

	if (hwidChecker() == true) {
		std::cout << "HWID verified";
		Sleep(3000);
		std::cout << "I will go now. GLHF!";
	}
	else{
		std::cout << "HWID not verified";
		Sleep(10000);
		return 0;
	}

	bool isRunning;
	if ((FindWindowA(NULL, "Counter-Strike: Global Offensive")) == NULL) { // checks if CS:GO is Running
		isRunning = false;
		std::cout << "CANT FIND CSGO";
		Sleep(5000);
		ShowWindow(GetConsoleWindow(), SW_HIDE);
	}
	else {
		isRunning = true;
		ShowWindow(GetConsoleWindow(), SW_HIDE);
	}

	while (isRunning == true) {
		uintptr_t GlowManager = ReadMem<uintptr_t>(moduleBase + dwGlowObjectManager);
		const auto GlowListSize = ReadMem<uintptr_t>(moduleBase + dwGlowObjectManager + 0xC);

		for (auto glowableEntity = 0u; glowableEntity < GlowListSize; glowableEntity++) { // checks the whole glow list 
			uintptr_t playerEntity = ReadMem<uintptr_t>(moduleBase + dwEntityList + glowableEntity * 0x10);
			uintptr_t nonPlayerEntity = ReadMem<uintptr_t>(moduleBase + dwEntityList + glowableEntity * 0x38);

			int GlowIndex = ReadMem<int>(playerEntity + m_iGlowIndex);
			int EnemyHealth = ReadMem<int>(playerEntity + m_iHealth);
			int localPlayerHealth = ReadMem<int>(getLocalPlayer() + m_iHealth);

			if (EnemyHealth < 1 || EnemyHealth > 100)
				continue;

			int EntityTeam = ReadMem<int>(playerEntity + m_iTeamNum);
			int localTeam = ReadMem<int>(getLocalPlayer() + m_iTeamNum);
			bool Dormant = ReadMem<bool>(playerEntity + m_bDormant);

			if (Dormant)
				continue;

			bhopMechanic();
			antiFlash();

			if (localTeam != EntityTeam) { // if the entity team is not on my team
				radarAlwaysSeen(playerEntity);
				basicGlowEnemy(GlowManager, GlowIndex, playerEntity);
			}
		}
	}
}