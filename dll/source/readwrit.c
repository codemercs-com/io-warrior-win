//
// readwrit.cpp
//
// IO-Warrior SDK library
// Read & write functions
//
#include "stdafx.h"
#include "iowkit2.h"
#include "iowdev.h"

// Internal IOW-Kit functions

BOOL IowiCancelIo(HANDLE hFile)
{
	HMODULE hKernel;
	BOOL(__stdcall *pCancelIo)(HANDLE hFile);

	hKernel = GetModuleHandle("kernel32.dll");
	if (hKernel == NULL)
		return FALSE;
	pCancelIo = (BOOL(__stdcall *)(HANDLE)) GetProcAddress(hKernel, "CancelIo");
	if (pCancelIo == NULL)
		return FALSE;

	(*pCancelIo)(hFile);

	return TRUE;
}

void __stdcall IowiDummyCompletion(DWORD errorCode, DWORD numBytes, OVERLAPPED *ovlp)
{
}

void __stdcall IowiWriteCompletion(DWORD errorCode, DWORD numBytes, OVERLAPPED *ovlp)
{
	BOOL rc;
	ULONG numWritten;
	PIOWI_WRITE pwriteInfo;

	pwriteInfo = (PIOWI_WRITE)ovlp->hEvent;
	// Get overlapped I/O result
	rc = GetOverlappedResult(pwriteInfo->writeHandle, ovlp, &numWritten, FALSE);
	// We had some I/O error, IowKit2Write() needs to repeat write
	pwriteInfo->writeOk = !((errorCode != 0) || (numBytes == 0));
}

ULONG IowiWrite(IOWKIT2_HANDLE devHandle, ULONG numPipe, PIOWKIT2_REPORT report, ULONG APIVersion)
{
	PIOWI_DEVICE iowDev;
	static IOWI_WRITE writeInfo;
	ULONG rc;
	ULONG ret;
	BOOL bOK;
	HANDLE DeviceMutex, ApplicationMutex;

	ret = 0;
	iowDev = IowiAccessMyDevice(devHandle, &DeviceMutex, &ApplicationMutex);
	if ((iowDev == NULL) || (iowDev->Cookie != IOWI_PRESENT) ||
		(IowiGetApplicationFromDevice(iowDev)->UsedAPIVersion != APIVersion) ||
		(report == NULL) || (numPipe >= IOWKIT2_MAX_PIPES) || !iowDev->InUse)
		SetLastError(ERROR_INVALID_PARAMETER);
	else
	{
		// Zero overlapped structure
		memset(&writeInfo, 0, sizeof(IOWI_WRITE));
		// Get pipe handle
		writeInfo.writeHandle = iowDev->Pipes[numPipe].WriteHandle;
		// Pipe doesn't exist, fail
		if (writeInfo.writeHandle == INVALID_HANDLE_VALUE)
			SetLastError(ERROR_INVALID_PARAMETER);
		else
		{
			// Save for IowWriteCompletion()
			writeInfo.ovlpWrite.hEvent = &writeInfo;
			// Perform async write waiting for results
			bOK = WriteFileEx(writeInfo.writeHandle, report, iowDev->Pipes[numPipe].HidInfo.Caps.OutputReportByteLength,
				&writeInfo.ovlpWrite, &IowiWriteCompletion);
			// Check for error
			if (!bOK && (GetLastError() != ERROR_IO_PENDING))
				SetLastError(ERROR_INVALID_PARAMETER);
			else
			{
				ULONG timeout;

				timeout = iowDev->ioWriteTimeout;
				IowiReleaseMyDevice(iowDev, DeviceMutex, ApplicationMutex);
				rc = SleepEx(timeout, TRUE);
				iowDev = IowiAccessMyDevice(devHandle, &DeviceMutex, &ApplicationMutex);
				if (iowDev != NULL)
				{
					// TODO: perform more strict checks
					if (rc == WAIT_IO_COMPLETION)
					{
						// Was anything written?
						if (writeInfo.writeOk)
						{
							// Return number of bytes written
							ret = iowDev->Pipes[numPipe].HidInfo.Caps.OutputReportByteLength;
							SetLastError(ERROR_SUCCESS);
						}
					}
					else
					{
						IowiCancelIo(writeInfo.writeHandle);
						// We failed with timeout, set error
						SetLastError(ERROR_TIMEOUT);
					}
				}
				else
					SetLastError(ERROR_TIMEOUT);
			}
		}
	}
	IowiReleaseMyDevice(iowDev, DeviceMutex, ApplicationMutex);
	return ret;
}

