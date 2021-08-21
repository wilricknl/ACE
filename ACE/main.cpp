/**
 * @file main.cpp
 * @brief Entrance of the program.
 * @author wilricknl
 * @see https://github.com/wilricknl/ACE and version.h for more information.
 */
#include "pch.h"
#include "MVC/Controller.h"

/**
 * @brief Logic of the Dynamic Linked Library.
 *
 * @param hModule Handle to the base of the thread.
 * 
 * @return No return, program exists by calling `FreeLibraryAndExitThread`
 */
DWORD WINAPI MainThread(HMODULE hModule)
{
    auto& controller = mvc::Controller::GetController();

	if (controller.Initialize())
	{
        while (!controller.IsFinished())
        {
            Sleep(25);
        }
	}

	FreeLibraryAndExitThread(hModule, 0);
}

/**
 * @brief Entrance of the program.
 *
 * @see https://docs.microsoft.com/en-us/windows/win32/dlls/dllmain
 */
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
