#include "../pch.hpp"
#include "Utility.hpp"

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
} // namespace utility
