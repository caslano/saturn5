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
ORlfCfQWRVI2FRrlFIijI4JPaGSS8LyLsbsL7gje0ue5Y2m6g9ytxGG51MkSGc+GsdxHuihP1rgfSQ183G8PFLYIO30WFMxtbCVBYbBxv9H3YhVLjDcafcdc3v3DipSiySLwCjJ0S0wb3SQWRbSFhVN6Rjw+Ouf++halhcVzT20/ASczt6ce04qjWtxqrVnQYDzcVH3J58wlh9xl0KbwiUWloulQ8SYnxaK+OIs24ByJqyNslr7dlPbUeuP56hU=
*/