#include "communication.h"

NTSTATUS Communication::CreateCall(PDEVICE_OBJECT pDeviceObject, PIRP Irp)
{
	Irp->IoStatus.Status	  = STATUS_SUCCESS;
	Irp->IoStatus.Information = 0;

	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	return STATUS_SUCCESS;
}
NTSTATUS Communication::CloseCall(PDEVICE_OBJECT pDeviceObject, PIRP Irp)
{
	Irp->IoStatus.Status	  = STATUS_SUCCESS;
	Irp->IoStatus.Information = 0;

	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	return STATUS_SUCCESS;
}
NTSTATUS Communication::IoControll(PDEVICE_OBJECT pDeviceObject, PIRP Irp)
{
	NTSTATUS		   status		 = STATUS_UNSUCCESSFUL;
	ULONG			   byteIO		 = 0;
	PIO_STACK_LOCATION stack         = IoGetCurrentIrpStackLocation(Irp);
	ULONG			   controle_code = stack->Parameters.DeviceIoControl.IoControlCode;


	if (controle_code == CallRequests::READ_VIRTUAL_MEMORY_CALL)
	{
		PREAD_VIRTUAL_MEMORY_REQUEST data = (PREAD_VIRTUAL_MEMORY_REQUEST)Irp->AssociatedIrp.SystemBuffer;
		PEPROCESS Process;
	
		if (PsLookupProcessByProcessId(reinterpret_cast<HANDLE>(data->ProcessId), &Process) == STATUS_SUCCESS)
		{
			status = STATUS_SUCCESS;
			byteIO = sizeof(READ_VIRTUAL_MEMORY_REQUEST);
			memory::KernelReadVirtualMemory(Process, (PVOID)data->Address, data->buff, data->Size);
		}
	}
	else if (controle_code == CallRequests::WRITE_VIRTUAL_MEMORY_CALL)
	{
		PWRITE_VIRTUAL_MEMORY_REQUEST data = (PWRITE_VIRTUAL_MEMORY_REQUEST)Irp->AssociatedIrp.SystemBuffer;
		PEPROCESS					  Process;

		if (PsLookupProcessByProcessId(reinterpret_cast<HANDLE>(data->ProcessId), &Process) == STATUS_SUCCESS)
		{
			status = STATUS_SUCCESS;
			byteIO = sizeof(PWRITE_VIRTUAL_MEMORY_REQUEST);
			memory::KernelWriteVirtualMemory(Process, data->pBuff, (PVOID)data->Address, data->Size);

		}
	}
	else if (controle_code == CallRequests::GET_CLIENTDLL_ADDR)
	{
		PDWORD32 out = (PDWORD32)Irp->AssociatedIrp.SystemBuffer;

		*out   = clientDLL;
		status = STATUS_SUCCESS;
		byteIO = sizeof(*out);
	}
	else if (controle_code == CallRequests::GET_CSGO_PID)
	{
		PDWORD32 out = (PDWORD32)Irp->AssociatedIrp.SystemBuffer;

		*out = csgoPID;
		status = STATUS_SUCCESS;
		byteIO = sizeof(*out);
	}
	Irp->IoStatus.Status      = status;
	Irp->IoStatus.Information = byteIO;

	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	return status;
}