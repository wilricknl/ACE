#pragma once
#include <iostream>
#include <string>

namespace utility
{
	/** @brief Convert std::string to std::wstring
	 */
	std::wstring to_wstring(std::string string);

	/** @brief Exit with printing a message
	 *
	 * @p message The message to print
	 * @p value The return value
	 *
	 * @return Return @ref value
	 */
	template<typename T>
	T Exit(std::string message, T value)
	{
		std::cout << message << '\n';
		return value;
	}
} // namespace utility
