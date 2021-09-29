#include "Commandline.hpp"
#include <iostream>
#include "version.hpp"

namespace cmd
{
    /**
     * @p argc Argument count
     * @p argv Arguments
     * @p variables Out parsed variables
     *
     * @return `true` if success, else `false`
     */
    bool ParseArguments(
        int argc,
        char* argv[],
        options::variables_map& variables)
    {
        options::options_description description{
            "Allowed options"
        };
        description.add_options()
            ("help,h", "help message")
			("version,v", "version")
            ("program,p", options::value<std::string>()->default_value("ac_client.exe"), "executable name")
            ("cheat,c", options::value<std::string>()->required(), "path to the cheat");

        try
        {
            options::store(options::parse_command_line(argc, argv, description), variables);
            if (variables.count("help"))
            {
                std::cout << description << '\n';
                return false;
            }
            if (variables.count("version"))
            {
                std::cout << version::version << std::endl;
                return false;
            }
            options::notify(variables);
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
} // namespace cmd