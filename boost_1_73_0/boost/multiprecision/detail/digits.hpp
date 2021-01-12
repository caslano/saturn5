///////////////////////////////////////////////////////////////
//  Copyright 2012 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_MP_DIGITS_HPP
#define BOOST_MP_DIGITS_HPP

namespace boost { namespace multiprecision { namespace detail {

inline unsigned long digits10_2_2(unsigned long d10)
{
   return (d10 * 1000uL) / 301uL + ((d10 * 1000uL) % 301 ? 2u : 1u);
}

inline unsigned long digits2_2_10(unsigned long d2)
{
   return (d2 * 301uL) / 1000uL;
}

}}} // namespace boost::multiprecision::detail

#endif

/* digits.hpp
8M1i7VbkvdvtRyCPt1uWx9styzX9nHyWa/oht3xOPydf5JJ+Tr6uiz9k+7F2CP1EGW7z2z24UpX4uK219Lz07W6cQoe61LDvDF/hdVT1YvQ7FxjOu4QT/8aZ90HinOT3QPRdVW78GyCcVyU4yXH/2TzX6NRX+PtJuTfvkLAOcnRR7fLAjo+tXvXU7/jzvS7ed8F2O8oTBh6PcCsM8718CfMkf0Ksq82G0fvKJH+thTrgPTBJ
*/