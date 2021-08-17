#include "pch.h"

DWORD WINAPI MainThread(HMODULE hModule)
{
	FreeLibraryAndExitThread(hModule, 0);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
        auto hThread = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)MainThread, 
									hModule, 0, nullptr);
        if (hThread != INVALID_HANDLE_VALUE)
        {
            CloseHandle(hThread);
        }
	}
    
    return TRUE;
}

