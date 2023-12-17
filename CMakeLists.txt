cmake_minimum_required(VERSION 3.27)
project(FJSP)

set(CMAKE_CXX_STANDARD 23)

add_executable(FJSP main.cpp json/json.hpp json/json_fwd.hpp
        utils.cpp
        utils.h
        Item.cpp
        Item.h
        Job.cpp
        Job.h
        Solution.cpp
        Solution.h)
