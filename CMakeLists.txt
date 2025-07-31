cmake_minimum_required(VERSION 3.25)
set(CMAKE_CXX_STANDARD 20)

project(cube)
find_package(GTest REQUIRED)
enable_testing()

#ftxui
include(FetchContent)
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG v6.1.9
)
FetchContent_MakeAvailable(ftxui)

add_library(libcube STATIC
    src/libcube/cubie_cube.cpp
    src/libcube/face_cube.cpp
    src/libcube/move_table.cpp
    src/libcube/coords/edge_flip_generator.cpp
    src/libcube/coords/corner_twist_generator.cpp
    src/libcube/coords/ud_slice_pos_generator.cpp
    src/libcube/coords/ud_slice_perm_generator.cpp
    src/libcube/coords/corner_perm_generator.cpp
    src/libcube/coords/ud_perm_generator.cpp
    src/libcube/pruning.cpp
    src/libcube/phase1.cpp
    src/libcube/phase2.cpp
    src/libcube/multi_index.cpp
)
target_include_directories(libcube PUBLIC src/libcube)

add_executable(app
    src/app/main.cpp
    src/app/ui.cpp
    src/app/cube.cpp
)
target_include_directories(app PUBLIC
    src/app
)
target_link_Libraries(app
    libcube
    ftxui::component
    ftxui::dom
    ftxui::screen
)


#tests
add_executable(lehmer_code src/tests/lehmer_code.cpp)
target_link_libraries(lehmer_code libcube)

add_executable(bicoeff src/tests/bicoeff.cpp)
target_link_libraries(bicoeff libcube)

add_executable(combination src/tests/combination.cpp)
target_link_libraries(combination libcube)

add_executable(pruning src/tests/test_pruning.cpp)
target_link_libraries(pruning libcube)

add_executable(test_solver src/tests/test_solver.cpp)
target_link_libraries(test_solver libcube)

add_executable(tests
    src/tests/test_coords.cpp
)
target_link_libraries(tests
    GTest::gtest_main
    libcube
)
include(GoogleTest)
gtest_discover_tests(tests PROPERTIES DISCOVERY_TIMEOUT 1000)