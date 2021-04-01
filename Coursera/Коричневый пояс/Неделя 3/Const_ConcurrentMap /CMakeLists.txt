cmake_minimum_required(VERSION 3.0.0)
project(const_concurrent_map VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread")

include(CTest)
enable_testing()

add_executable(const_concurrent_map main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
