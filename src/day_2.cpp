#include "days.hpp"
#include "game.hpp"

void day_2()
{
    auto lines = split(read_file("inputs/input_2.txt"), "\n");

    size_t sum = 0, power = 0;

    for(auto line: lines)
    {
        std::stringstream ss(line);
        std::string       buffer;
        std::getline(ss, buffer, ':');

        if(buffer.empty())
        {
            continue;
        }

        Game game(std::stoi(buffer.substr(5, buffer.find(":"))));

        std::getline(ss, buffer, ':');
        game.from_string(buffer);

        if(game.valid())
        {
            sum += game.get_id();
        }

        power += game.get_max().get_power();
    }

    std::cout << "Sum: " << sum << std::endl;
    std::cout << "Power: " << power << std::endl;
}