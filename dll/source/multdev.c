//
// multdev.cpp
// IO-Warrior SDK library
//
// multiple devices support functions
//

#include "stdafx.h"
#include "iowkit2.h"
#include "iowdev.h"

static const char Kit2Version[] = "IO-Warrior Kit V2.0 beta";

PCSTR IOWKIT2_API IowKit2Version(void)
{
	SetLastError(ERROR_SUCCESS);
	return Kit2Version;
}

HANDLE IowiGetThreadHandle(IOWKIT2_HANDLE devHandle, ULONG numPipe, ULONG APIVersion)
{
	PIOWI_DEVICE iowDev;
	HANDLE ret;
	HANDLE DeviceMutex, ApplicationMutex;

	iowDev = IowiAccessMyDevice(devHandle, &DeviceMutex, &ApplicationMutex);
	if (iowDev == NULL || (numPipe >= IOWKIT2_MAX_PIPES) || (IowiGetApplicationFromDevice(iowDev)->UsedAPIVersion != APIVersion))
	{
		SetLastError(ERROR_INVALID_PARAMETER);
		ret = NULL;
	}
	else
	{
		SetLastError(ERROR_SUCCESS);
		ret = iowDev->Pipes[numPipe].ioThread;
	}
	IowiReleaseMyDevice(iowDev, DeviceMutex, ApplicationMutex);
	return ret;
}

HANDLE IOWKIT2_API IowKit2GetThreadHandle(IOWKIT2_HANDLE devHandle, ULONG numPipe)
{
	return IowiGetThreadHandle(devHandle, numPipe, 2);
}

ULONG IowiGetProductId(IOWKIT2_HANDLE devHandle, ULONG APIVersion)
{
	PIOWI_DEVICE iowDev;
	ULONG ret;
	HANDLE DeviceMutex, ApplicationMutex;

	iowDev = IowiAccessMyDevice(devHandle, &DeviceMutex, &ApplicationMutex);
	if ((iowDev == NULL) || (IowiGetApplicationFromDevice(iowDev)->UsedAPIVersion != APIVersion))
	{
		SetLastError(ERROR_INVALID_PARAMETER);
		ret = 0;
	}
	else
	{
		SetLastError(ERROR_SUCCESS);
		// both device parts have the same HID Attributes
		ret = (ULONG)iowDev->Pipes[IOWKIT2_PIPE_IO_PINS].HidInfo.Attributes.ProductID;
	}
	IowiReleaseMyDevice(iowDev, DeviceMutex, ApplicationMutex);
	return ret;
}

ULONG IOWKIT2_API IowKit2GetProductId(IOWKIT2_HANDLE devHandle)
{
	ULONG ret;

	ret = IowiGetProductId(devHandle, 2);
	return ret;
}

ULONG IowiGetRevision(IOWKIT2_HANDLE devHandle, ULONG APIVersion)
{
	PIOWI_DEVICE iowDev;
	ULONG ret;
	HANDLE DeviceMutex, ApplicationMutex;

	iowDev = IowiAccessMyDevice(devHandle, &DeviceMutex, &ApplicationMutex);
	if ((iowDev == NULL) || (IowiGetApplicationFromDevice(iowDev)->UsedAPIVersion != APIVersion))
	{
		SetLastError(ERROR_INVALID_PARAMETER);
		ret = 0;
	}
	else
	{
		SetLastError(ERROR_SUCCESS);
		// both device parts have the same HID Attributes
		ret = (ULONG)iowDev->Pipes[IOWKIT2_PIPE_IO_PINS].HidInfo.Attributes.VersionNumber;
	}
	IowiReleaseMyDevice(iowDev, DeviceMutex, ApplicationMutex);
	return ret;
}

ULONG IOWKIT2_API IowKit2GetRevision(IOWKIT2_HANDLE devHandle)
{
	return IowiGetRevision(devHandle, 2);
}

