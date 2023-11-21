//
// openclos.cpp
// IO-Warrior SDK library
//
// IOW open & close functions
//
#include "stdafx.h"
#include "iowkit2.h"
#include "iowdev.h"
#include "iowkitcustom.h"

static void IowiKitEnumDevices(void);
static void IowiFinalizeDevice(PIOWI_DEVICE iowDev, BOOL Mutexed);

HANDLE IowiAquireNamedMutex(PCSTR Name)
{
	HANDLE Mutex;

	Mutex = CreateMutex(NULL, FALSE, Name);
	if (Mutex != NULL)
		WaitForSingleObject(Mutex, INFINITE);
	return Mutex;
}

void IowiReleaseNamedMutex(HANDLE Mutex)
{
	if (Mutex != NULL)
	{
		ReleaseMutex(Mutex);
		CloseHandle(Mutex);
	}
}

//=============================================================================

ULONG IowiGetDeviceID(PIOWI_DEVICE iowDev)
{
	if (iowDev != NULL)
		return iowDev->DevID;
	return 0;
}

PIOWI_DEVICE IowiGetDevice(ULONG DevID)
{
	if (DevID != 0)
		return &ShMem->Devices[DevID - 1];
	return NULL;
}

//=============================================================================

PIOWI_APPLICATION IowiGetApplicationFromDevice(PIOWI_DEVICE iowDev)
{
	if ((iowDev != NULL) && (iowDev->AppNo != 0))
		return &ShMem->Applications[iowDev->AppNo - 1];
	else
		return NULL;
}

ULONG IowiGetApplicationID(PIOWI_APPLICATION Appl)
{
	if (Appl != NULL)
		return Appl->AppID;
	return 0;
}

PIOWI_APPLICATION IowiGetApplication(ULONG AppID)
{
	if (AppID != 0)
		return &ShMem->Applications[AppID - 1];
	return NULL;
}

PIOWI_APPLICATION IowiFindApplication(void)
{
	DWORD ProcessID;
	PIOWI_APPLICATION ret;
	ULONG i;
	HANDLE ApplicationsMutex;

	ret = NULL;
	ApplicationsMutex = IowiAquireNamedMutex(ApplicationsMutexName);
	ProcessID = GetCurrentProcessId();
	for (i = 0; i < IOWI_MAX_APPLICATIONS; i++)
		if ((ShMem->Applications[i].Cookie == IOWI_IS_USED) && (ShMem->Applications[i].ProcessID == ProcessID))
		{
			ret = &ShMem->Applications[i];
			break;
		}
	IowiReleaseNamedMutex(ApplicationsMutex);
	return ret;
}

static ULONG IowiAccessMyApplication(PHANDLE Mutex)
{
	DWORD ProcessID;
	ULONG ret;
	ULONG i;
	PIOWI_APPLICATION Appl;
	HANDLE ApplicationsMutex;

	ret = 0;
	*Mutex = NULL;
	ApplicationsMutex = IowiAquireNamedMutex(ApplicationsMutexName);
	ProcessID = GetCurrentProcessId();
	for (i = 0; i < IOWI_MAX_APPLICATIONS; i++)
	{
		Appl = &ShMem->Applications[i];
		if ((Appl->Cookie == IOWI_IS_USED) && (Appl->ProcessID == ProcessID))
		{
			ret = IowiGetApplicationID(Appl);
			*Mutex = IowiAquireNamedMutex(Appl->ApplicationMutexName);
			break;
		}
	}
	IowiReleaseNamedMutex(ApplicationsMutex);
	return ret;
}

void IowiEnumerate(APIVersion)
{
	if (!ShMem->DevListInitialized)
	{
		ShMem->Enumerating = TRUE;
		ShMem->DevListInitialized = TRUE;
		IowiKitEnumDevices();
		ShMem->Enumerating = FALSE;
	}
	else
		IowKit2Enumerate();
}

LRESULT CALLBACK ProcessWindowMessages(HWND Wnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	PIOWI_APPLICATION Appl;

	// do data callback for device (DevNo in lParam)
	if ((Msg == DataMessageValue) && (lParam != 0))
	{
		PIOWI_DEVICE Dev;
		LRESULT ret;

		Dev = IowiGetDevice((ULONG)lParam);
		Appl = IowiGetApplicationFromDevice(Dev);
		if ((Dev != NULL) && (Dev->Cookie != IOWI_IS_FREE) &&
			(Appl != NULL) && (Appl->DataCallbacks[wParam].DataCallback != NULL))
		{
			Appl->InDataCallback = TRUE;
			ret = (LRESULT)(*Appl->DataCallbacks[wParam].DataCallback)((IOWKIT2_HANDLE)Dev, (ULONG)wParam,
				&(Dev->Pipes[wParam].CallbackReport), Dev->Pipes[wParam].HidInfo.Caps.InputReportByteLength,
				Appl->DataCallbacks[wParam].DataContext);
			Appl->InDataCallback = FALSE;
			return ret;
		}
		return 0;
	}
	else
		// do device change callback for device (DevNo in lParam)
		if (Msg == DeviceChangeMessageValue)
		{
			PIOWI_DEVICE Dev;

			Dev = IowiGetDevice((ULONG)lParam);
			Appl = IowiGetApplicationFromDevice(Dev);
			if ((Dev->Cookie != IOWI_IS_FREE) && (Appl != NULL) &&
				(Appl->DeviceChangeCallback != NULL))
			{
				//char buf[256];

				Appl->InDevChangeCallback = TRUE;
				if (wParam == IOWKIT2_ACTION_REMOVAL)
				{
					//sprintf(buf, "device removal %u to %u", lParam, GetCurrentProcessId());
					//OutputDebugString(buf);
					IowiFinalizeDevice(Dev, TRUE);
				}
				else
				{
					//sprintf(buf, "device arrival %u to %u", lParam, GetCurrentProcessId());
					//OutputDebugString(buf);
				}
				(*Appl->DeviceChangeCallback)((ULONG)wParam, (IOWKIT2_HANDLE)Dev, Appl->DeviceChangeContext);
				Appl->InDevChangeCallback = FALSE;
			}
			return 0;
		}
		else
			// handle device change message of Windows (reenumerate devices)
			if ((Msg == WM_DEVICECHANGE) && ((wParam == DBT_DEVICEARRIVAL) || (wParam == DBT_DEVICEREMOVECOMPLETE)))
			{
				LONG tim;

				// for 5 secs we only use messages from this app
				tim = GetMessageTime();
				if ((tim < ShMem->LastMsgTime) || (tim - ShMem->LastMsgTime >= 5000) || (lParam != 0))
					ShMem->DevMgrWindow = NULL;
				ShMem->LastMsgTime = tim;

				if (!ShMem->Enumerating)
				{
					if (ShMem->DevMgrWindow == NULL)
						ShMem->DevMgrWindow = Wnd;
					if (ShMem->DevMgrWindow == Wnd)
					{
						ShMem->Enumerating = TRUE;
						IowiKitEnumDevices();
						ShMem->Enumerating = FALSE;
					}
				}
			}
			else
				// handle new application requesting initial device reenumeration
				if (Msg == WM_USER)
					IowiEnumerate(wParam);
	return DefWindowProc(Wnd, Msg, wParam, lParam);
}

