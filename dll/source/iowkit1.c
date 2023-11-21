//
// IO-Warrior SDK library
//
#include "stdafx.h"
#include "iowkit.h"
#include "iowkit2.h"
#include "iowdev.h"

IOWKIT_HANDLE iow1Devices[IOWKIT_MAX_DEVICES];
ULONG iow1NumDevices = 0;

void IOWKIT2_API Iowi1Event(ULONG action, IOWKIT2_HANDLE devHandle, PVOID Context)
{
	if ((action == IOWKIT2_ACTION_ARRIVAL) && (iow1NumDevices < IOWKIT_MAX_DEVICES) /* &&
	  (IowiGetProductId(devHandle, 1) != IOWKIT2_PID_IOW56) */)
		if (IowiSetDeviceUse(devHandle, TRUE, 1))
			iow1Devices[iow1NumDevices++] = (IOWKIT_HANDLE)devHandle;
}

IOWKIT_HANDLE IOWKIT_API IowKitOpenDevice(void)
{
	DWORD ret;

	PIOWI_APPLICATION Appl;

	Appl = IowiFindApplication();
	if ((Appl != NULL) && (Appl->UsedAPIVersion == 2))
	{
		SetLastError(ERROR_ALREADY_ASSIGNED);
		return 0;
	}
	else
	{
		IowKitCloseDevice(iow1Devices[0]);
		ret = IowiInitialize(Iowi1Event, 0, 1);
		Appl = IowiFindApplication();
		if (Appl != NULL)
			Appl->DeviceChangeCallback = NULL;
		if (ret != ERROR_SUCCESS)
			IowKitCloseDevice(iow1Devices[0]);

		return iow1Devices[0];
	}
}

void IOWKIT_API IowKitCloseDevice(IOWKIT_HANDLE devHandle)
{
	IowKit2Finalize();
	memset(iow1Devices, 0, sizeof(iow1Devices));
	iow1NumDevices = 0;
}

ULONG IOWKIT_API IowKitWrite(IOWKIT_HANDLE devHandle, ULONG numPipe, PCHAR buffer, ULONG length)
{
	PIOWI_DEVICE iowDev;
	DWORD err;
	ULONG i, n;
	HANDLE DeviceMutex, ApplicationMutex;

	iowDev = IowiAccessMyDevice(devHandle, &DeviceMutex, &ApplicationMutex);
	err = ERROR_SUCCESS;
	n = 0;
	if ((iowDev == NULL) || (iowDev->Cookie != IOWI_PRESENT) ||
		((buffer == NULL) && (length != 0)) || (numPipe >= IOWKIT2_MAX_PIPES))
		err = ERROR_INVALID_PARAMETER;
	else
		n = iowDev->Pipes[numPipe].HidInfo.Caps.OutputReportByteLength;
	IowiReleaseMyDevice(iowDev, DeviceMutex, ApplicationMutex);
	SetLastError(err);
	if (err != ERROR_SUCCESS)
		return 0;

	for (i = 0; i + n <= length; i += n)
		if (IowiWrite((IOWKIT2_HANDLE)devHandle, numPipe, (PIOWKIT2_REPORT)(buffer + i), 1) != n)
			break;
	return i;
}

ULONG IOWKIT_API IowKitRead(IOWKIT_HANDLE devHandle, ULONG numPipe, PCHAR buffer, ULONG length)
{
	PIOWI_DEVICE iowDev;
	IOWKIT2_REPORT report;
	DWORD err;
	ULONG i, n;
	HANDLE DeviceMutex, ApplicationMutex;

	iowDev = IowiAccessMyDevice(devHandle, &DeviceMutex, &ApplicationMutex);
	err = ERROR_SUCCESS;
	n = 0;

	if (iowDev == NULL || (iowDev->Cookie != IOWI_PRESENT) ||
		((buffer == NULL) && (length != 0)) || (numPipe >= IOWKIT2_MAX_PIPES))
		err = ERROR_INVALID_PARAMETER;
	else
		n = iowDev->Pipes[numPipe].HidInfo.Caps.InputReportByteLength;

	IowiReleaseMyDevice(iowDev, DeviceMutex, ApplicationMutex);
	SetLastError(err);

	if (err != ERROR_SUCCESS)
		return 0;

	for (i = 0; i + n <= length; i += n)
	{
		if (IowiRead((IOWKIT2_HANDLE)devHandle, numPipe, (PIOWKIT2_REPORT)&report, 1) == n)
			memcpy(buffer + i, &report, n);
		else
			break;
	}

	return i;
}