ULONG IOWKIT2_API IowKit2Write(IOWKIT2_HANDLE devHandle, ULONG numPipe, PIOWKIT2_REPORT report)
{
	ULONG ret;

	ret = IowiWrite(devHandle, numPipe, report, 2);
	return ret;
}

int IowiPendingReports(IOWKIT2_HANDLE devHandle, ULONG numPipe, ULONG APIVersion)
{
	PIOWI_DEVICE iowDev;
	int ret;
	HANDLE DeviceMutex, ApplicationMutex;

	iowDev = IowiAccessMyDevice(devHandle, &DeviceMutex, &ApplicationMutex);
	if ((iowDev == NULL) || (numPipe >= IOWKIT2_MAX_PIPES) ||
		(IowiGetApplicationFromDevice(iowDev)->UsedAPIVersion != APIVersion))
	{
		ret = -1;
		SetLastError(ERROR_INVALID_PARAMETER);
	}
	else
	{
		HANDLE Mutex;

		Mutex = IowiAquireNamedMutex(iowDev->Pipes[numPipe].bufMutexName);
		ret = (int)iowDev->Pipes[numPipe].numBuf;
		IowiReleaseNamedMutex(Mutex);
		SetLastError(ERROR_SUCCESS);
	}
	IowiReleaseMyDevice(iowDev, DeviceMutex, ApplicationMutex);
	return ret;
}

int IOWKIT2_API IowKit2PendingReports(IOWKIT2_HANDLE devHandle, ULONG numPipe)
{
	return IowiPendingReports(devHandle, numPipe, 2);
}

BOOL IowiInsertBuffer(PIOWI_DEVICE iowDev, ULONG numPipe, IOWKIT2_REPORT *report, DWORD size)
{
	BOOL Ret;
	HANDLE Mutex;
	PIOWI_DEVICE_PIPE Pipe;

	Pipe = &iowDev->Pipes[numPipe];
	// lock data
	Mutex = IowiAquireNamedMutex(Pipe->bufMutexName);

	// Check if buffer is overflowing
	Ret = Pipe->numBuf != IOWI_NUM_BUFFERS;
	// Insert value at the end of queue
	memset(&Pipe->Queue[Pipe->bufEnd], 0, IOWKIT2_REPORT_SIZE);
	memcpy(&Pipe->Queue[Pipe->bufEnd], report, size);
	if (Ret)
		Pipe->numBuf++;
	else
		Pipe->bufStart = (Pipe->bufStart + 1) % IOWI_NUM_BUFFERS;
	// Set new buffer end position
	Pipe->bufEnd = (Pipe->bufEnd + 1) % IOWI_NUM_BUFFERS;
	IowiReleaseNamedMutex(Mutex);
	SetEvent(Pipe->insertEvent);
	return Ret;
}

BOOL IowiGetBuffer(PIOWI_DEVICE iowDev, ULONG numPipe, PIOWKIT2_REPORT report)
{
	BOOL Ret;
	HANDLE Mutex;
	PIOWI_DEVICE_PIPE Pipe;

	if (iowDev == NULL)
		return FALSE;

	Pipe = &iowDev->Pipes[numPipe];
	// Acquire mutex and get value from buffer
	Mutex = IowiAquireNamedMutex(Pipe->bufMutexName);
	Ret = Pipe->numBuf != 0;
	if (Ret)
	{
		// Copy buffered value
		*report = Pipe->Queue[Pipe->bufStart];
		// Set new buffer start
		Pipe->bufStart = (Pipe->bufStart + 1) % IOWI_NUM_BUFFERS;
		// Decrement number of buffered values
		Pipe->numBuf--;
		// Reset start & end positions
		if (Pipe->numBuf == 0)
			Pipe->bufStart = Pipe->bufEnd = 0;
	}
	IowiReleaseNamedMutex(Mutex);
	if (!Ret)
		ResetEvent(Pipe->insertEvent);
	return Ret;
}

