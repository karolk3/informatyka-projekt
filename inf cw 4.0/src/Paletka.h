#pragma once
#include <SFML/Graphics.hpp>

class Paletka {
private:
    float x;
    float y;
    float szerokosc;
    float wysokosc;
    sf::RectangleShape shape;
public:
    Paletka(float startX = 400.f, float startY = 550.f, float szer = 100.f, float wys = 20.f);
    void moveLeft();
    void moveRight();
    void clampToBounds(float width);
    void update(float width);
    void draw(sf::RenderTarget& target) const;
    float getX() const;
    float getY() const;
    float getSzerokosc() const;
    float getWysokosc() const;
    sf::Vector2f getPosition() const;
    void setPosition(const sf::Vector2f& pos);
};
