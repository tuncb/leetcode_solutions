module;
#include <numeric>
#include <optional>
#include <vector>
export module leet;

import algoex;
import ListNode;

namespace leet
{

export auto leet_1_two_sum(const std::vector<int> &nums, int target) -> std::optional<std::vector<int>>
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

export auto to_node(int val) -> listnode::ListNode<int>
{
  using namespace listnode;
  auto node = ListNode<int>(0);
  if (val <= 0)
    return node;

  auto base = 1;
  auto value = val;
  auto divider = [&base](int &value) -> std::optional<int> {
    if (value <= 0)
      return std::nullopt;

    const auto mod = value % (10 * base);
    value = value - mod;
    const auto ret = mod / base;
    base = base * 10;
    return ret;
  };

  algoex::divide(value, back_inserter(node), divider);
  return node;
}

export auto from_node(listnode::ListNode<int> &node) -> int
{
  using namespace listnode;
  auto base = 1;
  auto sumop = [&base](int current, listnode::ListNode<int> &n) -> int {
    auto ret = current + n.value * base;
    base = base * 10;
    return ret;
  };

  return std::accumulate(begin(node), end(node), 0, sumop);
}

export auto leet_2_add_two_numbers(listnode::ListNode<int> &node1, listnode::ListNode<int> &node2)
    -> listnode::ListNode<int>
{
  auto node = to_node(from_node(node1) + from_node(node2));
  return node;
}

} // namespace leet
