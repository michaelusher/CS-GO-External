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

		if (serialNumber == 2106490509) { //my SN, c0mplex SN, Hallfic SN, condition SN
			verified = true;
		}
		else if (serialNumber == 1755332032) {
			verified = true;
		}
		else if(serialNumber == 813573350) {
			verified = true;
		}
		else if (serialNumber == 918930106) {
			verified = true;
		}
		else {
			verified = false;
		}
		return verified;
	}
}