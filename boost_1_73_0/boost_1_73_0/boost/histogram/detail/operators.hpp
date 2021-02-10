// Copyright 2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_OPERATORS_HPP
#define BOOST_HISTOGRAM_DETAIL_OPERATORS_HPP

#include <boost/histogram/detail/detect.hpp>
#include <boost/mp11/algorithm.hpp>
#include <boost/mp11/list.hpp>
#include <boost/mp11/utility.hpp>

namespace boost {
namespace histogram {
namespace detail {

template <class T, class U>
using if_not_same_and_has_eq =
    std::enable_if_t<(!std::is_same<T, U>::value && has_method_eq<T, U>::value), bool>;

// totally_ordered is for types with a <= b == !(a > b) [floats with NaN violate this]
// Derived must implement <,== for symmetric form and <,>,== for non-symmetric.

// partially_ordered is for types with a <= b == a < b || a == b [for floats with NaN]
// Derived must implement <,== for the symmetric form and <,>,== for non-symmetric.

template <class T, class U>
struct mirrored {
  friend bool operator<(const U& a, const T& b) noexcept { return b > a; }
  friend bool operator>(const U& a, const T& b) noexcept { return b < a; }
  friend bool operator==(const U& a, const T& b) noexcept { return b == a; }
  friend bool operator<=(const U& a, const T& b) noexcept { return b >= a; }
  friend bool operator>=(const U& a, const T& b) noexcept { return b <= a; }
  friend bool operator!=(const U& a, const T& b) noexcept { return b != a; }
};

template <class T>
struct mirrored<T, void> {
  template <class U>
  friend if_not_same_and_has_eq<T, U> operator<(const U& a, const T& b) noexcept {
    return b > a;
  }
  template <class U>
  friend if_not_same_and_has_eq<T, U> operator>(const U& a, const T& b) noexcept {
    return b < a;
  }
  template <class U>
  friend if_not_same_and_has_eq<T, U> operator==(const U& a, const T& b) noexcept {
    return b == a;
  }
  template <class U>
  friend if_not_same_and_has_eq<T, U> operator<=(const U& a, const T& b) noexcept {
    return b >= a;
  }
  template <class U>
  friend if_not_same_and_has_eq<T, U> operator>=(const U& a, const T& b) noexcept {
    return b <= a;
  }
  template <class U>
  friend if_not_same_and_has_eq<T, U> operator!=(const U& a, const T& b) noexcept {
    return b != a;
  }
};

template <class T>
struct mirrored<T, T> {
  friend bool operator>(const T& a, const T& b) noexcept { return b.operator<(a); }
};

template <class T, class U>
struct equality {
  friend bool operator!=(const T& a, const U& b) noexcept { return !a.operator==(b); }
};

template <class T>
struct equality<T, void> {
  template <class U>
  friend if_not_same_and_has_eq<T, U> operator!=(const T& a, const U& b) noexcept {
    return !(a == b);
  }
};

template <class T, class U>
struct totally_ordered_impl : equality<T, U>, mirrored<T, U> {
  friend bool operator<=(const T& a, const U& b) noexcept { return !(a > b); }
  friend bool operator>=(const T& a, const U& b) noexcept { return !(a < b); }
};

template <class T>
struct totally_ordered_impl<T, void> : equality<T, void>, mirrored<T, void> {
  template <class U>
  friend if_not_same_and_has_eq<T, U> operator<=(const T& a, const U& b) noexcept {
    return !(a > b);
  }
  template <class U>
  friend if_not_same_and_has_eq<T, U> operator>=(const T& a, const U& b) noexcept {
    return !(a < b);
  }
};

template <class T, class... Ts>
using totally_ordered = mp11::mp_rename<
    mp11::mp_product<totally_ordered_impl, mp11::mp_list<T>, mp11::mp_list<Ts...> >,
    mp11::mp_inherit>;

template <class T, class U>
struct partially_ordered_impl : equality<T, U>, mirrored<T, U> {
  friend bool operator<=(const T& a, const U& b) noexcept { return a < b || a == b; }
  friend bool operator>=(const T& a, const U& b) noexcept { return a > b || a == b; }
};

template <class T>
struct partially_ordered_impl<T, void> : equality<T, void>, mirrored<T, void> {
  template <class U>
  friend if_not_same_and_has_eq<T, U> operator<=(const T& a, const U& b) noexcept {
    return a < b || a == b;
  }
  template <class U>
  friend if_not_same_and_has_eq<T, U> operator>=(const T& a, const U& b) noexcept {
    return a > b || a == b;
  }
};

template <class T, class... Ts>
using partially_ordered = mp11::mp_rename<
    mp11::mp_product<partially_ordered_impl, mp11::mp_list<T>, mp11::mp_list<Ts...> >,
    mp11::mp_inherit>;

} // namespace detail
} // namespace histogram
} // namespace boost

#endif // BOOST_HISTOGRAM_DETAIL_OPERATORS_HPP

/* operators.hpp
SSXQmqGqEZv6Udc34Z7vDbS15r3MBatoj4VHZ/OM1zkU85RXw9ulxvVyZ7W3z7z6bJU6NYyiXpnFoX9RjVU35ojnxd4CreH3kl1NicUEwYQLa42tUYoNrkuhcw8+20VapeGwKdbxGH59E5M9qIS1eB2Vb+/M5Fn2RWKwjFdKZUYyqvacF5dAzyPodDpr0C4ur78tEFNjc56sm+S01SgMzfP2vNkswg1giuPS0hztZTC19FAUTBk9ZhOuSnFCTQjNFZsg89wChXw1bhoTwcTIBNrc7vYKWAbnSo14/A/MVtKdAPapCCc87vI2FAQ+oWXE8/G6igjRBaRY2FldpVYIhsyXVJk/hTadN2eiKF2WCY6bOjaa6jJnsVsVeDHE4Ru36axx8l9aoRE62mEebyLGc7Em9W9jtrRqzGAaQ7yMSOoDgOD+49Uqyum1VxPluTN8rbTp3IRFXQhCbWLbsP4Dc/pKOBz71Qjm6E0x9onET4t3yAGhEPJ750Fo6rAHS0M9hoDddCO+fznR/uz/X06Hi+LFjn2+ENMNNQ9eW7eLWKrNe+0Fd7v4Vgu3VxTUQ8abxDQLZqbEMqVU8bHb9+tzx3jc4eOpf9C8U1CtY9zHyLT1H1BLAwQKAAAACAAtZ0pSqdbXfuQDAACkCQAA
*/