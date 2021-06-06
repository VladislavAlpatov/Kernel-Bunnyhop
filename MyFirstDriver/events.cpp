#include "events.h"


PLOAD_IMAGE_NOTIFY_ROUTINE ImageLoadCallback(PUNICODE_STRING ImageName, HANDLE ProcessID, PIMAGE_INFO ImageInfo)
{
	if (wcsstr(ImageName->Buffer, L"\\Counter-Strike Global Offensive\\csgo\\bin\\client.dll"))
	{
		clientDLL = (DWORD32)ImageInfo->ImageBase;
		csgoPID	  = (DWORD32)ProcessID;
	}

	return STATUS_SUCCESS;
}