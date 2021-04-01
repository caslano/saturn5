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
RSjiBnpk74o/cAA/Hqm4bWTNEtl6f6+DBRrj1wnx2wOGTBL0yOiC1e4DE5++JZYQJanycHUGntUB6GVWLQUBLbRPO70BRvdWsVFgBOSmK5qPRMBl9fUaVXVKBc/Oev2MFaY06tvUY16abRFJHQkp1nrz3qos84AuZcI6YNqEpdcDCsZM6TL9i08ZHimCx4cjo8NMbKM0ws8GQmoMM2NpK670LRgT6pFGceMRplk9+m8FaHNAiyfBxASTCLbwerKODrOcDrNMlQIZHLflYZZns3psKzi7pPRnKgCfNfyafnzoNrpe6xPpeWBIY734MJG9uSys/KPDCB1g792v64NCYLWOXjjqzfCTJfqVj0dAS4G9K88x8Q2oBZtSe+REm5TpsrfvZ5gBqFKZro7WSqTj7kxzNeJx+OXEKspi0KVdW4ispzGH60/VsZWlfefMPGJL86e9D/s/Mlgg4VB6wrmnLXPU6wSZMuL4seI8LbFlOy/tL+sFitOzJBC8fp6LMOli0OZkfphJuHVujhUXjmeooU7L+q0Q8N2a9vxRmQ8ihrTW0uF8mBWc0S4XnQ==
*/