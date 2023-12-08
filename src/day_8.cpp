#include "days.hpp"

#include <map>
#include <numeric>

struct Intersection
{
    std::string value;
    std::string left;
    std::string right;
};

struct Path
{
    std::string current;

    uint64_t calculate(std::map<std::string, Intersection>& intersections, std::string directions)
    {
        uint64_t steps = 0;
        uint64_t cursor = 0;

        while(current[2] != 'Z')
        {
            current = directions[cursor] == 'L' ? intersections[current].left : intersections[current].right;
            ++steps;
            cursor = (cursor + 1) % directions.size();
        }

        return steps;
    }
};

void day_8()
{
    auto lines = split(read_file("inputs/input_8.txt"), "\n");

    std::stringstream ss(lines[0]);
    std::string       directions = read_string(ss);

    std::map<std::string, Intersection> intersections;
    std::vector<Path>                   paths;

    for(int i = 1; i < lines.size(); ++i)
    {
        if(!lines[i].empty())
        {
            std::string  value = lines[i].substr(0, 3);
            intersections[value] = {value, lines[i].substr(7, 3), lines[i].substr(12, 3)};

            if(value[2] == 'A')
            {
                paths.push_back({value});
            }
        }
    }

    uint64_t lcm = paths[0].calculate(intersections, directions);
    for(int i = 1; i < paths.size(); ++i)
    {
        lcm = std::lcm(lcm, paths[i].calculate(intersections, directions));
    }

    std::cout << lcm << std::endl;
}