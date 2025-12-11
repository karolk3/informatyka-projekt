#include "Game.h"
#include "GameState.h"
#include <iostream>

Game::Game()
    : window(sf::VideoMode((unsigned)WIDTH, (unsigned)HEIGHT), "Arkanoid")
    , state(State::Menu)
    , menu(window.getSize().x, window.getSize().y)
    , paletka()
    , pilka()
    , bloki(Stone::createDefaultLevel())
{
    window.setFramerateLimit(60);
}

void Game::run()
{
    while (window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::KeyPressed)
        {
            if (state == State::Menu)
            {
                if (event.key.code == sf::Keyboard::Up)
                    menu.moveUp();
                else if (event.key.code == sf::Keyboard::Down)
                    menu.moveDown();
                else if (event.key.code == sf::Keyboard::Enter)
                {
                    int s = menu.getSelectedIndex();
                    if (s == 0)
                        newGame();
                    else if (s == 1)
                        loadGame();
                    else if (s == 2)
                        window.close();
                }
            }
            else if (state == State::Playing)
            {
                if (event.key.code == sf::Keyboard::Escape)
                    state = State::Menu;
                else if (event.key.code == sf::Keyboard::F5)
                    saveGame();
                else if (event.key.code == sf::Keyboard::F9)
                    loadGame();
            }
        }
    }
}

void Game::update()
{
    if (state == State::Playing)
    {
        paletka.update(WIDTH);

        if (pilka.update(paletka, bloki, WIDTH, HEIGHT))
            newGame();
    }
}

void Game::render()
{
    window.clear(sf::Color(20, 20, 30));

    if (state == State::Menu)
    {
        menu.draw(window);
    }
    else if (state == State::Playing)
    {
        for (auto& b : bloki)
            b.draw(window);
        paletka.draw(window);
        pilka.draw(window);
    }

    window.display();
}

void Game::newGame()
{
    paletka = Paletka();
    pilka = Pilka();
    bloki = Stone::createDefaultLevel();
    state = State::Playing;
}

void Game::loadGame()
{
    GameState st;
    if (!st.loadFromFile("zapis.txt"))
    {
        std::cout << "Blad wczytywania\n";
        return;
    }
    st.apply(paletka, pilka, bloki);
    state = State::Playing;
}

void Game::saveGame()
{
    GameState st;
    st.capture(paletka, pilka, bloki);
    if (st.saveToFile("zapis.txt"))
        std::cout << "Zapisano\n";
    else
        std::cout << "Blad zapisu\n";
}
