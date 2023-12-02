#pragma once

#include <vector>

#include "gameset.hpp"

class Game
{
public:
    Game(int id);

    std::string to_string();
    void        from_string(std::string buffer);
    bool        valid();
    int         get_id();
    GameSet     get_max();

private:
    std::vector<GameSet> sets;
    int                  id;
};
