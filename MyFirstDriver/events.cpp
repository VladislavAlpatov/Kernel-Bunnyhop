#include "events.h"


PLOAD_IMAGE_NOTIFY_ROUTINE ImageLoadCallback(PUNICODE_STRING ImageName, HANDLE ProcessID, PIMAGE_INFO ImageInfo)
{
	if (wcsstr(ImageName->Buffer, L"\\Counter-Strike Global Offensive\\csgo\\bin\\client.dll"))
	{
		clientDLL = reinterpret_cast<DWORD32>(ImageInfo->ImageBase);
		csgoPID	  = reinterpret_cast<DWORD32>(ProcessID);
		DbgPrintEx(0, 0, "pid: %d", csgoPID);
	}

	return STATUS_SUCCESS;
}