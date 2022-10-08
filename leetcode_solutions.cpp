#include <format>
#include <iostream>
#include <vector>
import leet;

int main()
{
  std::vector<int> i1 = {2, 7, 11, 15};
  const auto t1 = 9;
  std::vector<int> i2 = {3, 2, 4};
  const auto t2 = 6;
  std::vector<int> i3 = {3, 3};
  const auto t3 = 6;

  const auto twins_op = leet::leet_1_two_sum(i3, t3);
  if (twins_op.has_value())
  {
    std::cout << std::format("Solution {} {}", twins_op.value()[0], twins_op.value()[1]);
  }
}
