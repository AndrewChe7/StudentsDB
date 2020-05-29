
include_directories(${CMAKE_CURRENT_BINARY_DIR}/../Parser)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/../DB)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../Parser)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../DB)
add_library(server_module STATIC newServer.cpp newServer.hpp)
target_link_libraries(server_module ${Boost_LIBRARIES} db_module parser_module)