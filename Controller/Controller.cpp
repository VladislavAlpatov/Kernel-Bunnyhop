#include <iostream>
#include "kInterface.h"
#include <thread>

DWORD32 clientDll   = 0;
DWORD32 localplayer = 0;
DWORD32 pid         = 0;

int main()
{
    Kernel drive = Kernel("\\\\.\\tdrive");
    if (!drive.CheckValid())
    {
        printf("Not valid connection!\n");
        Sleep(2000);
        exit(0);
    }
    else
        printf("Connected!\n");

    clientDll   = drive.GetClientAddres();
    pid         = drive.GetProcessID();
    localplayer = drive.ReadVirtualMemory<DWORD32>(pid, clientDll + 0xD892CC);


    while (true)
    {
        short int state = drive.ReadVirtualMemory<int>(pid, localplayer + 0x104);
        if ( (state == 257 or state == 263) and GetAsyncKeyState(VK_SPACE))
        {
            drive.WriteVirtualMemory<int>(pid, clientDll + 0x524BF4C, 5);
            Sleep(50);
            drive.WriteVirtualMemory<int>(pid, clientDll + 0x524BF4C, 4);
        }
    }
    Sleep(5000);
}
