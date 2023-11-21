//
// IO-Warrior kit library V2.0 include file
//

#ifndef _IOWKIT2_H_
#define _IOWKIT2_H_

#ifndef _IOWKIT_BUILD_RUN
#ifdef _IOW_KIT_H_
#error "including both iowkit2.h and iowkit.h is not allowed"
#endif // _IOW_KIT_H_
#endif // _IOWKIT_BUILD_RUN

#ifdef _WIN32

#define IOWKIT2_API __stdcall

#else

#define IOWKIT2_API

// the following legacy types can only be defined once
#ifndef _IOW_WINTYPES_H_
#define _IOW_WINTYPES_H_

/*
 * Windows specific types and defines
 */
typedef unsigned long          ULONG;
typedef long                   LONG;
typedef unsigned short         USHORT;
typedef unsigned short         WORD;
typedef unsigned char          UCHAR;
typedef unsigned char          BYTE;
typedef char *                 PCHAR;
typedef unsigned short *       PWCHAR;
typedef int                    BOOL;
typedef unsigned char          BOOLEAN;
typedef unsigned long          DWORD;
typedef DWORD *                PDWORD;
typedef void *                 PVOID;
typedef DWORD                  HANDLE;
typedef ULONG *                PULONG;
typedef const char *           PCSTR;
typedef const unsigned short * PWCSTR;

#define FALSE 0
#define TRUE 1

#endif // _IOW_WINTYPES_H_

#endif // _WIN32

// IO-Warrior vendor & product IDs
#define IOWKIT2_VENDOR_ID			0x07c0
#define IOWKIT2_VID					IOWKIT2_VENDOR_ID

// IO-Warrior 40
#define IOWKIT2_PRODUCT_ID_IOW40	0x1500
#define IOWKIT2_PID_IOW40			IOWKIT2_PRODUCT_ID_IOW40

// IO-Warrior 24
#define IOWKIT2_PRODUCT_ID_IOW24	0x1501
#define IOWKIT2_PID_IOW24			IOWKIT2_PRODUCT_ID_IOW24

// IO-Warrior PowerVampire
#define IOWKIT2_PRODUCT_ID_IOWPV1	0x1511
#define IOWKIT2_PID_IOWPV1			IOWKIT2_PRODUCT_ID_IOWPV1
#define IOWKIT2_PRODUCT_ID_IOWPV2	0x1512
#define IOWKIT2_PID_IOWPV2			IOWKIT2_PRODUCT_ID_IOWPV2

// IO-Warrior 24 Sensirion
#define IOWKIT2_PRODUCT_ID_IOW_SENSI1  0x158a
#define IOWKIT2_PID_IOW_SENSI1        IOWKIT2_PRODUCT_ID_IOW_SENSI1

// IO-Warrior 56
#define IOWKIT2_PRODUCT_ID_IOW56	0x1503
#define IOWKIT2_PID_IOW56			IOWKIT2_PRODUCT_ID_IOW56

// IO-Warrior 28
#define IOWKIT2_PRODUCT_ID_IOW28	0x1504
#define IOWKIT2_PID_IOW28			IOWKIT2_PRODUCT_ID_IOW28

// IO-Warrior 28L
#define IOWKIT2_PRODUCT_ID_IOW28L	0x1505
#define IOWKIT2_PID_IOW28L			IOWKIT2_PRODUCT_ID_IOW28L

// IO-Warrior 28L
#define IOWKIT2_PRODUCT_ID_IOW100	0x1506
#define IOWKIT2_PID_IOW100			IOWKIT2_PRODUCT_ID_IOW100

//Test-Warrior (Internal, IOW28 based)
#define IOWKIT2_PRODUCT_ID_TW		0x15FF
#define IOWKIT2_PID_TW				IOWKIT2_PRODUCT_ID_TW

// Max number of pipes per IOW device
//IOW40, 24, 56, 28L = 2
//IOW28 = 4
#define IOWKIT2_MAX_PIPES    4

// pipe names
#define IOWKIT2_PIPE_IO_PINS		0
#define IOWKIT2_PIPE_SPECIAL_MODE	1
#define IOWKIT2_PIPE_I2C_MODE		2	//only IOW28 (not IOW28L)
#define IOWKIT2_PIPE_ADC_MODE		3	//only IOW28 (not IOW28L)

