#include "Utility.hpp"
#include <iostream>

namespace utility
{
	/**
	 * @p string `std::string` to be converted to `std::wstring`
	 *
	 * @return `std::wstring`
	 */
	std::wstring to_wstring(std::string string)
	{
		return std::wstring{ string.begin(), string.end() };
	}

	/**
	 * @p message The message to print
	 * @p value The return value
	 *
	 * @return Return @ref value
	 */
	int Exit(std::string message, int value)
	{
		std::cout << message << '\n';
		return value;
	}
} // namespace utility
