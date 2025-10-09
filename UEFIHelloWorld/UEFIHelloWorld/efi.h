#pragma once
//#include <stdint.h>
typedef signed char        int8_t;
typedef short              int16_t;
typedef int                int32_t;
typedef long long          int64_t;
typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned int       uint32_t;
typedef unsigned long long uint64_t;

typedef signed char        int_least8_t;
typedef short              int_least16_t;
typedef int                int_least32_t;
typedef long long          int_least64_t;
typedef unsigned char      uint_least8_t;
typedef unsigned short     uint_least16_t;
typedef unsigned int       uint_least32_t;
typedef unsigned long long uint_least64_t;

typedef signed char        int_fast8_t;
typedef int                int_fast16_t;
typedef int                int_fast32_t;
typedef long long          int_fast64_t;
typedef unsigned char      uint_fast8_t;
typedef unsigned int       uint_fast16_t;
typedef unsigned int       uint_fast32_t;
typedef unsigned long long uint_fast64_t;


//typedef short CHAR16;
typedef int16_t CHAR16;
typedef uint16_t UINT16;
typedef uint32_t UINT32;
typedef uint64_t UINT64;
typedef uint8_t UINT8;
typedef uint8_t BOOLEAN;
typedef struct {
	UINT32    Data1;
	UINT16    Data2;
	UINT16    Data3;
	UINT8     Data4[8];
} GUID;
typedef void VOID;
typedef UINT64 UINTN;
typedef UINTN RETURN_STATUS;
///
#define IN
#define OUT
#define OPTIONAL
#define TRUE  ((BOOLEAN)(1==1))
#define FALSE  ((BOOLEAN)(0==1))



#define EFI_SHIFT_STATE_VALID          0x80000000
#define EFI_RIGHT_SHIFT_PRESSED        0x00000001
#define EFI_LEFT_SHIFT_PRESSED         0x00000002
#define EFI_RIGHT_CONTROL_PRESSED      0x00000004
#define EFI_LEFT_CONTROL_PRESSED       0x00000008
#define EFI_RIGHT_ALT_PRESSED          0x00000010
#define EFI_LEFT_ALT_PRESSED           0x00000020
#define EFI_RIGHT_LOGO_PRESSED         0x00000040
#define EFI_LEFT_LOGO_PRESSED          0x00000080
#define EFI_MENU_KEY_PRESSED           0x00000100
#define EFI_SYS_REQ_PRESSED            0x00000200

//*****************************************************
// EFI_KEY_TOGGLE_STATE
//*****************************************************
typedef UINT8 EFI_KEY_TOGGLE_STATE;

#define EFI_TOGGLE_STATE_VALID 0x80
#define EFI_KEY_STATE_EXPOSED 0x40
#define EFI_SCROLL_LOCK_ACTIVE 0x01
#define EFI_NUM_LOCK_ACTIVE 0x02
#define EFI_CAPS_LOCK_ACTIVE 0x04

#define EFIAPI __fastcall
typedef uint64_t  EFI_STATUS;
///
/// 128-bit buffer containing a unique identifier value.
///
typedef GUID EFI_GUID;
///
/// Function return status for EFI API.
///
typedef RETURN_STATUS EFI_STATUS;
///
/// A collection of related interfaces.
///
typedef VOID* EFI_HANDLE;
///
/// Handle to an event structure.
///
typedef VOID* EFI_EVENT;
///
/// Task priority level.
///
typedef UINTN EFI_TPL;
///
/// Logical block address.
///
typedef UINT64 EFI_LBA;

///
/// 64-bit physical memory address.
///
typedef UINT64 EFI_PHYSICAL_ADDRESS;

///
/// 64-bit virtual memory address.
///
typedef UINT64 EFI_VIRTUAL_ADDRESS;




typedef struct {
	UINT32         Version;
	UINT32         Length;
	UINT64         MemoryProtectionAttribute;
}   EFI_PROPERTIES_TABLE;

/**********************************************
/* EFI_MEMORY_ATTRIBUTES_TABLE
/**********************************************/
typedef struct {
  UINT32                       Version ;
  UINT32                       NumberOfEntries ;
  UINT32                       DescriptorSize ;
  UINT32                       Flags ;
  // EFI_MEMORY_DESCRIPTOR     Entry [1] ;
  }  EFI_MEMORY_ATTRIBUTES_TABLE;

typedef struct {
	UINT16   Version;
	UINT16   NumberOfProfiles;
	//EFI_GUID ConformanceProfiles [];
} EFI_CONFORMANCE_PROFILES_TABLE;


typedef struct EFI_HANDLE
{

} EFI_HANDLE;

typedef struct {
	UINT64      Signature;
	UINT32      Revision;
	UINT32      HeaderSize;
	UINT32      CRC32;
	UINT32      Reserved;
} EFI_TABLE_HEADER;

