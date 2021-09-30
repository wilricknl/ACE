#include "../pch.hpp"
#include "Injector.hpp"
#include "../Memory/Memory.hpp"
#include "../Utility/Utility.hpp"
#include "../version.hpp"

namespace injector
{
    namespace options = boost::program_options;
    namespace property = boost::property_tree;

    /**
     * @p argc Argument count
     * @p argv Commandline arguments
     *
     * @return `true` if success, else `false`
     */
	bool Injector::Initialize(int argc, char* argv[])
	{
        if (argc == 1)
        {
            return LoadIni();
        }

        options::options_description description{+
            "Allowed options"
        };
        description.add_options()
            ("program,p", options::value<std::string>()->default_value("ac_client.exe"), "executable name")
            ("cheat,c", options::value<std::string>()->required(), "path to the cheat")
            ("save,s", "save provided arguments to an ini file")
            ("help,h", "help message")
            ("version,v", "version");

		try
        {
            options::variables_map arguments;
            options::store(options::parse_command_line(argc, argv, description), arguments);
            if (arguments.count("help"))
            {
                std::cout << description << '\n';
                return false;
            }
            if (arguments.count("version"))
            {
                return utility::Exit(version::version, false);
            }
            if (not arguments.count("cheat"))
            {
                return utility::Exit("Provide a path to the cheat\n", false);
            }

            program = arguments["program"].as<std::string>();
            cheat = arguments["cheat"].as<std::string>();

            if (not boost::filesystem::exists(cheat))
            {
                return utility::Exit("Could not find: " + cheat, false);
            }

            if (arguments.count("save"))
            {
                SaveIni();
            }

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
	int Injector::Inject() const
	{
        DWORD processId;
        if (not memory::SelectProcessId(
            utility::to_wstring(program).c_str(),
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

    /**
     * @return `true` if success, else `false`
     */
	bool Injector::LoadIni()
	{
        if (not boost::filesystem::exists("settings.ini"))
        {
            return utility::Exit("Could not find settings.ini", false);
        }

        property::ptree settings;
        read_ini("settings.ini", settings);
        if (not settings.empty())
        {
            try
            {
        		program = settings.get<std::string>("Injector.program");
				cheat = settings.get<std::string>("Injector.cheat");
                return true;
            }
            catch(std::exception& e)
            {
                std::cout << "Error: " << e.what() << '\n';
                return utility::Exit("The ini file is corrupt. Regenerate the ini file using --save", false);
            }
        }
        return utility::Exit("No suitable ini file found. Use --help for more information", false);
	}

	void Injector::SaveIni() const
	{
        std::fstream ini{ "settings.ini",  std::ofstream::out|std::ofstream::trunc };
        if (ini.is_open())
        {
            std::string content{ "[Injector]\nprogram=" + program + "\ncheat=" + cheat };
            ini.write(content.c_str(), content.size());
        }
	}
} // namespace injector
