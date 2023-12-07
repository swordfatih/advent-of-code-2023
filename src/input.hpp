#pragma once

#include <filesystem>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

std::string              read_file(const std::filesystem::path& path);
std::vector<std::string> split(const std::string& string, const std::string_view& delimiter);
int64_t                  read_int(std::stringstream& stream);
std::string              read_string(std::stringstream& stream);
void                     replace(std::stringstream& stream, const std::string& string);