typedef
EFI_STATUS
(EFIAPI * EFI_INPUT_RESET) (
	/*IN*/ EFI_SIMPLE_TEXT_INPUT_PROTOCOL* This,
	/*IN*/ BOOLEAN                         ExtendedVerification
	);

typedef
EFI_STATUS
(EFIAPI  EFI_INPUT_READ_KEY) (
	/*IN*/ EFI_SIMPLE_TEXT_INPUT_PROTOCOL* This,
	/*OUT*/ EFI_INPUT_KEY* Key
	);

typedef struct {
	EFI_INPUT_KEY           Key;
	EFI_KEY_STATE           KeyState;
} EFI_KEY_DATA;

//*****************************************************
// EFI_KEY_STATE
//*****************************************************
//
// Any Shift or Toggle State that is valid should have
// high order bit set.
//
typedef struct EFI_KEY_STATE {
	UINT32                       KeyShiftState;
	EFI_KEY_TOGGLE_STATE         KeyToggleState;
} EFI_KEY_STATE;


//******************************************************
// EFI_INPUT_KEY
//******************************************************
typedef struct {
	UINT16                             ScanCode;
	CHAR16                             UnicodeChar;
} EFI_INPUT_KEY;

typedef
EFI_STATUS
(EFIAPI* EFI_INPUT_READ_KEY_EX)(
	IN  EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL* This,
	OUT EFI_KEY_DATA* KeyData
	);

typedef
EFI_STATUS
(EFIAPI* EFI_INPUT_RESET_EX)(
	IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL* This,
	IN BOOLEAN                           ExtendedVerification
	);

typedef
EFI_STATUS
(EFIAPI* EFI_SET_STATE)(
	IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL* This,
	IN EFI_KEY_TOGGLE_STATE* KeyToggleState
	);


typedef
EFI_STATUS
(EFIAPI* EFI_KEY_NOTIFY_FUNCTION)(
	IN EFI_KEY_DATA* KeyData
	);

typedef
EFI_STATUS
(EFIAPI* EFI_REGISTER_KEYSTROKE_NOTIFY)(
	IN  EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL* This,
	IN  EFI_KEY_DATA* KeyData,
	IN  EFI_KEY_NOTIFY_FUNCTION           KeyNotificationFunction,
	OUT VOID** NotifyHandle
	);

typedef struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL {
	EFI_INPUT_RESET                       Reset;
	EFI_INPUT_READ_KEY                    ReadKeyStroke;
	EFI_EVENT                             WaitForKey;
} EFI_SIMPLE_TEXT_INPUT_PROTOCOL;


typedef
EFI_STATUS
(EFIAPI* EFI_UNREGISTER_KEYSTROKE_NOTIFY)(
	IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL* This,
	IN VOID* NotificationHandle
	);

typedef struct _EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL {
	EFI_INPUT_RESET_EX                          Reset;
	EFI_INPUT_READ_KEY_EX                       ReadKeyStrokeEx;
	EFI_EVENT                                   WaitForKeyEx;
	EFI_SET_STATE                               SetState;
	EFI_REGISTER_KEYSTROKE_NOTIFY               RegisterKeyNotify;
	EFI_UNREGISTER_KEYSTROKE_NOTIFY             UnregisterKeyNotify;
} EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL;

typedef struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;


typedef VOID EFI_BOOT_SERVICES;
typedef VOID EFI_RUNTIME_SERVICES;
typedef VOID EFI_CONFIGURATION_TABLE;

typedef struct {
	EFI_TABLE_HEADER                 Hdr;
	CHAR16* FirmwareVendor;
	UINT32                           FirmwareRevision;
	EFI_HANDLE                       ConsoleInHandle;
	EFI_SIMPLE_TEXT_INPUT_PROTOCOL* ConIn;
	EFI_HANDLE                       ConsoleOutHandle;
	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* ConOut;
	EFI_HANDLE                       StandardErrorHandle;
	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* StdErr;
	EFI_RUNTIME_SERVICES* RuntimeServices;
	EFI_BOOT_SERVICES* BootServices;
	UINTN                            NumberOfTableEntries;
	EFI_CONFIGURATION_TABLE* ConfigurationTable;
} EFI_SYSTEM_TABLE;


typedef struct {
	EFI_TABLE_HEADER                 Hdr;
	CHAR16* FirmwareVendor;
	UINT32                           FirmwareRevision;
	EFI_HANDLE                       ConsoleInHandle;
	EFI_SIMPLE_TEXT_INPUT_PROTOCOL* ConIn;
	EFI_HANDLE                       ConsoleOutHandle;
	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* ConOut;
	EFI_HANDLE                       StandardErrorHandle;
	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* StdErr;
	EFI_RUNTIME_SERVICES* RuntimeServices;
	EFI_BOOT_SERVICES* BootServices;
	UINTN                            NumberOfTableEntries;
	EFI_CONFIGURATION_TABLE* ConfigurationTable;
} EFI_SYSTEM_TABLE;