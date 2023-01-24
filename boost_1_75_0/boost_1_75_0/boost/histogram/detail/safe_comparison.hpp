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
MG3k/2vUnnVOPf20/Ifd9L1qBa+yaBMCbbin3FtbLLt1PQzlsudGv0Z9G6bBk82CO9v41CrWNCGFi7mXZlA8FPZn69b+Fm6IXcmVBy4M9u3mYa+lYVllAiYmjOcrANkLffHrmZV4gc0g+7+GfjbuBtol7I+SN7ubDOeqpS8P/Gm8zUlriNkQsRkPha19ZAhq5GreBbrmxwdY0JrENRA3CSYha1gibQthPugGJu8JpkEWUQPfv9iCR4RhXmb0gWK/piGnwKy9IHWaIAEYxZt1XG9hZzp/AYj3EB+WvJZkUGczV2bbi3CTY95A0NeLfmfZmiKvTm7nfYQDGFvmDEz2rxm6541e6vX/1er//aCb6+8Z2srGzd3C9T8OujUGPcTcGpMSvHWCY7sPXLDjEt5FrkujmVwl3BewYBpHc3hGH9XJEdqsz1fXYf2p6Kz1XX5nTj/WbobOos3TdK3hamEgJPjtB7XVfg+D5NbGr0LyJzQ/bSSyl+IUdgau7vni/RpxmPF/vVC/dP5zeNtnLCODu/65yi3ZKOjycn6ziNIGH3/6uYWLaZj5NUaX/zVG/7V0QDf7+euTavEmHE/sqgZPXP9rjGZHjkNMhR8N2Q3BDcYNScY7m9KIumaO+PX64JkiyV+turLhm12y4o0Che5IG2J8fbfc56Gv+LhSPsBKx/FSJV5L4kByv6jlBKfqFIv+ORn0YxQkpAueBFNU
*/