static PIOWI_APPLICATION IowiNewApplication(HANDLE DLLModule, IOWKIT2_DEVICECHANGE_EVENT Event, PVOID Context, ULONG APIVersion)
{
	DWORD ProcessID;
	PIOWI_APPLICATION ret;
	WNDCLASS WndClass;
	ULONG i;
	DWORD err;
	HANDLE ApplicationsMutex;

	ret = NULL;
	err = ERROR_SUCCESS;
	ApplicationsMutex = IowiAquireNamedMutex(ApplicationsMutexName);
	ProcessID = GetCurrentProcessId();
	for (i = 0; i < IOWI_MAX_APPLICATIONS; i++)
		if (ShMem->Applications[i].Cookie == IOWI_IS_FREE)
		{
			ret = &ShMem->Applications[i];
			memset(ret, 0, sizeof(IOWI_APPLICATION));
			ret->AppID = i + 1;
			ret->Cookie = IOWI_IS_USED;
			ret->ProcessID = ProcessID;
			ret->UsedAPIVersion = APIVersion;
			ret->DeviceChangeCallback = Event;
			ret->DeviceChangeContext = Context;
			sprintf(ret->ApplicationMutexName, "IowKit2ApplicationMutex%u", ret->AppID);

			memset(&WndClass, 0, sizeof(WNDCLASS));
			WndClass.lpszClassName = "IowKit2WndClass";
			WndClass.hInstance = DLLModule;
			WndClass.lpfnWndProc = ProcessWindowMessages;
			RegisterClass(&WndClass);
			ret->MsgWnd = CreateWindowEx(WS_EX_TOOLWINDOW, WndClass.lpszClassName, "IowKit2MessageWindow",
				WS_POPUP, 0, 0, 0, 0, 0, 0, DLLModule, NULL);
			if (ret->MsgWnd == NULL)
				err = GetLastError();
			if (err == ERROR_SUCCESS)
			{
				DEV_BROADCAST_DEVICEINTERFACE NotificationFilter;

				memset(&NotificationFilter, 0, sizeof(NotificationFilter));
				NotificationFilter.dbcc_size = sizeof(DEV_BROADCAST_DEVICEINTERFACE);
				NotificationFilter.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
				HidD_GetHidGuid(&NotificationFilter.dbcc_classguid);
				ret->Notify = RegisterDeviceNotification(ret->MsgWnd, &NotificationFilter, DEVICE_NOTIFY_WINDOW_HANDLE);
				if (ret->Notify == NULL)
					err = GetLastError();
			}

			if (err == ERROR_SUCCESS)
			{
				ret->FinalizeEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
				if (ret->FinalizeEvent == NULL)
					err = GetLastError();
			}
			if (err != ERROR_SUCCESS)
			{
				if (ret->Notify != NULL)
					UnregisterDeviceNotification(ret->Notify);
				if (ret->MsgWnd != NULL)
					DestroyWindow(ret->MsgWnd);
				if (ret->FinalizeEvent != NULL)
					CloseHandle(ret->FinalizeEvent);
				memset(ret, 0, sizeof(IOWI_APPLICATION));
				ret->Cookie = IOWI_IS_FREE;
				ret = NULL;
			}
			break;
		}
	if ((ret == NULL) && (err == ERROR_SUCCESS))
		err = ERROR_OUT_OF_STRUCTURES;
	IowiReleaseNamedMutex(ApplicationsMutex);
	SetLastError(err);
	return ret;
}

static void IowiDeleteApplication(PIOWI_APPLICATION Appl)
{
	ULONG i;
	PIOWI_DEVICE Dev;
	HANDLE ApplicationsMutex;

	for (i = 0; i < IOWI_MAX_DEVICES; i++)
	{
		Dev = &ShMem->Devices[i];
		if ((Dev->Cookie != IOWI_IS_FREE) && (IowiGetApplicationFromDevice(Dev) == Appl))
			IowKit2SetDeviceUse((IOWKIT2_HANDLE)Dev, FALSE);
	}
	ApplicationsMutex = IowiAquireNamedMutex(ApplicationsMutexName);
	if (Appl->FinalizeEvent != NULL)
		CloseHandle(Appl->FinalizeEvent);
	if (Appl->MsgWnd != NULL)
	{
		if (ShMem->DevMgrWindow == Appl->MsgWnd)
			ShMem->DevMgrWindow = NULL;
		if (Appl->Notify != NULL)
			UnregisterDeviceNotification(Appl->Notify);
		DestroyWindow(Appl->MsgWnd);
	}
	memset(Appl, 0, sizeof(IOWI_APPLICATION));
	Appl->Cookie = IOWI_IS_FREE;
	IowiReleaseNamedMutex(ApplicationsMutex);
	SetLastError(ERROR_SUCCESS);
}

//=============================================================================

PIOWI_DEVICE IowiAccessMyDevice(IOWKIT2_HANDLE devHandle, HANDLE *DeviceMutex, HANDLE *ApplicationMutex)
{
	ULONG i;
	PIOWI_DEVICE ret;
	ULONG AppNo;
	HANDLE DevicesMutex;

	ret = NULL;
	*DeviceMutex = NULL;
	AppNo = IowiAccessMyApplication(ApplicationMutex);
	if (AppNo != 0)
	{
		DevicesMutex = IowiAquireNamedMutex(DevicesMutexName);
		for (i = 0; i < IOWI_MAX_DEVICES; i++)
			if (((PIOWI_DEVICE)devHandle == &ShMem->Devices[i]) && (ShMem->Devices[i].Cookie != IOWI_IS_FREE) &&
				(AppNo == ShMem->Devices[i].AppNo))
			{
				ret = &ShMem->Devices[i];
				*DeviceMutex = IowiAquireNamedMutex(ret->DeviceMutexName);
				break;
			}
		IowiReleaseNamedMutex(DevicesMutex);
	}
	else
	{
		IowiReleaseNamedMutex(*ApplicationMutex);
		*ApplicationMutex = NULL;
	}
	return ret;
}

