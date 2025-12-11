#include "Menu.h"

Menu::Menu(float width, float height)
    : selectedIndex(0)
{
    font.loadFromFile("C:/Users/kkaro/Desktop/inf cw 4.0/build/ariali.ttf");


    items.resize(3);

    items[0].setFont(font);
    items[0].setString("Nowa gra");
    items[0].setCharacterSize(40);
    items[0].setFillColor(sf::Color::Yellow);
    items[0].setPosition(width / 2.f - 100.f, height / 2.f - 60.f);

    items[1].setFont(font);
    items[1].setString("Wczytaj gre");
    items[1].setCharacterSize(40);
    items[1].setFillColor(sf::Color::White);
    items[1].setPosition(width / 2.f - 120.f, height / 2.f);

    items[2].setFont(font);
    items[2].setString("Wyjscie");
    items[2].setCharacterSize(40);
    items[2].setFillColor(sf::Color::White);
    items[2].setPosition(width / 2.f - 90.f, height / 2.f + 60.f);
}

void Menu::moveUp()
{
    if (selectedIndex > 0)
    {
        items[selectedIndex].setFillColor(sf::Color::White);
        selectedIndex--;
        items[selectedIndex].setFillColor(sf::Color::Yellow);
    }
}

void Menu::moveDown()
{
    if (selectedIndex + 1 < (int)items.size())
    {
        items[selectedIndex].setFillColor(sf::Color::White);
        selectedIndex++;
        items[selectedIndex].setFillColor(sf::Color::Yellow);
    }
}

int Menu::getSelectedIndex() const
{
    return selectedIndex;
}

void Menu::draw(sf::RenderWindow& window) const
{
    for (const auto& t : items)
        window.draw(t);
}
