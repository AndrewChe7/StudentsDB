#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include "Modules/Parser/interpreter.h"

int main(int argc, char **argv) {
    std::string f, f2;
    FILE* q1;
    FILE* q2;
    if (argc != 3) {
        printf("Usage: %s [DBfile] [Script]\n", argv[0]);
        return -1;
    }
    if ((q1 = fopen(argv[1], "r")) == nullptr) {
        printf("Can't open file %s\n", argv[1]);
        return -2;
    }
    if ((q2 = fopen(argv[2], "r")) == nullptr) {
        printf("Can't open file %s\n", argv[2]);
        return -2;
    }
    fclose(q1);
    fclose(q2);
    f = argv[1];
    f2 = argv[2];

    ParserModule::Interpreter i(f, f2);
    std::string res = i.parse();
    std::cout << res;
    return 0;
}