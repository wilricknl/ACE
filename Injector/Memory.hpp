#pragma once
#include <Windows.h>
#include <vector>

namespace memory
{
	/** @brief Select the process id on commandline
	 */
	BOOL SelectProcessId(const TCHAR* processName, DWORD& processId);
	/** @brief Find all the processes with @ref processName
	 */
	BOOL ListProcesses(const TCHAR* processName, std::vector<DWORD>& processes);
} // namespace memory
