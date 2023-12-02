#include <sstream>

#include "game.hpp"

Game::Game(int id) : id(id)
{
}

std::string Game::to_string()
{
    std::string buffer = "Game " + std::to_string(id) + ": ";

    for(auto set: sets)
    {
        buffer += set.to_string() + "; ";
    }

    return buffer;
}

void Game::from_string(std::string buffer)
{
    std::stringstream ss(buffer);
    while(std::getline(ss, buffer, ';'))
    {
        std::string value, color;
        auto&       set = sets.emplace_back();

        std::stringstream set_stream(buffer);

        while(set_stream >> value >> color)
        {
            set.from_string(color, std::stoi(value));
        }
    }
}

bool Game::valid()
{
    for(auto set: sets)
    {
        if(!set.valid())
        {
            return false;
        }
    }

    return true;
}

int Game::get_id()
{
    return id;
}

GameSet Game::get_max()
{
    GameSet max = sets[0];

    for(int i = 1; i < sets.size(); ++i)
    {
        max.choose_max(sets[i]);
    }
    
    return max;
}