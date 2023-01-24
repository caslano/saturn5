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
sDda2GHRINmO9tarA4bDpvtutobCZp4L5001ay9j/0m+YL0Dmn65wkCo0J3X6+QJzQx426ZB3ugW19a9C51tCCxKI9Btb+N8c3LSSeQfB+yp0JyTtpAQTDH5IAADG0Hd68p3PqgVv/x4nLGcWS5QE9wChJ2RnamnkNde2CM5ogJfdqAvvVqTADjgOahDHQb90GpQWvCWMMBI/mLdP1vJzxHXDbe7xufBiAC0IMp3Rt8As21YQ2HbCFDzHJuwmzf5RqJv+bBp8tNb3kQeXe6qwO9K3igMcFFHxMUTc5vlH2lzTnMN5fSaUxHvpFNbus6xz+44AWbJaq19P5j2ffs2K3zUQCSYLEtSGrCj0LY4NUs0S9iyHk1sycyBH07j7vaURj6ZC4mfNv8lU4DmO5Y39pLza4kG4J3uyDfTIo40pR87yNV8A7GHRybhcbyJLv8onb/69oZapKxL3nXluXTeRfD30jk61XPpXGvkZnDG5bfjIgmXus0jtXnmAtfljJWK8itil0JL2c05jt8KQdfiwhxJ02HRwbUaAnFC1FhCkjTdOCFzfvTx3FnU0wQkcuEBH2vnrPUpCJBRyB5ndlzyP1Nwe4sbnYqIqMiqJ6Gaela/vnC3pzc7XkMq6x4r1RBImbhIyB+uBRbw/8SUnLKSUT6R4+EQ6MoyxB5UU7UpmJsgN8ptpiM9JrW2gzyirUg4AIMmYl67nuXd6kmI
*/