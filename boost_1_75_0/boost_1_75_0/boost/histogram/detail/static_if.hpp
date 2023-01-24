// Copyright 2018-2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_STATIC_IF_HPP
#define BOOST_HISTOGRAM_DETAIL_STATIC_IF_HPP

#include <type_traits>
#include <utility>

namespace boost {
namespace histogram {
namespace detail {

template <class T, class F, class... Args>
constexpr decltype(auto) static_if_impl(
    std::true_type, T&& t, F&&,
    Args&&... args) noexcept(noexcept(std::declval<T>()(std::declval<Args>()...))) {
  return std::forward<T>(t)(std::forward<Args>(args)...);
}

template <class T, class F, class... Args>
constexpr decltype(auto) static_if_impl(
    std::false_type, T&&, F&& f,
    Args&&... args) noexcept(noexcept(std::declval<F>()(std::declval<Args>()...))) {
  return std::forward<F>(f)(std::forward<Args>(args)...);
}

template <bool B, class... Ts>
constexpr decltype(auto) static_if_c(Ts&&... ts) noexcept(
    noexcept(static_if_impl(std::integral_constant<bool, B>{}, std::declval<Ts>()...))) {
  return static_if_impl(std::integral_constant<bool, B>{}, std::forward<Ts>(ts)...);
}

template <class Bool, class... Ts>
constexpr decltype(auto) static_if(Ts&&... ts) noexcept(
    noexcept(static_if_impl(Bool{}, std::declval<Ts>()...))) {
  return static_if_impl(Bool{}, std::forward<Ts>(ts)...);
}

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* static_if.hpp
Ai9pT/leLNXhCx7yu/N3soWP1HMEp+9iAkW6dVQYpphR3rc29/tJytjlr28hO3QLgeFkCgvn8GMHPTd9wXtXg9BqubLeC+enM78mYzghnDMX5U5Nsad6MxBeVJCAbV6r87X0yUlfvLLRYZDSVHpPuBeSEO40XHMODnOtCAHWAG67uZm5lR3NCtn7+2Dr3NeCQBYalCC3SkliAS2Qi/fxV2WrGODGqvHDYjOLF/irQmozuOMepTnApqKtu3burKzeLUHGg3bnSi4dq2kM44tZ0TR6FvF0lqnMXNvolsSYGz/phA9mW6+NViGCKOFqnauceMFC4BF5Oy7qRV/Idbul86H46zJsO835aE3NtFSCw/ZhluTMjz69/ilZUqiaxjYgljNMnQl8tAhxglgvVN85boD56AgEIGH7kTH0PFflvNPDbZUY1sobpP8H6U1zN8CLP3VuGRoscmIqbkRD3I5YRIBWhRGOgUv2WO1ysLN98cao7NeGjr62Nv3zAVu6SqOE2NNKLaFt+ddGEpxatl/bxgEi2DYGvwAaudxujpHEzajUUek0oxe3QxXQUtvyxcXjip/cDXdInuHFzLrEB7NYrnEvuDyDFNX4SXkiXsct6io554AsHdFaAwJSITfIoO+PYn1NGDo0QzZOzPd+zcyJZa5qpx40YTCX518N+00Dun6nWi76tgVbO+r5w6L7qByS/iKJULEEtVpVZXnP
*/