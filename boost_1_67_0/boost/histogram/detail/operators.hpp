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
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
*/