BOOL IowiGetLastBuffer(PIOWI_DEVICE iowDev, ULONG numPipe, PIOWKIT2_REPORT preport)
{
	BOOL Ret;
	HANDLE Mutex;
	PIOWI_DEVICE_PIPE Pipe;

	if (iowDev == NULL)
		return FALSE;

	Pipe = &iowDev->Pipes[numPipe];
	// Acquire mutex and get value from buffer
	Mutex = IowiAquireNamedMutex(Pipe->bufMutexName);
	Ret = Pipe->numBuf != 0;
	if (Ret)
	{
		// Set new buffer end
		if (Pipe->bufEnd > 0)
			Pipe->bufEnd--;
		else
			Pipe->bufEnd = IOWI_NUM_BUFFERS - 1;
		// Copy buffered value
		*preport = Pipe->Queue[Pipe->bufEnd];
		// Decrement number of buffered values
		Pipe->numBuf--;
		// Reset start & end positions
		if (Pipe->numBuf == 0)
			Pipe->bufStart = Pipe->bufEnd = 0;
	}
	IowiReleaseNamedMutex(Mutex);
	if (!Ret)
		ResetEvent(Pipe->insertEvent);
	return Ret;
}

int IowiFlush(PIOWI_DEVICE iowDev, ULONG numPipe)
{
	int Ret;
	HANDLE Mutex;
	PIOWI_DEVICE_PIPE Pipe;

	Pipe = &iowDev->Pipes[numPipe];
	Mutex = IowiAquireNamedMutex(Pipe->bufMutexName);
	Ret = (int)Pipe->numBuf;
	Pipe->bufStart = 0;
	Pipe->bufEnd = 0;
	Pipe->numBuf = 0;
	IowiReleaseNamedMutex(Mutex);
	ResetEvent(Pipe->insertEvent);
	return Ret;
}

int IOWKIT2_API IowKit2Flush(IOWKIT2_HANDLE devHandle, ULONG numPipe)
{
	PIOWI_DEVICE iowDev;
	int ret;
	HANDLE DeviceMutex, ApplicationMutex;

	iowDev = IowiAccessMyDevice(devHandle, &DeviceMutex, &ApplicationMutex);
	if ((iowDev == NULL) || (numPipe >= IOWKIT2_MAX_PIPES))
	{
		ret = -1;
		SetLastError(ERROR_INVALID_PARAMETER);
	}
	else
	{
		IowiFlush(iowDev, numPipe);
		SetLastError(ERROR_SUCCESS);
	}
	IowiReleaseMyDevice(iowDev, DeviceMutex, ApplicationMutex);
	return ret;
}

BOOL IOWKIT2_API IowKit2Register(IOWKIT2_HANDLE devHandle, ULONG numPipe, IOWKIT2_DATA_EVENT Event, PVOID Context)
{
	PIOWI_DEVICE iowDev;
	PIOWI_APPLICATION Appl;
	BOOL ret;
	HANDLE DeviceMutex, ApplicationMutex;

	iowDev = IowiAccessMyDevice(devHandle, &DeviceMutex, &ApplicationMutex);
	Appl = IowiGetApplicationFromDevice(iowDev);
	if ((iowDev == NULL) || (iowDev->Cookie != IOWI_PRESENT) ||
		(numPipe >= IOWKIT2_MAX_PIPES) || (Appl == NULL) || (Appl->UsedAPIVersion != 2))
	{
		SetLastError(ERROR_INVALID_PARAMETER);
		ret = FALSE;
	}
	else
	{
		HANDLE Mutex;

		Mutex = IowiAquireNamedMutex(iowDev->Pipes[numPipe].msgMutexName);
		Appl->DataCallbacks[numPipe].DataCallback = Event;
		Appl->DataCallbacks[numPipe].DataContext = Context;
		IowiReleaseNamedMutex(Mutex);
		SetLastError(ERROR_SUCCESS);
	}
	IowiReleaseMyDevice(iowDev, DeviceMutex, ApplicationMutex);
	return ret;
}

