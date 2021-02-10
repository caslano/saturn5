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
Vo4zDye9U/jx06ef4Af4+OHjhwjOuZZCwdALPRJ2HMHnJPT8lvHHx44Tv0YgPHDVqaBuMunAmdQ/cCsA20rGQjuRAHeQCBdbOcIbqcFnAlKpMNOXV3f9we8RPGQyzghkakpwmSlVAhmfCLAiFnIywyi49WBSNEfwRDqPgKWXRnfQtwAvbO4Ig9xz5QzwCZeKj9AR95B5X7ifu924tArZdxMTu248D7+T+fw5kjskkfMpmMKDN1A6EQGNjCA3iUzpioJgZ1GOlHRZtGCDrnTSNRacUIqw0E4KN6MtYFjJE9EwKJCx9HRxRjty9ZCZfGkg6kgoaWk1OkIdcFBiUOYISpxINgwOkc9dVJoGgTemZsE3AaORDBydDaE/PIIRd9JF8L1/8/Xy9ga+n11fnw1u7uDyAs4GdwT2R39wjqmX6MyCeCyscOjcgswLJUVS+cT/wx3d1rHUsSoTAUchf9lRrUdwN13uyUvlJXW1WmH9+PLXzZfrAcQZt9AmADZBzbFyWBw7mZyU2smxDsXpIXSd/rLJkrwxrGZeiMqaBkI7w4wqEbVeX1ZqR4w59xUyZUPjFCP/SuixzxoALbF3gdO+1skuwZd6c/jrotqdC9QFCO22KX1jQd4qyS6iYGwlvgyCKg4XAV8pFNqMF4XQ
*/