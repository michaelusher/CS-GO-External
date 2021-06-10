#pragma once

extern bool rageStatus;

using namespace hazedumper::netvars;
using namespace hazedumper::signatures;

using namespace hazedumper;

struct glowStructure { // Source SDK
	float red;
	float green;
	float blue;
	float alpha;
	uint8_t padding[8];
	float unknown = 1.f;
	uint8_t padding2[4];
	BYTE renderOccluded = true;
	BYTE renderUnoccluded = false;
	BYTE fullBloom = false;
	BYTE buffer[5];
	int glowSyle;
};

void basicGlowEnemy(uintptr_t glowObjectManager, short int glowIndex, uintptr_t entity) {
	glowStructure EnemyOutline;

	EnemyOutline.red = 0;
	EnemyOutline.green = 1;
	EnemyOutline.blue = 1;
	EnemyOutline.alpha = 0.4f;
	EnemyOutline.glowSyle = 0;

	WriteMem<glowStructure>(glowObjectManager + (glowIndex * 0x38) + 0x4, EnemyOutline);
}

void glowEnemy(uintptr_t glowObjectManager, short int glowIndex, uintptr_t entity, int health) {
	glowStructure EnemyOutline;
	glowStructure EnemyOutlineHealth;
	short int diffusing = ReadMem<short int>(entity + m_bIsDefusing);
	
	if (rageStatus == true) { // enemy glows based off of health
		
		EnemyOutlineHealth.red = health * -0.01 + 1;
		EnemyOutlineHealth.green = health * 0.01;
		EnemyOutlineHealth.blue = 0;

		WriteMem<glowStructure>(glowObjectManager + (glowIndex * 0x38) + 0x4, EnemyOutlineHealth);
	}
	else if (rageStatus == false) { //enemy glows cyan
		EnemyOutlineHealth.red = 0;
		EnemyOutlineHealth.green = 1;
		EnemyOutlineHealth.blue = 1;
		EnemyOutlineHealth.glowSyle = 0;
		WriteMem<glowStructure>(glowObjectManager + (glowIndex * 0x38) + 0x4, EnemyOutlineHealth);
	}
	else if (diffusing == true){ // if diffusing, enemy glow is set to white
		EnemyOutline.red = 1.f;
		EnemyOutline.green = 1.f;
		EnemyOutline.blue = 1.f;

		WriteMem<glowStructure>(glowObjectManager + (glowIndex * 0x38) + 0x4, EnemyOutline);
	}
}

void glowTeam(uintptr_t glowObjectManager, short int glowIndex, uintptr_t entity) { // team glow is set to cyan
	glowStructure TeamGlow;

	TeamGlow.red = 0.f;
	TeamGlow.green = 1.f;
	TeamGlow.blue = 1.f;

	WriteMem<glowStructure>(glowObjectManager + (glowIndex * 0x38) + 0x4, TeamGlow);
}
