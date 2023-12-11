#include "days.hpp"

#include <fstream>
#include <map>
#include <set>
#include <stack>

enum Type : char
{
    NOT_FOUND = 0,
    START = 'S',
    GROUND = '.',
    BOTTOM_RIGHT = 'F',
    BOTTOM_LEFT = '7',
    BOTTOM_TOP = '|',
    LEFT_RIGHT = '-',
    TOP_LEFT = 'J',
    TOP_RIGHT = 'L'
};

enum Direction : int
{
    LEFT = 0,
    TOP,
    RIGHT,
    BOTTOM
};

typedef std::pair<int64_t, int64_t> Position;

struct Tile
{
    Type               type = NOT_FOUND;
    uint64_t           x;
    uint64_t           y;
    std::vector<Tile*> adjacents;

    void find_adjacents(std::vector<std::vector<Tile>>& tiles)
    {
        uint64_t height = tiles.size();
        uint64_t width = tiles[0].size();

        adjacents.push_back(x > 0 ? &tiles[y][x - 1] : nullptr);
        adjacents.push_back(y > 0 ? &tiles[y - 1][x] : nullptr);
        adjacents.push_back(x < width - 1 ? &tiles[y][x + 1] : nullptr);
        adjacents.push_back(y < height - 1 ? &tiles[y + 1][x] : nullptr);
    }

    bool left() const
    {
        return type == START || type == BOTTOM_LEFT || type == LEFT_RIGHT || type == TOP_LEFT;
    }

    bool right() const
    {
        return type == START || type == BOTTOM_RIGHT || type == LEFT_RIGHT || type == TOP_RIGHT;
    }

    bool top() const
    {
        return type == START || type == TOP_LEFT || type == TOP_RIGHT || type == BOTTOM_TOP;
    }

    bool bottom() const
    {
        return type == START || type == BOTTOM_LEFT || type == BOTTOM_RIGHT || type == BOTTOM_TOP;
    }

    // rel: relative position of the other tile
    bool linked(const Tile& other, Direction rel)
    {
        return rel == LEFT && left() && other.right() || rel == RIGHT && right() && other.left() || rel == TOP && top() && other.bottom() || rel == BOTTOM && bottom() && other.top();
    }
};

void print_grid(std::vector<std::vector<Tile>>& tiles, std::set<Position>& scaled, std::set<Position>& alive)
{
    std::ofstream file("file.txt");

    for(uint64_t y = 0; y < tiles.size(); ++y)
    {
        for(uint64_t x = 0; x < tiles[0].size(); ++x)
        {
            if(scaled.count(std::make_pair(y * 2 + 1, x * 2 + 1)) > 0)
            {
                file << 'O';
            }
            else if(alive.count(std::make_pair(y * 2 + 1, x * 2 + 1)) > 0)
            {
                file << '-';
            }
            else
            {
                file << ' ';
            }
        }

        file << std::endl;
    }
}

void erase_outbounds(const std::set<Position>& loop, std::set<Position>& alive)
{
    std::stack<Position> to_visit;

    to_visit.push({0, 0});

    while(!to_visit.empty())
    {
        auto current = to_visit.top();
        alive.erase(current);
        to_visit.pop();

        Position directions[4]{{0, -1}, {-1, 0}, {0, 1}, {1, 0}};

        for(auto direction: directions)
        {
            Position next = std::make_pair(current.first + direction.first, current.second + direction.second);

            if(alive.count(next) > 0 && loop.count(next) == 0)
            {
                to_visit.push(next);
            }
        }
    }
}

void day_10()
{
    auto lines = split(read_file("inputs/input_10.txt"), "\n");

    std::vector<std::vector<Tile>> tiles;
    Position                       start;

    for(uint64_t y = 0; y < lines.size(); ++y)
    {
        if(lines[y].empty())
        {
            continue;
        }

        tiles.emplace_back();

        for(uint64_t x = 0; x < lines[y].size(); ++x)
        {
            tiles[y].push_back({Type{lines[y][x]}, x, y});

            if(lines[y][x] == START)
            {
                start = std::make_pair(y, x);
            }
        }
    }

    Tile*  last = nullptr;
    Tile*  current = &tiles[start.first][start.second];
    size_t count = 0;

    std::vector<Position> loop;
    while(true)
    {
        count++;
        current->find_adjacents(tiles);
        loop.push_back(std::make_pair(current->y * 2 + 1, current->x * 2 + 1));

        for(int i = 0; i < current->adjacents.size(); ++i)
        {
            auto adjacent = current->adjacents[i];

            if(adjacent != nullptr && adjacent != last)
            {
                if(current->linked(*adjacent, Direction{i}))
                {
                    last = current;
                    current = adjacent;
                    break;
                }
            }
        }

        if(current->type == START && last != nullptr)
        {
            std::cout << "total: " << count << std::endl
                      << "mid: " << count / 2 << std::endl;
            break;
        }
    }

    std::set<Position> filled_loop;
    for(uint64_t i = 0; i < loop.size(); ++i)
    {
        filled_loop.emplace(loop[i]);

        int delta_x = loop[i].first - loop[(i + 1) % loop.size()].first;
        int delta_y = loop[i].second - loop[(i + 1) % loop.size()].second;

        if(delta_x == 0)
        {
            filled_loop.emplace(std::make_pair(loop[i].first, loop[i].second - delta_y / 2));
        }
        else if(delta_y == 0)
        {
            filled_loop.emplace(std::make_pair(loop[i].first - delta_x / 2, loop[i].second));
        }
    }

    std::set<Position> alive;

    for(uint64_t y = 0; y < tiles.size() * 2 + 2; ++y)
    {
        for(uint64_t x = 0; x < tiles[0].size() * 2 + 2; ++x)
        {
            alive.emplace(std::make_pair(y, x));
        }
    }

    erase_outbounds(filled_loop, alive);

    uint64_t sum = 0;
    for(uint64_t y = 0; y < tiles.size(); ++y)
    {
        for(uint64_t x = 0; x < tiles[0].size(); ++x)
        {
            Position pos = std::make_pair(y * 2 + 1, x * 2 + 1);
            if(alive.count(pos) > 0 && filled_loop.count(pos) == 0)
            {
                sum++;
            }
        }
    }

    std::cout << "alive: " << sum << std::endl;

    print_grid(tiles, filled_loop, alive);
}