ULONG IOWKIT2_API IowKit2GetSerialNumber(IOWKIT2_HANDLE devHandle)
{
	PIOWI_DEVICE iowDev;
	ULONG ret;
	HANDLE DeviceMutex, ApplicationMutex;

	iowDev = IowiAccessMyDevice(devHandle, &DeviceMutex, &ApplicationMutex);
	if ((iowDev == NULL) || (IowiGetApplicationFromDevice(iowDev)->UsedAPIVersion != 2))
	{
		SetLastError(ERROR_INVALID_PARAMETER);
		ret = 0;
	}
	else
	{
		char buf[sizeof(iowDev->SerialNumber)];
		int i;

		ret = 0;
		memset(buf, 0, sizeof(buf));
		for (i = 0; i < sizeof(buf); i++)
			buf[i] = (char)iowDev->SerialNumber[i];
		if (buf[0] != '\0')
			sscanf(buf, "%x", &ret);
		SetLastError(ERROR_SUCCESS);
	}
	IowiReleaseMyDevice(iowDev, DeviceMutex, ApplicationMutex);
	return ret;
}

BOOL IowiSetTimeout(IOWKIT2_HANDLE devHandle, ULONG timeout, ULONG APIVersion)
{
	PIOWI_DEVICE iowDev;
	BOOL ret;
	HANDLE DeviceMutex, ApplicationMutex;

	iowDev = IowiAccessMyDevice(devHandle, &DeviceMutex, &ApplicationMutex);
	if ((iowDev == NULL) || (IowiGetApplicationFromDevice(iowDev)->UsedAPIVersion != APIVersion))
	{
		SetLastError(ERROR_INVALID_PARAMETER);
		ret = FALSE;
	}
	else
	{
		SetLastError(ERROR_SUCCESS);
		iowDev->ioTimeout = timeout;
		ret = TRUE;
	}
	IowiReleaseMyDevice(iowDev, DeviceMutex, ApplicationMutex);
	return ret;
}

BOOL IOWKIT2_API IowKit2SetTimeout(IOWKIT2_HANDLE devHandle, ULONG timeout)
{
	return IowiSetTimeout(devHandle, timeout, 2);
}

BOOL IowiSetWriteTimeout(IOWKIT2_HANDLE devHandle, ULONG timeout, ULONG APIVersion)
{
	PIOWI_DEVICE iowDev;
	BOOL ret;
	HANDLE DeviceMutex, ApplicationMutex;

	iowDev = IowiAccessMyDevice(devHandle, &DeviceMutex, &ApplicationMutex);
	if ((iowDev == NULL) || (IowiGetApplicationFromDevice(iowDev)->UsedAPIVersion != APIVersion))
	{
		SetLastError(ERROR_INVALID_PARAMETER);
		ret = FALSE;
	}
	else
	{
		SetLastError(ERROR_SUCCESS);
		iowDev->ioWriteTimeout = timeout;
		ret = TRUE;
	}
	IowiReleaseMyDevice(iowDev, DeviceMutex, ApplicationMutex);
	return ret;
}

BOOL IOWKIT2_API IowKit2SetWriteTimeout(IOWKIT2_HANDLE devHandle, ULONG timeout)
{
	return IowiSetWriteTimeout(devHandle, timeout, 2);
}

ULONG IOWKIT2_API IowKit2GetNumDevs(void)
{
	ULONG i;
	ULONG ret;
	PIOWI_DEVICE Dev;
	PIOWI_APPLICATION Appl;
	HANDLE DevicesMutex;

	Appl = IowiFindApplication();
	DevicesMutex = IowiAquireNamedMutex(DevicesMutexName);
	for (ret = 0, i = 0; i < IOWI_MAX_DEVICES; i++)
	{
		Dev = &ShMem->Devices[i];
		// count unused devices and devices assigned to this application
		ret += (Dev->Cookie == IOWI_PRESENT) && ((Dev->AppNo == 0) || (IowiGetApplicationFromDevice(Dev) == Appl));
	}
	IowiReleaseNamedMutex(DevicesMutex);
	return ret;
}

