#pragma once
#include "Includes.h"

bool hwidChecker() {
	bool verified = false;
	//First part gets the HDD informations
	//std::cout << "HWID information" << std::endl;
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
	//	std::cout << "Volume Name: " << volumeName << std::endl;
	//	std::cout << "HDD Serial: " << serialNumber << std::endl;
	//	std::cout << "File System Type: " << fileSystemName << std::endl;
	//	std::cout << "Max Component Length: " << maxComponentLen << std::endl;
		if (serialNumber == 2106490509) {
			verified = true;
		}
		else {
			verified = false;
		}
		return verified;
	}
}