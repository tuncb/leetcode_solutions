#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <memory>
#include <vector>
import listnode;

TEST_CASE("ListNode", "[listnode]")
{
  using namespace listnode;
  using namespace std;

  auto n = make_node(10);
  REQUIRE(n.value == 10);
  REQUIRE(!n.next);

  auto vec = std::vector{1, 5, 8};
  auto node = ListNode<int>();
  copy(begin(vec), end(vec), back_inserter(node));

  REQUIRE(distance(begin(node), end(node)) == vec.size());

  auto are_equal = [](const int i, const ListNode<int> &node) { return i == node.value; };
  REQUIRE(std::equal(begin(vec), end(vec), begin(node), end(node), are_equal));
}