void IowiReleaseMyDevice(PIOWI_DEVICE iowDev, HANDLE DeviceMutex, HANDLE ApplicationMutex)
{
	IowiReleaseNamedMutex(DeviceMutex);
	IowiReleaseNamedMutex(ApplicationMutex);
}

//=============================================================================

static void IowiFinalizePipe(PIOWI_DEVICE iowDev, ULONG numPipe)
{
	PIOWI_DEVICE_PIPE Pipe;

	Pipe = &iowDev->Pipes[numPipe];
	if (Pipe->insertEvent != NULL)
		CloseHandle(Pipe->insertEvent);
	if (Pipe->readFailedEvent != NULL)
		CloseHandle(Pipe->readFailedEvent);
	if (Pipe->endEvent != NULL)
		CloseHandle(Pipe->endEvent);
	if (Pipe->threadTermEvent != NULL)
		CloseHandle(Pipe->threadTermEvent);

	if (Pipe->ReadHandle != NULL)
		CloseHandle(Pipe->ReadHandle);
	if (Pipe->WriteHandle != NULL)
		CloseHandle(Pipe->WriteHandle);

	Pipe->insertEvent = NULL;
	Pipe->readFailedEvent = NULL;
	Pipe->endEvent = NULL;
	Pipe->threadTermEvent = NULL;

	Pipe->WriteHandle = NULL;
	Pipe->ReadHandle = NULL;
}

static BOOL IowiInitializePipe(PIOWI_DEVICE iowDev, ULONG numPipe)
{
	PIOWI_DEVICE_PIPE Pipe;

	Pipe = &iowDev->Pipes[numPipe];
	Pipe->insertEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	Pipe->readFailedEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	Pipe->endEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	Pipe->threadTermEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	sprintf(Pipe->bufMutexName, "IowKit2BufMutex%u_%u", iowDev->DevID, numPipe);
	sprintf(Pipe->readMutexName, "IowKit2ReadMutex%u_%u", iowDev->DevID, numPipe);
	sprintf(Pipe->msgMutexName, "IowKit2MsgMutex%u_%u", iowDev->DevID, numPipe);
	sprintf(Pipe->cancelMutexName, "IowKit2CancelMutex%u_%u", iowDev->DevID, numPipe);

	Pipe->bufStart = 0;
	Pipe->bufEnd = 0;
	Pipe->numBuf = 0;

	Pipe->ReadHandle = CreateFile(Pipe->HidInfo.DevicePath,	GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
	Pipe->WriteHandle = CreateFile(Pipe->HidInfo.DevicePath, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);

	if ((Pipe->insertEvent == NULL) || (Pipe->readFailedEvent == NULL) || (Pipe->endEvent == NULL) || (Pipe->threadTermEvent == NULL))
	{
		IowiFinalizePipe(iowDev, numPipe);
		return FALSE;
	}
	return TRUE;
}

static BOOL IowiStartThread(PIOWI_DEVICE iowDev, ULONG numPipe)
{
	BOOL ret;
	static LPTHREAD_START_ROUTINE ThreadCallbacks[IOWKIT2_MAX_PIPES] =
	{ &IowiReadIOThread, &IowiReadSpecialThread , &IowiReadI2CThread, &IowiReadADCThread };

	if (iowDev->Cookie != IOWI_PRESENT)
		return FALSE;
	if (!IowiInitializePipe(iowDev, numPipe))
		return FALSE;

	HidD_SetNumInputBuffers(iowDev->Pipes[numPipe].ReadHandle, IOWI_NUM_BUFFERS);

	iowDev->Pipes[numPipe].ioThread = CreateThread(NULL, 0, ThreadCallbacks[numPipe], iowDev, 0, NULL);
	ret = iowDev->Pipes[numPipe].ioThread != NULL;
	if (!ret)
		IowiFinalizePipe(iowDev, numPipe);
	return ret;
}

static void IowiStopThread(PIOWI_DEVICE iowDev, ULONG numPipe)
{
	PIOWI_DEVICE_PIPE Pipe;

	Pipe = &iowDev->Pipes[numPipe];
	// Check if thread has been started
	if (Pipe->ioThread != NULL)
	{
		// Tell thread to terminate
		SetEvent(Pipe->endEvent);
		// Wait for thread to tell it terminates
		WaitForSingleObject(Pipe->threadTermEvent, INFINITE);
		// Wait for thread to terminate
		WaitForSingleObject(Pipe->ioThread, INFINITE);
		// Close thread handle
		CloseHandle(Pipe->ioThread);
		Pipe->ioThread = NULL;
	}
	IowiFinalizePipe(iowDev, numPipe);
}

void IowiStopDevice(PIOWI_DEVICE iowDev, BOOL Mutexed)
{
	ULONG i;
	HANDLE Mutex;

	if (Mutexed)
		Mutex = IowiAquireNamedMutex(iowDev->DeviceMutexName);
	for (i = 0; i < IOWKIT2_MAX_PIPES; i++)
		IowiStopThread(iowDev, i);
	if (Mutexed)
		IowiReleaseNamedMutex(Mutex);
}

BOOL IowiStartDevice(PIOWI_DEVICE iowDev)
{
	BOOL ret;
	ULONG i;
	HANDLE Mutex;

	Mutex = IowiAquireNamedMutex(iowDev->DeviceMutexName);
	ret = TRUE;
	for (i = 0; i < IOWKIT2_MAX_PIPES; i++)
		ret &= IowiStartThread(iowDev, i);
	if (!ret)
		IowiStopDevice(iowDev, TRUE);
	IowiReleaseNamedMutex(Mutex);
	return ret;
}

static void IowiFinalizeDevice(PIOWI_DEVICE iowDev, BOOL Mutexed)
{
	HANDLE Mutex;

	if (Mutexed)
		Mutex = IowiAquireNamedMutex(iowDev->DeviceMutexName);
	IowiStopDevice(iowDev, Mutexed);
	iowDev->Cookie = IOWI_NOTPRESENT;
	if (Mutexed)
		IowiReleaseNamedMutex(Mutex);
}

static void IowiInitializeDevice(PIOWI_DEVICE iowDev)
{
	memset(&iowDev->lastReport, 0xFF, sizeof(IOWKIT2_REPORT));
	iowDev->lastReport.ReportID = 0;
	iowDev->readAny = FALSE;
	iowDev->ioTimeout = INITIAL_TIMEOUT;
	iowDev->ioWriteTimeout = INITIAL_TIMEOUT;
	sprintf(iowDev->DeviceMutexName, "IowKit2DeviceMutex%u", iowDev->DevID);
}

static void IowiFreeDevice(PIOWI_DEVICE iowDev, BOOL Mutexed)
{
	HANDLE Mutex;

	if (Mutexed)
		Mutex = IowiAquireNamedMutex(iowDev->DeviceMutexName);
	IowiFinalizeDevice(iowDev, Mutexed);
	if (Mutexed)
		IowiReleaseNamedMutex(Mutex);
	memset(iowDev, 0, sizeof(IOWI_DEVICE));
	iowDev->Cookie = IOWI_IS_FREE;
}

//=============================================================================

// Get device_interface_detail_data for given device
static BOOL IowiGetDevicePath(HDEVINFO devInfo, PSP_DEVICE_INTERFACE_DATA devInterfaceData,
	PSP_DEVINFO_DATA devData, char *PathBuffer)
{
	PSP_DEVICE_INTERFACE_DETAIL_DATA_A devDetails;
	char buffer[IOWI_DEVICEPATH_LEN];
	ULONG len, req_len;

	*PathBuffer = '\0';
	// Get length
	SetupDiGetDeviceInterfaceDetailA(devInfo, devInterfaceData, NULL, 0, &len, devData);
	if ((len == 0) || (len > IOWI_DEVICEPATH_LEN))
		return FALSE;
	devDetails = (PSP_DEVICE_INTERFACE_DETAIL_DATA_A)buffer;
	// Get details
	devDetails->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA_A);
	SetupDiGetDeviceInterfaceDetailA(devInfo, devInterfaceData, devDetails, len, &req_len, devData);
	strcpy(PathBuffer, devDetails->DevicePath);
	return TRUE;
}

