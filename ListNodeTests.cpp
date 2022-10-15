#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <memory>
#include <vector>
import ListNode;

TEST_CASE("ListNode", "[listnode]")
{
  using namespace listnode;
  using namespace std;

  auto vec = std::vector{1, 5, 8};
  auto node = ListNode<int>();

  copy(begin(vec), end(vec), back_inserter(node));

  REQUIRE(distance(begin(node), end(node)) == vec.size());

  auto are_equal = [](const int i, const ListNode<int> &node) { return i == node.value; };
  REQUIRE(std::equal(begin(vec), end(vec), begin(node), end(node), are_equal));
}