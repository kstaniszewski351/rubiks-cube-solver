#pragma once

#include <array>
#include <string>
#include "ftxui/screen/color.hpp"
#include "defs.h"

constexpr std::array<char, FaceCount> FACE_NAMES
{
    'U',
    'D',
    'R',
    'L',
    'F',
    'B'
};

constexpr std::array<std::string_view, 18> MOVE_NAMES
{
    "U",
    "U2",
    "U'",
    "D",
    "D2",
    "D'",
    "R",
    "R2",
    "R'",
    "L",
    "L2",
    "L'",
    "F",
    "F2",
    "F'",
    "B",
    "B2",
    "B'"
};