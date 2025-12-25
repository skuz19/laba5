#pragma once
#include <SFML/Graphics.hpp>
#include "Field.hpp"
#include "Difficulty.hpp"

enum class GameState
{
    Menu,
    Playing
};

class Game
{
public:
    Game();
    void run();

private:
    sf::RenderWindow window;
    GameState state = GameState::Menu;

    sf::Font font;

    sf::Text title;
    sf::Text easyBtn;
    sf::Text mediumBtn;
    sf::Text hardBtn;

    Field* field = nullptr;
    Difficulty currentDiff;

    sf::RectangleShape background;
    sf::RectangleShape topPanel;

    sf::Text minesLabel;
    sf::Text minesCounter;
    sf::Text restartBtn;
    sf::Text endText;

    void drawMenu();
    void startGame(const Difficulty& diff);
};