#ifndef _IOW_DEVICE_
#define _IOW_DEVICE_

#define IOWI_PRESENT     0x494F5761
#define IOWI_NOTPRESENT  0x0feeb1e0
#define IOWI_IS_USED     IOWI_PRESENT
#define IOWI_IS_FREE     0x00000000

// last 128 values are buffered
#define IOWI_NUM_BUFFERS     128
// IOW KIT serial number string length
#define IOWI_SN_LEN       8

#define INITIAL_TIMEOUT INFINITE

#define IOWI_MAX_DEVICES 32
#define IOWI_MAX_APPLICATIONS 32

#define IOWI_DEVICEPATH_LEN 4096

#define IOWI_MUTEXSIZE 64 //default 32

typedef struct _IOWI_WRITE
{
	OVERLAPPED ovlpWrite;
	HANDLE writeHandle;
	BOOL writeOk;
}
IOWI_WRITE, *PIOWI_WRITE;

typedef struct _IOWI_HID_INFO
{
	DEVINST DevInst;
	DEVINST Parent;
	DEVINST GrandParent;
	HIDP_CAPS Caps;
	HIDD_ATTRIBUTES Attributes;
	CHAR DevicePath[IOWI_DEVICEPATH_LEN];
}
IOWI_HID_INFO;

typedef struct _IOWI_DATACALLBACK
{
	IOWKIT2_DATA_EVENT DataCallback;
	PVOID DataContext;
}
IOWI_DATACALLBACK, *PIOWI_DATACALLBACK;

typedef struct _IOWI_DEVICE_PIPE
{
	IOWI_HID_INFO HidInfo;
	char bufMutexName[IOWI_MUTEXSIZE];
	char readMutexName[IOWI_MUTEXSIZE];
	char msgMutexName[IOWI_MUTEXSIZE];
	char cancelMutexName[IOWI_MUTEXSIZE];
	HANDLE ioThread;                            // Async I/O thread handle
	HANDLE insertEvent;                         // Read complete event
	HANDLE readFailedEvent;                     // Read complete with failure event
	HANDLE endEvent;                            // Terminate event
	HANDLE threadTermEvent;                     // Thread has been terminated event
	IOWKIT2_REPORT CallbackReport;
	IOWKIT2_REPORT Queue[IOWI_NUM_BUFFERS];     // Last reports read
	ULONG bufStart;                             // Start & end buffer positions
	ULONG bufEnd;
	ULONG numBuf;                               // Number of buffers used
	HANDLE ReadHandle;
	HANDLE WriteHandle;
}
IOWI_DEVICE_PIPE, *PIOWI_DEVICE_PIPE;

typedef struct _IOWI_DEVICE *PIOWI_DEVICE;

typedef struct _IOWI_APPLICATION
{
	DWORD Cookie;
	ULONG AppID;
	DWORD ProcessID;
	ULONG UsedAPIVersion;
	char ApplicationMutexName[IOWI_MUTEXSIZE];
	HANDLE FinalizeEvent;
	HWND MsgWnd;
	HDEVNOTIFY Notify;
	BOOL InDataCallback;
	BOOL InDevChangeCallback;
	IOWKIT2_DEVICECHANGE_EVENT DeviceChangeCallback;
	PVOID DeviceChangeContext;
	IOWI_DATACALLBACK DataCallbacks[IOWKIT2_MAX_PIPES];
}
IOWI_APPLICATION, *PIOWI_APPLICATION;

typedef struct _IOWI_DEVICE
{
	char DeviceMutexName[IOWI_MUTEXSIZE];
	DWORD Cookie;
	ULONG DevID;
	ULONG AppNo;
	BOOL NewDev;
	BOOL InUse;

	ULONG ioTimeout;
	ULONG ioWriteTimeout;

	IOWKIT2_REPORT lastReport;
	BOOL readAny;

	ULONG PipeCount;
	WCHAR SerialNumber[IOWI_SN_LEN + 1];

	IOWI_DEVICE_PIPE Pipes[IOWKIT2_MAX_PIPES];
}
IOWI_DEVICE;