static BOOL IowiReadReport(PIOWI_DEVICE iowDev, ULONG numPipe, PIOWKIT2_REPORT preport,	PHANDLE DeviceMutex, PHANDLE ApplicationMutex)
{
	BOOL ret;

	ret = IowiGetBuffer(iowDev, numPipe, preport);
	if (!ret)
	{
		if ((iowDev->Cookie == IOWI_PRESENT) && iowDev->Pipes[numPipe].ioThread != NULL)
		{
			DWORD rc;
			HANDLE Waiters[4];

			// Synchronize with thread
			Waiters[0] = iowDev->Pipes[numPipe].insertEvent;
			Waiters[1] = iowDev->Pipes[numPipe].readFailedEvent;
			Waiters[2] = iowDev->Pipes[numPipe].threadTermEvent;
			Waiters[3] = IowiGetApplicationFromDevice(iowDev)->FinalizeEvent;
			ResetEvent(iowDev->Pipes[numPipe].readFailedEvent);
			IowiReleaseMyDevice(iowDev, *DeviceMutex, *ApplicationMutex);
			rc = WaitForMultipleObjects(4, Waiters, FALSE, iowDev->ioTimeout);

			if (rc == WAIT_OBJECT_0 + 3)
				return FALSE;

			iowDev = IowiAccessMyDevice((IOWKIT2_HANDLE)iowDev, DeviceMutex, ApplicationMutex);

			if (iowDev != NULL)
			{
				if (rc == WAIT_OBJECT_0)
					ret = IowiGetBuffer(iowDev, numPipe, preport);
			}
		}
	}
	return ret;
}

int IowiRead(IOWKIT2_HANDLE devHandle, ULONG numPipe, PIOWKIT2_REPORT report, ULONG APIVersion)
{
	PIOWI_DEVICE iowDev;
	ULONG len, n;
	DWORD err;
	HANDLE DeviceMutex, ApplicationMutex;
	PIOWI_APPLICATION Appl;

	len = 0;
	err = ERROR_SUCCESS;
	iowDev = IowiAccessMyDevice(devHandle, &DeviceMutex, &ApplicationMutex);
	Appl = IowiGetApplicationFromDevice(iowDev);

	if (iowDev == NULL || (report == NULL) || (numPipe >= IOWKIT2_MAX_PIPES) ||
		Appl->InDataCallback || (Appl->UsedAPIVersion != APIVersion) || !iowDev->InUse)
		err = ERROR_INVALID_PARAMETER;
	else
	{
		if (iowDev != NULL)
		{
			HANDLE Mutex;

			Mutex = IowiAquireNamedMutex(iowDev->Pipes[numPipe].readMutexName);
			n = (ULONG)iowDev->Pipes[numPipe].HidInfo.Caps.InputReportByteLength;

			if (IowiReadReport(iowDev, numPipe, report, &DeviceMutex, &ApplicationMutex))
				len = n;
			else
				err = ERROR_TIMEOUT;
			IowiReleaseNamedMutex(Mutex);
		}
		else
			err = ERROR_TIMEOUT;
	}

	IowiReleaseMyDevice(iowDev, DeviceMutex, ApplicationMutex);
	SetLastError(err);
	return (int)len;
}

