#include "days.hpp"

void day_6()
{
    auto lines = split(read_file("inputs/input_6.txt"), "\n");

    std::stringstream time_ss(lines[0]);
    std::stringstream distance_ss(lines[1]);
    std::string       buf;

    time_ss >> buf;
    distance_ss >> buf;

    std::string time, distance;

    while(time_ss >> buf)
    {
        time += buf;
        distance_ss >> buf;
        distance += buf;
    }

    uint64_t duration = std::stoll(time);
    uint64_t record = std::stoll(distance);

    uint64_t ways = 0;

    for(uint64_t i = 0; i < duration; ++i)
    {
        if(i * (duration - i) > record)
        {
            ++ways;
        }
    }

    std::cout << ways << std::endl;
}