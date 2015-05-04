#ifndef MISC_H
#define MISC_H


#ifndef MISC_GLOBALS
#define MISC_EXT extern
#else
#define MISC_EXT
#endif

MISC_EXT char GetUsbStorage(void);

#if _ENB_USB_UPDATE
MISC_EXT volatile INT8 UpdateLocker;
MISC_EXT BOOL UsbUpdateProc(VOID);
#endif

MISC_EXT VOID PutSystemLog(const char *log);

MISC_EXT DATETIME *GetCompileDateTime(void);
#if _ENB_AUTOUSB
MISC_EXT void SetUsbStorageStatus(char status);
#endif

#endif

