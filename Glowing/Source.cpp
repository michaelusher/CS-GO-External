#include "Includes.h"

using namespace hazedumper::netvars;
using namespace hazedumper::signatures;

using namespace hazedumper;

void printInstructions() {
	system("Color 0B");
	for (int i = 0; i < 5; i++) {
		std::cout << "...\n";
		Sleep(100);
	}
	std::cout << "\nCOOL VIBES ONLY! (CVO)\n\n";
	Sleep(100);
	std::cout << "Instructions for\n";
	Sleep(100);
	std::cout << "1. Anti-Flash, Radar and Glow are always toggled on by default.\n";
	Sleep(100);
	std::cout << "2. Hold the Spacebar to bhop.\n";
	Sleep(100);
	std::cout << "3. Toggle on Caps Lock to enable the trigger bot.\n";
	Sleep(100);
	std::cout << "4. Have Fun! :)\n";
}

int main() {
	handleWindow = FindWindowA(NULL, "Counter-Strike: Global Offensive");
	GetWindowThreadProcessId(handleWindow, & processId);
	handleProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, processId);
	moduleBase = GetModuleBaseAddress("client.dll");
	engineModule = GetModuleBaseAddress("engine.dll");
	hdc = GetDC(handleWindow);

	printInstructions();
	hwidChecker();

	while (hwidChecker()) {
		uintptr_t GlowManager = RPM<uintptr_t>(moduleBase + dwGlowObjectManager);
		const auto GlowListSize = RPM<uintptr_t>(moduleBase + dwGlowObjectManager + 0xC);

		for (auto i = 0u; i < GlowListSize; i++) { // checks the whole glow list 
			uintptr_t playerEntity = RPM<uintptr_t>(moduleBase + dwEntityList + i * 0x10);
			uintptr_t nonPlayerEntity = RPM<uintptr_t>(moduleBase + dwEntityList + i * 0x38);

			int GlowIndex = RPM<int>(playerEntity + m_iGlowIndex);
			int EnemyHealth = RPM<int>(playerEntity + m_iHealth);

			if (EnemyHealth < 1 || EnemyHealth > 100) // checks if the enemy is alive
				continue;

			int EntityTeam = RPM<int>(playerEntity + m_iTeamNum);
			int localTeam = RPM<int>(getLocalPlayer() + m_iTeamNum);
			bool Dormant = RPM<bool>(playerEntity + m_bDormant);

			if (Dormant) // dormant check
				continue;

			triggerbot(localTeam);
			bhopMechanic();
		
			if (localTeam != EntityTeam) { // if the entity team is not on my team
				colorRenderEnemy(playerEntity, EnemyHealth);
				glowEnemy(GlowManager, GlowIndex, playerEntity, EnemyHealth);
			}
			else if (localTeam == EntityTeam) { // if the entity team is on my team
				glowTeam(GlowManager, GlowIndex, playerEntity);
				colorRenderTeam(playerEntity);
			}
		}
	}
}