#include <cstdint>
#include <exception>
#include <iostream>
#include <boost/program_options.hpp>

#include "pwgen.h"

namespace propts = boost::program_options;
    
constexpr const char *EXCLUDE_UPPER_OPT   = "xupper",
                     *EXCLUDE_LOWER_OPT   = "xlower",
                     *EXCLUDE_NUMBERS_OPT = "xnumbers",
                     *EXCLUDE_SYMBOLS_OPT = "xsymbols",
                     *PWLEN_OPT           = "pwlen",
                     *REPEAT_OPT          = "repeat",
                     *HELP_OPT            = "help";

int main(int argc, char *argv[]) {
    pwgencc::PwOpts pwOpts;
    uint32_t pwLen, repeat;

    try {
        propts::options_description desc("All options");

        desc.add_options()
        (HELP_OPT,              "Prints this help message")
        (EXCLUDE_UPPER_OPT,     "Exclude uppercase characters")
        (EXCLUDE_LOWER_OPT,     "Exclude lowercase characters")
        (EXCLUDE_NUMBERS_OPT,   "Exclude numbers")
        (EXCLUDE_SYMBOLS_OPT,   "Exclude symbols")
        (PWLEN_OPT,     propts::value<uint32_t>(),  "Length of random password")
        (REPEAT_OPT,    propts::value<uint32_t>(),  "How many passwords to generate");


        propts::variables_map varMap;
        propts::store(propts::parse_command_line(argc, argv, desc), varMap);

        propts::notify(varMap);

        boost::any(0);

        if (varMap.contains(HELP_OPT)) {
            std::cout << desc << std::endl;
            return 0;
        }

        pwOpts.useUpperCase = !varMap.contains(EXCLUDE_UPPER_OPT);
        pwOpts.useLowerCase = !varMap.contains(EXCLUDE_LOWER_OPT);
        pwOpts.useNumbers = !varMap.contains(EXCLUDE_NUMBERS_OPT);
        pwOpts.useSymbols = !varMap.contains(EXCLUDE_SYMBOLS_OPT);

        
        pwLen = varMap.count(PWLEN_OPT) 
                ? varMap[PWLEN_OPT].as<uint32_t>() 
                : 15;

         
        repeat = varMap.count(REPEAT_OPT) 
                ? varMap[REPEAT_OPT].as<uint32_t>() 
                : 10;


    } catch(const std::exception& e) {
        std::cerr << "Error occured with exception: " << e.what() << std::endl;
        return 1;
    } catch(...) {
        std::cerr << "Unknown exception occured." << std::endl;
        return 1;
    }

    const pwgencc::Generator pwGenerator(pwLen, pwOpts);

    for (uint32_t i = 0; i < repeat; ++i) {
        std::cout << pwGenerator.generate() << '\n';
    }

    return 0;
}