void IOWKIT2_API IowKit2Enumerate(void)
{
	PIOWI_APPLICATION Appl;
	PIOWI_DEVICE Dev;
	ULONG i;
	HANDLE DevicesMutex;

	Appl = IowiFindApplication();
	if (Appl != NULL)
	{
		if (Appl->InDataCallback || Appl->InDevChangeCallback)
			SetLastError(ERROR_INVALID_FUNCTION);
		else
		{
			DevicesMutex = IowiAquireNamedMutex(DevicesMutexName);
			for (i = 0; i < IOWI_MAX_DEVICES; i++)
			{
				Dev = &ShMem->Devices[i];
				if ((Dev->Cookie == IOWI_PRESENT) && (Dev->AppNo == 0) && (Appl->DeviceChangeCallback != NULL))
				{
					Dev->AppNo = IowiGetApplicationID(Appl);
					IowiReleaseNamedMutex(DevicesMutex);
					SendMessage(Appl->MsgWnd, DeviceChangeMessageValue, IOWKIT2_ACTION_ARRIVAL, (LPARAM)Dev->DevID);
					DevicesMutex = IowiAquireNamedMutex(DevicesMutexName);
					if (!Dev->InUse)
						Dev->AppNo = 0;
				}
			}
			IowiReleaseNamedMutex(DevicesMutex);
			SetLastError(ERROR_SUCCESS);
		}
	}
	else
		SetLastError(ERROR_INVALID_PARAMETER);
}

BOOL IOWKIT2_API IowKit2GetDeviceUse(IOWKIT2_HANDLE devHandle)
{
	PIOWI_DEVICE iowDev;
	BOOL ret;
	HANDLE DeviceMutex, ApplicationMutex;

	iowDev = IowiAccessMyDevice(devHandle, &DeviceMutex, &ApplicationMutex);
	if ((iowDev != NULL) && (IowiGetApplicationFromDevice(iowDev)->UsedAPIVersion != 2))
	{
		ret = FALSE;
		SetLastError(ERROR_INVALID_PARAMETER);
	}
	else
	{
		ret = iowDev != NULL;
		SetLastError(ERROR_SUCCESS);
	}
	IowiReleaseMyDevice(iowDev, DeviceMutex, ApplicationMutex);
	return ret;
}

BOOL IowiSetDeviceUse(IOWKIT2_HANDLE devHandle, BOOL Use, ULONG APIVersion)
{
	PIOWI_DEVICE iowDev;
	PIOWI_APPLICATION Appl;
	BOOL ret;
	HANDLE DeviceMutex, ApplicationMutex;

	iowDev = IowiAccessMyDevice(devHandle, &DeviceMutex, &ApplicationMutex);
	if ((iowDev == NULL) || ((iowDev->Cookie == IOWI_NOTPRESENT) && Use))
	{
		SetLastError(ERROR_INVALID_PARAMETER);
		ret = FALSE;
	}
	else
	{
		if (Use)
		{
			ret = IowiStartDevice(iowDev);
			if (ret)
				SetLastError(ERROR_SUCCESS);
			else
				SetLastError(ERROR_INVALID_FUNCTION);
			iowDev->InUse = ret;
		}
		else
		{
			IowiStopDevice(iowDev, TRUE);
			Appl = IowiGetApplicationFromDevice(iowDev);
			iowDev->AppNo = 0;
			iowDev->InUse = FALSE;
			iowDev->NewDev = TRUE;
			IowiReleaseMyDevice(iowDev, DeviceMutex, ApplicationMutex);
			if (!Appl->InDevChangeCallback && (iowDev->Cookie == IOWI_PRESENT))
				IowiEnumerateNewDevices(Appl);
			SetLastError(ERROR_SUCCESS);
			return TRUE;
		}
	}
	IowiReleaseMyDevice(iowDev, DeviceMutex, ApplicationMutex);
	return ret;
}

BOOL IOWKIT2_API IowKit2SetDeviceUse(IOWKIT2_HANDLE devHandle, BOOL Use)
{
	BOOL ret;

	ret = IowiSetDeviceUse(devHandle, Use, 2);
	return ret;
}

BOOL IOWKIT2_API IowKit2IsConnected(IOWKIT2_HANDLE devHandle)
{
	PIOWI_DEVICE iowDev;
	BOOL ret;
	HANDLE DeviceMutex, ApplicationMutex;

	iowDev = IowiAccessMyDevice(devHandle, &DeviceMutex, &ApplicationMutex);
	if (iowDev == NULL || (IowiGetApplicationFromDevice(iowDev)->UsedAPIVersion != 2))
	{
		SetLastError(ERROR_INVALID_PARAMETER);
		ret = FALSE;
	}
	else
	{
		ret = iowDev->Cookie == IOWI_PRESENT;
		SetLastError(ERROR_SUCCESS);
	}
	IowiReleaseMyDevice(iowDev, DeviceMutex, ApplicationMutex);
	return ret;
}