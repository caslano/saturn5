// Copyright 2015-2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_LIMITS_HPP
#define BOOST_HISTOGRAM_DETAIL_LIMITS_HPP

#include <limits>

namespace boost {
namespace histogram {
namespace detail {

template <class T>
constexpr T lowest() {
  return std::numeric_limits<T>::lowest();
}

template <>
constexpr double lowest() {
  return -std::numeric_limits<double>::infinity();
}

template <>
constexpr float lowest() {
  return -std::numeric_limits<float>::infinity();
}

template <class T>
constexpr T highest() {
  return (std::numeric_limits<T>::max)();
}

template <>
constexpr double highest() {
  return std::numeric_limits<double>::infinity();
}

template <>
constexpr float highest() {
  return std::numeric_limits<float>::infinity();
}

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* limits.hpp
sOZKCLg8v8FC5nwqUfaFDpCZTxdIoLq8CsnePfEAe/bFFknoHbdlFvPb0i2JxVKTlf6NEfM0UodVHLMWBm1LJnY8k8LJA+4YZHWgE9kS+ej49yUIA/jyiQd2AuLnWgYNGKDe4Hs4pQxO5mCVjn400prsRufz2euTZvEPM282evH6T42ak4FKC60VXw74yGcXTyavRsOW4kZKTlX1H4NpS41KeLWrYKNwDnY1m08upsP/vBo6ep0OzwZX53PvcjqZT04m580GY0wmm+KlVWfdCA5n07PBSXNirD2fnAzOvdFlE4dm7Z+btZOXHvzZKB++OG0h4nB8MjmVOdBWxdn88nIybXaAcm9wcjK5GrfUncPCxoP56PXQm0+8q9mwSY72xY9ms6vhFDOIG1Wvhm8uB7PZD6fNmun358PXw+ayzycvRupE1STDxWB07g2uHKxHNWfTyUWjZjycT0+aCWFUNQFm+PFNo5yAnkybYF+OxuPh6eXV9+cjII2j43TotQzZXto+G9YiNRqJcVbtpQO/VNkmvarSKcOyskXEuLadrly/G03YCmVtdDL02leHqZtOxrJqG5mBVost81Pl9t7eyejy5XDqOfUQt5qfz558Kds1OVa3Qa7dwlhWsy0wqSatbDEdjE8njgRIWffC
*/