static BOOL IowiReadReportUnbuffered(PIOWI_DEVICE iowDev, ULONG numPipe, PIOWKIT2_REPORT preport,
	PHANDLE DeviceMutex, PHANDLE ApplicationMutex)
{
	BOOL ret;

	if ((iowDev->Cookie == IOWI_PRESENT) && iowDev->Pipes[numPipe].ioThread != NULL)
	{
		DWORD rc;
		HANDLE Waiters[4];

		// Synchronize with thread
		ResetEvent(iowDev->Pipes[numPipe].insertEvent);
		Waiters[0] = iowDev->Pipes[numPipe].insertEvent;
		Waiters[1] = iowDev->Pipes[numPipe].readFailedEvent;
		Waiters[2] = iowDev->Pipes[numPipe].threadTermEvent;
		Waiters[3] = IowiGetApplicationFromDevice(iowDev)->FinalizeEvent;
		ResetEvent(iowDev->Pipes[numPipe].readFailedEvent);
		IowiReleaseMyDevice(iowDev, *DeviceMutex, *ApplicationMutex);
		rc = WaitForMultipleObjects(4, Waiters, FALSE, iowDev->ioTimeout);
		if (rc == WAIT_OBJECT_0 + 3)
			return FALSE;
		iowDev = IowiAccessMyDevice((IOWKIT2_HANDLE)iowDev, DeviceMutex, ApplicationMutex);
		if (iowDev != NULL)
		{
			if (rc == WAIT_OBJECT_0)
				ret = IowiGetLastBuffer(iowDev, numPipe, preport);
		}
	}
	return ret;
}

int IowiReadUnbuffered(IOWKIT2_HANDLE devHandle, ULONG numPipe, PIOWKIT2_REPORT report, ULONG APIVersion)
{
	PIOWI_DEVICE iowDev;
	ULONG len, n;
	DWORD err;
	HANDLE DeviceMutex, ApplicationMutex;
	PIOWI_APPLICATION Appl;

	len = 0;
	err = ERROR_SUCCESS;
	iowDev = IowiAccessMyDevice(devHandle, &DeviceMutex, &ApplicationMutex);
	Appl = IowiGetApplicationFromDevice(iowDev);
	if (iowDev == NULL || (report == NULL) || (numPipe >= IOWKIT2_MAX_PIPES) ||
		Appl->InDataCallback || (Appl->UsedAPIVersion != APIVersion) || !iowDev->InUse)
		err = ERROR_INVALID_PARAMETER;
	else
	{
		if (iowDev != NULL)
		{
			HANDLE Mutex;

			Mutex = IowiAquireNamedMutex(iowDev->Pipes[numPipe].readMutexName);
			n = (ULONG)iowDev->Pipes[numPipe].HidInfo.Caps.InputReportByteLength;
			if (IowiReadReportUnbuffered(iowDev, numPipe, report, &DeviceMutex, &ApplicationMutex))
				len = n;
			else
				err = ERROR_TIMEOUT;
			IowiReleaseNamedMutex(Mutex);
		}
		else
			err = ERROR_TIMEOUT;
	}
	IowiReleaseMyDevice(iowDev, DeviceMutex, ApplicationMutex);
	SetLastError(err);
	return (int)len;
}

int IOWKIT2_API IowKit2Read(IOWKIT2_HANDLE devHandle, ULONG numPipe, PIOWKIT2_REPORT report)
{
	int ret;

	ret = IowiRead(devHandle, numPipe, report, 2);
	return ret;
}

void IowiSetData(PIOWI_DEVICE iowDev, ULONG numPipe, PIOWKIT2_REPORT preport)
{
	HANDLE Mutex;

	Mutex = IowiAquireNamedMutex(iowDev->Pipes[numPipe].msgMutexName);
	iowDev->Pipes[numPipe].CallbackReport = *preport;
	IowiReleaseNamedMutex(Mutex);
}

