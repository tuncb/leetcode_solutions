module;
#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <functional>
#include <iterator>
#include <span>
#include <string_view>
#include <vector>
export module leet3;
import algoex;

// Given a string s, find the length of the longest substring without repeating characters.
// https://leetcode.com/problems/longest-substring-without-repeating-characters/
export auto leet3_max_non_repeating_substr(const std::string_view str) -> size_t
{
  using namespace algoex;
  std::vector<std::span<const char>> substrings;

  find_twin_member_blocks(str, std::back_inserter(substrings), std::identity());
  if (substrings.size() <= 0)
    return 0;
  auto elem = std::max_element(std::begin(substrings), std::end(substrings),
                               [](const auto &s1, const auto &s2) -> size_t { return s1.size() < s2.size(); });
  return elem->size();
}

TEST_CASE("Leet solution 3", "[leet3]")
{
  REQUIRE(leet3_max_non_repeating_substr("abcbb") == 3);
  REQUIRE(leet3_max_non_repeating_substr("abcabcbb") == 3);
  REQUIRE(leet3_max_non_repeating_substr("bbbbb") == 1);
  REQUIRE(leet3_max_non_repeating_substr("pwwkew") == 3);
}
