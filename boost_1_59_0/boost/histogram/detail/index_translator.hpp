// Copyright 2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_INDEX_TRANSLATOR_HPP
#define BOOST_HISTOGRAM_DETAIL_INDEX_TRANSLATOR_HPP

#include <algorithm>
#include <boost/histogram/axis/traits.hpp>
#include <boost/histogram/axis/variant.hpp>
#include <boost/histogram/detail/relaxed_equal.hpp>
#include <boost/histogram/detail/relaxed_tuple_size.hpp>
#include <boost/histogram/fwd.hpp>
#include <boost/histogram/multi_index.hpp>
#include <boost/mp11/algorithm.hpp>
#include <boost/mp11/integer_sequence.hpp>
#include <cassert>
#include <initializer_list>
#include <tuple>
#include <vector>

namespace boost {
namespace histogram {
namespace detail {

template <class A>
struct index_translator {
  using index_type = axis::index_type;
  using multi_index_type = multi_index<relaxed_tuple_size_t<A>::value>;
  using cref = const A&;

  cref dst, src;
  bool pass_through[buffer_size<A>::value];

  index_translator(cref d, cref s) : dst{d}, src{s} { init(dst, src); }

  template <class T>
  void init(const T& a, const T& b) {
    std::transform(a.begin(), a.end(), b.begin(), pass_through,
                   [](const auto& a, const auto& b) {
                     return axis::visit(
                         [&](const auto& a) {
                           using U = std::decay_t<decltype(a)>;
                           return relaxed_equal{}(a, axis::get<U>(b));
                         },
                         a);
                   });
  }

  template <class... Ts>
  void init(const std::tuple<Ts...>& a, const std::tuple<Ts...>& b) {
    using Seq = mp11::mp_iota_c<sizeof...(Ts)>;
    mp11::mp_for_each<Seq>([&](auto I) {
      pass_through[I] = relaxed_equal{}(std::get<I>(a), std::get<I>(b));
    });
  }

  template <class T>
  static index_type translate(const T& dst, const T& src, index_type i) noexcept {
    assert(axis::traits::is_continuous<T>::value == false); // LCOV_EXCL_LINE: unreachable
    return dst.index(src.value(i));
  }

  template <class... Ts, class It>
  void impl(const std::tuple<Ts...>& a, const std::tuple<Ts...>& b, It i,
            index_type* j) const noexcept {
    using Seq = mp11::mp_iota_c<sizeof...(Ts)>;
    mp11::mp_for_each<Seq>([&](auto I) {
      if (pass_through[I])
        *(j + I) = *(i + I);
      else
        *(j + I) = this->translate(std::get<I>(a), std::get<I>(b), *(i + I));
    });
  }

  template <class T, class It>
  void impl(const T& a, const T& b, It i, index_type* j) const noexcept {
    const bool* p = pass_through;
    for (unsigned k = 0; k < a.size(); ++k, ++i, ++j, ++p) {
      if (*p)
        *j = *i;
      else {
        const auto& bk = b[k];
        axis::visit(
            [&](const auto& ak) {
              using U = std::decay_t<decltype(ak)>;
              *j = this->translate(ak, axis::get<U>(bk), *i);
            },
            a[k]);
      }
    }
  }

  template <class Indices>
  auto operator()(const Indices& seq) const noexcept {
    auto mi = multi_index_type::create(seq.size());
    impl(dst, src, seq.begin(), mi.begin());
    return mi;
  }
};

template <class Axes>
auto make_index_translator(const Axes& dst, const Axes& src) noexcept {
  return index_translator<Axes>{dst, src};
}

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* index_translator.hpp
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
*/