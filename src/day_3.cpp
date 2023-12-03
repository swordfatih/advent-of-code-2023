#include "days.hpp"

#include <map>
#include <numeric>

static bool is_symbol(char c)
{
    return !std::isdigit(c) && c != '.';
}

static void part_1()
{
    auto lines = split(read_file("inputs/input_3.txt"), "\n");

    size_t sum = 0;
    for(int i = 0; i < lines.size(); ++i)
    {
        std::string line = lines[i];

        std::cout << "line ";
        printf("%3d", i + 1);
        std::cout << ": ";

        std::string number;
        size_t      position;

        for(int k = 0; k < line.size(); ++k)
        {
            char c = line[k];

            if(std::isdigit(c))
            {
                if(number.empty())
                {
                    position = k;
                }

                number.push_back(c);
            }

            if((!std::isdigit(c) && !number.empty()) || (k == line.size() - 1 && !number.empty()))
            {
                int value = std::stoi(number);

                printf("%4d", value);

                int start = position == 0 ? 0 : position - 1;
                int end = position + number.size() >= lines[i].size() ? lines[i].size() - 1 : position + number.size();

                int old_sum = sum;
                for(int j = start; j <= end; ++j)
                {
                    if(i > 0 && is_symbol(lines[i - 1][j])) // upper line
                    {
                        sum += value;
                        break;
                    }

                    else if(is_symbol(lines[i][j])) // same line
                    {
                        sum += value;
                        break;
                    }

                    else if(i < lines.size() - 1 && !lines[i + 1].empty() && is_symbol(lines[i + 1][j])) // bottom line
                    {
                        sum += value;
                        break;
                    }
                }

                if(sum != old_sum)
                {
                    std::cout << "\x1B[32m[V]\033[0m";
                }
                else
                {
                    std::cout << "\x1B[31m[F]\033[0m";
                }

                number.clear();
            }
        }

        std::cout << std::endl;
    }

    std::cout << sum << std::endl;
}

static void part_2()
{
    auto lines = split(read_file("inputs/input_3.txt"), "\n");

    std::map<std::pair<int, int>, std::vector<int>> gears;
    const char                                      gear = '*';

    for(int i = 0; i < lines.size(); ++i)
    {
        std::string line = lines[i];

        std::string number;
        size_t      position;

        for(int k = 0; k < line.size(); ++k)
        {
            char c = line[k];

            if(std::isdigit(c))
            {
                if(number.empty())
                {
                    position = k;
                }

                number.push_back(c);
            }

            if((!std::isdigit(c) && !number.empty()) || (k == line.size() - 1 && !number.empty()))
            {
                int value = std::stoi(number);

                int start = position == 0 ? 0 : position - 1;
                int end = position + number.size() >= lines[i].size() ? lines[i].size() - 1 : position + number.size();

                for(int j = start; j <= end; ++j)
                {
                    if(i > 0 && lines[i - 1][j] == gear) // upper line
                    {
                        gears[std::make_pair(i - 1, j)].push_back(value);
                    }

                    if(lines[i][j] == gear) // same line
                    {
                        gears[std::make_pair(i, j)].push_back(value);
                    }

                    if(i < lines.size() - 1 && !lines[i + 1].empty() && lines[i + 1][j] == gear) // bottom line
                    {
                        gears[std::make_pair(i + 1, j)].push_back(value);
                    }
                }

                number.clear();
            }
        }
    }

    size_t sum = 0;
    for(auto [pos, values]: gears)
    {
        if(values.size() == 2)
        {
            sum += values[0] * values[1];
        }
    }

    std::cout << sum << std::endl;
}

void day_3()
{
    part_1();
    part_2();
}