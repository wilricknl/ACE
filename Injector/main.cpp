#include <iostream>
#include "Commandline.hpp"
#include "Memory.hpp"

int exit(std::string message, int value)
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
        to_wstring(variables["executable"].as<std::string>()).c_str(), 
        processId))
    {
		return exit("Failed to find the executable", 1);
    }

	std::cout << "Process id: " << std::to_string(processId) << '\n';
}

