#include <iostream>
#include "kInterface.h"
int main()
{
    Kernel drive = Kernel("\\\\.\\tdrive");
    if (!drive.CheckValid())
    {
        printf("Not valid connection!\n");
        Sleep(2000);
    }
    else
        printf("Connected!\n");

    DWORD clientDll = 0x2ccb0000;
    DWORD localplayer = drive.ReadVirtualMemory<DWORD>(14980, clientDll + 0xD892CC);
    std::cout << "0x" << std::hex << clientDll << "\n";
    std::cout << "0x" << std::hex << localplayer << "\n";

    while (true)
    {
        short int state = drive.ReadVirtualMemory<int>(14980, localplayer + 0x104);
        if ( (state == 257 or state == 263 ) and GetAsyncKeyState(VK_SPACE))
        {
            drive.WriteVirtualMemory<int>(14980, clientDll + 0x524BF4C, 6);
        }
    }
    Sleep(5000);
}