static BOOL IowiIsIowDevice(HANDLE devHandle, PHIDD_ATTRIBUTES phidAttr)
{
	BOOL bOK;

	// Set up structure for call
	phidAttr->Size = sizeof(HIDD_ATTRIBUTES);
	// Get HID device attributes
	bOK = HidD_GetAttributes(devHandle, phidAttr);
	if (bOK)
		// Compare vendorID & productID with IoWarrior's
		// NOTE: we don't care about VersionNumber
#if IOWARRIOR_CUSTOM_LEVEL == IOWARRIOR_ORIGINAL_ONLY

		bOK =
		(phidAttr->VendorID == IOWKIT2_VID) &&
		(
			   (phidAttr->ProductID == IOWKIT2_PID_IOW40)
			|| (phidAttr->ProductID == IOWKIT2_PID_IOW24)
			|| (phidAttr->ProductID == IOWKIT2_PID_IOWPV1)
			|| (phidAttr->ProductID == IOWKIT2_PID_IOWPV2)
			|| (phidAttr->ProductID == IOWKIT2_PID_IOW_SENSI1)
			|| (phidAttr->ProductID == IOWKIT2_PID_IOW56)
			|| (phidAttr->ProductID == IOWKIT2_PID_IOW28)
			|| (phidAttr->ProductID == IOWKIT2_PID_IOW28L)
			|| (phidAttr->ProductID == IOWKIT2_PID_IOW100)
			|| (phidAttr->ProductID == IOWKIT2_PID_TW)
		);

#elif IOWARRIOR_CUSTOM_LEVEL == IOWARRIOR_PLUS_CUSTOM

		bOK =
		(
		(phidAttr->VendorID == IOWKIT2_VID) &&
			(
			(phidAttr->ProductID == IOWKIT2_PID_IOW40) ||
				(phidAttr->ProductID == IOWKIT2_PID_IOW24) ||
				(phidAttr->ProductID == IOWKIT2_PID_IOWPV1) ||
				(phidAttr->ProductID == IOWKIT2_PID_IOWPV2) ||
				(phidAttr->ProductID == IOWKIT2_PID_IOW_SENSI1) ||
				(phidAttr->ProductID == IOWKIT2_PID_IOW56) ||
				(phidAttr->ProductID == IOWKIT2_PID_IOW28) ||
				(phidAttr->ProductID == IOWKIT2_PID_IOW28L) ||
				(phidAttr->ProductID == IOWKIT2_PID_IOW100) ||
				(phidAttr->ProductID == IOWKIT2_PID_TW)
				)
			)
		||
		(
		(phidAttr->VendorID == IOWKIT_CUSTOM_VID) &&
			(
			(phidAttr->ProductID == IOWKIT_CUSTOM_PID_1)
#if IOWARRIOR_NUM_CUSTOM_PIDS >= 2
				|| (phidAttr->ProductID == IOWKIT_CUSTOM_PID_2)
#endif
#if IOWARRIOR_NUM_CUSTOM_PIDS >= 3
				|| (phidAttr->ProductID == IOWKIT_CUSTOM_PID_3)
#endif
#if IOWARRIOR_NUM_CUSTOM_PIDS >= 4
				|| (phidAttr->ProductID == IOWKIT_CUSTOM_PID_4)
#endif
#if IOWARRIOR_NUM_CUSTOM_PIDS >= 5
				|| (phidAttr->ProductID == IOWKIT_CUSTOM_PID_5)
#endif
#if IOWARRIOR_NUM_CUSTOM_PIDS >= 6
				|| (phidAttr->ProductID == IOWKIT_CUSTOM_PID_6)
#endif
				)
			);

#elif IOWARRIOR_CUSTOM_LEVEL == IOWARRIOR_CUSTOM_ONLY

		bOK =
		(phidAttr->VendorID == IOWKIT_CUSTOM_VID) &&
		(
		(phidAttr->ProductID == IOWKIT_CUSTOM_PID_1)
#if IOWARRIOR_NUM_CUSTOM_PIDS >= 2
			|| (phidAttr->ProductID == IOWKIT_CUSTOM_PID_2)
#endif
#if IOWARRIOR_NUM_CUSTOM_PIDS >= 3
			|| (phidAttr->ProductID == IOWKIT_CUSTOM_PID_3)
#endif
#if IOWARRIOR_NUM_CUSTOM_PIDS >= 4
			|| (phidAttr->ProductID == IOWKIT_CUSTOM_PID_4)
#endif
#if IOWARRIOR_NUM_CUSTOM_PIDS >= 5
			|| (phidAttr->ProductID == IOWKIT_CUSTOM_PID_5)
#endif
#if IOWARRIOR_NUM_CUSTOM_PIDS >= 6
			|| (phidAttr->ProductID == IOWKIT_CUSTOM_PID_6)
#endif
			);

#else
#error Bad value for IOWARRIOR_CUSTOM_LEVEL
#endif

		return bOK;
}

