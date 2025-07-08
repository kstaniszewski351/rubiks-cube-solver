#pragma once

#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/elements.hpp>
#include <cubie_cube.h>
#include <face_cube.h>

using namespace ftxui;

enum MoveDir
{
    MoveUp,
    MoveDown,
    MoveLeft,
    MoveRight,
};

struct Pos
{
    constexpr Pos(int x_, int y_) : x(x_), y(y_) {};
    int x;
    int y;
    bool operator==(const Pos& pos) const;
    bool operator!=(const Pos& pos) const;
    Pos operator+(const Pos& pos) const;
};

class CubeBase : public ComponentBase
{
public:
    explicit CubeBase(FaceCube& cube, int square_size, bool& input);
    Element OnRender() override;
    bool OnEvent(Event event) override;
    bool MoveCursor(MoveDir dir);
    void InputOn();
private:
    FaceCube& face_cube_;
    int square_size_;
    Pos cursor_pos_;
    Face to_set_;
    bool& input_;
};

Component Cube(FaceCube& cube, int square_size, bool& input);