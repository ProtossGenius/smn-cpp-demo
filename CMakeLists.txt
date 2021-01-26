cmake_minimum_required(VERSION 2.6)

project (smn-rip-demo)

SET(CXX_FLAGS -g2 -ggdb -Wall -Werror)

add_executable(smn-rip-demo main.cpp)
target_link_libraries(smn-rip-demo ric_code ric_pb smncpp protobuf pthread)

add_subdirectory(ric_code)
