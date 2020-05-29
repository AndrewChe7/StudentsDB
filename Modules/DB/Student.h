//
// Created by godknows on 17.05.2020.
//

#ifndef PROJECT_STUDENT_H
#define PROJECT_STUDENT_H
#include <string>
#include <utility>
#include <iostream>
#include <iomanip>

namespace DB {
    class Student {
    public:
        Student(int i, std::string  fn, std::string  ln, int g, int c, bool s, std::string  ct) :
        id(i), first_name(std::move(fn)), last_name(std::move(ln)), group(g), course(c), isSettled(s), city(std::move(ct)) {}

        std::string print() const {
            std::ostringstream str;
            str << std::setfill('0') << std::setw(6) << id << " | " << first_name << " " << last_name << " | " << group << " " << course << " | " << (isSettled ? "TRUE" : "FALSE") << " | " << city << std::endl;
            return str.str();
        }

        std::string getCSVRepr () const {
            return std::to_string(id) + "," + first_name + "," + last_name + "," + std::to_string(group) + "," + std::to_string(course) + "," + std::to_string((isSettled)?1:0) + "," + city;
        }

        int id;
        std::string first_name;
        std::string last_name;
        int group;
        int course;
        bool isSettled;
        std::string city;
    };
}

#endif //PROJECT_STUDENT_H
