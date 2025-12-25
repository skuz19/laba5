#include "Cell.hpp"

static const float CELL_SIZE = 32.f;

Cell::Cell()
{
    sprite.setTexture(TextureManager::instance().get(TextureID::Closed));
    applySize();
}

void Cell::setPosition(float x, float y)
{
    position = {x, y};
    sprite.setPosition(position);
}

void Cell::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

void Cell::open()
{
    if (opened || flag)
        return;

    opened = true;
    updateTexture();
}

void Cell::toggleFlag()
{
    if (opened)
        return;

    flag = !flag;
    updateTexture();
}

void Cell::placeMine()
{
    mine = true;
}

void Cell::setMinesAround(int n)
{
    minesAround = n;
}

bool Cell::hasMine() const { return mine; }
bool Cell::isOpened() const { return opened; }
bool Cell::hasFlag() const { return flag; }
int  Cell::getMinesAround() const { return minesAround; }

void Cell::applySize()
{
    const sf::Texture* tex = sprite.getTexture();
    if (!tex) return;

    sf::Vector2u s = tex->getSize();
    sprite.setScale(
        CELL_SIZE / s.x,
        CELL_SIZE / s.y
    );
    sprite.setPosition(position);
}

void Cell::updateTexture()
{
    auto& tm = TextureManager::instance();

    if (!opened)
    {
        sprite.setTexture(flag ? tm.get(TextureID::Flag)
                               : tm.get(TextureID::Closed));
        applySize();
        return;
    }

    if (mine)
    {
        sprite.setTexture(tm.get(TextureID::Explode));
        applySize();
        return;
    }

    static TextureID nums[] = {
        TextureID::Opened,
        TextureID::One, TextureID::Two, TextureID::Three,
        TextureID::Four, TextureID::Five, TextureID::Six,
        TextureID::Seven, TextureID::Eight
    };

    sprite.setTexture(nums[minesAround] == TextureID::Opened
                      ? tm.get(TextureID::Opened)
                      : tm.get(nums[minesAround]));
    applySize();
}