#include <random>
#include <vector>

#include "pwgencc.h"

pwgencc::Generator::Generator(uint32_t pwlen, const PwOpts& pwOpts): pwLen(pwlen) {
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

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, seedLen);

    std::string password;
    password.reserve(this->pwLen);

    for (uint32_t i = 0; i < this->pwLen; ++i) {
        char randChar;

        do {
            randChar = this->seed[dis(gen)];
        } while (useUniqueChars && password.find(randChar) != std::string::npos);

        password += randChar;
    }

    return std::move(password);
}
