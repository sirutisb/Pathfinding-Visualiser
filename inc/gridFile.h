#pragma once
#include <string>
#include "grid.h"

class GridFile {
public:
    explicit GridFile(Grid& grid);

    bool save(const std::string& filename) const;
    bool load(const std::string& filename) const;
private:
    Grid& grid;
};