typedef struct _IOWI_GLOBAL
{
	int volatile NumberOfLoads;
	BOOL volatile Enumerating;  // drops further WM_DEVICECHANGEs if already one is currently handled
	HWND volatile DevMgrWindow; // the window to currently handle WM_DEVICECHANGEs from
	LONG volatile LastMsgTime;
	BOOL volatile DevListInitialized;

	IOWI_DEVICE Devices[IOWI_MAX_DEVICES];
	IOWI_APPLICATION Applications[IOWI_MAX_APPLICATIONS];
}
IOWI_GLOBAL, *PIOWI_GLOBAL;

// iowkit.c internal data
extern HANDLE DLLModule;
extern PIOWI_GLOBAL ShMem;
extern UINT DeviceChangeMessageValue;
extern UINT DataMessageValue;
extern const char ApplicationsMutexName[];
extern const char DevicesMutexName[];

DWORD __stdcall IowiReadIOThread(PIOWI_DEVICE iowDev);
DWORD __stdcall IowiReadSpecialThread(PIOWI_DEVICE iowDev);
DWORD __stdcall IowiReadI2CThread(PIOWI_DEVICE iowDev);
DWORD __stdcall IowiReadADCThread(PIOWI_DEVICE iowDev);

BOOL IowiCancelIo(HANDLE hFile);
DWORD IowiInitialize(IOWKIT2_DEVICECHANGE_EVENT Event, PVOID Context, ULONG APIVersion);
ULONG IowiWrite(IOWKIT2_HANDLE devHandle, ULONG numPipe, PIOWKIT2_REPORT report, ULONG APIVersion);
int IowiRead(IOWKIT2_HANDLE devHandle, ULONG numPipe, PIOWKIT2_REPORT report, ULONG APIVersion);
int IowiReadUnbuffered(IOWKIT2_HANDLE devHandle, ULONG numPipe, PIOWKIT2_REPORT report, ULONG APIVersion);
int IowiReadNonBlocking(IOWKIT2_HANDLE devHandle, ULONG numPipe, PIOWKIT2_REPORT report, ULONG APIVersion);
ULONG IowiGetProductId(IOWKIT2_HANDLE devHandle, ULONG APIVersion);
ULONG IowiGetRevision(IOWKIT2_HANDLE devHandle, ULONG APIVersion);
HANDLE IowiGetThreadHandle(IOWKIT2_HANDLE devHandle, ULONG numPipe, ULONG APIVersion);
BOOL IowiSetTimeout(IOWKIT2_HANDLE devHandle, ULONG timeout, ULONG APIVersion);
BOOL IowiSetWriteTimeout(IOWKIT2_HANDLE devHandle, ULONG timeout, ULONG APIVersion);
BOOL IowiSetDeviceUse(IOWKIT2_HANDLE devHandle, BOOL Use, ULONG APIVersion);
int IowiPendingReports(IOWKIT2_HANDLE devHandle, ULONG numPipe, ULONG APIVersion);
int IowiReadImmediate(IOWKIT2_HANDLE devHandle, PIOWKIT2_REPORT report, ULONG APIVersion);
int IowiFlush(PIOWI_DEVICE iowDev, ULONG numPipe);

HANDLE IowiAquireNamedMutex(PCSTR Name);
void IowiReleaseNamedMutex(HANDLE Mutex);

PIOWI_APPLICATION IowiGetApplicationFromDevice(PIOWI_DEVICE iowDev);
PIOWI_APPLICATION IowiFindApplication(void);
ULONG IowiGetApplicationID(PIOWI_APPLICATION Appl);

PIOWI_DEVICE IowiAccessMyDevice(IOWKIT2_HANDLE devHandle, HANDLE *DeviceMutex, HANDLE *ApplicationMutex);
void IowiReleaseMyDevice(PIOWI_DEVICE iowDev, HANDLE DeviceMutex, HANDLE ApplicationMutex);
void IowiEnumerateNewDevices(PIOWI_APPLICATION AAppl);

void IowiStopDevice(PIOWI_DEVICE iowDev, BOOL Mutexed);
BOOL IowiStartDevice(PIOWI_DEVICE iowDev);

void IowiEnumerate(APIVersion);

#endif // _IOW_DEVICE_
