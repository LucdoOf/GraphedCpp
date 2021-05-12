cmake_minimum_required(VERSION 3.17)
project(GraphedCpp)

set(CMAKE_CXX_STANDARD 14)

include_directories(includes)

add_executable(GraphedCpp
        src/utils/CGraphException.cpp
        includes/CGraphException.h
        src/core/CGraphReader.cpp
        includes/CGraphReader.h
        includes/CSommet.h
        src/core/CSommet.cpp
        includes/CArc.h
        src/core/CArc.cpp
        includes/CGraphe.h
        src/core/CGraphe.cpp
        includes/defines.h
        src/main.cpp
        src/utils/string_utils.cpp
        includes/string_utils.h)