#include "Includes.h"

using namespace hazedumper::netvars;
using namespace hazedumper::signatures;

using namespace hazedumper;

int main() {
	hwnd = FindWindowA(NULL, "Counter-Strike: Global Offensive");
	GetWindowThreadProcessId(hwnd, & procId);
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL,  procId);
	moduleBase = GetModuleBaseAddress("client.dll");
	engineModule = GetModuleBaseAddress("engine.dll");
	hdc = GetDC(hwnd);

	for (int i = 0; i < 5; i++) {
		std::cout << "...\n";
		Sleep(100);
	}
	std::cout << "Hack Initiated";

	while (!GetAsyncKeyState(VK_END)) {
		uintptr_t GlowManager = RPM<uintptr_t>(moduleBase + dwGlowObjectManager);
		const auto GlowListSize = RPM<uintptr_t>(moduleBase + dwGlowObjectManager + 0xC);

		for (auto i = 0u; i < GlowListSize; i++) { // checks the whole glow list 
			uintptr_t playerEntity = RPM<uintptr_t>(moduleBase + dwEntityList + i * 0x10);
			uintptr_t nonPlayerEntity = RPM<uintptr_t>(moduleBase + dwEntityList + i * 0x38);

			int GlowIndex = RPM<int>(playerEntity + m_iGlowIndex);
			int EnemyHealth = RPM<int>(playerEntity + m_iHealth);
			bool Dormant = RPM<bool>(playerEntity + m_bDormant); if (Dormant) continue;
			int EntityTeam = RPM<int>(playerEntity + m_iTeamNum); if (EnemyHealth < 1 || EnemyHealth > 100) continue;
			int localTeam = RPM<int>(getLocalPlayer() + m_iTeamNum);

			radarAlwaysSeen(playerEntity);
			bhopMechanic();
			antiFlash();
			triggerbot(playerEntity);

			if (localTeam != EntityTeam) { // if the entity team is not on my team
				colorRenderEnemy(playerEntity, EnemyHealth);
				glowStructureEnemy(GlowManager, GlowIndex, playerEntity, EnemyHealth);
			}
			else if (localTeam == EntityTeam) { // of tje entity team is on my team
				teamColorAndGlow(GlowManager, GlowIndex, playerEntity);
			}
		}
	}
}