static PIOWI_DEVICE IowiFindByDevInst(DEVINST devInst, PIOWI_DEVICE DevList, ULONG count, DEVINST *Parent, DEVINST *GrandParent)
{
	ULONG i;

	CM_Get_Parent(Parent, devInst, 0);
	CM_Get_Parent(GrandParent, *Parent, 0);

	for (i = 0; i < count; i++)
	{
		if (DevList[i].Pipes[IOWKIT2_PIPE_IO_PINS].HidInfo.GrandParent != 0)
		{
			if (DevList[i].Pipes[IOWKIT2_PIPE_IO_PINS].HidInfo.GrandParent == *GrandParent)
				return &DevList[i];
		}
		else if (DevList[i].Pipes[IOWKIT2_PIPE_SPECIAL_MODE].HidInfo.GrandParent != 0)
		{
			if (DevList[i].Pipes[IOWKIT2_PIPE_SPECIAL_MODE].HidInfo.GrandParent == *GrandParent)
				return &DevList[i];
		}
		else if (DevList[i].Pipes[IOWKIT2_PIPE_I2C_MODE].HidInfo.GrandParent != 0)
		{
			if (DevList[i].Pipes[IOWKIT2_PIPE_I2C_MODE].HidInfo.GrandParent == *GrandParent)
				return &DevList[i];
		}
		else
		{
			if (DevList[i].Pipes[IOWKIT2_PIPE_ADC_MODE].HidInfo.GrandParent == *GrandParent)
				return &DevList[i];
		}

	}
	return NULL;
}

/*
static PIOWI_DEVICE IowiFindByDevPath(PIOWI_DEVICE DevList, ULONG count, char *DevPath)
 {
  ULONG i;
  char path[IOWI_DEVICEPATH_LEN];
  char buffer[IOWI_DEVICEPATH_LEN];
  char *p;

  strcpy(path, DevPath);
  _strlwr(path);
  p = strstr(path, "mi_");
  if (p != NULL)
	for (i = 0; i < count; i++)
	  if (DevList[i].Pipes[IOWKIT2_PIPE_IO_PINS].HidInfo.DevicePath[0] != '\0')
	   {
		strcpy(buffer, DevList[i].Pipes[IOWKIT2_PIPE_IO_PINS].HidInfo.DevicePath);
		_strlwr(buffer);
		if (strncmp(path, buffer, p - path) == 0)
		  return &DevList[i];
	   }
	  else
	   {
		strcpy(buffer, DevList[i].Pipes[IOWKIT2_PIPE_SPECIAL_MODE].HidInfo.DevicePath);
		_strlwr(buffer);
		if (strncmp(path, buffer, p - path) == 0)
		  return &DevList[i];
	   }
  return NULL;
 }
*/

typedef struct _TPidKindPair
{
	unsigned int Pid;
	unsigned int Kind;
}
TPidKindPair;

static TPidKindPair CustomPIDKind[6] =
{
 {IOWKIT_CUSTOM_PRODUCT_ID_1, IOWKIT_CUSTOM_PRODUCT_ID_1_KIND},
 {IOWKIT_CUSTOM_PRODUCT_ID_2, IOWKIT_CUSTOM_PRODUCT_ID_2_KIND},
 {IOWKIT_CUSTOM_PRODUCT_ID_3, IOWKIT_CUSTOM_PRODUCT_ID_3_KIND},
 {IOWKIT_CUSTOM_PRODUCT_ID_4, IOWKIT_CUSTOM_PRODUCT_ID_4_KIND},
 {IOWKIT_CUSTOM_PRODUCT_ID_5, IOWKIT_CUSTOM_PRODUCT_ID_5_KIND},
 {IOWKIT_CUSTOM_PRODUCT_ID_6, IOWKIT_CUSTOM_PRODUCT_ID_6_KIND}
};