DWORD __stdcall IowiReadIOThread(PIOWI_DEVICE iowDev)
{
	PIOWI_DEVICE_PIPE Pipe;
	IOWKIT2_REPORT report;
	OVERLAPPED ovlp;
	DWORD rc;
	DWORD size;
	BOOL Handled;
	BOOL UnplugError = FALSE;

	memset(&ovlp, 0, sizeof(ovlp));
	Pipe = &iowDev->Pipes[IOWKIT2_PIPE_IO_PINS];
	for (;;)
	{
		// Read asynchronously
		memset(&report, 0, IOWKIT2_REPORT_SIZE);
		ReadFileEx(Pipe->ReadHandle, &report, Pipe->HidInfo.Caps.InputReportByteLength, &ovlp, &IowiDummyCompletion);
		// Perform async read
		for (;;)
		{
			// Wait for either I/O completion or for
			// "terminate thread" event
			rc = WaitForSingleObjectEx(Pipe->endEvent, 250, TRUE);
			// OK, we read something
			if (rc == WAIT_IO_COMPLETION)
			{
				size = 0;
				if (GetOverlappedResult(Pipe->ReadHandle, &ovlp, &size, TRUE))
				{
					if (size != 0)
					{
						PIOWI_APPLICATION Appl;

						// last value read for legacy IowKitReadImmediate
						iowDev->lastReport = report;
						iowDev->readAny = TRUE;
						Handled = FALSE;
						Appl = IowiGetApplicationFromDevice(iowDev);
						if ((Appl != NULL) && (Appl->DataCallbacks[IOWKIT2_PIPE_IO_PINS].DataCallback != NULL))
						{
							IowiSetData(iowDev, IOWKIT2_PIPE_IO_PINS, &report);
							if (Appl->MsgWnd != NULL)
								Handled = (BOOL)SendMessage(Appl->MsgWnd, DataMessageValue, IOWKIT2_PIPE_IO_PINS, (LPARAM)iowDev->DevID);
						}

						if (!Handled)
							IowiInsertBuffer(iowDev, IOWKIT2_PIPE_IO_PINS, &report, size);
					}
					else
						SetEvent(Pipe->readFailedEvent);
				}
				else
				{
					// this seems to happen only once on unplug of the device
					SetEvent(Pipe->readFailedEvent);
					UnplugError = TRUE;
				}
				break;
			}
			else
				// OK, we gotta terminate thread
				// AND tell the program it's safe to close everything
				if (rc == WAIT_OBJECT_0)
				{
					// Don't forget to cancel all I/O
					IowiCancelIo(Pipe->ReadHandle);
					// Signal that thread is now gone
					SetEvent(Pipe->threadTermEvent);
					// Goodbye, cruel world!
					ExitThread(0);
				}
				else
					if ((rc != WAIT_TIMEOUT) || UnplugError)
					{
						IowiCancelIo(Pipe->ReadHandle);
						SetEvent(Pipe->readFailedEvent);
						break;
					}
		}
	}
}

DWORD __stdcall IowiReadSpecialThread(PIOWI_DEVICE iowDev)
{
	PIOWI_DEVICE_PIPE Pipe;
	IOWKIT2_REPORT report;
	OVERLAPPED ovlp;
	DWORD rc;
	DWORD size;
	BOOL Handled;
	PIOWI_APPLICATION Appl;
	BOOL UnplugError;

	UnplugError = FALSE;
	memset(&ovlp, 0, sizeof(ovlp));
	Pipe = &iowDev->Pipes[IOWKIT2_PIPE_SPECIAL_MODE];
	for (;;)
	{
		// Read asynchronously
		memset(&report, 0, sizeof(report));
		ReadFileEx(Pipe->ReadHandle, &report, Pipe->HidInfo.Caps.InputReportByteLength, &ovlp, &IowiDummyCompletion);
		// Perform async read
		for (;;)
		{
			// Wait for either I/O completion or for
			// "terminate thread" event
			rc = WaitForSingleObjectEx(Pipe->endEvent, 250, TRUE);
			// OK, we read something
			if (rc == WAIT_IO_COMPLETION)
			{
				size = 0;
				if (GetOverlappedResult(Pipe->ReadHandle, &ovlp, &size, TRUE))
				{
					if (size != 0)
					{
						Handled = FALSE;
						Appl = IowiGetApplicationFromDevice(iowDev);
						if ((Appl != NULL) && (Appl->DataCallbacks[IOWKIT2_PIPE_SPECIAL_MODE].DataCallback != NULL))
						{
							IowiSetData(iowDev, IOWKIT2_PIPE_SPECIAL_MODE, &report);
							if (Appl->MsgWnd != NULL)
								Handled = (BOOL)SendMessage(Appl->MsgWnd, DataMessageValue, IOWKIT2_PIPE_SPECIAL_MODE, (LPARAM)iowDev->DevID);
						}
						if (!Handled)
							IowiInsertBuffer(iowDev, IOWKIT2_PIPE_SPECIAL_MODE, &report, size);
					}
					else
						SetEvent(Pipe->readFailedEvent);
				}
				else
				{
					// this seems to happen only once on unplug of the device
					SetEvent(Pipe->readFailedEvent);
					UnplugError = TRUE;
				}
				break;
			}
			else
				// OK, we gotta terminate thread
				// AND tell the program it's safe to close everything
				if (rc == WAIT_OBJECT_0)
				{
					// Don't forget to cancel all I/O
					IowiCancelIo(Pipe->ReadHandle);
					// Signal that thread is now gone
					SetEvent(Pipe->threadTermEvent);
					// Goodbye, cruel world!
					ExitThread(0);
				}
				else
					if ((rc != WAIT_TIMEOUT) || UnplugError)
					{
						IowiCancelIo(Pipe->ReadHandle);
						SetEvent(Pipe->readFailedEvent);
						break;
					}
		}
	}
}


