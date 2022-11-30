// Copyright 2015-2018 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_FILL_HPP
#define BOOST_HISTOGRAM_DETAIL_FILL_HPP

#include <algorithm>
#include <boost/config/workaround.hpp>
#include <boost/histogram/axis/traits.hpp>
#include <boost/histogram/axis/variant.hpp>
#include <boost/histogram/detail/argument_traits.hpp>
#include <boost/histogram/detail/axes.hpp>
#include <boost/histogram/detail/linearize.hpp>
#include <boost/histogram/detail/make_default.hpp>
#include <boost/histogram/detail/optional_index.hpp>
#include <boost/histogram/detail/priority.hpp>
#include <boost/histogram/detail/tuple_slice.hpp>
#include <boost/histogram/fwd.hpp>
#include <boost/mp11/algorithm.hpp>
#include <boost/mp11/integral.hpp>
#include <boost/mp11/tuple.hpp>
#include <boost/mp11/utility.hpp>
#include <cassert>
#include <mutex>
#include <tuple>
#include <type_traits>

namespace boost {
namespace histogram {
namespace detail {

template <class T, class U>
struct sample_args_passed_vs_expected;

template <class... Passed, class... Expected>
struct sample_args_passed_vs_expected<std::tuple<Passed...>, std::tuple<Expected...>> {
  static_assert(!(sizeof...(Expected) > 0 && sizeof...(Passed) == 0),
                "error: accumulator requires samples, but sample argument is missing");
  static_assert(
      !(sizeof...(Passed) > 0 && sizeof...(Expected) == 0),
      "error: accumulator does not accept samples, but sample argument is passed");
  static_assert(sizeof...(Passed) == sizeof...(Expected),
                "error: numbers of passed and expected sample arguments differ");
  static_assert(
      std::is_convertible<std::tuple<Passed...>, std::tuple<Expected...>>::value,
      "error: sample argument(s) not convertible to accumulator argument(s)");
};

template <class A>
struct storage_grower {
  const A& axes_;
  struct {
    axis::index_type idx, old_extent;
    std::size_t new_stride;
  } data_[buffer_size<A>::value];
  std::size_t new_size_;

  storage_grower(const A& axes) noexcept : axes_(axes) {}

  void from_shifts(const axis::index_type* shifts) noexcept {
    auto dit = data_;
    std::size_t s = 1;
    for_each_axis(axes_, [&](const auto& a) {
      const auto n = axis::traits::extent(a);
      *dit++ = {0, n - std::abs(*shifts++), s};
      s *= n;
    });
    new_size_ = s;
  }

  // must be extents before any shifts were applied
  void from_extents(const axis::index_type* old_extents) noexcept {
    auto dit = data_;
    std::size_t s = 1;
    for_each_axis(axes_, [&](const auto& a) {
      const auto n = axis::traits::extent(a);
      *dit++ = {0, *old_extents++, s};
      s *= n;
    });
    new_size_ = s;
  }

