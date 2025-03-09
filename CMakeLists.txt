cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 20)

project(cube)
enable_testing()

find_package(GTest REQUIRED)


add_library(libcube STATIC
    src/libcube/coord_cube.cpp
    src/libcube/coord_moves.cpp
    src/libcube/cubie_cube.cpp
    src/libcube/util.cpp
)
target_include_directories(libcube PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/libcube)


add_executable(main
    src/test/main.cpp
)
target_link_Libraries(main libcube)


add_executable(cubetest
    src/test/test.cpp
)
target_Link_libraries(cubetest libcube GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(cubetest)