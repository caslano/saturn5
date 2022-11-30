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
#include <type_traits>

namespace boost {
namespace histogram {
namespace detail {

template <class T, class U>
using if_not_same = std::enable_if_t<(!std::is_same<T, U>::value), bool>;

// template <class T, class U>
// using if_not_same_and_has_eq =
//     std::enable_if_t<(!std::is_same<T, U>::value && !has_method_eq<T, U>::value),
//     bool>;

// totally_ordered is for types with a <= b == !(a > b) [floats with NaN violate this]
// Derived must implement <,== for symmetric form and <,>,== for non-symmetric.

// partially_ordered is for types with a <= b == a < b || a == b [for floats with NaN]
// Derived must implement <,== for symmetric form and <,>,== for non-symmetric.

template <class T, class U>
struct mirrored {
  friend bool operator<(const U& a, const T& b) noexcept { return b > a; }
  friend bool operator>(const U& a, const T& b) noexcept { return b < a; }
  friend bool operator==(const U& a, const T& b) noexcept { return b == a; }
  friend bool operator<=(const U& a, const T& b) noexcept { return b >= a; }
  friend bool operator>=(const U& a, const T& b) noexcept { return b <= a; }
  friend bool operator!=(const U& a, const T& b) noexcept { return b != a; }
}; // namespace histogram

template <class T>
struct mirrored<T, void> {
  template <class U>
  friend if_not_same<T, U> operator<(const U& a, const T& b) noexcept {
    return b > a;
  }
  template <class U>
  friend if_not_same<T, U> operator>(const U& a, const T& b) noexcept {
    return b < a;
  }
  template <class U>
  friend std::enable_if_t<(!has_method_eq<U, T>::value), bool> operator==(
      const U& a, const T& b) noexcept {
    return b.operator==(a);
  }
  template <class U>
  friend if_not_same<T, U> operator<=(const U& a, const T& b) noexcept {
    return b >= a;
  }
  template <class U>
  friend if_not_same<T, U> operator>=(const U& a, const T& b) noexcept {
    return b <= a;
  }
  template <class U>
  friend if_not_same<T, U> operator!=(const U& a, const T& b) noexcept {
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
  friend if_not_same<T, U> operator!=(const T& a, const U& b) noexcept {
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
  friend if_not_same<T, U> operator<=(const T& a, const U& b) noexcept {
    return !(a > b);
  }
  template <class U>
  friend if_not_same<T, U> operator>=(const T& a, const U& b) noexcept {
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
  friend if_not_same<T, U> operator<=(const T& a, const U& b) noexcept {
    return a < b || a == b;
  }
  template <class U>
  friend if_not_same<T, U> operator>=(const T& a, const U& b) noexcept {
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