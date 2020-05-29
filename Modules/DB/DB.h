//
// Created by godknows on 17.05.2020.
//

#ifndef PROJECT_DB_H
#define PROJECT_DB_H
#include <vector>
#include <set>
#include "Student.h"


namespace DB {
    class DB {
    private:
        std::set<Student*> students;
    public:
        void loadDB (const std::string& filename);
        void saveDB (const std::string& filename);
        std::string printDB ();
        void unloadDB ();
        void add (Student* student);

        DB* select (const std::string& fnamer, const std::string& lnamer, const std::string& cityr, int groupr, bool isSettledr, int mask);
        int insert (const std::string& fnamer, const std::string& lnamer, const std::string& cityr, int groupr, bool isSettledr);
        DB* deletefromdb (const std::string& fnamer, const std::string& lnamer, const std::string& cityr, int groupr, bool isSettledr, int mask);
        int getFreeID ();
    };
}


#endif //PROJECT_DB_H
