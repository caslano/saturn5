// Copyright 2015-2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_TUPLE_SLICE_HPP
#define BOOST_HISTOGRAM_DETAIL_TUPLE_SLICE_HPP

#include <boost/mp11/integer_sequence.hpp>
#include <tuple>
#include <type_traits>

namespace boost {
namespace histogram {
namespace detail {

template <std::size_t I, class T, std::size_t... K>
decltype(auto) tuple_slice_impl(T&& t, mp11::index_sequence<K...>) {
  return std::forward_as_tuple(std::get<(I + K)>(std::forward<T>(t))...);
}

template <std::size_t I, std::size_t N, class Tuple>
decltype(auto) tuple_slice(Tuple&& t) {
  constexpr auto S = std::tuple_size<std::decay_t<Tuple>>::value;
  static_assert(I + N <= S, "I, N must be a valid subset");
  return tuple_slice_impl<I>(std::forward<Tuple>(t), mp11::make_index_sequence<N>{});
}

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* tuple_slice.hpp
zT47vDXNg5YfP+SYp40XUZ8DGV/r4POZkyXaJlkqiMSGM+LtfhapXO7XXMywJPyaQA8G2spXaYykvJcxtsg46tPxwED6CVu0/FofZtG64kh0rmxBz3QM1Ua2CSXIgXVKU7w3+0M2JUieAoaH9VtZpt+WjdRv0+SeI/rWrLOvnTJ3oB3VHLkaXoywFrclIb/bgkN6Ob08h0+DeG6bqcaWKgK5q1mqht/P/TVLbZffbeOH8GHa
*/