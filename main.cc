#include <iostream>
#include <exception>
#include <boost/program_options.hpp>

#include "pwgencc.h"

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

        if (varMap.count(HELP_OPT)) {
            std::cout << desc << std::endl;
            return 0;
        }

        if (varMap.count(EXCLUDE_UPPER_OPT)) {
            pwOpts.useUpperCase = false;
        }

        if (varMap.count(EXCLUDE_LOWER_OPT)) {
            pwOpts.useLowerCase = false;
        }

        if (varMap.count(EXCLUDE_NUMBERS_OPT)) {
            pwOpts.useNumbers = false;
        }

        if (varMap.count(EXCLUDE_SYMBOLS_OPT)) {
            pwOpts.useSymbols = false;
        }

        
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