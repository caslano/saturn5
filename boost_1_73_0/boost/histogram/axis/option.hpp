// Copyright 2015-2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_AXIS_OPTION_HPP
#define BOOST_HISTOGRAM_AXIS_OPTION_HPP

#include <type_traits>

/**
  \file option.hpp Options for builtin axis types.

  Options `circular` and `growth` are mutually exclusive.
  Options `circular` and `underflow` are mutually exclusive.
*/

namespace boost {
namespace histogram {
namespace axis {
namespace option {

/// Holder of axis options.
template <unsigned Bits>
struct bitset : std::integral_constant<unsigned, Bits> {
  /// Returns true if all option flags in the argument are set and false otherwise.
  template <unsigned B>
  static constexpr auto test(bitset<B>) {
    return std::integral_constant<bool, static_cast<bool>((Bits & B) == B)>{};
  }
};

/// Set union of the axis option arguments.
template <unsigned B1, unsigned B2>
constexpr auto operator|(bitset<B1>, bitset<B2>) {
  return bitset<(B1 | B2)>{};
}

/// Set intersection of the option arguments.
template <unsigned B1, unsigned B2>
constexpr auto operator&(bitset<B1>, bitset<B2>) {
  return bitset<(B1 & B2)>{};
}

/// Set difference of the option arguments.
template <unsigned B1, unsigned B2>
constexpr auto operator-(bitset<B1>, bitset<B2>) {
  return bitset<(B1 & ~B2)>{};
}

/**
  Single option flag.

  @tparam Pos position of the bit in the set.
*/
template <unsigned Pos>
struct bit : bitset<(1 << Pos)> {};

/// All options off.
using none_t = bitset<0>;
constexpr none_t none{}; ///< Instance of `none_t`.
/// Axis has an underflow bin. Mutually exclusive with `circular`.
using underflow_t = bit<0>;
constexpr underflow_t underflow{}; ///< Instance of `underflow_t`.
/// Axis has overflow bin.
using overflow_t = bit<1>;
constexpr overflow_t overflow{}; ///< Instance of `overflow_t`.
/// Axis is circular. Mutually exclusive with `growth` and `underflow`.
using circular_t = bit<2>;
constexpr circular_t circular{}; ///< Instance of `circular_t`.
/// Axis can grow. Mutually exclusive with `circular`.
using growth_t = bit<3>;
constexpr growth_t growth{}; ///< Instance of `growth_t`.

} // namespace option
} // namespace axis
} // namespace histogram
} // namespace boost

#endif

/* option.hpp
UUQ3pHfZMv7O3vXHR13W8bvbHRzjxn2RAVOnDB1KYkZhpU5r0JZIzLbJjIpSU+gchAQ3ROPXGMsdxxWUKywqKy0rLCoyMCxUBLRVy1ZSrVq26s6jXLVy4YLen/fneb53t91QX/0Zpzuee57P8zyf5/N8nl+f5/N8Ptg7dbCMDi/KOE/KWMwJrUcyo8weDsweUMTnGbHsYkMYxBaZWJaBVk78Mxw+hzdv052OOEDsaTk+f/UY
*/