int IowiReadImmediate(IOWKIT_HANDLE devHandle, PIOWKIT2_REPORT report, ULONG APIVersion)
{
	PIOWI_DEVICE iowDev;
	PIOWI_APPLICATION Appl;
	IOWKIT2_REPORT rep;
	DWORD err;
	int ret;
	IOWKIT2_DATA_EVENT SaveDataEvent;
	HANDLE DeviceMutex, ApplicationMutex;

	iowDev = IowiAccessMyDevice(devHandle, &DeviceMutex, &ApplicationMutex);
	if ((iowDev == NULL) || (iowDev->Cookie != IOWI_PRESENT) ||
		(IowiGetApplicationFromDevice(iowDev)->UsedAPIVersion != APIVersion) || (report == NULL) ||
		((iowDev->Pipes[IOWKIT2_PIPE_IO_PINS].HidInfo.Attributes.VendorID == IOWKIT2_VENDOR_ID) &&
		(iowDev->Pipes[IOWKIT2_PIPE_IO_PINS].HidInfo.Attributes.ProductID == IOWKIT2_PID_IOW56)))
	{
		err = ERROR_INVALID_PARAMETER;
		ret = -1;
	}
	else
	{
		if ((iowDev->Pipes[IOWKIT2_PIPE_IO_PINS].HidInfo.Attributes.VendorID == IOWKIT2_VENDOR_ID) &&
			(iowDev->Pipes[IOWKIT2_PIPE_IO_PINS].HidInfo.Attributes.ProductID == IOWKIT2_PID_IOW40) &&
			(iowDev->Pipes[IOWKIT2_PIPE_IO_PINS].HidInfo.Attributes.VersionNumber < IOWKIT2_NON_LEGACY_REVISION))
		{
			*report = iowDev->lastReport;
			if (iowDev->readAny)
				ret = iowDev->Pipes[IOWKIT2_PIPE_IO_PINS].HidInfo.Caps.InputReportByteLength;
			else
				ret = 0;
			err = ERROR_SUCCESS;
		}
		else
		{
			err = ERROR_READ_FAULT;
			ret = 0;
			memset(&rep, 0, sizeof(rep));
			rep.ReportID = 0xFF;
			Appl = IowiGetApplicationFromDevice(iowDev);
			SaveDataEvent = Appl->DataCallbacks[IOWKIT2_PIPE_SPECIAL_MODE].DataCallback;
			Appl->DataCallbacks[IOWKIT2_PIPE_SPECIAL_MODE].DataCallback = NULL;
			if (IowiWrite((IOWKIT2_HANDLE)devHandle, IOWKIT2_PIPE_SPECIAL_MODE, &rep, APIVersion) > 0)
				if (IowiReadUnbuffered((IOWKIT2_HANDLE)devHandle, IOWKIT2_PIPE_SPECIAL_MODE, &rep, APIVersion) > 0)
					if (rep.ReportID == 0xFF)
					{
						rep.ReportID = 0;
						err = ERROR_SUCCESS;
						ret = iowDev->Pipes[IOWKIT2_PIPE_IO_PINS].HidInfo.Caps.InputReportByteLength;
					}
			if (ret > 0)
			{
				*report = rep;
				iowDev->lastReport = rep;
			}
			else
				*report = iowDev->lastReport;
			Appl->DataCallbacks[IOWKIT2_PIPE_SPECIAL_MODE].DataCallback = SaveDataEvent;
		}
	}
	IowiReleaseMyDevice(iowDev, DeviceMutex, ApplicationMutex);
	SetLastError(err);
	return ret;
}

BOOL IOWKIT_API IowKitReadImmediate(IOWKIT_HANDLE devHandle, PDWORD value)
{
	IOWKIT2_REPORT report;
	BOOL ret;

	ret = IowiReadImmediate(devHandle, &report, 1) > 0;
	if (ret)
		memcpy(value, report.Bytes, sizeof(DWORD));
	return ret;
};

ULONG IOWKIT_API IowKitReadNonBlocking(IOWKIT_HANDLE devHandle, ULONG numPipe,
	PCHAR buffer, ULONG length)
{
	IOWKIT2_REPORT report;
	ULONG ret;
	int bret;
	PIOWI_DEVICE iowDev;
	HANDLE DeviceMutex, ApplicationMutex;

	// limit length to multiples of reports
	iowDev = IowiAccessMyDevice(devHandle, &DeviceMutex, &ApplicationMutex);
	length -= length % iowDev->Pipes[numPipe].HidInfo.Caps.InputReportByteLength;
	IowiReleaseMyDevice(iowDev, DeviceMutex, ApplicationMutex);

	memset(&report, 0, sizeof(report));
	for (ret = 0; ret < length; ret += (ULONG)bret, buffer += bret)
	{
		bret = IowiReadNonBlocking((IOWKIT2_HANDLE)devHandle, numPipe, &report, 1);
		if (bret > 0)
			memcpy(buffer, &report, bret);
		else
			break;
	}
	return ret;
}

