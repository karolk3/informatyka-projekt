#include "Stone.h"
#include "Pilka.h"
#include <cmath>

const std::array<sf::Color, 4> Stone::m_colorLUT = {
    sf::Color::Transparent,
    sf::Color::Red,
    sf::Color::Yellow,
    sf::Color::Blue
};

Stone::Stone(sf::Vector2f startPos, sf::Vector2f rozmiar, int L)
    : m_punktyZycia(L), m_jestZniszczony(false)
{
    this->setPosition(startPos);
    this->setSize(rozmiar);
    this->setOrigin(rozmiar.x / 2.f, rozmiar.y / 2.f);
    this->setOutlineThickness(2.f);
    aktualizujKolor();
}

void Stone::trafienie() {
    if (m_jestZniszczony) return;
    m_punktyZycia--;
    aktualizujKolor();
    if (m_punktyZycia <= 0) m_jestZniszczony = true;
}

void Stone::aktualizujKolor() {
    if (m_punktyZycia >= 0 && m_punktyZycia < (int)m_colorLUT.size())
        this->setFillColor(m_colorLUT[m_punktyZycia]);
    else if (m_punktyZycia < 0)
        this->setFillColor(m_colorLUT[0]);
    else
        this->setFillColor(m_colorLUT.back());
}

bool Stone::isDestroyed() const {
    return m_jestZniszczony;
}

void Stone::draw(sf::RenderTarget& target) const {
    if (!m_jestZniszczony)
        target.draw(*this);
}

bool Stone::handleCollision(Pilka& p) {
    if (m_jestZniszczony) return false;

    float bx = this->getPosition().x;
    float by = this->getPosition().y;
    float bw = this->getSize().x;
    float bh = this->getSize().y;

    float left = bx - bw / 2.f;
    float right = bx + bw / 2.f;
    float top = by - bh / 2.f;
    float bottom = by + bh / 2.f;

    float px = p.getX();
    float py = p.getY();
    float r = p.getRadius();

    bool col = (px + r >= left) && (px - r <= right) &&
        (py + r >= top) && (py - r <= bottom);

    if (!col) return false;

    float dx = px - bx;
    float dy = py - by;

    if (std::abs(dx) > std::abs(dy))
        p.bounceX();
    else
        p.bounceY();

    trafienie();
    return true;
}

std::vector<Stone> Stone::createDefaultLevel() {
    std::vector<Stone> v;
    sf::Vector2f size(80.f, 25.f);

    v.emplace_back(sf::Vector2f(150.f, 50.f), size, 3);
    v.emplace_back(sf::Vector2f(250.f, 50.f), size, 3);
    v.emplace_back(sf::Vector2f(350.f, 50.f), size, 3);
    v.emplace_back(sf::Vector2f(450.f, 50.f), size, 3);
    v.emplace_back(sf::Vector2f(550.f, 50.f), size, 3);

    v.emplace_back(sf::Vector2f(150.f, 80.f), size, 2);
    v.emplace_back(sf::Vector2f(250.f, 80.f), size, 2);
    v.emplace_back(sf::Vector2f(350.f, 80.f), size, 2);
    v.emplace_back(sf::Vector2f(450.f, 80.f), size, 2);
    v.emplace_back(sf::Vector2f(550.f, 80.f), size, 2);

    v.emplace_back(sf::Vector2f(150.f, 110.f), size, 1);
    v.emplace_back(sf::Vector2f(250.f, 110.f), size, 1);
    v.emplace_back(sf::Vector2f(350.f, 110.f), size, 1);
    v.emplace_back(sf::Vector2f(450.f, 110.f), size, 1);
    v.emplace_back(sf::Vector2f(550.f, 110.f), size, 1);

    return v;
}

int Stone::getHP() const {
    return m_punktyZycia;
}
