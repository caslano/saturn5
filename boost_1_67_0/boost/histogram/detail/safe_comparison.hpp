// Copyright 2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_SAFE_COMPARISON_HPP
#define BOOST_HISTOGRAM_DETAIL_SAFE_COMPARISON_HPP

#include <boost/mp11/utility.hpp>
#include <boost/type.hpp>
#include <type_traits>

namespace boost {
namespace histogram {
namespace detail {

template <class T>
auto make_unsigned(const T& t) noexcept {
  static_assert(std::is_integral<T>::value, "");
  return static_cast<std::make_unsigned_t<T>>(t);
}

template <class T>
using number_category =
    mp11::mp_if<std::is_integral<T>,
                mp11::mp_if<std::is_signed<T>, type<int>, type<unsigned>>, type<void>>;

// version of std::equal_to<> which handles signed and unsigned integers correctly
struct safe_equal {
  template <class T, class U>
  bool operator()(const T& t, const U& u) const noexcept {
    return impl(number_category<T>{}, number_category<U>{}, t, u);
  }

  template <class C1, class C2, class T, class U>
  bool impl(C1, C2, const T& t, const U& u) const noexcept {
    return t == u;
  }

  template <class T, class U>
  bool impl(type<int>, type<unsigned>, const T& t, const U& u) const noexcept {
    return t >= 0 && make_unsigned(t) == u;
  }

  template <class T, class U>
  bool impl(type<unsigned>, type<int>, const T& t, const U& u) const noexcept {
    return impl(type<int>{}, type<unsigned>{}, u, t);
  }
};

// version of std::less<> which handles signed and unsigned integers correctly
struct safe_less {
  template <class T, class U>
  bool operator()(const T& t, const U& u) const noexcept {
    return impl(number_category<T>{}, number_category<U>{}, t, u);
  }

  template <class C1, class C2, class T, class U>
  bool impl(C1, C2, const T& t, const U& u) const noexcept {
    return t < u;
  }

  template <class T, class U>
  bool impl(type<int>, type<unsigned>, const T& t, const U& u) const noexcept {
    return t < 0 || make_unsigned(t) < u;
  }

  template <class T, class U>
  bool impl(type<unsigned>, type<int>, const T& t, const U& u) const noexcept {
    return 0 < u && t < make_unsigned(u);
  }
};

// version of std::greater<> which handles signed and unsigned integers correctly
struct safe_greater {
  template <class T, class U>
  bool operator()(const T& t, const U& u) const noexcept {
    return safe_less()(u, t);
  }
};

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* safe_comparison.hpp
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
*/