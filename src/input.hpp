#pragma once

#include <filesystem>
#include <string>
#include <string_view>
#include <vector>

std::string              read_file(const std::filesystem::path& path);
std::vector<std::string> split(const std::string& string, const std::string_view& delimiter);