#pragma once

using namespace hazedumper::netvars;
using namespace hazedumper::signatures;

using namespace hazedumper;

struct glowStructure {
	float red = 0;
	float green = 0;
	float blue = 0;
	float alpha = 0.8;
	uint8_t padding[8];
	float unknown = 1.f;
	uint8_t padding2[4];
	BYTE renderOccluded = true;
	BYTE renderUnoccluded = false;
	BYTE fullBloom = false;
	BYTE buffer[5];
};

struct ClrRender {
	BYTE red = 0, green = 0, blue = 0;
};

void colorRenderEnemy(uintptr_t entity, short int health) {
	ClrRender clrRenderEnemy;
	if (health < 80 && health > 20) {
		clrRenderEnemy.red = 255;
		clrRenderEnemy.green = 255;
	}
	else if (health <= 20) {
		clrRenderEnemy.red = 255;
	}
	else {
		clrRenderEnemy.green = 255;
	}
	WPM<ClrRender>(clrRenderEnemy, entity + m_clrRender);
}

void colorRenderTeam(uintptr_t entity) {
	ClrRender clrRenderTeam;
	clrRenderTeam.green = 255;
	clrRenderTeam.blue = 255;

	WPM<ClrRender>(clrRenderTeam, entity + m_clrRender);
}

void glowStructureEnemy(uintptr_t glowObjectManager, short int glowIndex, uintptr_t entity, short int health) {
	glowStructure EnemyGlow;
	short int diffusing = RPM<short int>(entity + m_bIsDefusing);
	
	while (diffusing == false) {
		EnemyGlow.red = health * -0.01 + 1;
		EnemyGlow.green = health * 0.01;
		EnemyGlow.blue= 0;
	}
	if (diffusing == true) {
		EnemyGlow.red = 1.f;
		EnemyGlow.green = 1.f;
		EnemyGlow.blue = 1.f;
	}
	WPM<glowStructure>(EnemyGlow, glowObjectManager + (glowIndex * 0x38) + 0x4);
}

void glowStructureTeam(uintptr_t glowObjectManager, short int glowIndex, uintptr_t entity) {
	glowStructure TeamGlow;
	TeamGlow.green = 1.f;
	TeamGlow.blue = 1.f;

	WPM<glowStructure>(TeamGlow, glowObjectManager + (glowIndex * 0x38) + 0x4);
}