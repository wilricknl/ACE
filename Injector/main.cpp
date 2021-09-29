#include <iostream>
#include "Commandline.hpp"
#include "Memory.hpp"

int exit(std::string const& message, int value)
{
    std::cout << message << '\n';
    return value;
}

std::wstring to_wstring(std::string text)
{
    return std::wstring{ text.begin(), text.end() };
}

int main(int argc, char* argv[])
{
    cmd::options::variables_map variables;
    if (not cmd::ParseArguments(argc, argv, variables))
    {
        return exit("Failed parsing commandline arguments", 1);
    }

    DWORD processId;
    if (not memory::SelectProcessId(
        to_wstring(variables["program"].as<std::string>()).c_str(), 
        processId))
    {
		return exit("Failed to find the executable", 1);
    }

    auto handle = OpenProcess(PROCESS_ALL_ACCESS, false, processId);
    if (handle == INVALID_HANDLE_VALUE)
    {
        return exit("Failed to acquire a handle", 1);
    }

    auto* location = VirtualAllocEx(handle, 0, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (not location)
    {
        return exit("Failed to allocate memory", 1);
    }

    auto cheat = variables["cheat"].as<std::string>();
    if (not WriteProcessMemory(handle, location, cheat.c_str(), cheat.size() + 1, nullptr))
    {
        return exit("Failed to write DLL path to memory", 1);
    }

	auto hThread = CreateRemoteThread(handle, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, location, 0, 0);
    CloseHandle(handle);
    if (not hThread)
    {
        return exit("Failed to load the DLL", 1);
    }

	return exit("Successfully injected!", 0);
}

