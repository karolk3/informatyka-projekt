#include "Pilka.h"
#include "Stone.h"
#include <cmath>
#include <iostream>

Pilka::Pilka(float startX, float startY, float velX, float velY, float r)
    : x(startX), y(startY), vx(velX), vy(velY), radius(r)
{
    shape.setRadius(radius);
    shape.setOrigin(radius, radius);
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::White);
}

void Pilka::move() {
    x += vx;
    y += vy;
    shape.setPosition(x, y);
}

void Pilka::bounceX() {
    vx = -vx;
}

void Pilka::bounceY() {
    vy = -vy;
}

void Pilka::collideWalls(float width, float height) {
    if (x - radius <= 0.f) {
        x = radius;
        bounceX();
        shape.setPosition(x, y);
    }
    if (x + radius >= width) {
        x = width - radius;
        bounceX();
        shape.setPosition(x, y);
    }
    if (y - radius <= 0.f) {
        y = radius;
        bounceY();
        shape.setPosition(x, y);
    }
}

bool Pilka::collidePaddle(const Paletka& p) {
    float palLeft = p.getX() - p.getSzerokosc() / 2.f;
    float palRight = p.getX() + p.getSzerokosc() / 2.f;
    float palTop = p.getY() - p.getWysokosc() / 2.f;

    bool horizontallyAbove = (x >= palLeft) && (x <= palRight);
    bool touchingTop = (y + radius >= palTop) && (y - radius < palTop);

    if (horizontallyAbove && touchingTop && vy > 0.f) {
        vy = -std::abs(vy);
        y = palTop - radius - 0.001f;
        shape.setPosition(x, y);
        return true;
    }
    return false;
}

void Pilka::draw(sf::RenderTarget& target) const {
    target.draw(shape);
}

float Pilka::getX() const { return x; }
float Pilka::getY() const { return y; }
float Pilka::getVx() const { return vx; }
float Pilka::getVy() const { return vy; }
float Pilka::getRadius() const { return radius; }

bool Pilka::update(Paletka& pal, std::vector<Stone>& bloki, float width, float height) {
    move();
    collideWalls(width, height);

    for (auto& b : bloki) {
        if (!b.isDestroyed()) {
            if (b.handleCollision(*this)) {
                std::cout << "HIT BLOCK\n";
            }
        }
    }

    if (collidePaddle(pal)) {
        std::cout << "HIT PADDLE\n";
    }

    if (y - radius > height) {
        return true;
    }
    return false;
}

sf::Vector2f Pilka::getPosition() const {
    return sf::Vector2f(x, y);
}

sf::Vector2f Pilka::getVelocity() const {
    return sf::Vector2f(vx, vy);
}

void Pilka::reset(const sf::Vector2f& pos, const sf::Vector2f& vel) {
    x = pos.x;
    y = pos.y;
    vx = vel.x;
    vy = vel.y;
    shape.setPosition(x, y);
}
