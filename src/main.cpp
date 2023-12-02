#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

#include "game.hpp"
#include "input.hpp"

void day_1()
{
    auto tokens = split(read_file("inputs/input_1.txt"), "\n");

    std::string digits[10] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

    int sum = 0;
    for(auto token: tokens)
    {
        auto is_digit = [](char letter)
        {
            return std::isdigit(letter);
        };

        auto first_it = std::find_if(token.begin(), token.end(), is_digit);
        auto last_it = std::find_if(token.rbegin(), token.rend(), is_digit);

        size_t first = first_it != token.end() ? *first_it - '0' : 0;
        size_t last = last_it != token.rend() ? *last_it - '0' : 0;

        size_t first_distance = first_it == token.end() ? 0 : std::distance(token.begin(), first_it);
        size_t last_distance = last_it == token.rend() ? 0 : (token.size() - std::distance(token.rbegin(), last_it) - 1);

        for(int i = 0; i < 10; ++i)
        {
            auto first_pos = token.find(digits[i]);
            auto last_pos = token.rfind(digits[i]);

            if(first_pos != std::string::npos && first_pos < first_distance)
            {
                first_distance = first_pos;
                first = i;
            }

            if(last_pos != std::string::npos && last_pos > last_distance)
            {
                last_distance = last_pos;
                last = i;
            }
        }

        sum += first * 10 + last;
    }

    std::cout << sum << std::endl;
}

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

int main()
{
    day_2();

    return 0;
}