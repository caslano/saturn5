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
Wc2Q4HV45+WLR6UO8eo01SOdWz10Gg9DlwTzOEVsHQ0CiWC+Ts8hLY2Q6oeVX0Fjh3dTYyd4dgc46rLTe36n95xO7yWd3p2d3h2d3jM7vds6vVs7vRd1ei823nHgRdXnhpsT9VlCw1qwrywyMuWZgjnZzZ0r7WK9ELdXyUrLUZX2TVlpl7vPu9KIP972qy3odjvPj9R1ppxiK9tkgjJaeU6wSlH/lqT+valM3bhwOFirJGCg5Dc65uwXBif4yZb8fCA89yzw/LPAc84CLzkL3HkWuOMs8MyzwG1ngVvPAi86C7z4g+AOgpfF6rODFwVKqIbvDH4S1bv1BmWxtDw72F9CPsWQnxgQtmnnncB3v2s1ncNxHTme8M5f2Zn6gegmON07gnchXd8N6vgbmxMhaa2xsJksB8SjSJ5XhArbLCdgQ8LUcCfDhxoPsX42KhAChQDN3gKflYJ7ZLKi09gVf2wS/hqJ/+yH4U9Lwv+Mvv//YfgTk/BXS/w5H4IvC/RD3nOGddBYN85i+1d/8vnhGRrOEFPBh3x4y3SdxPsCP60/kmdJMc5FrZzOSMTxoaluGx3T9bDRMhuLROfzrShrDyHcdWAkErJv2MYeznEdBi7S6BM7hbs2qLpipxx46K01ym282CmbH++XiEXzjJk6lp4JtgzffL+4LGAAVnJpsEm7X/RU4aH5liNBU9n8/HtW5JBDfEsToE23KugU7R0obKHWoYhXBMhjBqSEwrUt8CHOILKcQlwx7dssqNo748ooZr59/UjkmszsTfjAWMTsY8OIgFyZdsoLVmfx6sasc+5mL/ijjt529xWP5rP2b3BhnBdf4e1yXhznuqlAqdrvIZ12gU97PJ92/ajxLQOWYyq8kqyV7lideC+K0kVQz4czRBraobaVD5WcnGavOhalU8yVHhq9tF0oFlyxXLgV2PkTyvbXXx0sD3yfe43Al6U43zeBxVmuwepn0nNmyEPlFWWnll+NNsYx7lExZncT4w2/jMHFkdM0HkuTs83jwSsWVyxHvPHH87HAzneSAl6BGbOxEHZjCpse5Rei9mrhQP4aMtWe+02rCSnnQiBihU3TqDgtze6mirhZXA+QDzumo7hwyQTOQQtx/sJ2ZtMvbvHLdpAJatnYKLo6eJPMQKXKwFdru2ZgiJ4BPn2ApSkR+ZhaaV37iBkN6UU0tQ20d4AI8Haeu3Bpw/g4vPVvXZLeUEkPWxbN05ovH2wyrVzaozay9XAFnQvRDg5BvgrhFJYc1zfMdtB8BS/5ZOSooVLsDlNDRa7dMbng8G32t7fae9cetjsye0c2I6ziqB50tAxX+Sz7HS0sEvWyV5YXRZGO9lrhfDSTbYWvqvu41lmHNEwwF1fGI63y9q9sokN5Qqsq8VMj9rnF928ysvacibN20r7h87yInbtwQcMkeBwoudays2zfEhsZgcHv+0ytKTln2s4GrM4Wbm2AL+LCM+j2W5kdSc6BLIF9mas0I1eUHQRYDht52rPsZeKubO/yizm5Mw2ZAwqPr7OO5CzIC8yC87juvGJxWeJUZFK1LfTqcvdJHW+KxAN4gaxfIN3gPR8fCf/JH3Vk4oO+YlEe30D+QUWxcSOff3Yn3xf9OILQ9zzN3dNX81+gdgxhQtBWGni0x/J/J4NsCNqHRxq2Sl0n8UbLvCT51F81V0EQZd9dzPM3qKx0CfWbbPkXThfXyx3P4jVxt73qFPlWF/dOkQui9FYw8vH83TSKbVhmoUNE9g0h/Ja12tcfTSE3B8tTTHgV9vV/oA7lIK+nFb42icXCAyZKxST0ibyiph2VwhINIXS4h7si2X/aV/dAotQtvY9UvNQVvfw1K1+dVigsGH8=
*/