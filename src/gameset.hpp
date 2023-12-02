#pragma once

#include <string>

class GameSet
{
public:
    GameSet();

    std::string to_string();
    void        from_string(std::string color, int value);
    bool        valid();
    void        choose_max(GameSet other);
    int         get_power();

private:
    int red = 0;
    int green = 0;
    int blue = 0;
};