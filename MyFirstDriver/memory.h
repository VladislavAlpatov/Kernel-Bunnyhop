#pragma once
#include <ntifs.h>

extern "C" NTSTATUS NTAPI MmCopyVirtualMemory
(
	PEPROCESS SourceProcess,
	PVOID SourceAddress,
	PEPROCESS TargetProcess,
	PVOID TargetAddress,
	SIZE_T BufferSize,
	KPROCESSOR_MODE PreviousMode,
	PSIZE_T ReturnSize
);

typedef struct _READ_VIRTUAL_MEMORY_REQUEST
{
	DWORD32 ProcessId;
	DWORD32 Address;
	PVOID   buff;
	DWORD32 Size;

} READ_VIRTUAL_MEMORY_REQUEST, * PREAD_VIRTUAL_MEMORY_REQUEST;

typedef struct _WRITE_VIRTUAL_MEMORY_REQUEST
{
	DWORD32 ProcessId;
	DWORD32 Address;
	PVOID   pBuff;
	DWORD32 Size;

}WRITE_VIRTUAL_MEMORY_REQUEST, * PWRITE_VIRTUAL_MEMORY_REQUEST;

namespace Memory
{

	inline NTSTATUS KernelReadVirtualMemory(PEPROCESS Process, PVOID SourceAddress, PVOID TargetAddress, SIZE_T Size)
	{
		SIZE_T bytes = 0;

		return MmCopyVirtualMemory(Process, SourceAddress, PsGetCurrentProcess(), TargetAddress, Size, KernelMode, &bytes);
	}

	inline NTSTATUS KernelWriteVirtualMemory(PEPROCESS Process, PVOID SourceAddress, PVOID TargetAddress, SIZE_T Size)
	{
		SIZE_T bytes = 0;

		return MmCopyVirtualMemory(PsGetCurrentProcess(), SourceAddress, Process, TargetAddress, Size, KernelMode, &bytes);
	}
}