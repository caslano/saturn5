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
J3/S7XsxtE9919hpv9KxNl5fbZH2XulqozJLbVTm0EYlzLj4gbwc1WJFrG+oGkT2L1XmluRWvz36ZqSDuLNe+4roZSwyO9nwVaOTz3yUdbCLmKrBiwa7wlLfc0ZwB3u0eo6jnAD2sVs8D47hRkd/fwMCuciXYBOWCecb56nT1Wfypp8ztuk37xnS49p/0qafptfH/hRPrxvi6HU+mjLjkQR6zdZf3EKxTGoPujzJKQ5Kn2uyqT8WPhXfH1ly/zhfdkuu6pYS1S15+CU9GFIUUw+p56HK5q5MRuciqJK6Bvr/XLxnidnQnivnS4Ec39myOXN8tWjObX9QzWnpJK98Ib11WbAGjQr081T1w14GQPmPVMf60ul+tAuup316PiMhau4zg8+RwbSXAMyNV9eJ58WM3YjfF7rE/Kuxf50WhmUImblt4W5f2NPnltWaydVKRbU8Ytd1mmBmU83C8E5MexoeSfVuL6ulhXOx7K9c2m/rBx1BIMPtEunLuGIe8QQD4csejsCaLSiNlGHq5U8TO7HvBtIteFY24muv6FcLYM1IDyTmxejryLVEX9k/ib5+6kfTp3PNgfjpSw8l0GfBgb5eUb0nyjQ76fHkeOpLB+d/1hj/A/D98y+zPWV/PFB7fnzwoPOTVbbl4R9lW65bmVxb2ua/cfWf8GNS9V+0+kD1L33woPObqv8Xu2X9X38sufpD//kk6z9fjOk/e8qr77LvpvINsiVDFZ56oC0VaMbK1qfmXn9ZMjDXY0mdmvOKC7n87rp8bv9DsfJ9NdT+NgsPP9a68O6NsvA3H02qcHzk/dyDVjEkGvzp8TJo3HOOti7m89Cu2ME6UbU+TjZ1si8n1o402MlO157UapFahVmPyme3t7DQ+f56Zitb7za3egI9jL+YiDnMCMuOyb2fcWO8r6MIlLgZe03GB3FBuaIOQXRlf/NPvMK7DfxFMfI9fCrHTijyeBQynXozj/VObMugDyIp5GWv08jrMFljz8uplXyfLU5dYQ6N2gmiYrnyfuXyUgqP+N1D2nS2KDQcDuNK8XQiaVvJ4d8oT/Q1GXkEOUmGBFAMCeDcp5UEEDkePrHkC7Yfr49D7jKJ3KZ7JXJvSEBu/98AuSsSkJuPIEbuT70gvdVHnq+5fWXr8zUwDCvYd5rH/M7BRVtHj3IZpPAkdTedNmXcN4yRDwXamtSlH8xDX/XP6P44chJMA7gsuv9wlXnagyZR1nOyc1L0ECllkyJyAK0gKUdd8yqy74rtYi4ZRVuHwtEolYxbYOfZmbyr/l4dfp6EyFOW8nNLLytrZtujf5SXZMcXfuztsWvGl2xW45305EompVNroKBiiBeRDHnypkOtFk5zfYMkoRi+K0n+wRjFQY25TAItZJzNWIah2m+qJUM6gePoRPQMjzhpfatGrn0q1sizG/g5Uqb0wqddp0/m9OVDQKj6nps1xffsN3aqvzsFM7FXRQtFx4VcEoBvxSrYo+iZq7nzLrkKHsuBvEUwG6B84/R7AYtC9yNMCYSgBNM4dtzj/5EHfvTnIPNr7qOKifD89nTc/BaSI/3dOw8oIvAXznRVf17OE1LuwSeYNWP4/rM/xNuHu2jkTCU9zdTQcOrGc4LVZRb/0OgsVmYYU6liLpd4AuuZ2PrM42UqRI7orDJRyLRYzLe8uNA7a3m6HdOE17Hqlpf7ZVD7emvNRPb/nVDfsQDqh/6ompRjM0g55qcWzKIWzKK1AeoE1kJ+5EcHq3GQt1K2JMeoVC1pWajnV6axfJxMu5nOVEBb5TIeO9MC74oLuD1Ea9QEVL+F5/CJTaNHIXW9Si1uvYGJc4mFiVOR5rMyaftaGt/eQQ8nthcWrdQ=
*/