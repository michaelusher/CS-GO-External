#pragma once

using namespace hazedumper::netvars;
using namespace hazedumper::signatures;

using namespace hazedumper;

struct glowStructure {
	float red;
	float green;
	float blue;
	float alpha = 0.8;
	uint8_t padding[8];
	float unknown = 1.f;
	uint8_t padding2[4];
	BYTE renderOccluded = true;
	BYTE renderUnoccluded = false;
	BYTE fullBloom = false;
	BYTE buffer[5];
};

void glowEnemyHealth(short int health) {
	glowStructure EnemyGlowHealth;
	EnemyGlowHealth.red = health * -0.01 + 1;
	EnemyGlowHealth.green = health * 0.01;
	EnemyGlowHealth.blue = 0;
}

void glowEnemy(uintptr_t glowObjectManager, short int glowIndex, uintptr_t entity, short int health) {
	glowStructure EnemyGlow;
	short int diffusing = RPM<short int>(entity + m_bIsDefusing);

	if (diffusing == false) { // if not diffusing, enemy glow color will reflect health
		EnemyGlow.red = health * -0.01 + 1;
		EnemyGlow.green = health * 0.01;
		EnemyGlow.blue = 0;
	}
	else { // if diffusing, enemy glow is set to white
		EnemyGlow.red = 1.f;
		EnemyGlow.green = 1.f;
		EnemyGlow.blue = 1.f;
	}
	WPM<glowStructure>(EnemyGlow, glowObjectManager + (glowIndex * 0x38) + 0x4);
}

void glowTeam(uintptr_t glowObjectManager, short int glowIndex, uintptr_t entity) {
	glowStructure TeamGlow;

	// team glow is set to cyan
	TeamGlow.red = 0.f;
	TeamGlow.green = 1.f;
	TeamGlow.blue = 1.f;

	WPM<glowStructure>(TeamGlow, glowObjectManager + (glowIndex * 0x38) + 0x4);
}
