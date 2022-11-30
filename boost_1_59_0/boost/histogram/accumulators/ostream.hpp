// Copyright 2015-2017 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_ACCUMULATORS_OSTREAM_HPP
#define BOOST_HISTOGRAM_ACCUMULATORS_OSTREAM_HPP

#include <boost/histogram/detail/counting_streambuf.hpp>
#include <boost/histogram/fwd.hpp>
#include <ios>

/**
  \file boost/histogram/accumulators/ostream.hpp
  Simple streaming operators for the builtin accumulator types.

  The text representation is not guaranteed to be stable between versions of
  Boost.Histogram. This header is only included by
  [boost/histogram/ostream.hpp](histogram/reference.html#header.boost.histogram.ostream_hpp).
  To use your own, include your own implementation instead of this header and do not
  include
  [boost/histogram/ostream.hpp](histogram/reference.html#header.boost.histogram.ostream_hpp).
 */

#ifndef BOOST_HISTOGRAM_DOXYGEN_INVOKED

namespace boost {
namespace histogram {

namespace detail {

template <class CharT, class Traits, class T>
std::basic_ostream<CharT, Traits>& handle_nonzero_width(
    std::basic_ostream<CharT, Traits>& os, const T& x) {
  const auto w = os.width();
  os.width(0);
  std::streamsize count = 0;
  {
    auto g = make_count_guard(os, count);
    os << x;
  }
  if (os.flags() & std::ios::left) {
    os << x;
    for (auto i = count; i < w; ++i) os << os.fill();
  } else {
    for (auto i = count; i < w; ++i) os << os.fill();
    os << x;
  }
  return os;
}

} // namespace detail

namespace accumulators {

template <class CharT, class Traits, class U, bool B>
std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os,
                                              const count<U, B>& x) {
  return os << x.value();
}

template <class CharT, class Traits, class U>
std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os,
                                              const sum<U>& x) {
  if (os.width() == 0)
    return os << "sum(" << x.large_part() << " + " << x.small_part() << ")";
  return detail::handle_nonzero_width(os, x);
}

template <class CharT, class Traits, class U>
std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os,
                                              const weighted_sum<U>& x) {
  if (os.width() == 0)
    return os << "weighted_sum(" << x.value() << ", " << x.variance() << ")";
  return detail::handle_nonzero_width(os, x);
}

template <class CharT, class Traits, class U>
std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os,
                                              const mean<U>& x) {
  if (os.width() == 0)
    return os << "mean(" << x.count() << ", " << x.value() << ", " << x.variance() << ")";
  return detail::handle_nonzero_width(os, x);
}

template <class CharT, class Traits, class U>
std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os,
                                              const weighted_mean<U>& x) {
  if (os.width() == 0)
    return os << "weighted_mean(" << x.sum_of_weights() << ", " << x.value() << ", "
              << x.variance() << ")";
  return detail::handle_nonzero_width(os, x);
}

#include <boost/histogram/detail/ignore_deprecation_warning_begin.hpp>
template <class CharT, class Traits, class T>
std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os,
                                              const thread_safe<T>& x) {
  os << static_cast<T>(x);
  return os;
}
#include <boost/histogram/detail/ignore_deprecation_warning_end.hpp>

} // namespace accumulators
} // namespace histogram
} // namespace boost

#endif // BOOST_HISTOGRAM_DOXYGEN_INVOKED

#endif

/* ostream.hpp
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
*/