  template <class S>
  void apply(S& storage, const axis::index_type* shifts) {
    auto new_storage = make_default(storage);
    new_storage.reset(new_size_);
    const auto dlast = data_ + axes_rank(axes_) - 1;
    for (auto&& x : storage) {
      auto ns = new_storage.begin();
      auto sit = shifts;
      auto dit = data_;
      for_each_axis(axes_, [&](const auto& a) {
        using opt = axis::traits::get_options<std::decay_t<decltype(a)>>;
        if (opt::test(axis::option::underflow)) {
          if (dit->idx == 0) {
            // axis has underflow and we are in the underflow bin:
            // keep storage pointer unchanged
            ++dit;
            ++sit;
            return;
          }
        }
        if (opt::test(axis::option::overflow)) {
          if (dit->idx == dit->old_extent - 1) {
            // axis has overflow and we are in the overflow bin:
            // move storage pointer to corresponding overflow bin position
            ns += (axis::traits::extent(a) - 1) * dit->new_stride;
            ++dit;
            ++sit;
            return;
          }
        }
        // we are in a normal bin:
        // move storage pointer to index position; apply positive shifts if any
        ns += (dit->idx + (*sit >= 0 ? *sit : 0)) * dit->new_stride;
        ++dit;
        ++sit;
      });
      // assign old value to new location
      *ns = x;
      // advance multi-dimensional index
      dit = data_;
      ++dit->idx;
      while (dit != dlast && dit->idx == dit->old_extent) {
        dit->idx = 0;
        ++(++dit)->idx;
      }
    }
    storage = std::move(new_storage);
  }
};

template <class T, class... Us>
auto fill_storage_element_impl(priority<2>, T&& t, const Us&... args) noexcept
    -> decltype(t(args...), void()) {
  t(args...);
}

template <class T, class U>
auto fill_storage_element_impl(priority<1>, T&& t, const weight_type<U>& w) noexcept
    -> decltype(t += w, void()) {
  t += w;
}

// fallback for arithmetic types and accumulators that do not handle the weight
template <class T, class U>
auto fill_storage_element_impl(priority<0>, T&& t, const weight_type<U>& w) noexcept
    -> decltype(t += w.value, void()) {
  t += w.value;
}

template <class T>
auto fill_storage_element_impl(priority<1>, T&& t) noexcept -> decltype(++t, void()) {
  ++t;
}

template <class T, class... Us>
void fill_storage_element(T&& t, const Us&... args) noexcept {
  fill_storage_element_impl(priority<2>{}, std::forward<T>(t), args...);
}

// t may be a proxy and then it is an rvalue reference, not an lvalue reference
template <class IW, class IS, class T, class U>
void fill_storage_2(IW, IS, T&& t, U&& u) noexcept {
  mp11::tuple_apply(
      [&](const auto&... args) {
        fill_storage_element(std::forward<T>(t), std::get<IW::value>(u), args...);
      },
      std::get<IS::value>(u).value);
}

// t may be a proxy and then it is an rvalue reference, not an lvalue reference
template <class IS, class T, class U>
void fill_storage_2(mp11::mp_int<-1>, IS, T&& t, const U& u) noexcept {
  mp11::tuple_apply(
      [&](const auto&... args) { fill_storage_element(std::forward<T>(t), args...); },
      std::get<IS::value>(u).value);
}

// t may be a proxy and then it is an rvalue reference, not an lvalue reference
template <class IW, class T, class U>
void fill_storage_2(IW, mp11::mp_int<-1>, T&& t, const U& u) noexcept {
  fill_storage_element(std::forward<T>(t), std::get<IW::value>(u));
}

// t may be a proxy and then it is an rvalue reference, not an lvalue reference
template <class T, class U>
void fill_storage_2(mp11::mp_int<-1>, mp11::mp_int<-1>, T&& t, const U&) noexcept {
  fill_storage_element(std::forward<T>(t));
}

template <class IW, class IS, class Storage, class Index, class Args>
auto fill_storage(IW, IS, Storage& s, const Index idx, const Args& a) noexcept {
  if (is_valid(idx)) {
    assert(idx < s.size());
    fill_storage_2(IW{}, IS{}, s[idx], a);
    return s.begin() + idx;
  }
  return s.end();
}

template <int S, int N>
struct linearize_args {
  template <class Index, class A, class Args>
  static void impl(mp11::mp_int<N>, Index&, const std::size_t, A&, const Args&) {}

  template <int I, class Index, class A, class Args>
  static void impl(mp11::mp_int<I>, Index& o, const std::size_t s, A& ax,
                   const Args& args) {
    const auto e = linearize(o, s, axis_get<I>(ax), std::get<(S + I)>(args));
    impl(mp11::mp_int<(I + 1)>{}, o, s * e, ax, args);
  }