DWORD __stdcall IowiReadI2CThread(PIOWI_DEVICE iowDev)
{
	PIOWI_DEVICE_PIPE Pipe;
	IOWKIT2_REPORT report;
	OVERLAPPED ovlp;
	DWORD rc;
	DWORD size;
	BOOL Handled;
	PIOWI_APPLICATION Appl;
	BOOL UnplugError;

	UnplugError = FALSE;
	memset(&ovlp, 0, sizeof(ovlp));
	Pipe = &iowDev->Pipes[IOWKIT2_PIPE_I2C_MODE];
	for (;;)
	{
		// Read asynchronously
		memset(&report, 0, sizeof(report));
		ReadFileEx(Pipe->ReadHandle, &report, Pipe->HidInfo.Caps.InputReportByteLength, &ovlp, &IowiDummyCompletion);
		// Perform async read
		for (;;)
		{
			// Wait for either I/O completion or for
			// "terminate thread" event
			rc = WaitForSingleObjectEx(Pipe->endEvent, 250, TRUE);
			// OK, we read something
			if (rc == WAIT_IO_COMPLETION)
			{
				size = 0;
				if (GetOverlappedResult(Pipe->ReadHandle, &ovlp, &size, TRUE))
				{
					if (size != 0)
					{
						Handled = FALSE;
						Appl = IowiGetApplicationFromDevice(iowDev);
						if ((Appl != NULL) && (Appl->DataCallbacks[IOWKIT2_PIPE_I2C_MODE].DataCallback != NULL))
						{
							IowiSetData(iowDev, IOWKIT2_PIPE_I2C_MODE, &report);
							if (Appl->MsgWnd != NULL)
								Handled = (BOOL)SendMessage(Appl->MsgWnd, DataMessageValue, IOWKIT2_PIPE_I2C_MODE, (LPARAM)iowDev->DevID);
						}
						if (!Handled)
							IowiInsertBuffer(iowDev, IOWKIT2_PIPE_I2C_MODE, &report, size);
					}
					else
						SetEvent(Pipe->readFailedEvent);
				}
				else
				{
					// this seems to happen only once on unplug of the device
					SetEvent(Pipe->readFailedEvent);
					UnplugError = TRUE;
				}
				break;
			}
			else
				// OK, we gotta terminate thread
				// AND tell the program it's safe to close everything
				if (rc == WAIT_OBJECT_0)
				{
					// Don't forget to cancel all I/O
					IowiCancelIo(Pipe->ReadHandle);
					// Signal that thread is now gone
					SetEvent(Pipe->threadTermEvent);
					// Goodbye, cruel world!
					ExitThread(0);
				}
				else
					if ((rc != WAIT_TIMEOUT) || UnplugError)
					{
						IowiCancelIo(Pipe->ReadHandle);
						SetEvent(Pipe->readFailedEvent);
						break;
					}
		}
	}
}

