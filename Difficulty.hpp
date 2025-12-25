#pragma once

struct Difficulty
{
    int width;
    int height;
    int mines;
};

// Готовые пресеты сложностей
namespace Difficulties
{
    const Difficulty Easy   { 9,  9,  10 };
    const Difficulty Medium { 16, 16, 40 };
    const Difficulty Hard   { 30, 16, 99 };
}