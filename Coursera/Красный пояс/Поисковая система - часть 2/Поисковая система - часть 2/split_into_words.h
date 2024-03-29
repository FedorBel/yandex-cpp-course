#pragma once

#include <string>
#include <string_view>
#include <vector>

void LeftStrip(std::string_view& sv);

std::string_view ReadToken(std::string_view& sv);

std::vector<std::string_view> SplitIntoWords(std::string_view line);