DWORD __stdcall IowiReadADCThread(PIOWI_DEVICE iowDev)
{
	PIOWI_DEVICE_PIPE Pipe;
	IOWKIT2_REPORT report;
	OVERLAPPED ovlp;
	DWORD rc;
	DWORD size;
	BOOL Handled;
	PIOWI_APPLICATION Appl;
	BOOL UnplugError;

	UnplugError = FALSE;
	memset(&ovlp, 0, sizeof(ovlp));
	Pipe = &iowDev->Pipes[IOWKIT2_PIPE_ADC_MODE];
	for (;;)
	{
		// Read asynchronously
		memset(&report, 0, sizeof(report));
		ReadFileEx(Pipe->ReadHandle, &report, Pipe->HidInfo.Caps.InputReportByteLength, &ovlp, &IowiDummyCompletion);
		// Perform async read
		for (;;)
		{
			// Wait for either I/O completion or for
			// "terminate thread" event
			rc = WaitForSingleObjectEx(Pipe->endEvent, 250, TRUE);
			// OK, we read something
			if (rc == WAIT_IO_COMPLETION)
			{
				size = 0;
				if (GetOverlappedResult(Pipe->ReadHandle, &ovlp, &size, TRUE))
				{
					if (size != 0)
					{
						Handled = FALSE;
						Appl = IowiGetApplicationFromDevice(iowDev);
						if ((Appl != NULL) && (Appl->DataCallbacks[IOWKIT2_PIPE_ADC_MODE].DataCallback != NULL))
						{
							IowiSetData(iowDev, IOWKIT2_PIPE_ADC_MODE, &report);
							if (Appl->MsgWnd != NULL)
								Handled = (BOOL)SendMessage(Appl->MsgWnd, DataMessageValue, IOWKIT2_PIPE_ADC_MODE, (LPARAM)iowDev->DevID);
						}
						if (!Handled)
							IowiInsertBuffer(iowDev, IOWKIT2_PIPE_ADC_MODE, &report, size);
					}
					else
						SetEvent(Pipe->readFailedEvent);
				}
				else
				{
					// this seems to happen only once on unplug of the device
					SetEvent(Pipe->readFailedEvent);
					UnplugError = TRUE;
				}
				break;
			}
			else
				// OK, we gotta terminate thread
				// AND tell the program it's safe to close everything
				if (rc == WAIT_OBJECT_0)
				{
					// Don't forget to cancel all I/O
					IowiCancelIo(Pipe->ReadHandle);
					// Signal that thread is now gone
					SetEvent(Pipe->threadTermEvent);
					// Goodbye, cruel world!
					ExitThread(0);
				}
				else
					if ((rc != WAIT_TIMEOUT) || UnplugError)
					{
						IowiCancelIo(Pipe->ReadHandle);
						SetEvent(Pipe->readFailedEvent);
						break;
					}
		}
	}
}

int IowiReadNonBlocking(IOWKIT2_HANDLE devHandle, ULONG numPipe, PIOWKIT2_REPORT report, ULONG APIVersion)
{
	PIOWI_DEVICE iowDev;
	int ret;
	HANDLE DeviceMutex, ApplicationMutex;
	PIOWI_APPLICATION Appl;

	iowDev = IowiAccessMyDevice(devHandle, &DeviceMutex, &ApplicationMutex);
	Appl = IowiGetApplicationFromDevice(iowDev);
	if (iowDev == NULL || (report == NULL) || (numPipe >= IOWKIT2_MAX_PIPES) ||
		(Appl == NULL) || Appl->InDataCallback || (Appl->UsedAPIVersion != APIVersion))
	{
		SetLastError(ERROR_INVALID_PARAMETER);
		ret = -1;
	}
	else
	{
		SetLastError(ERROR_SUCCESS);
		if (IowiGetBuffer(iowDev, numPipe, report))
			ret = (int)iowDev->Pipes[numPipe].HidInfo.Caps.InputReportByteLength;
		else
			ret = 0;
	}
	IowiReleaseMyDevice(iowDev, DeviceMutex, ApplicationMutex);
	return ret;
}

int IOWKIT2_API IowKit2ReadNonBlocking(IOWKIT2_HANDLE devHandle, ULONG numPipe, PIOWKIT2_REPORT report)
{
	return IowiReadNonBlocking(devHandle, numPipe, report, 2);
}

int IOWKIT2_API IowKit2ReadImmediate(IOWKIT2_HANDLE devHandle, PIOWKIT2_REPORT report)
{
	return IowiReadImmediate(devHandle, report, 2);
};