cmake_minimum_required(VERSION 3.10)
project(StudentsDB)


set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-pthread")
find_package(Boost 1.40.0 REQUIRED system)
add_subdirectory(Modules)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/students.csv
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

include_directories(${CMAKE_CURRENT_BINARY_DIR}/Modules/Parser)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Modules/Parser)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/Modules/DB)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Modules/DB)

add_executable(parser justParser.cpp)
add_executable(generator generator.cpp)
add_executable(client client.cpp)
add_executable(server server.cpp)

target_link_libraries(client ${Boost_LIBRARIES})
target_link_libraries(server db_module parser_module server_module)
target_link_libraries(parser db_module parser_module)
target_link_libraries(generator db_module)
