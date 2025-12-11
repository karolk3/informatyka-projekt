#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include <vector>

class Pilka;

class Stone : public sf::RectangleShape
{
private:
    int m_punktyZycia;
    bool m_jestZniszczony;
    static const std::array<sf::Color, 4> m_colorLUT;
public:
    Stone(sf::Vector2f startPos, sf::Vector2f rozmiar, int L);
    void trafienie();
    void aktualizujKolor();
    bool isDestroyed() const;
    void draw(sf::RenderTarget& target) const;
    bool handleCollision(Pilka& p);
    static std::vector<Stone> createLevel(float szerokosc, int cols, int rows, float blockY, float gap, float offsetTop);
    static std::vector<Stone> createDefaultLevel();
    int getHP() const;
};
