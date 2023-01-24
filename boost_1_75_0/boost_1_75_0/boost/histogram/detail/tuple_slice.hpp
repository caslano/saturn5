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
YuedpnqfUyTbtDkWiDsiEl8J8UKzyurJqFZpAKODE9uZwnPdhD3tNY79c47NCP/sxDt2L0s33ZscoWKyS4vGjnGbhhHMKXruCbzDWUEGtcAygfnsRIHHOfXOytydlLoOLKj6QNNmRCm7Qj42hK0Cym6DbmfKvOTadRfMFcso+/vWuI/B+WOHXUWwQw97C6qyVbKuQD5B04FWZ7RmDbMOUdt3x6IE5ETK98Uu9jhZA3Le8ECyrQdE3OUfpl80r+llvpoyZnWV1OHw5iqZBPRtx8P12zNYV0aOm9cvG9xja41XmymXIFaHmEN+FV3o6S15ka+k0JbSRCm1xNSyJ4YpkgtLRbAk3BwAULoXkfCidBGLZk3exqGBw5EHWfnhvbmwJj4FWs1kKN6OHzF/i+MdMkTCyC0pPcoQ5rfrricQps/Pbul7eiINmA0FsYKtuoB73aNpXcZt+N2285Wp87UoWt+sMOzMFTjLYzjgRnVEct9m3CJhOs1klYs4aY5XIy8tCzclsFoSDocZ6V0yv91o3IKS4seWgqeAnXw39218npr+DjB+PQ7YCeD6mUp55KIKHLAAktuwWVe5xjyB11Wil9+IgKbs5Xx4oA4kHNgHeRmJ0l0AeTl8LjzeJj+Yr6a3U7Slyb+gZrSr+EUOCzUOprdr++FeWLYzk6fruFw/q9RBIPa0o+PdzrLmVopGuHHbHARchTQX4+COpQNj
*/