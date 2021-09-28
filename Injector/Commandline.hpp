#pragma once
#include <boost/program_options.hpp>

namespace cmd
{
    namespace options = boost::program_options;

    /** @brief Parse commandline arguments
     */
	bool ParseArguments(
        int argc,
        char* argv[],
        options::variables_map& variables);
} // namespace cmd
