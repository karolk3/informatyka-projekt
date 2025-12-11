#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Menu.h"
#include "Paletka.h"
#include "Pilka.h"
#include "Stone.h"

class Game
{
public:
    Game();
    void run();

private:
    enum class State { Menu, Playing };

    static constexpr float WIDTH = 800.f;
    static constexpr float HEIGHT = 600.f;

    sf::RenderWindow window;
    State state;

    Menu menu;
    Paletka paletka;
    Pilka pilka;
    std::vector<Stone> bloki;

    void processEvents();
    void update();
    void render();

    void newGame();
    void loadGame();
    void saveGame();
};
