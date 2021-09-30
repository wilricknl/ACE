#include "pch.hpp"
#include "Injector/Injector.hpp"

int main(int argc, char* argv[])
{
    injector::Injector injector;
    if (injector.Initialize(argc, argv))
    {
        return injector.Inject();
    }
    return 0;
}

