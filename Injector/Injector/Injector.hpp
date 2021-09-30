#pragma once
#include <string>

namespace injector
{
	/** @brief Injector injects DLLs into other program
	 */
	class Injector
	{
	public:
		Injector() = default;
		/** @brief Setup the injector for injection
		 */
		bool Initialize(int argc, char* argv[]);
		/** @brief Attempt the injection
		 */
		int Inject() const;
	private:
		/** @brief Load settings from the ini file
		 */
		bool LoadIni();
		/** @brief Save the arguments as ini file
		 */
		void SaveIni() const;
	private:
		std::string program; ///< Program where the cheat will be injected
		std::string cheat; ///< Path to the cheat DLL
	};
} // namespace injector
