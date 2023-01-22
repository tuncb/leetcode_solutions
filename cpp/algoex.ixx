module;
#include <iterator>
#include <optional>
#include <ranges>
#include <span>
#include <unordered_map>
export module algoex;

namespace algoex
{

export template <std::ranges::input_range R, class TwinProvider, class Proj = std::identity>
auto find_twins(R &&range, TwinProvider twin_provider, Proj proj = {})
    -> std::optional<std::pair<std::ranges::iterator_t<R>, std::ranges::iterator_t<R>>>
{
  using Iter = std::ranges::iterator_t<R>;
  using T = std::iter_value_t<Iter>;
  std::unordered_map<T, Iter> map;
  auto first = std::ranges::begin(range);
  auto last = std::ranges::end(range);
  for (; first != last; ++first)
  {
    const T twin = std::invoke(twin_provider, std::invoke(proj, *first));
    if (auto iter = map.find(twin); iter != map.end())
    {
      return std::make_pair(iter->second, first);
    }
    else
    {
      map.insert({*first, first});
    }
  }

  return std::nullopt;
}

export template <std::ranges::input_range R, std::output_iterator<std::span<std::ranges::range_value_t<R>>> OIter,
                 class TwinProvider, class Proj = std::identity>
auto find_twin_member_blocks(R &&range, OIter oIter, TwinProvider twin_provider, Proj proj = {}) -> void
{
  auto first = std::ranges::begin(range);
  auto last = std::ranges::end(range);
  auto res = find_twins(std::ranges::subrange(first, last), twin_provider, proj);
  while (res)
  {
    *oIter = std::span{first, res.value().second};
    ++oIter;
    first = res.value().second;
    res = find_twins(std::ranges::subrange(first, last), twin_provider, proj);
  }
}

export template <typename T, std::output_iterator<T> Iter, class Divider>
auto divide(T &val, Iter iter, Divider divider)
{
  auto retop = divider(val);
  while (retop)
  {
    *iter = *retop;
    ++iter;
    retop = divider(val);
  }
}

} // namespace algoex
