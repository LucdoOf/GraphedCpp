cmake_minimum_required(VERSION 3.17)
project(MatrixedCpp)

set(CMAKE_CXX_STANDARD 14)

include_directories(includes)

add_executable(MatrixedCpp
        includes/CMatrix.h
        src/utils/CMatrixException.cpp
        includes/CMatrixException.h
        src/core/CMatrixReader.cpp
        includes/CMatrixReader.h
        includes/defines.h
        src/main.cpp
        src/utils/string_utils.cpp
        includes/string_utils.h)
