#include <iostream>
#include "kInterface.h"
#include <thread>

DWORD clientDll   = 0;
DWORD localplayer = 0;

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

    clientDll = 0x2ccb0000;
    localplayer = drive.ReadVirtualMemory<DWORD>(14980, clientDll + 0xD892CC);
    std::cout << "0x" << std::hex << clientDll << "\n";
    std::cout << "0x" << std::hex << localplayer << "\n";

    while (true)
    {
        short int state = drive.ReadVirtualMemory<int>(14980, localplayer + 0x104);
        if ( (state == 257 or state == 263 ) and GetAsyncKeyState(VK_SPACE))
        {
            drive.WriteVirtualMemory<int>(14980, clientDll + 0x524BF4C, 5);
            Sleep(10);
            drive.WriteVirtualMemory<int>(14980, clientDll + 0x524BF4C, 4);
        }
    }
    Sleep(5000);
}
