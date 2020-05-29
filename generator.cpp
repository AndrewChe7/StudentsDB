//
// Created by godknows on 20.05.2020.
//

#include <iostream>
#include <cstdio>
#include "Modules/DB/DB.h"
#include "Modules/DB/Generator.h"

int main(int argc, char **argv) {
    int count = 100;
    if (argc == 3) {
        std::string s = argv[2];
        count = std::stoi(s);
    } else if (argc != 2) {
        printf("Usage: %s <filename> <count=100>\n", argv[0]);
        return -1;
    }

    std::string fn = argv[1];
    DB::DB* db = DB::generateDB(count);
    db->printDB();
    db->saveDB(fn);
    db->unloadDB();
    return 0;
}
