#include "Field.hpp"
#include <cstdlib>
#include <ctime>
#include <cmath>

static const int SIZE = 32;

Field::Field(int w, int h, int m)
    : width(w), height(h), mines(m)
{
    std::srand((unsigned)std::time(nullptr));
    reset();
}

void Field::reset()
{
    cells.assign(height, std::vector<Cell>(width));
    gameOver = false;
    firstClick = true;
    setOffset(offsetX, offsetY);
}

bool Field::isGameOver() const
{
    return gameOver;
}

bool Field::inside(int x, int y) const
{
    return x >= 0 && y >= 0 && x < width && y < height;
}

void Field::setOffset(int x, int y)
{
    offsetX = x;
    offsetY = y;

    for (int y = 0; y < height; ++y)
        for (int x = 0; x < width; ++x)
            cells[y][x].setPosition(
                offsetX + x * SIZE,
                offsetY + y * SIZE
            );
}

void Field::generate(int sx, int sy)
{
    int placed = 0;
    while (placed < mines)
    {
        int x = rand() % width;
        int y = rand() % height;

        if (std::abs(x - sx) <= 1 && std::abs(y - sy) <= 1)
            continue;

        if (!cells[y][x].hasMine())
        {
            cells[y][x].placeMine();
            placed++;
        }
    }
}

void Field::count()
{
    for (int y = 0; y < height; ++y)
        for (int x = 0; x < width; ++x)
        {
            if (cells[y][x].hasMine())
                continue;

            int c = 0;
            for (int dy = -1; dy <= 1; ++dy)
                for (int dx = -1; dx <= 1; ++dx)
                    if (inside(x + dx, y + dy) &&
                        cells[y + dy][x + dx].hasMine())
                        c++;

            cells[y][x].setMinesAround(c);
        }
}

void Field::open(int x, int y)
{
    if (!inside(x, y))
        return;

    Cell& cell = cells[y][x];
    if (cell.isOpened() || cell.hasFlag())
        return;

    cell.open();

    if (cell.hasMine())
    {
        gameOver = true;
        return;
    }

    if (cell.getMinesAround() == 0)
        for (int dy = -1; dy <= 1; ++dy)
            for (int dx = -1; dx <= 1; ++dx)
                if (dx || dy)
                    open(x + dx, y + dy);
}

void Field::click(int mx, int my, bool right)
{
    if (gameOver)
        return;

    int x = (mx - offsetX) / SIZE;
    int y = (my - offsetY) / SIZE;

    if (!inside(x, y))
        return;

    if (firstClick && !right)
    {
        generate(x, y);
        count();
        firstClick = false;
    }

    if (right)
        cells[y][x].toggleFlag();
    else
        open(x, y);
}

int Field::getFlagCount() const
{
    int c = 0;
    for (auto& row : cells)
        for (auto& cell : row)
            if (cell.hasFlag())
                c++;
    return c;
}

bool Field::isWin() const
{
    for (auto& row : cells)
        for (auto& cell : row)
            if (!cell.hasMine() && !cell.isOpened())
                return false;
    return true;
}

void Field::draw(sf::RenderWindow& window)
{
    for (auto& row : cells)
        for (auto& cell : row)
            cell.draw(window);
}