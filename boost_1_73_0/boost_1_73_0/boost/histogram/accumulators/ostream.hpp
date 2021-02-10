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
OiN+ZxCyYP/q6nzUez99IngDwQL/C/xfMt1EBjSQod6NPHc5aajlmdsPdOQQHgXh/NDqaPiOJHKLtZyfANu1pEu73SVpI50v0zSW2IlKP1dLbZJsY2Sh09gGkykeKJMlMuQytqAMMVGFKua8U8iABFLtQnOBHuXc2Zy2LdAh8Ep9xxkncsPjurO4iE1vbfHgZKH20i/dQfMHLDOYAyZISWmdi7alazLBzvB+DZNO+ZhZYOdylCJ/iDL6cFYXz+kC+3pZo4nla49JPOwE2CcVjQE566BENwY7FOcxRblP2+qrhiQCCFsk9KlHlVaeZwlyDFCXOZH6JnRQGDII5TtUB++ahBCoyViuzR1BBsNWtkrXaUZkI8XSWtRwZTXRhg1q2jHNIuQpZ4d3GzyTWUZ4atLnLdRxfJyxtdVhGYVkK9+N47hr55+7gFCXXdy/GXqCnxGF1NWkmcXZoA/WNBlCV2NVKflhvbsG3iSdTCfgYh6u6q0YlGFo53NV7htyIRLfQqlhBraTW3tHVmnDo9bJ9Z1iMoauE+afHYeLe7jBKe9R9lD0JuD9vSe0Ec+VDEdXd1djFuVGy5Ttt+yv6J3+hoLmLITsxPFv4ocfxCce+MEop0cve12MPFRuj4SZ6jF6/PHfXW9tnq6kNl1Z
*/