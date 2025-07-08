#pragma once

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <cubie_cube.h>
#include <face_cube.h>


using namespace ftxui;

class UI
{
public:
    UI();
    void Run();
private:
    Component main_component_;
    ScreenInteractive screen_;
    CubieCube cube_;
    FaceCube face_cube_;
    std::vector<Move> scramble_;
};