// Copyright 2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_NON_MEMBER_CONTAINER_ACCESS_HPP
#define BOOST_HISTOGRAM_DETAIL_NON_MEMBER_CONTAINER_ACCESS_HPP

#if __cpp_lib_nonmember_container_access >= 201411

#include <iterator>

namespace boost {
namespace histogram {
namespace detail {

using std::data;
using std::size;

} // namespace detail
} // namespace histogram
} // namespace boost

#else

#include <initializer_list>
#include <type_traits>

namespace boost {
namespace histogram {
namespace detail {

template <class C>
constexpr auto data(C& c) -> decltype(c.data()) {
  return c.data();
}

template <class C>
constexpr auto data(const C& c) -> decltype(c.data()) {
  return c.data();
}

template <class T, std::size_t N>
constexpr T* data(T (&array)[N]) noexcept {
  return array;
}

template <class E>
constexpr const E* data(std::initializer_list<E> il) noexcept {
  return il.begin();
}

template <class C>
constexpr auto size(const C& c) -> decltype(c.size()) {
  return c.size();
}

template <class T, std::size_t N>
constexpr std::size_t size(const T (&)[N]) noexcept {
  return N;
}

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

#endif // BOOST_HISTOGRAM_DETAIL_NON_MEMBER_CONTAINER_ACCESS_HPP

/* non_member_container_access.hpp
xK9WXzAEah5KkxmdefunbPi35KHeXrs8/x5X2AP9eGe00s0OoHlyt769OriCjpowwmC78UNMZJNjR6sU5PtX0GnDC2wtqu75GPuXk02QfghbdHXxWnb6yAHVivXPp9im81ednGFONXcQ5afHtND6OAraVqD8vduZDxHjPMTJoj5uMpQFsksRjv1JpPZRztzubmZtgKL857I/fB5VRMBPVf3bckw3/MRZeBT+9xN2PjsvJdX/2zp//79b5/85FgjQ++wDn2jclSYVVNoWygjbblCa6ast+NCkd2ByssUYV6Bjr6ZNnElyMqDFJH+erDHIEmRnbWwxryD3e0BLsYaHhGT+Xajj3nTV+qGxGcl6PjsqSWho55daz6cmDol+uFAVYGco5uwGsro5eB/wh0u8zroWnjh5jAH/IkjpAvfK23Urzc6IlOV+juLROKL/V+n8c1T/TwP9J5uHWjnRF7aEzXu2pOve1xzVSFrIdl+ivjT29PcISH5m5ZlQg8yC4Vxkhe/fKZJjqCM5JQ4UO6HUFyXvslb6iEiTW2szj+Qkz3cqrSR+znaCOh5L7ksAdWlH1+akiYgRD79CEGVciHHTf75X5NjFq7/YkFvR/HvrHPF8yrxL8KoJOp29IOZnfi4gOGs6Q7iYVp3YegVCraq/jocaVL8Q/Jj6C3Nf1AnqhOqZAt7oDmQmxVlvBEWonCDZT9UgwJiCUg1m77wM
*/