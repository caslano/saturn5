///////////////////////////////////////////////////////////////
//  Copyright 2012 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_MATH_MAX_DIGITS10_HPP
#define BOOST_MATH_MAX_DIGITS10_HPP

namespace boost {
namespace multiprecision {
namespace detail {

template <unsigned digits>
struct calc_max_digits10
{
   static constexpr unsigned max_digits_10(unsigned d)
   {
      //
      // We need ceil(log10(2) * d) + 1 decimal places to
      // guarantee round tripping, see: https://www.exploringbinary.com/number-of-digits-required-for-round-trip-conversions/
      // and references therein.  Since log10(2) is irrational, then d*log10(2) will
      // never be exactly an integer so we can replace by trunc(log10(2) * d) + 2
      // and avoid the call to ceil:
      //
      return static_cast<unsigned>(0.301029995663981195213738894724493026768189881462108541310 * d) + 2;
   }
   static constexpr const unsigned value = max_digits_10(digits);
};

template <std::size_t digits>
struct calc_max_digits10_s
{
   static constexpr std::size_t max_digits_10(std::size_t d)
   {
      //
      // We need ceil(log10(2) * d) + 1 decimal places to
      // guarantee round tripping, see: https://www.exploringbinary.com/number-of-digits-required-for-round-trip-conversions/
      // and references therein.  Since log10(2) is irrational, then d*log10(2) will
      // never be exactly an integer so we can replace by trunc(log10(2) * d) + 2
      // and avoid the call to ceil:
      //
      return static_cast<std::size_t>(0.301029995663981195213738894724493026768189881462108541310 * d) + 2;
   }
   static constexpr const std::size_t value = max_digits_10(digits);
};

template <unsigned digits>
struct calc_digits10
{
   static constexpr unsigned digits_10(unsigned d)
   {
      //
      // We need floor(log10(2) * (d-1)), see: 
      // https://www.exploringbinary.com/number-of-digits-required-for-round-trip-conversions/
      // and references therein.
      //
      return static_cast<unsigned>(0.301029995663981195213738894724493026768189881462108541310 * (d - 1));
   }
   static constexpr const unsigned value = digits_10(digits);
};

template <std::size_t digits>
struct calc_digits10_s
{
   static constexpr std::size_t digits_10(std::size_t d)
   {
      //
      // We need floor(log10(2) * (d-1)), see: 
      // https://www.exploringbinary.com/number-of-digits-required-for-round-trip-conversions/
      // and references therein.
      //
      return static_cast<std::size_t>(0.301029995663981195213738894724493026768189881462108541310 * (d - 1));
   }
   static constexpr const std::size_t value = digits_10(digits);
};

}}} // namespace boost::multiprecision::detail

#endif

/* max_digits10.hpp
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
*/