#include "days.hpp"

#include <algorithm>

struct Hand
{
    std::string cards;
    int64_t     bid;

    enum Type
    {
        HIGH_CARD = 0,
        ONE_PAIR,
        TWO_PAIR,
        BRELAN,
        FULL_HOUSE,
        QUAD,
        FIVE
    };

    static int compare_cards(char first, char second)
    {
        const std::string power = "AKQT98765432J";
        return power.find(second) - power.find(first);
    }

    int compare_values(const Hand& other) const
    {
        for(int i = 0; i < 5; ++i)
        {
            auto compare = compare_cards(cards[i], other.cards[i]);
            if(compare != 0)
            {
                return compare;
            }
        }

        return 0;
    }

    Type get_type() const
    {
        std::vector<Type> types;

        std::string sorted = cards;
        std::sort(sorted.begin(), sorted.end(), [](char first, char second)
                  { return compare_cards(first, second) > 0; });

        auto jokers = std::ranges::count(sorted, 'J');
        int  same = 1;

        for(int i = 0; i < 4; ++i)
        {
            if(sorted[i] == sorted[i + 1] && sorted[i] != 'J')
            {
                ++same;
            }

            if(sorted[i] != sorted[i + 1] || i == 3 || sorted[i] == 'J')
            {
                if(same == 5 || same + jokers >= 5)
                {
                    return FIVE;
                }
                else if(same == 4 || same + jokers >= 4)
                {
                    return QUAD;
                }
                else if(same == 3)
                {
                    types.push_back(BRELAN);
                }
                if(same == 2)
                {
                    types.push_back(ONE_PAIR);
                }

                same = 1;
            }
        }

        if(types.size() == 0)
        {
            if(jokers == 1)
            {
                return ONE_PAIR;
            }
            else if(jokers == 2)
            {
                return BRELAN;
            }

            return HIGH_CARD;
        }
        else if(types.size() == 1)
        {
            if(jokers == 1)
            {
                return BRELAN;
            }

            return types[0];
        }
        else if(std::ranges::count(types, ONE_PAIR) == 2)
        {
            if(jokers == 1)
            {
                return FULL_HOUSE;
            }

            return TWO_PAIR;
        }

        return FULL_HOUSE;
    }

    static bool compare(Hand first, Hand second)
    {
        auto difference = first.get_type() - second.get_type();
        return difference != 0 ? difference < 0 : first.compare_values(second) < 0;
    }
};

void day_7()
{
    auto lines = split(read_file("inputs/input_7.txt"), "\n");

    std::vector<Hand> hands;

    for(auto line: lines)
    {
        if(!line.empty())
        {
            std::stringstream ss(line);
            hands.push_back(Hand{read_string(ss), read_int(ss)});
        }
    }

    std::sort(hands.begin(), hands.end(), Hand::compare);

    uint64_t sum = 0;
    for(uint64_t i = 0; i < hands.size(); ++i)
    {
        sum += (i + 1) * hands[i].bid;
        printf("%7s", hands[i].cards.c_str());
    }

    std::cout << std::endl << sum << std::endl;
}