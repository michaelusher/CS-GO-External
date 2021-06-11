bool rageStatus;

uintptr_t getLocalPlayer() {
	return ReadMem<uintptr_t>(moduleBase + dwLocalPlayer);
}

void radarAlwaysSeen(uintptr_t entity) {
	WriteMem<bool>(entity + m_bSpotted, true); // set radar to enemies are always seen
}

void antiFlash() {  // flash bang will not blind player 
	long double duration = 0.001;
	WriteMem<long double>(getLocalPlayer() + m_flFlashMaxAlpha, duration); // flash duration is consistenly set to 0
}

void bhopMechanic() {
	BYTE Flag = ReadMem<BYTE>(getLocalPlayer() + m_fFlags);
	if (GetAsyncKeyState(VK_SPACE) && Flag & (1 << 0)) {
		WriteMem<DWORD>(moduleBase + dwForceJump, 0x06); // if the player is on the ground, then force jump to 
	}
}

void wideFOV() { //wide fov cheat
	int normalFOV = 90;
	int wideFOV = 110;
	if (rageStatus == true) {
		if (GetAsyncKeyState(VK_F1)) {
			//WriteMem<int>(getLocalPlayer() + m_iFOV, normalFOV);
		}
		else if (GetAsyncKeyState(VK_F2)) {
			//WriteMem<int>(getLocalPlayer() + m_iFOV, wideFOV);
		}
	}
}

void literalNoScope() {
	if (rageStatus == true) {
		if (GetAsyncKeyState(VK_F3)) {
			WriteMem<bool>(getLocalPlayer() + m_bIsScoped, false); // will not scope in
		}
		else if(GetAsyncKeyState(VK_F4)) {
			WriteMem<bool>(getLocalPlayer() + m_bIsScoped, true);
		}
	}
}

void thirdPerson() { // third person mode will be toggled on if the alt key is pressed
	if (rageStatus == true) {
		if (GetKeyState(VK_MENU)) {
			WriteMem<int>(getLocalPlayer() + m_iObserverMode, 1); // when in thrid person, fov will be wide
			//WriteMem<int>(getLocalPlayer() + m_iFOV, 110);
		}
		else {
			WriteMem<int>(getLocalPlayer() + m_iObserverMode, 0);
		}
	}
}

void shoot() {
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0); // left click simulated
	Sleep(3);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}

void triggerBot(int health) {
	if (GetKeyState(VK_CAPITAL)) {
		int id = ReadMem<int>(getLocalPlayer() + m_iCrosshairId); // id of all players
		if ((health > 0)) // if a player is in the crosshair of local player
			Sleep(170);
			shoot();
	}
}