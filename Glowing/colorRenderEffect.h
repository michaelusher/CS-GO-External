#pragma once

using namespace hazedumper::netvars;
using namespace hazedumper::signatures;

using namespace hazedumper;

struct ColorRender { // Source SDK
	BYTE red, green, blue;
};

void colorRenderEnemy(uintptr_t entity, short int health) { // enemy render color is based off of health
	ColorRender clrRenderEnemy;

	if (rageStatus == false) {
		clrRenderEnemy.red = 255;
		clrRenderEnemy.green = 255;
		clrRenderEnemy.blue = 255;
	}
	else if (health < 80 && health > 20) { // yellow render
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
	WPM<ColorRender>(entity + m_clrRender, clrRenderEnemy);
}

void colorRenderTeam(uintptr_t entity) { // team render color is set to cyan
	ColorRender clrRenderTeam;

	if (rageStatus == false) {
		clrRenderTeam.red = 255;
		clrRenderTeam.green = 255;
		clrRenderTeam.blue = 255;
	}
	else {
		clrRenderTeam.red = 0;
		clrRenderTeam.green = 255;
		clrRenderTeam.blue = 255;
	}
	WPM<ColorRender>(entity + m_clrRender, clrRenderTeam);
}