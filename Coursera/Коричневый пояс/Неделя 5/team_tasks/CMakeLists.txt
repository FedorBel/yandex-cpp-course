cmake_minimum_required(VERSION 3.0.0)
project(team_tasks VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(team_tasks main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
