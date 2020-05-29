//
// Created by godknows on 17.05.2020.
//

#include "Generator.h"
#include <cstdlib>
#include <ctime>

DB::DB* DB::generateDB(int count) {
    DB* db = new DB();
    std::vector<std::string> fn;
    std::vector<std::string> ln;
    std::vector<std::string> ct;
    int courses = 5;
    int groups = 9;
    int id = 0;
    int i;
    srand (time(nullptr));

    fn.push_back("Антон");
    fn.push_back("Иван");
    fn.push_back("Петр");
    fn.push_back("Андрей");
    fn.push_back("Изя");
    fn.push_back("Владимир");
    fn.push_back("Пахом");
    fn.push_back("Герман");
    fn.push_back("Лейба");
    fn.push_back("Иосиф");
    fn.push_back("Геннадий");
    fn.push_back("Дмитрий");

    ln.push_back("Перельман");
    ln.push_back("Блюменталь");
    ln.push_back("Резник");
    ln.push_back("Левин");
    ln.push_back("Фишер");
    ln.push_back("Каплан");
    ln.push_back("Шустер");
    ln.push_back("Поляк");
    ln.push_back("Берг");

    ct.push_back("Москва");
    ct.push_back("Иерусалим");
    ct.push_back("Рязань");
    ct.push_back("Пермь");
    ct.push_back("Псков");
    ct.push_back("Омск");
    ct.push_back("Киев");

    for (i = 0; i < count; i++) {
        int fn_num = rand() % fn.size();
        int ln_num = rand() % ln.size();
        int ct_num = rand() % ct.size();
        int c = rand() % 5 + 1;
        int g = rand() % 9;

        auto student = new Student(id++, fn[fn_num], ln[ln_num], 10 + c*100 + g, c, (ct_num != 0) , ct[ct_num]);
        db->add(student);
    }
    return db;
}

