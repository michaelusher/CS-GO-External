#pragma once

using namespace hazedumper::netvars;
using namespace hazedumper::signatures;

using namespace hazedumper;

struct glowStructEnemy {
	float red = 1.f;
	float green = 0.f;
	float blue = 0.f;
	float alpha = 1.f;
	uint8_t padding[8];
	float unknown = 1.f;
	uint8_t padding2[4];
	BYTE renderOccluded = true;
	BYTE renderUnoccluded = false;
	BYTE fullBloom = false;
}glowEnem;

void basicGlowEnemy(uintptr_t glowObject, int glowIndex) {
	WriteMem<float>(glowObject + (glowIndex * 0x38) + 0x8, 0.f); // red
	WriteMem<float>(glowObject + (glowIndex * 0x38) + 0xC, 1.f); // green
	WriteMem<float>(glowObject + (glowIndex * 0x38) + 0x10, 1.f); // blue
	WriteMem<float>(glowObject + (glowIndex * 0x38) + 0x14, .7f); // alpha

	WriteMem<bool>(glowObject + (glowIndex * 0x38) + 0x27, true); // render when occluded
	WriteMem<bool>(glowObject + (glowIndex * 0x38) + 0x28, true); // render when unoccluded
}