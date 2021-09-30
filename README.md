# ACE
Assault Cube Enhancement is a cheat for Assault Cube and provides triggerbot, aimbot, ESP, and more. ACE is developed with C++ in Visual Studio Community 2019.

## Building

### Requirements

- [Visual Studio Community 2019](https://visualstudio.microsoft.com/) with the *Desktop development with C++* workload
- [Boost 1.77.0](https://www.boost.org/users/history/version_1_77_0.html)

### ACE

* Build the ACE project in Visual Studio for x86 in either Debug or Release mode

### Injector

1. [Download Boost 1.77.0](https://www.boost.org/users/history/version_1_77_0.html)
2. Create an environment variable BOOST_ROOT that points to the Boost root folder
3. Run bootstrap.bat in the Boost root folder
4. Run b2.exe that is created during the previous step in the Boost root folder
5. Build the Injector project in Visual Studio for x86 in either Debug or Release mode

## Usage

### Injection

1. Make sure Assault Cube is running
2. Execute `Injector.exe --cheat C:\path\to\ACE.dll`

### Saving a configuration

The provided commandline arguments can be saved by specifying `--save`. E.g. `Injector.exe --cheat C:\path\to\ACE.dll --save`. 
This will create `settings.ini` in the same folder as `Injector.exe` containing the target executable's name and the path to the cheat.

### Injection using a configuration

When a configuration is saved the Injector can be run by executing `Injector.exe` without arguments.

### Help

For detailed information about the injector's options execute `Injector.exe --help`.

## More information

For more information on programs like this visit the following websites:
* [Unknown Cheats](https://www.unknowncheats.me/)
* [Guided Hacking](https://guidedhacking.com/)