static void IowiFillInList(PIOWI_DEVICE DevList)
{
	HANDLE devHandle;
	GUID HidGuid;
	HDEVINFO devInfo;
	SP_INTERFACE_DEVICE_DATA devInterfaceData;
	SP_DEVINFO_DATA devData;
	PIOWI_DEVICE iowDev;
	ULONG i;
	ULONG n = 0;

#if IOWARRIOR_CUSTOM_LEVEL > IOWARRIOR_ORIGINAL_ONLY
	int j;
#endif

	char PathBuffer[IOWI_DEVICEPATH_LEN];
	PHIDP_PREPARSED_DATA prepData;
	HIDD_ATTRIBUTES hidAttr;
	HIDP_CAPS hidCaps;
	wchar_t Buffer[256];
	UINT NDevs;
	DEVINST Parent, GrandParent;
	int pipe_count = 0;

	//Für die PID beim IOW28 
	wchar_t productBuffer[512];
	memset(productBuffer, 0, 512);

	HidD_GetHidGuid(&HidGuid);
	// Start HID device enumeration
	devInfo = SetupDiGetClassDevsA(&HidGuid, NULL, NULL, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);
	// Check if error
	if (devInfo == INVALID_HANDLE_VALUE)
		return;

	// Set up DEVICE_DATA for enumeration
	devInterfaceData.cbSize = sizeof(devInterfaceData);
	// Init
	i = 0;
	NDevs = 0;

	// Enumerate IOW devices
	while (SetupDiEnumDeviceInterfaces(devInfo, NULL, &HidGuid, i, &devInterfaceData))
	{
		i++;
		

		devData.cbSize = sizeof(devData);
		memset(PathBuffer, 0, IOWI_DEVICEPATH_LEN);
		IowiGetDevicePath(devInfo, &devInterfaceData, &devData, PathBuffer);
		// Open device for HID access
		devHandle = CreateFile(PathBuffer, GENERIC_READ | GENERIC_WRITE,FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);

		if (devHandle == INVALID_HANDLE_VALUE)
			devHandle = CreateFile(PathBuffer, 0, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);

		// Check if we have handle
		if ((devHandle != INVALID_HANDLE_VALUE) && IowiIsIowDevice(devHandle, &hidAttr))
		{
			// We've got IO-Warrior device handle
			iowDev = IowiFindByDevInst(devData.DevInst, DevList, NDevs, &Parent, &GrandParent);

			if (iowDev == NULL)
			{
				if (NDevs >= IOWI_MAX_DEVICES)
					break;

				iowDev = &DevList[NDevs];
				iowDev->Cookie = IOWI_PRESENT;
				iowDev->AppNo = 0;
				NDevs++;
			}

			HidD_GetPreparsedData(devHandle, &prepData);
			HidP_GetCaps(prepData, &hidCaps);
			HidD_FreePreparsedData(prepData);

#if IOWARRIOR_CUSTOM_LEVEL < IOWARRIOR_CUSTOM_ONLY

			if (hidAttr.VendorID == IOWKIT2_VENDOR_ID)
			{
				switch (hidAttr.ProductID)
				{
				case IOWKIT2_PID_IOW40:
					pipe_count = (hidCaps.OutputReportByteLength == 5) ? IOWKIT2_PIPE_IO_PINS : IOWKIT2_PIPE_SPECIAL_MODE;
					//n = (hidCaps.OutputReportByteLength == 5) ? IOWKIT2_PIPE_IO_PINS : IOWKIT2_PIPE_SPECIAL_MODE;

					break;
					
				case IOWKIT2_PID_IOW28:
					HidD_GetProductString(devHandle, &productBuffer, 512);

					//IOW28-SimpleIO (each char ends with \0)
					//if (strncmp(productBuffer, "I\0O\0W\02\08\0-\0S\0i\0m\0p\0l\0e\0I\0O\0", 28) == 0)
					if (wcscmp(productBuffer, L"IOW28-SimpleIO\0") == 0)
						pipe_count = IOWKIT2_PIPE_IO_PINS;

					//IOW28-ComplexIO
					if (wcscmp(productBuffer, L"IOW28-ComplexIO\0") == 0)
						pipe_count = IOWKIT2_PIPE_SPECIAL_MODE;

					//IOW28-FastIIC
					if (wcscmp(productBuffer, L"IOW28-FastIIC\0") == 0)
						pipe_count = IOWKIT2_PIPE_I2C_MODE;

					//IOW28-ADC
					if (wcscmp(productBuffer, L"IOW28-ADC\0") == 0)
						pipe_count = IOWKIT2_PIPE_ADC_MODE;
					
					break;
				case IOWKIT2_PID_TW:
					HidD_GetProductString(devHandle, &productBuffer, 512);

					//TW28-SimpleIO
					if (wcscmp(productBuffer, L"TW28-SimpleIO\0") == 0)
						pipe_count = IOWKIT2_PIPE_IO_PINS;

					//TW28-Unused (not working but present)
					if (wcscmp(productBuffer, L"TW28-Unused\0") == 0)
						pipe_count = IOWKIT2_PIPE_SPECIAL_MODE;

					break;
				case IOWKIT2_PID_IOW100:
					HidD_GetProductString(devHandle, &productBuffer, 512);

					//IOW28-SimpleIO (each char ends with \0)
					if (wcscmp(productBuffer, L"IOW100-SimpleIO\0") == 0)
						pipe_count = IOWKIT2_PIPE_IO_PINS;

					//IOW28-ComplexIO
					if (wcscmp(productBuffer, L"IOW100-ComplexIO\0") == 0)
						pipe_count = IOWKIT2_PIPE_SPECIAL_MODE;

					//IOW28-FastIIC
					if (wcscmp(productBuffer, L"IOW100-FastIIC\0") == 0)
						pipe_count = IOWKIT2_PIPE_I2C_MODE;

					//IOW28-ADC
					if (wcscmp(productBuffer, L"IOW100-ADC\0") == 0)
						pipe_count = IOWKIT2_PIPE_ADC_MODE;
					break;

				case IOWKIT2_PID_IOW28L:
					//pipe_count = (hidCaps.OutputReportByteLength == 5) ? IOWKIT2_PIPE_IO_PINS : IOWKIT2_PIPE_SPECIAL_MODE;
					//memset(productBuffer, 0, 512);

					HidD_GetProductString(devHandle, &productBuffer, 512);

					//IOW28-SimpleIO (each char ends with \0
					if (wcscmp(productBuffer, L"IOW28-SimpleIO\0") == 0)
						pipe_count = IOWKIT2_PIPE_IO_PINS;

					//IOW28-ComplexIO
					if (wcscmp(productBuffer, L"IOW28-ComplexIO\0") == 0)
						pipe_count = IOWKIT2_PIPE_SPECIAL_MODE;

					break;

				case IOWKIT2_PID_IOW24:
				case IOWKIT2_PID_IOWPV1:
				case IOWKIT2_PID_IOWPV2:
				case IOWKIT2_PID_IOW_SENSI1:
					pipe_count = (hidCaps.OutputReportByteLength == 3) ? IOWKIT2_PIPE_IO_PINS : IOWKIT2_PIPE_SPECIAL_MODE;
					//n = (hidCaps.OutputReportByteLength == 3) ? IOWKIT2_PIPE_IO_PINS : IOWKIT2_PIPE_SPECIAL_MODE;
					break;
				case IOWKIT2_PID_IOW56:
					pipe_count = (hidCaps.OutputReportByteLength == 8) ? IOWKIT2_PIPE_IO_PINS : IOWKIT2_PIPE_SPECIAL_MODE;
					//n = (hidCaps.OutputReportByteLength == 8) ? IOWKIT2_PIPE_IO_PINS : IOWKIT2_PIPE_SPECIAL_MODE;
					break;
				}
#endif

#if IOWARRIOR_CUSTOM_LEVEL > IOWARRIOR_ORIGINAL_ONLY

				if (hidAttr.VendorID == IOWKIT_CUSTOM_VENDOR_ID)
					for (j = 0; j < IOWARRIOR_NUM_CUSTOM_PIDS; j++)
						if (CustomPIDKind[j].Pid == hidAttr.ProductID)
						{
							switch (CustomPIDKind[j].Kind)
							{
							case IOWARRIOR_KIND_40:
								n = (hidCaps.OutputReportByteLength == 5) ? IOWKIT2_PIPE_IO_PINS : IOWKIT2_PIPE_SPECIAL_MODE;
								break;
							/*
							case IOWARRIOR_KIND_28:
								n = (hidCaps.OutputReportByteLength == 5) ? IOWKIT2_PIPE_IO_PINS : IOWKIT2_PIPE_SPECIAL_MODE;
								break;
							*/
							case IOWARRIOR_KIND_24:

								n = (hidCaps.OutputReportByteLength == 3) ? IOWKIT2_PIPE_IO_PINS : IOWKIT2_PIPE_SPECIAL_MODE;
								break;
							case IOWARRIOR_KIND_56:
								n = (hidCaps.OutputReportByteLength == 8) ? IOWKIT2_PIPE_IO_PINS : IOWKIT2_PIPE_SPECIAL_MODE;
								break;
							}
							break;
						}
#endif

			}

			strcpy(iowDev->Pipes[pipe_count].HidInfo.DevicePath, PathBuffer);
			iowDev->Pipes[pipe_count].HidInfo.DevInst = GrandParent;
			iowDev->Pipes[pipe_count].HidInfo.Parent = Parent;
			iowDev->Pipes[pipe_count].HidInfo.GrandParent = GrandParent;
			iowDev->Pipes[pipe_count].HidInfo.Attributes = hidAttr;
			iowDev->Pipes[pipe_count].HidInfo.Caps = hidCaps;

			memset(iowDev->SerialNumber, 0, sizeof(iowDev->SerialNumber));
			if (HidD_GetSerialNumberString(devHandle, iowDev->SerialNumber, sizeof(iowDev->SerialNumber)))
			{
				// fix a bug in HID.DLL
				memset(Buffer, 0, sizeof(Buffer));
				HidD_GetIndexedString(devHandle, 0, Buffer, sizeof(Buffer));
				if (memcmp(iowDev->SerialNumber, Buffer, sizeof(iowDev->SerialNumber)) == 0)
					memset(iowDev->SerialNumber, 0, sizeof(iowDev->SerialNumber));
			}
			iowDev->PipeCount++;
			IowiInitializeDevice(iowDev);
		}
		if (devHandle != INVALID_HANDLE_VALUE)
			CloseHandle(devHandle);
	}
	SetupDiDestroyDeviceInfoList(devInfo);

	//Test wegen 4 Pipes vom IOW28
	/*
	// delete incomplete devices from DevList
	for (NDevs = 0, i = 0; i < IOWI_MAX_DEVICES; i++)
	{
		if ((DevList[i].Cookie != IOWI_IS_FREE) && (DevList[i].PipeCount != IOWKIT2_MAX_PIPES))
			IowiFreeDevice(&DevList[i], FALSE);
	}
	*/
}

