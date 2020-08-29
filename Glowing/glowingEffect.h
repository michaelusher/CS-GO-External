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

struct ClrRender {
	BYTE red, green, blue;
};

void colorRenderEnemy(uintptr_t entity, short int health) {
	ClrRender clrRenderEnemy;
	
	if (health < 80 && health > 20) {
		clrRenderEnemy.red = 255;
		clrRenderEnemy.green = 255;
		clrRenderEnemy.blue = 0;
	}
	else if (health < 30) {
		clrRenderEnemy.red = 255;
		clrRenderEnemy.green = 0;
		clrRenderEnemy.blue = 0;
	}
	else {
		clrRenderEnemy.red = 0;
		clrRenderEnemy.green = 255;
		clrRenderEnemy.blue = 0;
	}

	WPM<ClrRender>(clrRenderEnemy, entity + m_clrRender);
}

void colorRenderTeam(uintptr_t entity) {
	ClrRender clrRenderTeam;
	
	clrRenderTeam.red = 0;
	clrRenderTeam.green = 255;
	clrRenderTeam.blue = 255;

	WPM<ClrRender>(clrRenderTeam, entity + m_clrRender);
}

void glowStructureEnemy(uintptr_t glowObjectManager, short int glowIndex, uintptr_t entity, short int health) {
	glowStructure EnemyGlow;
	short int diffusing = RPM<short int>(entity + m_bIsDefusing);

	if (diffusing == true) {
		EnemyGlow.red = 1.f;
		EnemyGlow.green = 1.f;
		EnemyGlow.blue = 1.f;
	}
	else {
		EnemyGlow.red = health * -0.01 + 1;
		EnemyGlow.green = health * 0.01;
		EnemyGlow.blue = 0;
	}
	WPM<glowStructure>(EnemyGlow, glowObjectManager + (glowIndex * 0x38) + 0x4);
}

void glowStructureTeam(uintptr_t glowObjectManager, short int glowIndex, uintptr_t entity) {
	glowStructure TeamGlow;
	TeamGlow.green = 1.f;
	TeamGlow.blue = 1.f;

	WPM<glowStructure>(TeamGlow, glowObjectManager + (glowIndex * 0x38) + 0x4);
}