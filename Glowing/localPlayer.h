bool rageStatus;

uintptr_t getLocalPlayer() {
	return ReadMem<uintptr_t>(moduleBase + dwLocalPlayer);
}

void radarAlwaysSeen(uintptr_t entity) { // set radar to enemies are always seen
	WriteMem<bool>(entity + m_bSpotted, true); 
}

void antiFlash() {  // flash bang will not blind player 
	double duration = 0.001;
	WriteMem<double>(getLocalPlayer() + m_flFlashMaxAlpha, duration); // flash duration is consistenly set to 0.001
}

void bhopMechanic() { // if the player is on the ground, then force jump to 
	BYTE Flag = ReadMem<BYTE>(getLocalPlayer() + m_fFlags);
	if (GetAsyncKeyState(VK_SPACE) && Flag & (1 << 0)) {
		WriteMem<DWORD>(moduleBase + dwForceJump, 0x06); 
	}
}

void wideFOV() { // wide fov cheat
	int normalFOV = 90;
	int wideFOV = 110;
	if (GetAsyncKeyState(VK_F1)) {
		WriteMem<int>(getLocalPlayer() + m_iFOV, normalFOV); // toggle normal fov
	}
	else if (GetAsyncKeyState(VK_F2)) {
		WriteMem<int>(getLocalPlayer() + m_iFOV, wideFOV); // toggle wide fov
	}
}

void literalNoScope() { //no scope function
	if (GetAsyncKeyState(VK_F3)) {
		WriteMem<bool>(getLocalPlayer() + m_bIsScoped, false); // will not scope in
	}
	else if(GetAsyncKeyState(VK_F4)) {
		WriteMem<bool>(getLocalPlayer() + m_bIsScoped, true); // will scope in
	}
}

void thirdPerson() { // third person mode will be toggled on if the alt key is pressed
	if (GetKeyState(VK_MENU)) {
		WriteMem<int>(getLocalPlayer() + m_iObserverMode, 1); // when in third person, fov will be wide
		WriteMem<int>(getLocalPlayer() + m_iFOV, 110);
	}
	else {
		WriteMem<int>(getLocalPlayer() + m_iObserverMode, 0);
	}
}
