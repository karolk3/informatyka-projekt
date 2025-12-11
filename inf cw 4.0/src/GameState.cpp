#include "GameState.h"
#include <fstream>

void GameState::capture(const Paletka& p, const Pilka& b, const std::vector<Stone>& stones)
{
    paddlePosition = p.getPosition();
    ballPosition = b.getPosition();
    ballVelocity = b.getVelocity();

    blocks.clear();
    blocks.reserve(stones.size());

    for (const auto& s : stones) {
        if (!s.isDestroyed()) {
            BlockData bd;
            bd.x = s.getPosition().x;
            bd.y = s.getPosition().y;
            bd.hp = s.getHP();
            blocks.push_back(bd);
        }
    }
}

bool GameState::saveToFile(const std::string& filename) const
{
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    file << "PADDLE " << paddlePosition.x << " " << paddlePosition.y << "\n";
    file << "BALL " << ballPosition.x << " " << ballPosition.y << " "
        << ballVelocity.x << " " << ballVelocity.y << "\n";

    file << "BLOCKS_COUNT " << blocks.size() << "\n";
    for (const auto& b : blocks) {
        file << b.x << " " << b.y << " " << b.hp << "\n";
    }

    file.close();
    return true;
}

bool GameState::loadFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    std::string label;

    if (!(file >> label >> paddlePosition.x >> paddlePosition.y)) {
        return false;
    }

    if (!(file >> label >> ballPosition.x >> ballPosition.y >> ballVelocity.x >> ballVelocity.y)) {
        return false;
    }

    int blocksCount = 0;
    if (!(file >> label >> blocksCount)) {
        return false;
    }

    blocks.clear();
    blocks.reserve(blocksCount);

    for (int i = 0; i < blocksCount; ++i) {
        BlockData bd;
        if (!(file >> bd.x >> bd.y >> bd.hp)) {
            return false;
        }
        blocks.push_back(bd);
    }

    file.close();
    return true;
}

void GameState::apply(Paletka& p, Pilka& b, std::vector<Stone>& stones) const
{
    p.setPosition(paddlePosition);
    b.reset(ballPosition, ballVelocity);

    stones.clear();
    sf::Vector2f size(80.f, 25.f);

    for (const auto& data : blocks) {
        stones.emplace_back(sf::Vector2f(data.x, data.y), size, data.hp);
    }
}
