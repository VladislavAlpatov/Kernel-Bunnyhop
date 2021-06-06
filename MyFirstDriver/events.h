#pragma once
#include <ntifs.h>
#include "globals.h"
PLOAD_IMAGE_NOTIFY_ROUTINE ImageLoadCallback(PUNICODE_STRING ImageName, HANDLE ProcessID, PIMAGE_INFO ImageInfo);