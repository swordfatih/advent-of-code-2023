#include "days.hpp"

#include <set>
#include <map>

void sum_cards(std::map<int, int>& cards, int current, size_t& count)
{
    count++;
    for(int i = 0; i < cards[current]; ++i)
    {
        sum_cards(cards, current + i + 1, count);
    }
}

void day_4()
{
    auto lines = split(read_file("inputs/input_4.txt"), "\n");

    std::map<int, int> cards;

    int sum = 0;
    for(auto line: lines)
    {
        if(line.empty())
        {
            continue;
        }

        std::stringstream ss(line);
        std::string buf;

        ss >> buf >> buf;

        buf.pop_back();

        int card = std::stoi(buf);

        std::set<int> winning;
        for(int i = 0; i < 10; ++i)
        {
            ss >> buf;
            winning.emplace(std::stoi(buf));
        }

        ss >> buf;

        int matching = 0;
        while(ss >> buf)
        {
            int number = std::stoi(buf);

            if(winning.count(number))
            {
                matching++;
            }
        }

        cards[card] = matching;
    }

    size_t count = 0;

    for(auto [number, _]: cards)
    {
        sum_cards(cards, number, count);
    }
    
    std::cout << count << std::endl;
}