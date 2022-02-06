#pragma once
#include <tchar.h>
#include <intrin.h>

bool hwidChecker() {
	bool verified = false;
	TCHAR volumeName[MAX_PATH + 1] = { 0 };
	TCHAR fileSystemName[MAX_PATH + 1] = { 0 };
	DWORD serialNumber = 0;
	DWORD maxComponentLen = 0;
	DWORD fileSystemFlags = 0;

	if (GetVolumeInformation(
		_T("C:\\"),
		volumeName,
		ARRAYSIZE(volumeName),
		&serialNumber,
		&maxComponentLen,
		&fileSystemFlags,
		fileSystemName,
		ARRAYSIZE(fileSystemName))) {

		if (serialNumber == 2460684972) { // if the drive's serial number is the same as my HWID, return true
			verified = true;
		}
		else {
			verified = false;
		}
	}
	return verified;
}