#include <iostream>

#include "pwgencc.h"

int main() {
    const pwgencc::Generator pwGenerator(15, pwgencc::PwOpts { });

    for (int i = 0; i < 20; ++i) {
        std::cout << pwGenerator.generate() << '\n';
    }

    return 0;
}