#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Cell.hpp"

class Field
{
public:
    Field(int w, int h, int m);

    void setOffset(int x, int y);
    void draw(sf::RenderWindow& window);
    void click(int mx, int my, bool right);
    void reset();

    bool isGameOver() const;
    bool isWin() const;

    int getFlagCount() const;

private:
    int width;
    int height;
    int mines;

    bool gameOver = false;
    bool firstClick = true;

    int offsetX = 0;
    int offsetY = 0;

    std::vector<std::vector<Cell>> cells;

    void generate(int sx, int sy);
    void count();
    void open(int x, int y);
    bool inside(int x, int y) const;
};