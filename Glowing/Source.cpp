#include "Includes.h"

using namespace hazedumper::netvars;
using namespace hazedumper::signatures;

using namespace hazedumper;

extern bool rageStatus;

void getInput() {
	std::string input;
	std::cin >> input;
	
	if (input == "legit") {
		std::cout << "Legit mode has been toggled. Have fun! :)\n";
		rageStatus = false;
	}
	else if (input == "rage") {
		std::cout << "Rage mode has been toggled. Have fun! :)\n";
		rageStatus = true;
	}
}
void printInstructions() {
	system("Color 0B");

	std::cout << "COOL VIBES ONLY! V5 (CVO)\n\n";
	Sleep(100);
	std::cout << "Instructions\n";
	Sleep(100);
	//std::cout << "*To toggle bunnyhop, hold spacebar.\n";
	//Sleep(100);
	std::cout << "*To toggle triggerbot, press caps lock.\n";
	Sleep(100);
	//std::cout << "*To toggle third person, press left-alt.\n";
	//Sleep(100);
	//std::cout << "*To toggle wide FOV, press F1\n";
	//Sleep(100);
	//std::cout << "*To toggle normal FOV, press F2\n";
	//Sleep(100);
	//std::cout << "*To toggle no-scope obstruction, press F3.\n";
	//Sleep(100);
	//std::cout << "*To toggle scope obstruction, press F4.\n";
	//Sleep(100);
	rageStatus = true;
}

int main() {
	handleWindow = FindWindowA(NULL, "Counter-Strike: Global Offensive");
	GetWindowThreadProcessId(handleWindow, & processId);
	handleProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, processId);
	moduleBase = GetModuleBaseAddress("client.dll");
	hdc = GetDC(handleWindow);

	while ((!GetAsyncKeyState(VK_END)) && (hwidChecker())) {

		//uintptr_t GlowManager = RPM<uintptr_t>(moduleBase + dwGlowObjectManager);
		const auto GlowListSize = RPM<uintptr_t>(moduleBase + dwGlowObjectManager + 0xC);

		for (uintptr_t i = 0u; i < GlowListSize; i++) { // checks the whole glow list 
			uintptr_t playerEntity = RPM<uintptr_t>(moduleBase + dwEntityList + i * 0x10);
			//uintptr_t nonPlayerEntity = RPM<uintptr_t>(moduleBase + dwEntityList + i * 0x38);

			////int GlowIndex = RPM<int>(playerEntity + m_iGlowIndex);
			//int EnemyHealth = RPM<int>(playerEntity + m_iHealth);
			////int localPlayerHealth = RPM<int>(getLocalPlayer() + m_iHealth);
			//if (EnemyHealth < 1 || EnemyHealth > 100) // checks if the enemy is alive
			//	continue;
			/*int EntityTeam = RPM<int>(playerEntity + m_iTeamNum);
			int localTeam = RPM<int>(getLocalPlayer() + m_iTeamNum);*/
			//bool Dormant = RPM<bool>(playerEntity + m_bDormant);
			//if (Dormant) // dormant check
			//	continue;

			radarAlwaysSeen(playerEntity);
			
			//antiFlash();
			triggerbot(playerEntity);
			//if (localPlayerHealth >= 1 && localPlayerHealth <= 100) {
			//	thirdPerson();
			//}
			//literalNoScope();
			//wideFOV();
			//triggerbot(playerEntity);
			//bhopMechanic();
			//if (localTeam != EntityTeam) { // if the entity team is not on my team
			//	colorRenderEnemy(playerEntity, EnemyHealth);
			//	glowEnemy(GlowManager, GlowIndex, playerEntity, EnemyHealth);
			//}
			//else if (localTeam == EntityTeam) { // if the entity team is on my team
			//	glowTeam(GlowManager, GlowIndex, playerEntity);
			//	colorRenderTeam(playerEntity);
			//}
		}
	}
}