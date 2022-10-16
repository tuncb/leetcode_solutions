#include <catch2/catch_session.hpp>
#include <catch2/catch_test_macros.hpp>
#include <vector>
import leet;

TEST_CASE("Leet solution 1", "[leet1]")
{
  const auto check_solution = [](const std::vector<int> &vec, int target, const std::vector<int> &sol) {
    const auto solution_op = leet::leet_1_two_sum(vec, target);
    REQUIRE(solution_op.has_value());
    REQUIRE(solution_op.value() == sol);
  };

  check_solution({2, 7, 11, 15}, 9, {0, 1});
  check_solution({3, 2, 4}, 6, {1, 2});
  check_solution({3, 3}, 6, {0, 1});
}

TEST_CASE("Leet solution 2", "[leet2]")
{
  const auto check_solution = [](int val1, int val2) {
    auto node1 = leet::to_node(val1);
    auto node2 = leet::to_node(val2);
    auto node = leet::leet_2_add_two_numbers(node1, node2);
    REQUIRE(val1 + val2 == leet::from_node(node));
  };

  check_solution(342, 465);
  check_solution(0, 0);
  check_solution(9999999, 9999);
}

int main(int argc, char *argv[])
{
  Catch::Session session;
  int returnCode = session.applyCommandLine(argc, argv);
  if (returnCode != 0) // Indicates a command line error
    return returnCode;

  // writing to session.configData() or session.Config() here
  // overrides command line args
  // only do this if you know you need to

  int numFailed = session.run();

  // numFailed is clamped to 255 as some unices only use the lower 8 bits.
  // This clamping has already been applied, so just return it here
  // You can also do any post run clean-up here
  return numFailed;
}