void IowiEnumerateNewDevices(PIOWI_APPLICATION AAppl)
{
	ULONG i, j;
	HANDLE DevicesMutex, ApplicationsMutex;
	PIOWI_DEVICE Dev;
	PIOWI_APPLICATION Appl;

	ApplicationsMutex = IowiAquireNamedMutex(ApplicationsMutexName);
	for (i = 0; i < IOWI_MAX_DEVICES; i++)
	{
		Dev = &ShMem->Devices[i];
		if (Dev->NewDev)
			for (j = 0; j < IOWI_MAX_APPLICATIONS; j++)
			{
				Appl = &ShMem->Applications[j];
				if ((Appl->Cookie == IOWI_IS_USED) && (Appl->DeviceChangeCallback != NULL) && (Appl != AAppl))
				{
					Dev->AppNo = Appl->AppID;
					IowiReleaseNamedMutex(ApplicationsMutex);
					SendMessage(Appl->MsgWnd, DeviceChangeMessageValue, IOWKIT2_ACTION_ARRIVAL, (LPARAM)Dev->DevID);
					ApplicationsMutex = IowiAquireNamedMutex(ApplicationsMutexName);
					if (Dev->InUse)
						break;
					Dev->AppNo = 0;
				}
			}
	}
	IowiReleaseNamedMutex(ApplicationsMutex);

	DevicesMutex = IowiAquireNamedMutex(DevicesMutexName);
	for (i = 0; i < IOWI_MAX_DEVICES; i++)
	{
		Dev = &ShMem->Devices[i];
		if (Dev->Cookie != IOWI_IS_FREE)
		{
			HANDLE Mutex;

			Mutex = IowiAquireNamedMutex(Dev->DeviceMutexName);
			ShMem->Devices[i].NewDev = FALSE;
			IowiReleaseNamedMutex(Mutex);
		}
	}
	IowiReleaseNamedMutex(DevicesMutex);
}

