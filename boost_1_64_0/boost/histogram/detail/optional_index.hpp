// Copyright 2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_OPTIONAL_INDEX_HPP
#define BOOST_HISTOGRAM_DETAIL_OPTIONAL_INDEX_HPP

#include <boost/assert.hpp>
#include <cstdint>

namespace boost {
namespace histogram {
namespace detail {

constexpr auto invalid_index = ~static_cast<std::size_t>(0);

// integer with a persistent invalid state, similar to NaN
struct optional_index {
  std::size_t value;

  optional_index& operator=(std::size_t x) noexcept {
    value = x;
    return *this;
  }

  optional_index& operator+=(std::intptr_t x) noexcept {
    BOOST_ASSERT(x >= 0 || static_cast<std::size_t>(-x) <= value);
    if (value != invalid_index) { value += x; }
    return *this;
  }

  optional_index& operator+=(const optional_index& x) noexcept {
    if (value != invalid_index) return operator+=(x.value);
    value = invalid_index;
    return *this;
  }

  operator std::size_t() const noexcept { return value; }

  friend bool operator<=(std::size_t x, optional_index idx) noexcept {
    return x <= idx.value;
  }
};

constexpr inline bool is_valid(const std::size_t) noexcept { return true; }

inline bool is_valid(const optional_index x) noexcept { return x.value != invalid_index; }

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* optional_index.hpp
KB5Qmridr4SbttepG9Uk8lc/nlkH03Z0Ft7HfX++Zf2iSi5eSQ3kSUfq37J7iR13xhWj6GVHovsmECGAI6TD3sWOXZmCdDYnjnfEidCgtmp35uj6xi/fOv++0UXuvbhsH8rJHoZXEPdJJaYFPtzCxnsM8KfJAJiYKf6iygRs8+Bon2LFKW6qANc8VUlQGzitZKe6TFmUvfgBuxgthfVg3KqKOqKQoEDPBROcaaYXfbMx/qdTsUzKw+X3IjH2VsLHs4ZBoahsXxsc+l8mxKkSNQUiV+wHmA0yvw5rSOk5gUUJ2vrUrHqmcuBimerxv1HRyKyWBmFIwh9abFMP6Tc7mRRHfCym5NBAmU0BM2W3wlQOO4iKyVRlkNhRP7hz6cJ/tY2PfgtE+pPe1BKpicf3s9SowptFV2CU7B1qk30g5/qcBz6e0kjnqftbQYy48JIcRv9PZ4sFV6ujmFInzzCkBIGLJnKnP9kFn5Vli9Lp4S2KBJLIdX44Gk1XYW04uksKaMnaFNz1iqfBv58pm7Geksc/32HMmvjJJM+3AE5ydgu35UhxxCRCxb+n1A==
*/