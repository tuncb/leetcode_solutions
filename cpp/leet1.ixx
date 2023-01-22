module;
#include <catch2/catch_test_macros.hpp>
#include <iterator>
#include <vector>
export module leet1;

import algoex;

auto leet_1_two_sum(const std::vector<int> &nums, int target) -> std::optional<std::vector<int>>
{
  const auto b = std::ranges::begin(nums);
  auto twins_op = algoex::find_twins(nums, [target](int value) { return target - value; });
  if (twins_op.has_value())
  {
    const auto twins = twins_op.value();
    return std::vector<int>{static_cast<int>(std::distance(b, twins.first)),
                            static_cast<int>(std::distance(b, twins.second))};
  }
  else
    return std::nullopt;
}

TEST_CASE("Leet solution 1", "[leet1]")
{
  const auto check_solution = [](const std::vector<int> &vec, int target, const std::vector<int> &sol) {
    const auto solution_op = leet_1_two_sum(vec, target);
    REQUIRE(solution_op.has_value());
    REQUIRE(solution_op.value() == sol);
  };

  check_solution({2, 7, 11, 15}, 9, {0, 1});
  check_solution({3, 2, 4}, 6, {1, 2});
  check_solution({3, 3}, 6, {0, 1});
}