//
// IO-Warrior SDK 2.0 library
//
#include "stdafx.h"
#include "iowkit2.h"
#include "iowdev.h"

// per application global internal variables
HANDLE DLLModule = NULL;
PIOWI_GLOBAL ShMem = NULL;
UINT DeviceChangeMessageValue = 0;
UINT DataMessageValue = 0;
static HANDLE ShMemMap = NULL;

const char ApplicationsMutexName[] = "IowKit2ApplicationsMutex1";
const char DevicesMutexName[] = "IowKit2DevicesMutex1";

BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		BOOL FirstOne;

		DLLModule = hModule;
		DisableThreadLibraryCalls(DLLModule);

		ShMemMap = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(IOWI_GLOBAL), "IowKit2SharedMemory");
		if (ShMemMap == NULL)
			return FALSE;

		FirstOne = (GetLastError() != ERROR_ALREADY_EXISTS);
		ShMem = MapViewOfFile(ShMemMap, FILE_MAP_WRITE, 0, 0, 0);
		if (ShMem == NULL)
			return FALSE;
		if (FirstOne)
			memset(ShMem, 0, sizeof(IOWI_GLOBAL));
		ShMem->NumberOfLoads++;
		DeviceChangeMessageValue = RegisterWindowMessage("IowKit2DeviceChangeMessage");
		DataMessageValue = RegisterWindowMessage("IowKit2DataMessage");
		break;
	}
	case DLL_PROCESS_DETACH:
		if (ShMem != NULL)
		{
			if (IowiFindApplication() != NULL)
				IowKit2Finalize();

			ShMem->NumberOfLoads--;
			if (ShMem->NumberOfLoads < 0)
				ShMem->NumberOfLoads = 0;
			UnmapViewOfFile(ShMem);
		}
		if (ShMemMap != NULL)
			CloseHandle(ShMemMap);
		break;
	}
	return TRUE;
}