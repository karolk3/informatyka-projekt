#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Menu
{
public:
    Menu(float width, float height);
    void moveUp();
    void moveDown();
    int getSelectedIndex() const;
    void draw(sf::RenderWindow& window) const;

private:
    int selectedIndex;
    sf::Font font;
    std::vector<sf::Text> items;
};
