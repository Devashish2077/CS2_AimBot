#include "renderer/renderer.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    aimbot::procID = memory::GetProcID(L"cs2.exe");
    aimbot::module_base = memory::GetModuleBaseAddress(aimbot::procID, L"client.dll");

    while (true)
    {
        if(GetAsyncKeyState(VK_LSHIFT))
            aimbot::frame();
    }

    return 0;

}