  template <class Index, class A, class Args>
  static void apply(Index& o, A& ax, const Args& args) {
    impl(mp11::mp_int<0>{}, o, 1, ax, args);
  }
};

template <int S>
struct linearize_args<S, 1> {
  template <class Index, class A, class Args>
  static void apply(Index& o, A& ax, const Args& args) {
    linearize(o, 1, axis_get<0>(ax), std::get<S>(args));
  }
};

template <class A>
constexpr unsigned min(const unsigned n) noexcept {
  constexpr unsigned a = buffer_size<A>::value;
  return a < n ? a : n;
}

// not growing
template <class ArgTraits, class Storage, class Axes, class Args>
auto fill_2(ArgTraits, mp11::mp_false, const std::size_t offset, Storage& st,
            const Axes& axes, const Args& args) {
  mp11::mp_if<has_non_inclusive_axis<Axes>, optional_index, std::size_t> idx{offset};
  linearize_args<ArgTraits::start::value, min<Axes>(ArgTraits::nargs::value)>::apply(
      idx, axes, args);
  return fill_storage(typename ArgTraits::wpos{}, typename ArgTraits::spos{}, st, idx,
                      args);
}

// at least one axis is growing
template <class ArgTraits, class Storage, class Axes, class Args>
auto fill_2(ArgTraits, mp11::mp_true, const std::size_t, Storage& st, Axes& axes,
            const Args& args) {
  std::array<axis::index_type, ArgTraits::nargs::value> shifts;
  // offset must be zero for linearize_growth (value of offset argument is ignored)
  mp11::mp_if<has_non_inclusive_axis<Axes>, optional_index, std::size_t> idx{0};
  std::size_t stride = 1;
  bool update_needed = false;
  mp11::mp_for_each<mp11::mp_iota_c<min<Axes>(ArgTraits::nargs::value)>>([&](auto i) {
    auto& ax = axis_get<i>(axes);
    const auto extent = linearize_growth(idx, shifts[i], stride, ax,
                                         std::get<(ArgTraits::start::value + i)>(args));
    update_needed |= shifts[i] != 0;
    stride *= extent;
  });
  if (update_needed) {
    storage_grower<Axes> g(axes);
    g.from_shifts(shifts.data());
    g.apply(st, shifts.data());
  }
  return fill_storage(typename ArgTraits::wpos{}, typename ArgTraits::spos{}, st, idx,
                      args);
}

// pack original args tuple into another tuple (which is unpacked later)
template <int Start, int Size, class IW, class IS, class Args>
decltype(auto) pack_args(IW, IS, const Args& args) noexcept {
  return std::make_tuple(tuple_slice<Start, Size>(args), std::get<IW::value>(args),
                         std::get<IS::value>(args));
}

template <int Start, int Size, class IW, class Args>
decltype(auto) pack_args(IW, mp11::mp_int<-1>, const Args& args) noexcept {
  return std::make_tuple(tuple_slice<Start, Size>(args), std::get<IW::value>(args));
}

template <int Start, int Size, class IS, class Args>
decltype(auto) pack_args(mp11::mp_int<-1>, IS, const Args& args) noexcept {
  return std::make_tuple(tuple_slice<Start, Size>(args), std::get<IS::value>(args));
}

template <int Start, int Size, class Args>
decltype(auto) pack_args(mp11::mp_int<-1>, mp11::mp_int<-1>, const Args& args) noexcept {
  return std::make_tuple(args);
}

#if BOOST_WORKAROUND(BOOST_MSVC, >= 0)
#pragma warning(disable : 4702) // fixing warning would reduce code readability a lot
#endif

template <class ArgTraits, class S, class A, class Args>
auto fill(std::true_type, ArgTraits, const std::size_t offset, S& storage, A& axes,
          const Args& args) -> typename S::iterator {
  using growing = has_growing_axis<A>;

  // Sometimes we need to pack the tuple into another tuple:
  // - histogram contains one axis which accepts tuple
  // - user passes tuple to fill(...)
  // Tuple is normally unpacked and arguments are processed, this causes pos::nargs > 1.
  // Now we pack tuple into another tuple so that original tuple is send to axis.
  // Notes:
  // - has nice side-effect of making histogram::operator(1, 2) work as well
  // - cannot detect call signature of axis at compile-time in all configurations
  //   (axis::variant provides generic call interface and hides concrete
  //   interface), so we throw at runtime if incompatible argument is passed (e.g.
  //   3d tuple)

  if (axes_rank(axes) == ArgTraits::nargs::value)
    return fill_2(ArgTraits{}, growing{}, offset, storage, axes, args);
  else if (axes_rank(axes) == 1 &&
           axis::traits::rank(axis_get<0>(axes)) == ArgTraits::nargs::value)
    return fill_2(
        argument_traits_holder<
            1, 0, (ArgTraits::wpos::value >= 0 ? 1 : -1),
            (ArgTraits::spos::value >= 0 ? (ArgTraits::wpos::value >= 0 ? 2 : 1) : -1),
            typename ArgTraits::sargs>{},
        growing{}, offset, storage, axes,
        pack_args<ArgTraits::start::value, ArgTraits::nargs::value>(
            typename ArgTraits::wpos{}, typename ArgTraits::spos{}, args));
  return BOOST_THROW_EXCEPTION(
             std::invalid_argument("number of arguments != histogram rank")),
         storage.end();
}

#if BOOST_WORKAROUND(BOOST_MSVC, >= 0)
#pragma warning(default : 4702)
#endif

// empty implementation for bad arguments to stop compiler from showing internals
template <class ArgTraits, class S, class A, class Args>
auto fill(std::false_type, ArgTraits, const std::size_t, S& storage, A&, const Args&) ->
    typename S::iterator {
  return storage.end();
}

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* fill.hpp
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
*/