static void IowiKitEnumDevices(void)
{
	ULONG i, j;
	BOOL New;
	PIOWI_DEVICE CurrDev;
	PIOWI_DEVICE NewDevices;
	HANDLE DevicesMutex;
	//char buf[256];

	NewDevices = (PIOWI_DEVICE)LocalAlloc(LPTR, sizeof(IOWI_DEVICE)*IOWI_MAX_DEVICES);
	if (NewDevices == NULL)
		return;

	memset(NewDevices, 0, sizeof(IOWI_DEVICE)*IOWI_MAX_DEVICES);
	IowiFillInList(NewDevices);

	DevicesMutex = IowiAquireNamedMutex(DevicesMutexName);

	/*
	OutputDebugString("old devs:");
	for (i = 0; i < IOWI_MAX_DEVICES; i++)
	 {
	  CurrDev = &ShMem->Devices[i];
	  if (CurrDev->Cookie == IOWI_PRESENT)
	   {
		sprintf(buf, "%u) %s", CurrDev->DevID, CurrDev->Pipes[IOWKIT2_PIPE_IO_PINS].HidInfo.DevicePath);
		OutputDebugString(buf);
		sprintf(buf, "%u) %s", CurrDev->DevID, CurrDev->Pipes[IOWKIT2_PIPE_SPECIAL_MODE].HidInfo.DevicePath);
		OutputDebugString(buf);
	   }
	 }
	OutputDebugString("new devs:");
	for (i = 0; i < IOWI_MAX_DEVICES; i++)
	 {
	  CurrDev = &NewDevices[i];
	  if (CurrDev->Cookie != IOWI_IS_FREE)
	   {
		sprintf(buf, "%u) %s", i + 1, CurrDev->Pipes[IOWKIT2_PIPE_IO_PINS].HidInfo.DevicePath);
		OutputDebugString(buf);
		sprintf(buf, "%u) %s", i + 1, CurrDev->Pipes[IOWKIT2_PIPE_SPECIAL_MODE].HidInfo.DevicePath);
		OutputDebugString(buf);
	   }
	 }
	*/

	// delete devices which are in Devices but not in NewDevices
	for (i = 0; i < IOWI_MAX_DEVICES; i++)
	{
		if (ShMem->Devices[i].Cookie == IOWI_PRESENT)
		{
			CurrDev = &ShMem->Devices[i];
			for (j = 0; j < IOWI_MAX_DEVICES; j++)
			{
				if ((NewDevices[j].Cookie != IOWI_IS_FREE) && (strcmp(CurrDev->Pipes[IOWKIT2_PIPE_IO_PINS].HidInfo.DevicePath, NewDevices[j].Pipes[IOWKIT2_PIPE_IO_PINS].HidInfo.DevicePath) == 0))
				{
					CurrDev = NULL;
					break;
				}
			}

			if (CurrDev != NULL)
			{
				PIOWI_APPLICATION Appl;

				Appl = IowiGetApplicationFromDevice(CurrDev);
				IowiReleaseNamedMutex(DevicesMutex);

				if ((Appl != NULL) && (Appl->DeviceChangeCallback != NULL))
					SendMessage(Appl->MsgWnd, DeviceChangeMessageValue, IOWKIT2_ACTION_REMOVAL, (LPARAM)CurrDev->DevID);

				IowiFreeDevice(CurrDev, TRUE);
				DevicesMutex = IowiAquireNamedMutex(DevicesMutexName);
			}
		}
	}

	// remove zombies
	for (i = 0; i < IOWI_MAX_DEVICES; i++)
	{
		CurrDev = &ShMem->Devices[i];
		if ((CurrDev->Cookie == IOWI_NOTPRESENT) && (CurrDev->AppNo == 0))
			IowiFreeDevice(CurrDev, TRUE);
	}

	// delete devices from NewDevices which are in Devices
	for (i = 0; i < IOWI_MAX_DEVICES; i++)
	{
		for (j = 0; j < IOWI_MAX_DEVICES; j++)
		{
			if ((ShMem->Devices[i].Cookie == IOWI_PRESENT) && (NewDevices[j].Cookie != IOWI_IS_FREE) &&
				(strcmp(ShMem->Devices[i].Pipes[IOWKIT2_PIPE_IO_PINS].HidInfo.DevicePath, NewDevices[j].Pipes[IOWKIT2_PIPE_IO_PINS].HidInfo.DevicePath) == 0))
			{
				ShMem->Devices[i].Pipes[IOWKIT2_PIPE_IO_PINS].HidInfo = NewDevices[j].Pipes[IOWKIT2_PIPE_IO_PINS].HidInfo;
				ShMem->Devices[i].Pipes[IOWKIT2_PIPE_SPECIAL_MODE].HidInfo = NewDevices[j].Pipes[IOWKIT2_PIPE_SPECIAL_MODE].HidInfo;
				ShMem->Devices[i].Pipes[IOWKIT2_PIPE_I2C_MODE].HidInfo = NewDevices[j].Pipes[IOWKIT2_PIPE_I2C_MODE].HidInfo;			//IOW28
				ShMem->Devices[i].Pipes[IOWKIT2_PIPE_ADC_MODE].HidInfo = NewDevices[j].Pipes[IOWKIT2_PIPE_ADC_MODE].HidInfo;			//IOW28
				

				IowiFreeDevice(&NewDevices[j], FALSE);
				break;
			}
		}
	}

	// complete initialization of devices in NewDevices and move to Devices
	New = FALSE;
	for (j = 0; j < IOWI_MAX_DEVICES; j++)
	{
		if (NewDevices[j].Cookie != IOWI_IS_FREE)
		{
			for (CurrDev = NULL, i = 0; i < IOWI_MAX_DEVICES; i++)
				if (ShMem->Devices[i].Cookie == IOWI_IS_FREE)
				{
					CurrDev = &ShMem->Devices[i];
					break;
				}
			if (CurrDev != NULL)
			{
				*CurrDev = NewDevices[j];
				CurrDev->NewDev = TRUE;
				CurrDev->DevID = i + 1;
				New = TRUE;
			}
		}
	}

	LocalFree(NewDevices);
	IowiReleaseNamedMutex(DevicesMutex);

	if (New)
		IowiEnumerateNewDevices(NULL);
}

DWORD IowiInitialize(IOWKIT2_DEVICECHANGE_EVENT Event, PVOID Context, ULONG APIVersion)
{
	PIOWI_APPLICATION Appl;

	SetLastError(ERROR_SUCCESS);
	Appl = IowiNewApplication(DLLModule, Event, Context, APIVersion);
	if (Appl == NULL)
		return GetLastError();

	if (APIVersion == 1)
		IowiEnumerate(1);
	else
		PostMessage(Appl->MsgWnd, WM_USER, APIVersion, 0);

	SetLastError(ERROR_SUCCESS);
	return ERROR_SUCCESS;
}

DWORD IOWKIT2_API IowKit2Initialize(IOWKIT2_DEVICECHANGE_EVENT Event, PVOID Context)
{
	DWORD ret;
	PIOWI_APPLICATION Appl;

	Appl = IowiFindApplication();
	if (Appl != NULL)
		ret = ERROR_ALREADY_ASSIGNED;
	else
		ret = IowiInitialize(Event, Context, 2);
	return ret;
}

void IOWKIT2_API IowKit2Finalize(void)
{
	PIOWI_APPLICATION Appl;

	Appl = IowiFindApplication();
	// someone calling Finalize without Initialize
	if (Appl == NULL)
		SetLastError(ERROR_INVALID_FUNCTION);
	else
		if (Appl->InDataCallback || Appl->InDevChangeCallback)
			SetLastError(ERROR_INVALID_FUNCTION);
		else
		{
			SetEvent(Appl->FinalizeEvent);
			IowiDeleteApplication(Appl);
		}
}