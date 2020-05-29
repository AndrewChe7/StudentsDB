set(DB_SOURCES DB.cpp Generator.cpp)
set(DB_HEADERS DB.h Student.h Generator.h)

add_library(db_module STATIC ${DB_SOURCES} ${DB_HEADERS})

