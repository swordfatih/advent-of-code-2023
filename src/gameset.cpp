#include "gameset.hpp"

GameSet::GameSet()
{
}

std::string GameSet::to_string()
{
    return std::to_string(red) + " red, " + std::to_string(green) + " green, " + std::to_string(blue) + " blue";
}

void GameSet::from_string(std::string color, int value)
{
    if(color.find("red") != std::string::npos)
    {
        red = value;
    }
    else if(color.find("blue") != std::string::npos)
    {
        blue = value;
    }
    else if(color.find("green") != std::string::npos)
    {
        green = value;
    }
}

bool GameSet::valid()
{
    return red <= 12 && green <= 13 && blue <= 14;
}

void GameSet::choose_max(GameSet other)
{
    red = red > other.red ? red : other.red;
    green = green > other.green ? green : other.green;
    blue = blue > other.blue ? blue : other.blue;
}

int GameSet::get_power()
{
    return red * blue * green;
}