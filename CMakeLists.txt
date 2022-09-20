cmake_minimum_required(VERSION 3.20)
project(2)

set(CMAKE_CXX_STANDARD 14)
include_directories(D:/Environment/include)
link_directories(D:/Environment/lib)
add_executable(2 CRT.hpp LWE.hpp MyTools.hpp MyLWE.hpp TestMyLWE.cpp)
target_link_libraries(2 NTL2.a)
