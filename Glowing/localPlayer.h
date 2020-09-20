uintptr_t getLocalPlayer() {
	return RPM<uintptr_t>(moduleBase + dwLocalPlayer);
}

void antiFlash() {
	bool noFlash = true;
	if (noFlash) { // flash bang will not blind player 
		long double duration = 0.00;
		WPM<long double>(duration, getLocalPlayer() + m_flFlashMaxAlpha); // flash duration is consistenly set to 0
	}
}

void bhopMechanic() {
	antiFlash();
	BYTE Flag = RPM<BYTE>(getLocalPlayer() + m_fFlags);
	if (GetAsyncKeyState(VK_SPACE) && Flag & (1 << 0)) {
		WPM<DWORD>(0x06, moduleBase + dwForceJump); // if the player is on the ground, then force jump to 
	}
}

void radarAlwaysSeen(uintptr_t entity) {
	bhopMechanic();
	bool enemySeen = true;
	if (enemySeen) {
		WPM<bool>(enemySeen, entity + m_bSpotted); // set radar to enemies are always seen
	}
}

void triggerbot(uintptr_t entity) {
	radarAlwaysSeen(entity);
	int id = RPM<int>(getLocalPlayer() + m_iCrosshairId); // id of all players
	if (GetKeyState(VK_CAPITAL)) {
		if (id > 0 && id < 64) { // if a player is in the crosshair of local player
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0); // left click simulated
			Sleep(1);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
	}
}