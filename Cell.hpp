#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.hpp"

class Cell
{
public:
    Cell();

    void setPosition(float x, float y);
    void draw(sf::RenderWindow& window);

    void open();
    void toggleFlag();

    void placeMine();
    void setMinesAround(int n);

    bool hasMine() const;
    bool isOpened() const;
    bool hasFlag() const;
    int  getMinesAround() const;

private:
    bool opened = false;
    bool mine = false;
    bool flag = false;
    int minesAround = 0;

    sf::Sprite sprite;
    sf::Vector2f position;

    void updateTexture();
    void applySize();   // 🔥 КЛЮЧ
};