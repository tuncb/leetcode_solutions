module;
#include <iterator>
#include <optional>
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

// export template <std::forward_iterator Iter, typename T, class Generator>
// auto generate

} // namespace algoex
