#include <iostream>
#include <fstream>
#include "gameplay.h"

int main(int argc, char** argv) {

    try {

        std::unique_ptr<gameplay> g;
        if (argc < 3 || argc > 4) {
            std::cerr << "There should be 2 or 3 arguments\n";
            return 0;
        }
        if (argc == 4) {
            std::ifstream infile(argv[3]);

            if (!infile.good()) {
                std::cerr << "Bad file\n";
                return 0;
            }
            g = std::make_unique<gameplay>(argv[1], argv[2], argv[3]);
        }
        if (argc == 3) {
            g = std::make_unique<gameplay>(argv[1], argv[2]);
        }

        g->start();

    } catch (const char * w) {
        std::cout << "Wyjatek: " << w;
    }
    return 0;
}