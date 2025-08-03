#include <ftxui/dom/canvas.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>
#include "cube.h"
#include "const.h"


CubeBase::CubeBase(FaceCube& cube, int square_size, bool& input)
: face_cube_(cube), square_size_(square_size), cursor_pos_(3, 3), input_(input), to_set_(FaceCount)
{

}

const std::array<Pos, FaceCount> face_pos
{{
    Pos(1, 1),
    Pos(3, 1),
    Pos(1, 0),
    Pos(1, 2),
    Pos(2, 1),
    Pos(0, 1)
}};

Element CubeBase::OnRender()
{

    const std::array<Color, FaceCount> face_colors
    {{
        Color::White,
        Color::Yellow,
        Color::Red,
        Color::Orange1,
        Color::Green,
        Color::Blue
    }};

    auto can = Canvas(3 * 4 * square_size_, 3 * 3 * square_size_);

    for(int f = 0; f < FaceCount; f++)
    {
        for(int i = 0; i < 9; i++)
        {
            auto tile_pos = Pos(i % 3 + face_pos[f].x * 3, i / 3 + face_pos[f].y * 3);
            
            Face c;
            if(i == center_facelet)
            {
                c = static_cast<Face>(f);
            }
            else if( i > center_facelet)
            {
                c = face_cube_.facelets[f * facelet_count + i - 1];
            }
            else
            {
                c = face_cube_.facelets[f * facelet_count + i];
            }

            if(tile_pos == cursor_pos_ && to_set_ != FaceCount)
            {
                face_cube_.facelets[f * facelet_count + c] = to_set_;
                c = to_set_;
                to_set_ = FaceCount;
            }

            for(int px = 0; px < square_size_; px++)
            {
                for(int py = 0; py < square_size_; py++)
                {
                    can.DrawBlock(tile_pos.x * square_size_ + px, tile_pos.y * square_size_ + py, true, face_colors[c]);
                }
            }
        }
    }

    if(input_)
    {
        can.DrawBlock(cursor_pos_.x * square_size_, cursor_pos_.y * square_size_, true, Color::White);
    }

    return canvas(can);
}

bool CubeBase::OnEvent(Event event)
{
    if(input_ == false) {return false;}

    if(event == Event::ArrowUp)
    {
        return MoveCursor(MoveUp);
    }
    else if(event == Event::ArrowDown)
    {
        return MoveCursor(MoveDown);
    }
    else if(event == Event::ArrowLeft)
    {
        return MoveCursor(MoveLeft);
    }
    else if(event == Event::ArrowRight)
    {
        return MoveCursor(MoveRight);
    }
    else if(event.is_character())
    {
        char c = event.character()[0];

        auto result = std::ranges::find(FACE_NAMES, c);
        if(result == FACE_NAMES.end()) {return false;}

        to_set_ = static_cast<Face>(std::distance(FACE_NAMES.begin(), result));
        return true;
    }
    else
    {
        return false;
    }
}

bool CubeBase::MoveCursor(MoveDir dir)
{
    constexpr std::array<Pos, 4> dir_map
    {{
        Pos(0, -1),
        Pos(0, 1),
        Pos(-1, 0),
        Pos(1, 0)
    }};
    
    auto new_pos = Pos(cursor_pos_ + dir_map[dir]);

    if(new_pos.x >= 0 && new_pos.y >= 0 && new_pos.x <= 3 * 4 && new_pos.y <= 3 * 3)
    {
        cursor_pos_ = new_pos;
        return true;
    }
    else
    {
        return false;
    }
}

void CubeBase::InputOn()
{
    input_ = true;
}


Component Cube(FaceCube& cube, int square_size, bool& input)
{
    return Make<CubeBase>(cube, square_size, input);
};

bool Pos::operator==(const Pos& pos) const
{
    return (x == pos.x && y == pos.y);
}

bool Pos::operator!=(const Pos& pos) const
{
    return !operator==(pos);
}

Pos Pos::operator+(const Pos& pos) const
{
    return Pos(x + pos.x, y + pos.y);
}
