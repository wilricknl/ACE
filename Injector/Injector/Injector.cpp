#include "Injector.hpp"
#include <iostream>
#include "../Memory/Memory.hpp"
#include "../Utility/Utility.hpp"
#include "../version.hpp"

namespace injector
{
    /**
     * @p argc Argument count
     * @p argv Commandline arguments
     *
     * @return `true` if success, else `false`
     */
	bool Injector::Initialize(int argc, char* argv[])
	{
        options::options_description description{+
            "Allowed options"
        };
        description.add_options()
            ("help,h", "help message")
            ("version,v", "version")
            ("program,p", options::value<std::string>()->default_value("ac_client.exe"), "executable name")
            ("cheat,c", options::value<std::string>()->required(), "path to the cheat");

        try
        {
            options::store(options::parse_command_line(argc, argv, description), arguments);
            if (arguments.count("help"))
            {
                std::cout << description << '\n';
                return false;
            }
            if (arguments.count("version"))
            {
                std::cout << version::version << std::endl;
                return false;
            }
            options::notify(arguments);
            return true;
        }
        catch (std::exception& e)
        {
            std::cerr << "Error: " << e.what() << "\n";
            std::cout << "Use --help for more information\n";
        }
        catch (...)
        {
            std::cerr << "Unknown error!" << "\n";
        }

        return false;
	}

    /**
     * @return Exit value
     */
	int Injector::Run() const
	{
        DWORD processId;
        if (not memory::SelectProcessId(
            utility::to_wstring(arguments["program"].as<std::string>()).c_str(),
            processId))
        {
            return utility::Exit("Failed to find the executable", 1);
        }

        auto handle = OpenProcess(PROCESS_ALL_ACCESS, false, processId);
        if (handle == INVALID_HANDLE_VALUE)
        {
            return utility::Exit("Failed to acquire a handle", 1);
        }

        auto* location = VirtualAllocEx(handle, 0, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
        if (not location)
        {
            return utility::Exit("Failed to allocate memory", 1);
        }

        auto cheat = arguments["cheat"].as<std::string>();
        if (not WriteProcessMemory(handle, location, cheat.c_str(), cheat.size() + 1, nullptr))
        {
            return utility::Exit("Failed to write DLL path to memory", 1);
        }

        auto hThread = CreateRemoteThread(handle, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, location, 0, 0);
        CloseHandle(handle);
        if (not hThread)
        {
            return utility::Exit("Failed to load the DLL", 1);
        }

        return utility::Exit("Successfully injected!", 0);
	}
} // namespace injector
