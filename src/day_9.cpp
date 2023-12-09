#include "days.hpp"

bool empty(std::vector<int64_t> sequence)
{
    for(auto value: sequence)
    {
        if(value != 0)
        {
            return false;
        }
    }

    return true;
}

void day_9()
{
    auto lines = split(read_file("inputs/input_9.txt"), "\n");

    int64_t sum = 0;
    for(auto line: lines)
    {
        if(line.empty())
        {
            continue;
        }

        std::stringstream ss(line);
        std::string       buffer;

        std::vector<std::vector<int64_t>> sequences = {{}};
        while(ss >> buffer)
        {
            sequences.back().push_back(std::stoi(buffer));
        }

        while(!empty(sequences.back()))
        {
            auto current = sequences.back();
            sequences.emplace_back();

            for(int i = 1; i < current.size(); ++i)
            {
                sequences.back().push_back(current[i - 1] - current[i]);
            }
        }

        int64_t extrapolation = 0;
        for(auto sequence: sequences)
        {
            extrapolation += sequence.front();
        }

        sum += extrapolation;
    }

    std::cout << sum << std::endl;
}
