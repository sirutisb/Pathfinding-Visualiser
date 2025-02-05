#include "gridFile.h"
#include <fstream>
#include "application.h"

GridFile::GridFile(Grid &grid)
    : grid(grid)
{
}

bool GridFile::save(const std::string &filename) const {
    std::ofstream file("maps/" + filename, std::ios::binary);
    if (!file) return false;

    auto [startPos, endPos] = Application::get().getStartEndPos();
    const uint32_t startKey = startPos.x << 16 | startPos.y;
    const uint32_t endKey = endPos.x << 16 | endPos.y;
    size_t cellCount = grid.getCells().size();
    size_t bufferSize = 5 + cellCount;
    auto* buffer = new uint32_t[bufferSize];
    buffer[0] = grid.getWidth();
    buffer[1] = grid.getHeight();
    buffer[2] = startKey;
    buffer[3] = endKey;
    buffer[4] = cellCount;

    int idx = 5;
    for (const auto& cellKey : grid.getCells()) {
        buffer[idx] = cellKey;
        idx++;
    }

    file.write((const char*)buffer, sizeof(uint32_t) * bufferSize);
    delete[] buffer;
    return file.good();
}

bool GridFile::load(const std::string &filename) const {
    std::ifstream file("maps/" + filename, std::ios::binary);
    if (!file) return false;

    int32_t width, height;
    file.read(reinterpret_cast<char*>(&width), sizeof(width));
    file.read(reinterpret_cast<char*>(&height), sizeof(height));
    grid.resize(width, height);

    // Start/End positions
    int32_t startKey, endKey;
    file.read(reinterpret_cast<char*>(&startKey), sizeof(startKey));
    file.read(reinterpret_cast<char*>(&endKey), sizeof(endKey));

    sf::Vector2i startPos{ startKey >> 16, startKey & 0xFFFF };
    sf::Vector2i endPos{endKey >> 16, endKey & 0xFFFF};
    Application::get().setStartEndPos(startPos, endPos);

    uint32_t numObstacles;
    file.read(reinterpret_cast<char*>(&numObstacles), sizeof(numObstacles));

    grid.clear();
    for (int i = 0; i < numObstacles; i++) {
        uint32_t key;
        file.read(reinterpret_cast<char*>(&key), sizeof(key));
        //grid.getCells().insert(key);
        grid.setState(key >> 16, key & 0xFFFF, true);
    }

    return file.good();
}

