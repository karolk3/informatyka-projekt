#pragma once
#include <SFML/Graphics.hpp>
#include "Paletka.h"
#include <vector>

class Stone;

class Pilka {
private:
    float x;
    float y;
    float vx;
    float vy;
    float radius;
    sf::CircleShape shape;
public:
    Pilka(float startX = 400.f, float startY = 300.f, float velX = 4.f, float velY = 3.f, float r = 8.f);
    void move();
    void bounceX();
    void bounceY();
    void collideWalls(float width, float height);
    bool collidePaddle(const Paletka& p);
    void draw(sf::RenderTarget& target) const;
    float getX() const;
    float getY() const;
    float getVx() const;
    float getVy() const;
    float getRadius() const;
    bool update(Paletka& pal, std::vector<Stone>& bloki, float width, float height);
    sf::Vector2f getPosition() const;
    sf::Vector2f getVelocity() const;
    void reset(const sf::Vector2f& pos, const sf::Vector2f& vel);
};
