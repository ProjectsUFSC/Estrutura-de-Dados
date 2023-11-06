cmake_minimum_required(VERSION 3.0.0)
project(dec0006 VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)

include(CTest)
enable_testing()

find_package(PkgConfig REQUIRED)
pkg_search_module(GTEST REQUIRED gtest)

if( GTEST_FOUND )
    include_directories(${GTEST_INCLUDE_DIRS})
    link_directories(${GTEST_LIBRARY_DIRS})
    message(STATUS "Using GTest ${GTEST_VERSION}")
endif()

add_executable(main main.cpp)
target_link_libraries(main ${GTEST_LIBRARIES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
include(CPack)