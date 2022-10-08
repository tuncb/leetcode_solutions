module;
#include <iterator>
#include <unordered_map>
#include <optional>
export module algoex;

namespace algoex {

  export template<std::forward_iterator Iter, class TwinProvider>
    auto find_twins(Iter first, Iter last, TwinProvider twin_provider) -> std::optional<std::pair<Iter, Iter>>
  {
    using T = std::iter_value_t<Iter>;
    std::unordered_map<T, Iter> map;
    for (; first != last; ++first)
    {
      const T twin = twin_provider(*first);
      if (auto iter = map.find(twin); iter != map.end()) {
        return std::pair< Iter, Iter>{ iter->second, first };
      }
      else {
        map.insert({ *first, first });
      }
    }

    return std::nullopt;
  }

}

//namespace rg = std::ranges;
//
//export template<rg::input_range R> requires rg::view<R>
//class custom_take_view : public rg::view_interface<custom_take_view<R>>
//{
//private:
//  R                                         base_{};
//  std::iter_difference_t<rg::iterator_t<R>> count_{};
//  rg::iterator_t<R>                         iter_{ std::begin(base_) };
//public:
//  custom_take_view() = default;
//
//  constexpr custom_take_view(R base, std::iter_difference_t<rg::iterator_t<R>> count)
//    : base_(base)
//    , count_(count)
//    , iter_(std::begin(base_))
//  {}
//
//  constexpr R base() const&
//  {
//    return base_;
//  }
//  constexpr R base()&&
//  {
//    return std::move(base_);
//  }
//
//  constexpr auto begin() const
//  {
//    return iter_;
//  }
//  constexpr auto end() const
//  {
//    return std::next(iter_, count_);
//  }
//
//  constexpr auto size() const requires rg::sized_range<const R>
//  {
//    const auto s = rg::size(base_);
//    const auto c = static_cast<decltype(s)>(count_);
//    return s < c ? 0 : s - c;
//  }
//};
//
//export template<class R>
//custom_take_view(R&& base, std::iter_difference_t<rg::iterator_t<R>>)
//->custom_take_view<rg::views::all_t<R>>;
//
//namespace details
//{
//  struct custom_take_range_adaptor_closure
//  {
//    std::size_t count_;
//    constexpr custom_take_range_adaptor_closure(std::size_t count) : count_(count)
//    {}
//
//    template <rg::viewable_range R>
//    constexpr auto operator()(R&& r) const
//    {
//      return custom_take_view(std::forward<R>(r), count_);
//    }
//  };
//
//  struct custom_take_range_adaptor
//  {
//    template<rg::viewable_range R>
//    constexpr auto operator () (R&& r, std::iter_difference_t<rg::iterator_t<R>> count)
//    {
//      return custom_take_view(std::forward<R>(r), count);
//    }
//
//    constexpr auto operator () (std::size_t count)
//    {
//      return custom_take_range_adaptor_closure(count);
//    }
//  };
//
//  export template <rg::viewable_range R>
//    constexpr auto operator | (R&& r, custom_take_range_adaptor_closure const& a)
//  {
//    return a(std::forward<R>(r));
//  }
//}
//
//namespace views
//{
//  export details::custom_take_range_adaptor custom_take;
//}

//export module algorithms_extra;
//
//namespace algoex {
//  //export template<class InputIt1, class InputIt2, class T>
//  //  constexpr auto exclusive_outer_product(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2) {
//
//
//  //}
//
//}
