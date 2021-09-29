#pragma once
#include <string>

namespace utility
{
	/** @brief Convert std::string to std::wstring
	 */
	std::wstring to_wstring(std::string string);
	/** @brief Exit with printing a message
	 */
	int Exit(std::string message, int value);
} // namespace utility
