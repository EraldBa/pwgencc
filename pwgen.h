#pragma once

#include <string>
#include <cstdint>

namespace pwgencc {
    struct PwOpts {
        bool useLowerCase;
        bool useUpperCase;
        bool useNumbers;
        bool useSymbols;
    };

    class Generator {
        public:
            Generator(uint32_t pwlen, const PwOpts& pwOpts);
            std::string generate() const noexcept;

        private:
            std::string seed;
            uint32_t pwLen;
    };
}
