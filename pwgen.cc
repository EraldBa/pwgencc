#include <cstdint>
#include <string>
#include <boost/random/random_device.hpp>
#include <boost/random/uniform_int_distribution.hpp>

#include "pwgen.h"

pwgencc::Generator::Generator(uint32_t pwlen, const PwOpts& pwOpts)
    : pwLen(pwlen) {
    if (pwOpts.useLowerCase) {
        this->seed += "abcdefghijklmnopqrstuvwxyz";
    }

    if (pwOpts.useUpperCase) {
        this->seed += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    }

    if (pwOpts.useNumbers) {
        this->seed += "0123456789";
    }

    if (pwOpts.useSymbols) {
        this->seed += "!@#$%^&*()<>,./";
    }
}

std::string pwgencc::Generator::generate() const noexcept {
    const size_t seedLen = this->seed.length();
    if (seedLen == 0) {
        return "";
    }

    const bool useUniqueChars = this->pwLen < seedLen; 

    boost::random::random_device randomDevice;
    boost::random::uniform_int_distribution<> dis(0, seedLen);

    std::string password;
    password.reserve(this->pwLen);

    for (uint32_t i = 0; i < this->pwLen; ++i) {
        char randChar;

        do {
            randChar = this->seed[dis(randomDevice)];
        } while (useUniqueChars && password.contains(randChar));

        password += randChar;
    }

    return password;
}
