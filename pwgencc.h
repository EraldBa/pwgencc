#pragma once

#include <string>
#include <cstdint>

namespace pwgencc {
    struct PwOpts {
        bool useLowerCase   {true};
        bool useUpperCase   {true};
        bool useNumbers     {true};
        bool useSymbols     {true};
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