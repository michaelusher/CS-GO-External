bool rageStatus;

uintptr_t getLocalPlayer() {
	return RPM<uintptr_t>(moduleBase + dwLocalPlayer);
}

void antiFlash() {
	if (hwidChecker() != false) { // flash bang will not blind player 
		long double duration = 0.001;
		WPM<long double>(getLocalPlayer() + m_flFlashMaxAlpha, duration); // flash duration is consistenly set to 0
	}
}

void bhopMechanic() {
	antiFlash();
	BYTE Flag = RPM<BYTE>(getLocalPlayer() + m_fFlags);
	if (rageStatus == true) {
		if (GetAsyncKeyState(VK_SPACE) && Flag & (1 << 0)) {
			WPM<DWORD>(moduleBase + dwForceJump, 0x06); // if the player is on the ground, then force jump to 
		}
	}
}

void radarAlwaysSeen(uintptr_t entity) {
	if (hwidChecker() != false)
		WPM<int>(entity + m_bSpotted, true); // set radar to enemies are always seen
}

void wideFOV() { //wide fov cheat time
	int normalFOV = 90;
	int wideFOV = 110;
	if (rageStatus == true) {
		if (GetAsyncKeyState(VK_F1)) {
			WPM<int>(getLocalPlayer() + m_iFOV, normalFOV);
		}
		else if (GetAsyncKeyState(VK_F2)) {
			WPM<int>(getLocalPlayer() + m_iFOV, wideFOV);
		}
	}
}

void literalNoScope() {
	if (rageStatus == true) {
		if (GetAsyncKeyState(VK_F3)) {
			WPM<bool>(getLocalPlayer() + m_bIsScoped, false); // will not scope in
		}
		else if(GetAsyncKeyState(VK_F4)) {
			WPM<bool>(getLocalPlayer() + m_bIsScoped, true);
		}
	}
}

void thirdPerson() { // third person mode will be toggled on if the alt key is pressed
	if (rageStatus == true) {
		if (GetKeyState(VK_MENU)) {
			WPM<int>(getLocalPlayer() + m_iObserverMode, 1); // when in thrid person, fov will be wide
			WPM<int>(getLocalPlayer() + m_iFOV, 110);
		}
		else {
			WPM<int>(getLocalPlayer() + m_iObserverMode, 0);
		}
	}
}

void shoot() {
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0); // left click simulated
	Sleep(1);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}

void triggerbot(uintptr_t entity) {
	int id = RPM<int>(getLocalPlayer() + m_iCrosshairId); // id of all players
	if (GetKeyState(VK_CAPITAL)) {
		if ((id > 0 && id < 64)) { // if a player is in the crosshair of local player
			Sleep(253);
			shoot();
		}
	}
}
