#pragma once

using namespace hazedumper::netvars;
using namespace hazedumper::signatures;

using namespace hazedumper;

struct ClrRender {
	BYTE red, green, blue;
};

void colorRenderEnemy(uintptr_t entity, short int health) {
	ClrRender clrRenderEnemy;
	// enemy render color is based off of health

	if (health < 80 && health > 20) { // yellow render
		clrRenderEnemy.red = 255;
		clrRenderEnemy.green = 255;
		clrRenderEnemy.blue = 0;
	}
	else if (health <= 20) { // red render
		clrRenderEnemy.red = 255;
		clrRenderEnemy.green = 0;
		clrRenderEnemy.blue = 0;
	}
	else { // green render
		clrRenderEnemy.red = 0;
		clrRenderEnemy.green = 255;
		clrRenderEnemy.blue = 0;
	}
	WPM<ClrRender>(clrRenderEnemy, entity + m_clrRender);
}

void colorRenderTeam(uintptr_t entity) {
	ClrRender clrRenderTeam;
	// team render color is set to cyan

	clrRenderTeam.red = 0;
	clrRenderTeam.green = 255;
	clrRenderTeam.blue = 255;

	WPM<ClrRender>(clrRenderTeam, entity + m_clrRender);
}