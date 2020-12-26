#pragma once

extern bool rageStatus;

using namespace hazedumper::netvars;
using namespace hazedumper::signatures;

using namespace hazedumper;

struct glowStructure { // Source SDK
	float red;
	float green;
	float blue;
	float alpha = 1.f;
	uint8_t padding[8];
	float unknown = 1.f;
	uint8_t padding2[4];
	BYTE renderOccluded = true;
	BYTE renderUnoccluded = false;
	BYTE fullBloom = false;
	BYTE buffer[5];
};

void glowEnemy(uintptr_t glowObjectManager, short int glowIndex, uintptr_t entity, short int health) {
	glowStructure EnemyGlow;
	glowStructure EnemyGlowHealth;
	short int diffusing = ReadMem<short int>(entity + m_bIsDefusing);

	if (rageStatus == true) { // enemy glows based off of health
		
		EnemyGlowHealth.red = health * -0.01 + 1;
		EnemyGlowHealth.green = health * 0.01;
		EnemyGlowHealth.blue = 0;

		WriteMem<glowStructure>(glowObjectManager + (glowIndex * 0x38) + 0x4, EnemyGlowHealth);
	}
	else if (rageStatus == false) { // enemy glows red
		EnemyGlowHealth.red = 1;
		EnemyGlowHealth.green = 0;
		EnemyGlowHealth.blue = 0;

		WriteMem<glowStructure>(glowObjectManager + (glowIndex * 0x38) + 0x4, EnemyGlowHealth);
	}
	else if (diffusing == true){ // if diffusing, enemy glow is set to white
		EnemyGlow.red = 1.f;
		EnemyGlow.green = 1.f;
		EnemyGlow.blue = 1.f;

		WriteMem<glowStructure>(glowObjectManager + (glowIndex * 0x38) + 0x4, EnemyGlow);
	}
}

void glowTeam(uintptr_t glowObjectManager, short int glowIndex, uintptr_t entity) { // team glow is set to cyan
	glowStructure TeamGlow;

	TeamGlow.red = 0.f;
	TeamGlow.green = 1.f;
	TeamGlow.blue = 1.f;

	WriteMem<glowStructure>(glowObjectManager + (glowIndex * 0x38) + 0x4, TeamGlow);
}
