#include "Injector/Injector.hpp"
#include "Utility/Utility.hpp"

int main(int argc, char* argv[])
{
    injector::Injector injector;
    if (injector.Initialize(argc, argv))
    {
        return injector.Run();
    }
    return utility::Exit("Failed to intialize injector", 1);
}

