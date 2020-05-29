//
// Created by godknows on 17.05.2020.
//

#include "DB.h"
#include <fstream>
#include <sstream>
#include <algorithm>

void DB::DB::loadDB(const std::string& filename) {
    std::ifstream file(filename);
    for (auto student: students) {
        delete student;
    }
    students.clear();

    std::string line;
    std::string param;
    std::vector<std::string> data;
    std::getline(file, line);
    while (std::getline(file, line)) {
        std::stringstream lineStream(line);
        data.clear();
        while (std::getline(lineStream, param, ',')) {
            data.push_back(param);
        }
        auto* student = new Student(std::stoi(data[0]), data[1], data[2], std::stoi(data[3]),
                std::stoi(data[4]), (data[5] == "1"), data[6]);
        students.insert(student);
    }
    file.close();
}

std::string DB::DB::printDB() {
    std::string str;
    for (auto student: students) {
        str += student->print();
    }
    return str;
}

void DB::DB::unloadDB() {
    for (auto student: students) {
        delete student;
    }
    students.clear();
}

void DB::DB::saveDB(const std::string &filename) {
    std::ofstream file(filename);
    file << "id,first_name,last_name,group,course,isSettled,city" <<std::endl;
    for (auto student: students) {
        file << student->getCSVRepr() << std::endl;
    }
    file.close();
}

void DB::DB::add(Student* student) {
    students.insert(student);
}

int DB::DB::getFreeID() {
    std::vector<int> ids;
    for (auto student: students) {
        ids.push_back(student->id);
    }
    auto it = *std::max_element(std::begin(ids), std::end(ids));
    return it+1;
}

DB::DB* DB::DB::select(const std::string& fnamer, const std::string& lnamer, const std::string& cityr, int groupr, bool isSettledr, int mask) {
    DB* selectDB = new DB();
    bool isRight;
    for (auto student: students) {
        isRight = true;
        if ((mask % 2 != 0) && (student->first_name != fnamer)) {
            isRight = false;
        }
        if ((mask / 2 % 2 != 0) && (student->last_name != lnamer)) {
            isRight = false;
        }
        if ((mask / 4 % 2 != 0) && (student->city != cityr)) {
            isRight = false;
        }
        if ((mask / 8 % 2 != 0) && (student->group != groupr)) {
            isRight = false;
        }
        if ((mask / 16 % 2 != 0) && (student->isSettled != isSettledr)) {
            isRight = false;
        }
        if (isRight) {
            selectDB->add(student);
        }
    }
    return selectDB;
}

int DB::DB::insert(const std::string &fnamer, const std::string &lnamer, const std::string &cityr, int groupr,
                   bool isSettledr) {
    if (fnamer.empty() || lnamer.empty() || cityr.empty() || groupr == 0) {
        return -1;
    }
    auto* stud = new Student(this->getFreeID(), fnamer, lnamer, groupr, groupr/100, isSettledr, cityr);
    this->add(stud);
    return 0;
}

DB::DB* DB::DB::deletefromdb(const std::string &fnamer, const std::string &lnamer, const std::string &cityr, int groupr,
                         bool isSettledr, int mask) {
    DB* deleteDB = new DB();
    bool isRight;
    for (auto student: students) {
        isRight = true;
        if ((mask % 2 != 0) && (student->first_name != fnamer)) {
            isRight = false;
        }
        if ((mask / 2 % 2 != 0) && (student->last_name != lnamer)) {
            isRight = false;
        }
        if ((mask / 4 % 2 != 0) && (student->city != cityr)) {
            isRight = false;
        }
        if ((mask / 8 % 2 != 0) && (student->group != groupr)) {
            isRight = false;
        }
        if ((mask / 16 % 2 != 0) && (student->isSettled != isSettledr)) {
            isRight = false;
        }
        if (isRight) {
            students.erase(student);
            deleteDB->add(student);
        }
    }
    return deleteDB;
}
