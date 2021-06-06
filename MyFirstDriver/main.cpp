#include <ntifs.h>
#include <ntddk.h>
#include "events.h"
#include "communication.h"

extern "C" NTSTATUS DriverEntry(_In_ PDRIVER_OBJECT  DriverObject, _In_ PUNICODE_STRING RegistryPath);

DriverData data;


NTSTATUS UnloadDriver(PDRIVER_OBJECT  DriverObject)
{
	PsRemoveLoadImageNotifyRoutine(reinterpret_cast<PLOAD_IMAGE_NOTIFY_ROUTINE>(ImageLoadCallback));
	IoDeleteSymbolicLink(&data.dos);
	IoDeleteDevice(DriverObject->DeviceObject);

	return STATUS_SUCCESS;
}

NTSTATUS DriverEntry(_In_ PDRIVER_OBJECT  DriverObject, _In_ PUNICODE_STRING RegistryPath)
{
	DriverObject->DriverUnload = reinterpret_cast<PDRIVER_UNLOAD>(UnloadDriver);
	PsSetLoadImageNotifyRoutine(reinterpret_cast<PLOAD_IMAGE_NOTIFY_ROUTINE>(ImageLoadCallback));

	RtlInitUnicodeString(&data.dev, L"\\Device\\tdrive");
	RtlInitUnicodeString(&data.dos, L"\\DosDevices\\tdrive");

	IoCreateDevice(DriverObject, 0, &data.dev, FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &data.pDeviceObject);
	IoCreateSymbolicLink(&data.dos, &data.dev);

	DriverObject->MajorFunction[IRP_MJ_CREATE]		   = Communication::CreateCall;
	DriverObject->MajorFunction[IRP_MJ_CLOSE]		   = Communication::CloseCall;
	DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = Communication::IoControll;

	data.pDeviceObject->Flags |= DO_DIRECT_IO;
	//data.pDeviceObject->Flags &= ~DO_DEVICE_INITIALIZING;
	return STATUS_SUCCESS;
}