#pragma once
#include "communication.h"

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

class Kernel
{
public:
	HANDLE hDriver;
	Kernel(LPCSTR RegistryPath)
	{
		this->hDriver = CreateFileA(RegistryPath, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);

	}
	void TestCall()
	{

	}
	void BSOD()
	{
		int res = 0;

		//DeviceIoControl(this->hDriver, CallRequests::BSOD_CALL, &res, sizeof(res), &res, sizeof(res), &res, NULL);

	}
	bool CheckValid()
	{
		if (hDriver == INVALID_HANDLE_VALUE)
			return false;
		return true;
	}
	template <typename type>
	type ReadVirtualMemory(DWORD32 ProcessId, DWORD32 ReadAddress)
	{
		READ_VIRTUAL_MEMORY_REQUEST ReadRequest;
		type buff;
		ReadRequest.ProcessId = ProcessId;
		ReadRequest.Address   = ReadAddress;
		ReadRequest.Size      = sizeof(type);
		ReadRequest.buff	  = &buff;
		DeviceIoControl(this->hDriver, CallRequests::READ_VIRTUAL_MEMORY_CALL, &ReadRequest, sizeof(ReadRequest), &ReadRequest, sizeof(ReadRequest), 0, 0);
		
		return buff;
	}

	template <typename type>
	void WriteVirtualMemory(DWORD32 ProcessId, DWORD32 ReadAddress, type value)
	{
		WRITE_VIRTUAL_MEMORY_REQUEST ReadRequest;
		type buff;

		ReadRequest.ProcessId = ProcessId;
		ReadRequest.Address = ReadAddress;
		ReadRequest.Size = sizeof(type);
		ReadRequest.pBuff = &value;

		DeviceIoControl(this->hDriver, CallRequests::WRITE_VIRTUAL_MEMORY_CALL, &ReadRequest, sizeof(ReadRequest), &ReadRequest, sizeof(ReadRequest), 0, 0);
	}
	DWORD32 GetClientAddres()
	{
		DWORD32 addr = 0;
		DeviceIoControl(this->hDriver, CallRequests::GET_CLIENTDLL_ADDR, &addr, sizeof(addr), &addr, sizeof(addr), 0, 0);

		return addr;
	};
	DWORD GetProcessID()
	{
		DWORD id = 0;
		DeviceIoControl(this->hDriver, CallRequests::GET_CSGO_PID, &id, sizeof(id), &id, sizeof(id), 0, 0);

		return id;
	}
};