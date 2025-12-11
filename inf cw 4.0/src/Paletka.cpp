#include "Paletka.h"

static constexpr float MOVE_STEP = 10.f;

Paletka::Paletka(float startX, float startY, float szer, float wys)
    : x(startX), y(startY), szerokosc(szer), wysokosc(wys)
{
    shape.setSize({ szerokosc, wysokosc });
    shape.setOrigin(szerokosc / 2.f, wysokosc / 2.f);
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::White);
}

void Paletka::moveLeft() {
    x -= MOVE_STEP;
    shape.setPosition(x, y);
}

void Paletka::moveRight() {
    x += MOVE_STEP;
    shape.setPosition(x, y);
}

void Paletka::clampToBounds(float width) {
    float half = szerokosc / 2.f;
    if (x - half < 0.f) {
        x = half;
        shape.setPosition(x, y);
    }
    if (x + half > width) {
        x = width - half;
        shape.setPosition(x, y);
    }
}

void Paletka::update(float width) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        moveLeft();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        moveRight();
    clampToBounds(width);
}

void Paletka::draw(sf::RenderTarget& target) const {
    target.draw(shape);
}

float Paletka::getX() const { return x; }
float Paletka::getY() const { return y; }
float Paletka::getSzerokosc() const { return szerokosc; }
float Paletka::getWysokosc() const { return wysokosc; }

sf::Vector2f Paletka::getPosition() const {
    return sf::Vector2f(x, y);
}

void Paletka::setPosition(const sf::Vector2f& pos) {
    x = pos.x;
    y = pos.y;
    shape.setPosition(x, y);
}
