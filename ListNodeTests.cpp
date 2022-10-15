#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <memory>
import ListNode;

TEST_CASE("ListNode", "[listnode]")
{
  ListNode<int> node{1};
  node.next = std::make_unique<ListNode<int>>(2);
  node.next->next = std::make_unique<ListNode<int>>(2);

  REQUIRE(std::distance(node.begin(), node.end()) == 3);
}