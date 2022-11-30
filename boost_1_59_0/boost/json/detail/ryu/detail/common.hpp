// Copyright 2018 Ulf Adams
//
// The contents of this file may be used under the terms of the Apache License,
// Version 2.0.
//
//    (See accompanying file LICENSE-Apache or copy at
//     http://www.apache.org/licenses/LICENSE-2.0)
//
// Alternatively, the contents of this file may be used under the terms of
// the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE-Boost or copy at
//     https://www.boost.org/LICENSE_1_0.txt)
//
// Unless required by applicable law or agreed to in writing, this software
// is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.

/*
    This is a derivative work
*/

#ifndef BOOST_JSON_DETAIL_RYU_DETAIL_COMMON_HPP
#define BOOST_JSON_DETAIL_RYU_DETAIL_COMMON_HPP

#include <boost/json/detail/config.hpp>
#include <string.h>

BOOST_JSON_NS_BEGIN
namespace detail {

namespace ryu {
namespace detail {

constexpr int DOUBLE_MANTISSA_BITS = 52;
constexpr int DOUBLE_EXPONENT_BITS = 11;
constexpr int DOUBLE_BIAS = 1023;

#if defined(_M_IX86) || defined(_M_ARM)
#define BOOST_JSON_RYU_32_BIT_PLATFORM
#endif

inline uint32_t decimalLength9(const uint32_t v) {
  // Function precondition: v is not a 10-digit number.
  // (f2s: 9 digits are sufficient for round-tripping.)
  // (d2fixed: We print 9-digit blocks.)
  BOOST_ASSERT(v < 1000000000);
  if (v >= 100000000) { return 9; }
  if (v >= 10000000) { return 8; }
  if (v >= 1000000) { return 7; }
  if (v >= 100000) { return 6; }
  if (v >= 10000) { return 5; }
  if (v >= 1000) { return 4; }
  if (v >= 100) { return 3; }
  if (v >= 10) { return 2; }
  return 1;
}

// Returns e == 0 ? 1 : ceil(log_2(5^e)).
inline int32_t pow5bits(const int32_t e) {
  // This approximation works up to the point that the multiplication overflows at e = 3529.
  // If the multiplication were done in 64 bits, it would fail at 5^4004 which is just greater
  // than 2^9297.
  BOOST_ASSERT(e >= 0);
  BOOST_ASSERT(e <= 3528);
  return (int32_t) (((((uint32_t) e) * 1217359) >> 19) + 1);
}

// Returns floor(log_10(2^e)).
inline uint32_t log10Pow2(const int32_t e) {
  // The first value this approximation fails for is 2^1651 which is just greater than 10^297.
  BOOST_ASSERT(e >= 0);
  BOOST_ASSERT(e <= 1650);
  return (((uint32_t) e) * 78913) >> 18;
}

// Returns floor(log_10(5^e)).
inline uint32_t log10Pow5(const int32_t e) {
  // The first value this approximation fails for is 5^2621 which is just greater than 10^1832.
  BOOST_ASSERT(e >= 0);
  BOOST_ASSERT(e <= 2620);
  return (((uint32_t) e) * 732923) >> 20;
}

inline int copy_special_str(char * const result, const bool sign, const bool exponent, const bool mantissa) {
  if (mantissa) {
    memcpy(result, "NaN", 3);
    return 3;
  }
  if (sign) {
    result[0] = '-';
  }
  if (exponent) {
    memcpy(result + sign, "Infinity", 8);
    return sign + 8;
  }
  memcpy(result + sign, "0E0", 3);
  return sign + 3;
}

inline uint32_t float_to_bits(const float f) {
  uint32_t bits = 0;
  memcpy(&bits, &f, sizeof(float));
  return bits;
}

inline uint64_t double_to_bits(const double d) {
  uint64_t bits = 0;
  memcpy(&bits, &d, sizeof(double));
  return bits;
}

} // detail
} // ryu

} // detail
BOOST_JSON_NS_END

#endif

/* common.hpp
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
*/