cmake_minimum_required(VERSION 3.25)
set(CMAKE_CXX_STANDARD 20)

project(cube)

include(FetchContent)
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG v6.1.9
)
FetchContent_MakeAvailable(ftxui)

add_library(libcube STATIC
    src/libcube/coord_cube.cpp
    src/libcube/coord_moves.cpp
    src/libcube/cubie_cube.cpp
    src/libcube/util.cpp
    src/libcube/face_cube.cpp
    src/libcube/symmetry.cpp
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