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
  To you use your own, include your own implementation instead of this header and do not
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
  counting_streambuf<CharT, Traits> cb;
  const auto saved = os.rdbuf(&cb);
  os << x;
  os.rdbuf(saved);
  if (os.flags() & std::ios::left) {
    os << x;
    for (auto i = cb.count; i < w; ++i) os << os.fill();
  } else {
    for (auto i = cb.count; i < w; ++i) os << os.fill();
    os << x;
  }
  return os;
}

} // namespace detail

namespace accumulators {

template <class CharT, class Traits, class U>
std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os,
                                              const count<U>& x) {
  return os << x.value();
}

template <class CharT, class Traits, class U>
std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os,
                                              const sum<U>& x) {
  if (os.width() == 0) return os << "sum(" << x.large() << " + " << x.small() << ")";
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

template <class CharT, class Traits, class T>
std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os,
                                              const thread_safe<T>& x) {
  os << x.load();
  return os;
}
} // namespace accumulators
} // namespace histogram
} // namespace boost

#endif // BOOST_HISTOGRAM_DOXYGEN_INVOKED

#endif

/* ostream.hpp
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
*/