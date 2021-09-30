#include "../pch.hpp"
#include "Memory.hpp"

namespace memory
{
	/**
	 * @p processName The name of the process which should be found
	 * @p processId Out parameter to pass the process id
	 *
	 * @return `true` if succeeded, else `false`
	 */
	BOOL SelectProcessId(const TCHAR* processName, DWORD& processId)
	{
		std::vector<DWORD> processes;
		if (ListProcesses(processName, processes))
		{
			unsigned int choice{};
			do
			{
				std::wcout << "The following PIDs match " << processName << ":\n\n";
				for (size_t i = 0; i < processes.size(); ++i)
				{
					std::cout << std::dec << " [" << (i + 1) << "] 0x"
						<< std::hex << std::uppercase << processes[i] << '\n';
				}
				std::cout << "\nSelect a PID: ";
				std::cin >> choice;
			} while (choice == 0 or choice > processes.size());

			processId = processes.at(choice - 1);
			return TRUE;
		}

		return FALSE;
	}

	/**
	 * @p processName The name of the process which should be found
	 * @p processes Out parameter to store the matching processes
	 *
	 * @return `true` if succeeded, else `false`
	 */
	BOOL ListProcesses(const TCHAR* processName, std::vector<DWORD>& processes)
	{
		HANDLE hProcessSnap = INVALID_HANDLE_VALUE;
		PROCESSENTRY32 pe32;
		pe32.dwSize = sizeof(pe32);

		hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (hProcessSnap == INVALID_HANDLE_VALUE)
		{
			return FALSE;
		}

		if (not Process32First(hProcessSnap, &pe32))
		{
			CloseHandle(hProcessSnap);
			return FALSE;
		}

		do
		{
			if (not _wcsicmp(pe32.szExeFile, processName))
			{
				processes.push_back(pe32.th32ProcessID);
			}
		} while (Process32Next(hProcessSnap, &pe32));

		return not processes.empty();
	}
} // namespace memory
