#include <iostream>
#include "Commandline.hpp"

int main(int argc, char* argv[])
{
    cmd::options::variables_map variables;
    if (cmd::ParseArguments(argc, argv, variables))
    {
        return 0;
    }
    return 1;
}

