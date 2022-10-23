module;
#include <iterator>
#include <optional>
#include <span>
#include <unordered_map>
export module algoex;

namespace algoex
{

export template <std::forward_iterator Iter, class TwinProvider>
auto find_twins(Iter first, Iter last, TwinProvider twin_provider) -> std::optional<std::pair<Iter, Iter>>
{
  using T = std::iter_value_t<Iter>;
  std::unordered_map<T, Iter> map;
  for (; first != last; ++first)
  {
    const T twin = twin_provider(*first);
    if (auto iter = map.find(twin); iter != map.end())
    {
      return std::pair<Iter, Iter>{iter->second, first};
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
  using T = Iter::value_type;
  auto res = find_twins(first, last, twin_provider);
  while (res)
  {
    *oIter = std::span{first, res.value().second};
    ++oIter;
    first = res.value().second;
    res = find_twins(first, last, twin_provider);
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
