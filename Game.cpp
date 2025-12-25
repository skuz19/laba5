#include "Game.hpp"
#include "TextureManager.hpp"
#include <sstream>

static const int CELL  = 32;
static const int TOP   = 64;
static const int FRAME = 16;

Game::Game()
    : window(sf::VideoMode(640, 480), "Minesweeper")
{
    auto& tm = TextureManager::instance();

    tm.load(TextureID::Closed,  "img/closed.png");
    tm.load(TextureID::Opened, "img/opened.png");
    tm.load(TextureID::Flag,   "img/flag.png");

    tm.load(TextureID::One,   "img/1.png");
    tm.load(TextureID::Two,   "img/2.png");
    tm.load(TextureID::Three,"img/3.png");
    tm.load(TextureID::Four, "img/4.png");
    tm.load(TextureID::Five, "img/5.png");
    tm.load(TextureID::Six,  "img/6.png");
    tm.load(TextureID::Seven,"img/7.png");
    tm.load(TextureID::Eight,"img/8.png");
    tm.load(TextureID::Explode, "img/mine.png");

    font.loadFromFile("arial.ttf");

    // ===== MENU =====
    title.setFont(font);
    title.setString("MINESWEEPER");
    title.setCharacterSize(40);
    title.setPosition(180.f, 60.f);

    easyBtn.setFont(font);
    easyBtn.setString("Easy");
    easyBtn.setCharacterSize(28);
    easyBtn.setPosition(260.f, 150.f);

    mediumBtn = easyBtn;
    mediumBtn.setString("Medium");
    mediumBtn.setPosition(240.f, 200.f);

    hardBtn = easyBtn;
    hardBtn.setString("Hard");
    hardBtn.setPosition(260.f, 250.f);
}

void Game::startGame(const Difficulty& diff)
{
    currentDiff = diff;
    delete field;
    field = new Field(diff.width, diff.height, diff.mines);

    int winW = diff.width * CELL + FRAME * 2;
    int winH = diff.height * CELL + TOP + FRAME;
    window.create(sf::VideoMode(winW, winH), "Minesweeper");

    field->setOffset(FRAME, TOP);

    // ===== ФОН  =====
    background.setSize({ (float)winW, (float)winH });
    background.setFillColor(sf::Color(192,192,192));

    // ===== ВЕРХНЯЯ ПАНЕЛЬ =====
    topPanel.setSize({ (float)winW, (float)TOP });
    topPanel.setFillColor(sf::Color(192,192,192));

    minesLabel.setFont(font);
    minesLabel.setString("Mines");
    minesLabel.setCharacterSize(22);
    minesLabel.setFillColor(sf::Color::Black);
    minesLabel.setPosition(16.f, 18.f);

    minesCounter.setFont(font);
    minesCounter.setCharacterSize(22);
    minesCounter.setFillColor(sf::Color::Black);
    minesCounter.setPosition(90.f, 18.f);

    restartBtn.setFont(font);
    restartBtn.setString("Restart");
    restartBtn.setCharacterSize(20);
    restartBtn.setFillColor(sf::Color::Black);
    restartBtn.setPosition(winW - 120.f, 18.f);

    endText.setFont(font);
    endText.setCharacterSize(42);
    endText.setFillColor(sf::Color::Red);

    state = GameState::Playing;
}

void Game::drawMenu()
{
    window.clear(sf::Color(60,60,60));
    window.draw(title);
    window.draw(easyBtn);
    window.draw(mediumBtn);
    window.draw(hardBtn);
    window.display();
}

void Game::run()
{
    while (window.isOpen())
    {
        sf::Event e;
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                window.close();

            if (state == GameState::Menu &&
                e.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2f p(e.mouseButton.x, e.mouseButton.y);
                if (easyBtn.getGlobalBounds().contains(p))
                    startGame(Difficulties::Easy);
                else if (mediumBtn.getGlobalBounds().contains(p))
                    startGame(Difficulties::Medium);
                else if (hardBtn.getGlobalBounds().contains(p))
                    startGame(Difficulties::Hard);
            }

            if (state == GameState::Playing &&
                e.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2f p(e.mouseButton.x, e.mouseButton.y);

                if (restartBtn.getGlobalBounds().contains(p))
                {
                    field->reset();
                    continue;
                }

                field->click(
                    e.mouseButton.x,
                    e.mouseButton.y,
                    e.mouseButton.
                    button == sf::Mouse::Right
                );
            }
        }

        if (state == GameState::Menu)
        {
            drawMenu();
            continue;
        }

        // Счётчик флагов
        std::stringstream ss;
        ss << field->getFlagCount() << "/" << currentDiff.mines;
        minesCounter.setString(ss.str());

        window.clear();
        window.draw(background);
        window.draw(topPanel);
        window.draw(minesLabel);
        window.draw(minesCounter);
        window.draw(restartBtn);

        field->draw(window);

        if (field->isGameOver() || field->isWin())
        {
            endText.setString(
                field->isWin() ? "YOU WIN" : "GAME OVER"
            );

            auto r = endText.getLocalBounds();
            endText.setOrigin(r.width / 2.f, r.height / 2.f);
            endText.setPosition(
                window.getSize().x / 2.f,
                window.getSize().y / 2.f
            );

            window.draw(endText);
        }

        window.display();
    }
}
