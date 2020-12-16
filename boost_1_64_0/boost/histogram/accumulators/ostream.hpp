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
rBoE/+LWLqN6XGggWPiaJ+zfL2vfA4J1g/Z8VOdtWTtChe+7qN+MUEauEsSi+GvhXo/cTR1Cq+QqVhvAqPxyIDfBUaVi36afXfEEJH5pDdH9un6D7FdObXSsZ8OXj0xbXDhJs9tMLKxpdQ9SsD4eH9y+sSTpxioDMVw5PPJQrfiTVK/Qs7HeQnUB4coU70rgypnlOq7QM7Yo6hLTdzA5XFTfqf3Cr1BRAMll3mTLr3rOf6rMQ8qerG30HZpnLhOXo22N+HVIm5JB78W7z3ELEASwf5yO5ffYF6j+Cum6x62dxBReEHkP4HKTr0sRRvQRnZSyTvJ5qcjsEi8CwbW9aABMhMPtwc032V6DkmNaRO/UdmqeWGWA8fVWn0drEmRm8RZmmoHjUV9EdEhZxSl4RbwyMkj/AHUn0gwo+wHle27UoUwP8M6leisvcTyeBF6mrgnehoMlyFoDCQu4mgMOI1xibshPmIAHA8kV6UsN+WF4fO78G7skn1ECtbsCLWNXX+d4fMOGvyU7wxnVE/EPCIMkG1sT+NvC3wp/d+FvK38n8reNv7vydxJ/J/O3nb+78Xd3/nbQNw4R9fteTna+gb+38fce/o7i7wT+zuIvAR2w4a87/lLw1w9/6fi7GH8j8Dcaf7n4M5kTLEoXa6Ktq1N+kpLt3XDbq8OPTH/hi/pIf7uT1+K+Obth0l5spS9ZO9QfIfWlJp5j6F7XYfIFTf4hf7r6QNTkr8Lkf/d6Y4ktJC+ywNsymO35CsDB1ICxnjjBN1r+dFbV+nx8ke+3geNhvl29VzyIn/wQ2pqh1bVrhtTuV5LqaxKLUYv/ad3iT8HzN7lYS9qz3ID6qNGBcvFLSDvV30U6tJQ7lMgdgkQNZWSJX0ZyXMM53lmGYr9qrebrX4sq8eW4wqVlwe8w7/YNpLVvz2rBFRY79C7ZWR/4rezT4IjWACVd+5wmkQh+0yTnBD2ybN8w3uRLLJoCERZe7iLrHmgCzat6lm3qV7XPl1zTt2RKQTFiVh+Zj9yWBrMpdAVOFwU8vS+FlAkVlvM/eKKbGNjkuy6QrJ8yr+qxKZUr7ze9IL8ocAqVVz+HuhNMrdQxaxvqnV/fbn1cl7YNZbotvXP6hlzQN7LShPv5dvLz6+zGE8m95vEWaj+5t39tPmXuIH+vB+7BtrcdnBzqNdc7nGYaAvwnO5xTnLi54NSmpwdL2rUal/eLLlkF7SkdBA2TE5sr8ha4uJZdcKcQ4/ddKVl2ulq/GLGtFtZ/pEJ5ENp4N56unPQgfNivXiYDweIUmkbY+Do1FMF5feuzj/34W6yGS3uSLpqePGzZU3ear08OsmwLFtu2BmtqamQsX6wZZNmh1d138oxWR89a1AU9St3+BHq/5dnguEXzK+jSDLD4C7g7o/s/9x8Ph9BlCQrmfgAKUWHWIeHHs0ikKOFkfClGnmyRZ+TxvabZM2gesoC+WdPoofNK7NRrrdO7bCg1Q/C7NglaOOuUkRQiixYskYRgkrxzjl9mJuafVh2DjZjUteRbYjg7O5r94ckmDr10Wvuw7vAgy4eWN0L2VXUHErJOBY4kXLvzRjRTcbIppGX0xBFwUHVzqZETJQF+fVJCSj4c8Vvw5E8LAT5QC6P4a2v/gI1lY8MfvhkOW0BMIxksDZ29Yxq+iHC3Ncyq2a2JhaO2nTzsoemH7KbuyCDLaSIk1zYSrCywAIAdH/SgWVfY8PgWZNZKjbadwtu1BPy2HN14jjKu61q88TD9aE6uPrE2cfbGBgqEV9i1Ame+SytI6bIMeyH0IufC0nzasnOtfKJdm0YPkdjon2A2z0NnN+iycjmCP1uvG7+x4e/JZjh3s//BhA8B06E=
*/