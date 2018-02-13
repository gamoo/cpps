// SetupAPITest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <Windows.h>
#include <SetupAPI.h>

#include <iostream>

// https://msdn.microsoft.com/ko-kr/library/windows/desktop/aa379336(v=vs.85).aspx
#pragma comment(lib, "Rpcrt4") // for UuidFromString

#pragma comment(lib, "SetupAPI")

// https://msdn.microsoft.com/en-us/library/windows/hardware/ff551069(v=vs.85).aspx


#define IOS_DEVICE_INTERFACE	L"f0b32be3-6678-4879-9230-e43845d805ee"

using namespace std;

int main()
{
	//GUID guid;
	UUID uuid;		// GUID = UUID
	HDEVINFO hDevInfo;

	UuidFromString((RPC_WSTR)IOS_DEVICE_INTERFACE, &uuid);

	hDevInfo = SetupDiGetClassDevs(&uuid, NULL, NULL, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);

	if (hDevInfo == INVALID_HANDLE_VALUE) {

		wcout << L"Invalid handle : GetLastError() = " << GetLastError() << endl;
		exit(1);
	}

	// https://msdn.microsoft.com/en-us/library/windows/hardware/ff551069(v=vs.85).aspx

	DWORD devIndex = 0;
	SP_DEVINFO_DATA devInfoData;
	ZeroMemory(&devInfoData, sizeof(SP_DEVINFO_DATA));

	devInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

	// Could not get the property
	/*
	while (SetupDiEnumDeviceInfo(hDevInfo, devIndex, &devInfoData)) {

		devIndex++;

		DWORD dwSize = 0L;
		DEVPROPKEY devPropKey{ DEVPROP_TYPE_GUID };
		DEVPROPTYPE devPropType = DEVPROP_TYPE_GUID;

		// Key값을 설정해야 함
		if (!SetupDiGetDeviceProperty(hDevInfo, &devInfoData, &devPropKey, &devPropType, (PBYTE)&uuid, sizeof(GUID), &dwSize, 0) || devPropType != DEVPROP_TYPE_GUID) {

			wcout << L"Getting device propery is failed!" << endl;
		}
		else {

			wcout << L"Getting device propery is successfully fetched." << endl;

		}

	}

	if (hDevInfo) {

		SetupDiDestroyDeviceInfoList(hDevInfo);
	}
	*/

	// 디바이스 인터페이스 얻어오기
	SetupDiEnumDeviceInterfaces(hDevInfo, )

    return 0;
}