ULONG IOWKIT_API IowKitGetNumDevs(void)
{
	return iow1NumDevices;
}

IOWKIT_HANDLE IOWKIT_API IowKitGetDeviceHandle(ULONG numDevice)
{
	PIOWI_APPLICATION Appl;

	Appl = IowiFindApplication();
	if (((Appl != NULL) && (Appl->UsedAPIVersion != 1)) ||
		(numDevice < 1) || (numDevice > iow1NumDevices))
	{
		SetLastError(ERROR_INVALID_PARAMETER);
		return 0;
	}
	else
	{
		SetLastError(ERROR_SUCCESS);
		return iow1Devices[numDevice - 1];
	}
}

static ULONG iowLegacyOpenMode = IOW_OPEN_SIMPLE;

BOOL IOWKIT_API IowKitSetLegacyOpenMode(ULONG legacyOpenMode)
{
	if ((legacyOpenMode == IOW_OPEN_SIMPLE) || (legacyOpenMode == IOW_OPEN_COMPLEX))
	{
		SetLastError(ERROR_SUCCESS);
		iowLegacyOpenMode = legacyOpenMode;
		return TRUE;
	}
	else
	{
		SetLastError(ERROR_INVALID_PARAMETER);
		return FALSE;
	}
}

ULONG IOWKIT_API IowKitGetProductId(IOWKIT_HANDLE devHandle)
{
	return IowiGetProductId((IOWKIT2_HANDLE)devHandle, 1);
}

ULONG IOWKIT_API IowKitGetRevision(IOWKIT_HANDLE devHandle)
{
	return IowiGetRevision((IOWKIT2_HANDLE)devHandle, 1);
}

HANDLE IOWKIT_API IowKitGetThreadHandle(IOWKIT_HANDLE devHandle)
{
	return IowiGetThreadHandle((IOWKIT2_HANDLE)devHandle, IOWKIT2_PIPE_IO_PINS, 1);
}

BOOL IOWKIT_API IowKitGetSerialNumber(IOWKIT_HANDLE devHandle, PWCHAR serialNumber)
{
	PIOWI_DEVICE iowDev;
	BOOL ret;
	HANDLE DeviceMutex, ApplicationMutex;

	iowDev = IowiAccessMyDevice(devHandle, &DeviceMutex, &ApplicationMutex);
	if ((iowDev == NULL) || (serialNumber == NULL) || (IowiGetApplicationFromDevice(iowDev)->UsedAPIVersion != 1))
	{
		SetLastError(ERROR_INVALID_PARAMETER);
		ret = FALSE;
	}
	else
	{
		memcpy(serialNumber, iowDev->SerialNumber, sizeof(iowDev->SerialNumber));
		SetLastError(ERROR_SUCCESS);
		ret = (serialNumber[0] != 0);
	}
	IowiReleaseMyDevice(iowDev, DeviceMutex, ApplicationMutex);
	return ret;
}

BOOL IOWKIT_API IowKitSetTimeout(IOWKIT_HANDLE devHandle, ULONG timeout)
{
	return IowiSetTimeout((IOWKIT2_HANDLE)devHandle, timeout, 1);
}

BOOL IOWKIT_API IowKitSetWriteTimeout(IOWKIT_HANDLE devHandle, ULONG timeout)
{
	return IowiSetWriteTimeout((IOWKIT2_HANDLE)devHandle, timeout, 1);
}

BOOL IOWKIT_API IowKitCancelIo(IOWKIT_HANDLE devHandle, ULONG numPipe)
{
	PIOWI_DEVICE iowDev;
	BOOL ret1, ret2;
	HANDLE DeviceMutex, ApplicationMutex;

	iowDev = IowiAccessMyDevice(devHandle, &DeviceMutex, &ApplicationMutex);
	if ((iowDev == NULL) || (iowDev->Cookie != IOWI_PRESENT) ||
		(numPipe >= IOWKIT2_MAX_PIPES))
	{
		SetLastError(ERROR_INVALID_PARAMETER);
		ret1 = FALSE;
	}
	else
	{ 
		HANDLE Mutex;

		Mutex = IowiAquireNamedMutex(iowDev->Pipes[numPipe].cancelMutexName);
		ret1 = IowiCancelIo(iowDev->Pipes[numPipe].ReadHandle);
		ret2 = IowiCancelIo(iowDev->Pipes[numPipe].WriteHandle);
		ret1 &= ret2;
		IowiReleaseNamedMutex(Mutex);
	}
	IowiReleaseMyDevice(iowDev, DeviceMutex, ApplicationMutex);
	return ret1;
}

static const char Kit1Version[] = "IO-Warrior Kit V1.7.0.2";

PCSTR IOWKIT_API IowKitVersion(void)
{
	SetLastError(ERROR_SUCCESS);
	return Kit1Version;
}