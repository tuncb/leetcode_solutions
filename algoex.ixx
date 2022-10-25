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
auto find_twins(R range, TwinProvider twin_provider, Proj proj = {}) 
-> std::optional<std::ranges::ref_view<R>>
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
      auto r = std::ranges::subrange(iter->second, first);
      return r;
    }
    else
    {
      map.insert({*first, first});
    }
  }

  return std::nullopt;
}

export template <std::forward_iterator Iter, std::output_iterator<std::span<typename Iter::value_type>> OIter,
                 class TwinProvider>
auto find_twin_member_blocks(Iter first, Iter last, OIter oIter, TwinProvider twin_provider) -> void
{
  auto res = find_twins(std::ranges::subrange(first, last), twin_provider);
  while (res)
  {
    *oIter = std::span{first, res.value().end()};
    ++oIter;
    first = res.value().end();
    res = find_twins(std::ranges::subrange(first, last), twin_provider);
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
