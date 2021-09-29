#pragma once
#include <boost/program_options.hpp>

namespace injector
{
	namespace options = boost::program_options;

	class Injector
	{
	public:
		Injector() = default;
		bool Initialize(int argc, char* argv[]);
		int Run() const;
	private:
		options::variables_map arguments;
	};
} // namespace injector
