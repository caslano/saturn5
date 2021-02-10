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
Hs/UjXhAqsmgHc9dL5ZrH14cu+Dba6dBSV+inBCD081Q19t47YnwDC2yGf34eTVDxOPRdH6/cBCvyq+LI6G171tmDMrtNTpNGKX86ByH00sPUU6JFCjeWwRqwAkZBSiTPdffAouySAH0hmNgnzIgi/qz+xUuFN5vE9yxw7y7SarWb2DeQzHdEjtA2ymO4nUCgqVD5DJTTqXXM1IwaZ4lrBcN1fDW5Fj9EoWFCHbtaJVBTGkcAWJSFJosCgQ0rwdak1zb7AwMOk8rh2u1HXPhRv7Ajs9BxbwVQaCjEN3VcE9+EqiHEIDZNLBLq3h7rd4h64ErQQq5I/BI2nh9Ld8wmzdZbwbmSjEachnYYnhNmqdiFeSNjBfuH1ea96PW/VYdwEZZuq5RpkEZuol29mCYbm7IG8bpG9wsfYQc+5Cqn3xQOGC/T+fq9QH6l24o0iSUcA+g6GaTRk40yjgJa32SjZHpLUDkf1aDRnfeejUar/3n+fR331uMP7vr9qbZ2vsybj02dtJ+vBytH9uPF4vPU/fC4/vp7NLS30arCyuzqdemdbxYfl0uvPU9rE+89vJq1o3r2Vsvnlbur89uB9CJez96nq395WqxXowXs/aGued77uqLu2qjnCweffjaeu4+TC7w252PF5Pp/KG1
*/