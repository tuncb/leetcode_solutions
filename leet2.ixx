module;
#include <catch2/catch_test_macros.hpp>
#include <numeric>
#include <optional>
export module leet2;

import algoex;
import listnode;

auto to_node(int val) -> listnode::ListNode<int>
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

auto from_node(const listnode::ListNode<int> &node) -> int
{
  using namespace listnode;
  auto base = 1;
  auto sumop = [&base](int current, const listnode::ListNode<int> &n) -> int {
    auto ret = current + n.value * base;
    base = base * 10;
    return ret;
  };

  return std::accumulate(begin(node), end(node), 0, sumop);
}

auto leet_2_add_two_numbers(const listnode::ListNode<int> &node1, const listnode::ListNode<int> &node2)
    -> listnode::ListNode<int>
{
  auto node = to_node(from_node(node1) + from_node(node2));
  return node;
}

TEST_CASE("Leet solution 2", "[leet2]")
{
  const auto check_solution = [](int val1, int val2) {
    auto node = leet_2_add_two_numbers(to_node(val1), to_node(val2));
    REQUIRE(val1 + val2 == from_node(node));
  };

  check_solution(342, 465);
  check_solution(0, 0);
  check_solution(9999999, 9999);
}