// first IO-Warrior revision with serial numbers
#define IOWKIT2_NON_LEGACY_REVISION 0x1010

// values for action parameter of IOWKIT2_DEVICECHANGE_EVENT
#define IOWKIT2_ACTION_ARRIVAL 0
#define IOWKIT2_ACTION_REMOVAL 1

// max number of bytes in a report
#define IOWKIT2_REPORT_PAYLOAD_SIZE 63

// Opaque IO-Warrior handle
typedef PVOID IOWKIT2_HANDLE;

// Don't forget to pack it!
#pragma pack(push, 1)

// This is a max report which can hold any IO-Warrior report
typedef struct _IOWKIT2_REPORT
{
	UCHAR ReportID;
	UCHAR Bytes[IOWKIT2_REPORT_PAYLOAD_SIZE];
}
IOWKIT2_REPORT, *PIOWKIT2_REPORT;

#define IOWKIT2_REPORT_SIZE sizeof(IOWKIT2_REPORT)

#pragma pack(pop)

#ifdef  __cplusplus
extern "C" {
#endif // __cplusplus

	typedef BOOL(IOWKIT2_API *IOWKIT2_DATA_EVENT)(IOWKIT2_HANDLE devHandle, ULONG numPipe, PIOWKIT2_REPORT report, ULONG size, PVOID Context);
	typedef void (IOWKIT2_API *IOWKIT2_DEVICECHANGE_EVENT)(ULONG action, IOWKIT2_HANDLE devHandle, PVOID Context);

	DWORD IOWKIT2_API IowKit2Initialize(IOWKIT2_DEVICECHANGE_EVENT Event, PVOID Context);
	void IOWKIT2_API IowKit2Finalize(void);
	ULONG IOWKIT2_API IowKit2Write(IOWKIT2_HANDLE devHandle, ULONG numPipe, PIOWKIT2_REPORT report);
	int IOWKIT2_API IowKit2Read(IOWKIT2_HANDLE devHandle, ULONG numPipe, PIOWKIT2_REPORT report);
	int IOWKIT2_API IowKit2ReadNonBlocking(IOWKIT2_HANDLE devHandle, ULONG numPipe, PIOWKIT2_REPORT report);
	int IOWKIT2_API IowKit2ReadImmediate(IOWKIT2_HANDLE devHandle, PIOWKIT2_REPORT report);
	ULONG IOWKIT2_API IowKit2GetNumDevs(void);
	ULONG IOWKIT2_API IowKit2GetProductId(IOWKIT2_HANDLE devHandle);
	ULONG IOWKIT2_API IowKit2GetRevision(IOWKIT2_HANDLE devHandle);
	HANDLE IOWKIT2_API IowKit2GetThreadHandle(IOWKIT2_HANDLE devHandle, ULONG numPipe);
	ULONG IOWKIT2_API IowKit2GetSerialNumber(IOWKIT2_HANDLE devHandle);
	BOOL IOWKIT2_API IowKit2SetTimeout(IOWKIT2_HANDLE devHandle, ULONG timeout);
	BOOL IOWKIT2_API IowKit2SetWriteTimeout(IOWKIT2_HANDLE devHandle, ULONG timeout);
	PCSTR IOWKIT2_API IowKit2Version(void);
	BOOL IOWKIT2_API IowKit2Register(IOWKIT2_HANDLE devHandle, ULONG numPipe, IOWKIT2_DATA_EVENT Event, PVOID Context);
	BOOL IOWKIT2_API IowKit2GetDeviceUse(IOWKIT2_HANDLE devHandle);
	BOOL IOWKIT2_API IowKit2SetDeviceUse(IOWKIT2_HANDLE devHandle, BOOL Use);
	void IOWKIT2_API IowKit2Enumerate(void);
	int IOWKIT2_API IowKit2PendingReports(IOWKIT2_HANDLE devHandle, ULONG numPipe);
	int IOWKIT2_API IowKit2Flush(IOWKIT2_HANDLE devHandle, ULONG numPipe);
	BOOL IOWKIT2_API IowKit2IsConnected(IOWKIT2_HANDLE devHandle);

#ifdef  __cplusplus
}
#endif // __cplusplus

#endif // _IOWKIT2_H_
