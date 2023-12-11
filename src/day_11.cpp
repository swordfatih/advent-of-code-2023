#include "days.hpp"

#include <cmath>
#include <set>

struct Galaxy
{
    uint64_t x;
    uint64_t y;
};

void day_11()
{
    auto lines = split(read_file("inputs/input_11.txt"), "\n");

    std::set<uint64_t>  expanded_columns;
    std::set<uint64_t>  expanded_rows;
    std::vector<Galaxy> galaxies;

    // expand rows
    for(uint64_t y = 0; y < lines.size(); ++y)
    {
        bool contains = false;
        for(uint64_t x = 0; x < lines[y].size(); ++x)
        {
            if(lines[y][x] == '#')
            {
                contains = true;
                galaxies.push_back({x, y});
            }
        }

        if(!contains)
        {
            expanded_rows.emplace(y);
        }
    }

    // expand columns
    for(uint64_t x = 0; x < lines[0].size(); ++x)
    {
        bool contains = false;
        for(uint64_t y = 0; y < lines.size(); ++y)
        {
            if(lines[y][x] != '.')
            {
                contains = true;
                break;
            }
        }

        if(!contains)
        {
            expanded_columns.emplace(x);
        }
    }

    uint64_t sum = 0;
    for(uint64_t i = 0; i < galaxies.size(); ++i)
    {
        auto first = galaxies[i];
        for(uint64_t j = i + 1; j < galaxies.size(); ++j)
        {
            auto second = galaxies[j];

            for(uint64_t k = std::min(first.x, second.x) + 1; k < std::max(first.x, second.x); ++k)
            {
                if(expanded_columns.count(k) > 0)
                {
                    sum += 999999;
                }
            }

            for(uint64_t k = std::min(first.y, second.y) + 1; k < std::max(first.y, second.y); ++k)
            {
                if(expanded_rows.count(k) > 0)
                {
                    sum += 999999;
                }
            }

            sum += std::abs(static_cast<int64_t>(first.x - second.x)) + std::abs(static_cast<int64_t>(first.y - second.y));
        }
    }

    std::cout << sum << std::endl;
}