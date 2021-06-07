#include <iostream>
#include "kInterface.h"
#include <thread>

DWORD clientDll   = 0;
DWORD localplayer = 0;
DWORD pid         = 0;

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
    localplayer = drive.ReadVirtualMemory<DWORD>(pid, clientDll + 0xD892CC);

    std::cout << "0x" << std::hex << clientDll << "\n";
    std::cout << "0x" << std::hex << localplayer << "\n";
    printf("%d", pid);

    while (true)
    {
        short int state = drive.ReadVirtualMemory<int>(pid, localplayer + 0x104);
        if (!GetAsyncKeyState(VK_SPACE))
        {
            Sleep(10);
        }
        else if (state == 257 or state == 263)
        {
            drive.WriteVirtualMemory<int>(pid, clientDll + 0x524BF4C, 5);
            Sleep(10);
            drive.WriteVirtualMemory<int>(pid, clientDll + 0x524BF4C, 4);
            Sleep(100);
        }
    }
    Sleep(5000);
}
