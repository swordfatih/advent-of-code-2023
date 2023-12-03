#include "days.hpp"

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