#include "days.hpp"

#include <map>

struct Range
{
    uint64_t destination;
    uint64_t source;
    uint64_t length;
};

struct Map
{
    std::string        destination;
    std::vector<Range> ranges;
};

static uint64_t get_location(const std::map<std::string, Map>& maps, uint64_t value, uint64_t& same)
{
    std::string next = "seed";

    while(next != "location")
    {
        // convertion
        for(auto range: maps.at(next).ranges)
        {
            if(value >= range.source && value < range.source + range.length)
            {
                value = range.destination + value - range.source;

                uint64_t remaining = range.destination + range.length - value;

                if(same == -1 || remaining < same)
                {
                    same = remaining;
                }

                break;
            }
        }

        next = maps.at(next).destination;
    }

    return value;
}

void day_5()
{
    auto lines = split(read_file("inputs/input_5.txt"), "\n");

    std::stringstream ss(lines[0]);

    std::string buf1, buf2, buf3;
    ss >> buf1;

    std::vector<std::pair<uint64_t, uint64_t>> seeds;

    while(ss >> buf1 >> buf2)
    {
        seeds.push_back(std::make_pair(std::stoll(buf1), std::stoll(buf2)));
    }

    std::map<std::string, Map> maps;

    Map* current = nullptr;
    for(int i = 1; i < lines.size(); ++i)
    {
        auto line = lines[i];

        if(line.empty())
        {
            continue;
        }

        ss.clear();
        ss.str(line);

        if(!std::isdigit(line[0]))
        {
            ss >> buf1;

            std::string source = buf1.substr(0, buf1.find('-'));
            std::string destination = buf1.substr(buf1.rfind('-') + 1, buf1.find(' '));

            current = &maps[source];
            current->destination = destination;
        }
        else
        {
            Range range;

            ss >> buf1 >> buf2 >> buf3;
            range.destination = std::stoll(buf1);
            range.source = std::stoll(buf2);
            range.length = std::stoll(buf3);

            current->ranges.push_back(range);
        }
    }

    uint64_t lowest = -1;

    for(auto [start, length]: seeds)
    {
        for(uint64_t seed = start; seed < start + length; ++seed)
        {
            uint64_t same = -1;
            uint64_t value = get_location(maps, seed, same);

            if(same != -1)
            {
                seed += same - 1;
            }

            if(lowest == -1 || value < lowest)
            {
                lowest = value;
            }
        }
    }

    std::cout << lowest << std::endl;
}