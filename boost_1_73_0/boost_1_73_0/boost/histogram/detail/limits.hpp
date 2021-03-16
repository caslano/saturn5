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
zv5QQtUf+EMNyhiB7FEaGVU9Ph12kMkRj2heTyBQ5/E2Ae4PR/3xuZo/xNYffLiX+xTz++ZwtEkIM0Q8dPGH+tww1XAEtuCNFUWNugRwfA7owQFBLCPNYzw9x/S0jmnrUqaSZoilavGoJySEGCqaXOYmYxC9tcLcahhhkFLpHh9CwtuVy2fatdTivNaeyi/MtGLASvcl1hb62bWWnMc6jbQ2tbS2UstQtDyEjT+3SJszdfI1UF59WKNXnM3v6kg=
*/