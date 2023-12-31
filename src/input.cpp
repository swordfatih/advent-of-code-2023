#include <fstream>
#include <ranges>

#include "input.hpp"

std::string read_file(const std::filesystem::path& path)
{
    std::ifstream file{path, std::ios::in | std::ios::binary};
    const size_t  size = std::filesystem::file_size(path);

    std::string content(size, '\0');
    file.read(content.data(), size);

    return content;
}

std::vector<std::string> split(const std::string& string, const std::string_view& delimiter)
{
    std::vector<std::string> tokens;
    for(const auto token: std::views::split(string, delimiter))
    {
        tokens.push_back(std::string{std::string_view{token}});
    }

    return tokens;
}

int64_t read_int(std::stringstream& stream)
{
    std::string buf;
    stream >> buf;
    return std::stoi(buf);
}

std::string read_string(std::stringstream& stream)
{
    std::string buf;
    stream >> buf;
    return buf;
}

void replace(std::stringstream& stream, const std::string& string)
{
    stream.clear();
    stream.str(string);
}