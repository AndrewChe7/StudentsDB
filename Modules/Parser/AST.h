//
// Created by godknows on 18.05.2020.
//

#ifndef PROJECT_AST_H
#define PROJECT_AST_H
#include <utility>
#include <vector>
#include <string>
#include <iostream>
#include "../DB/DB.h"

namespace AST {
    class Param {
    public:
        std::string name;
        std::string value;
        Param() = default;
        Param(std::string n, std::string val) : name(std::move(n)), value(std::move(val)) {}
    };

    class Operation {
    public:
        std::string fn;
        std::string ln;
        std::string ct;
        bool isSettled;
        int group;
        int mask = 0;
        void addParam (const Param& param) {
            if (param.name == "first_name") {
                fn = param.value;
                mask += 1;
            }
            else if (param.name == "last_name") {
                ln = param.value;
                mask += 2;
            }
            else if (param.name == "city") {
                ct = param.value;
                mask += 4;
            }
            else if (param.name == "settled") {
                isSettled = (param.value == "TRUE");
                mask += 16;
            }
            else if (param.name == "group") {
                group = std::stoi(param.value);
                mask += 8;
            }
            else {
                std::cout << "Unknown Parameter: " << param.name << std::endl;
            }
        }
        virtual std::string execute (DB::DB* db) { return ""; }
    };

    class OperationSelect : public Operation {
        std::string execute(DB::DB* db) override {
            DB::DB* res = db->select(fn, ln, ct, group, isSettled, mask);
            std::string data = res->printDB();
            data += "\n";
            delete res;
            return data;
        }
    };

    class OperationInsert : public Operation {
        std::string execute(DB::DB* db) override {
            int res = db->insert(fn, ln, ct, group, isSettled);
            if (res == 0) {
                return "OK\n";
            } else {
                return "NOT OK\n";
            }
        }
    };

    class OperationDelete : public Operation {
        std::string execute(DB::DB* db) override {
            db->deletefromdb(fn, ln, ct, group, isSettled, mask);
            return "OK\n";
        }
    };
}

#endif //PROJECT_AST_H
