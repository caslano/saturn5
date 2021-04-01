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
g6ak8vyIOnWl+tJtuGG5/oUtDVQm91cYIdHRGr2KJ1Da7WrRBJrmnKbCFpmh45ONf6gp3AmRao1A0L8+xBgiIgoI9ETgDP/XjKgvQxfLW4XGPO6axgYA9komzUmf8ITksXJ5WHoSKEU1oCdNNq0vHhk6/dcxzGBfuBatjD58wx6Q1N82PXJ0Z6UPxdcyrs1DI9wG2FNepvkRmA+RxKn3cvO/zFqdiBn4ZTIT7vnD01Sx6+bCqlBp0f47tVdfJOcqVRYwqHBV5NiH33Gigq7uADd7/UlALmWffnMwBOJ51tgVH7DQRomfJMgld9w7zf2v71U1GM2RBPIVnYcC9fDK4m/Fsa+co+Ikv8/SE+Itmx1v622XsP9DNsFNj0AqOJxkx/rMzHp7Ouaau6YmEcUgB9txKa61OqacR+dRdQgNskGw1mEds6h8isMwSfTBrMs+E8IzzNvoKbAnBGdx14TWM9yX7UNkWCcTHWtRMeadiJX8wpWmqDp/qtU2Zqo/XW/MV6iXL0H7big+cmXL0sbPtwjZw15m52wEiYC5/6rQPlRMduBvbe1bRFWS8A==
*/