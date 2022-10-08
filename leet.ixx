module;
#include <optional>
#include <vector>
export module leet;

import algoex;

namespace leet
{

export auto leet_1_two_sum(std::vector<int> &nums, int target) -> std::optional<std::vector<int>>
{
  const auto b = nums.begin();
  auto twins_op = algoex::find_twins(nums.begin(), nums.end(), [target](int value) { return target - value; });
  if (twins_op.has_value())
  {
    const auto twins = twins_op.value();
    return std::vector<int>{static_cast<int>(twins.first - b), static_cast<int>(twins.second - b)};
  }
  else
    return std::nullopt;
}

} // namespace leet
