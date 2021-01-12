//  abi_sufffix header  -------------------------------------------------------//

// (c) Copyright John Maddock 2003
   
// Use, modification and distribution are subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt).

// This header should be #included AFTER code that was preceded by a #include
// <boost/config/abi_prefix.hpp>.

#ifndef BOOST_CONFIG_ABI_PREFIX_HPP
# error Header boost/config/abi_suffix.hpp must only be used after boost/config/abi_prefix.hpp
#else
# undef BOOST_CONFIG_ABI_PREFIX_HPP
#endif

// the suffix header occurs after all of our code:
#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#if defined( __BORLANDC__ )
#pragma nopushoptwarn
#endif



/* abi_suffix.hpp
y8LasBxsACvAJrAijIWVYRtYBXaE1WA3WB3GwZqwL6wF74a1YSKsA1NgPTgc1oeZsCHMgTFwDGwMx8MmcDJsBqfB5nAmjIWPwhbwcdgKPgVbw2dgW/gCbAcXwg5wCewIX4ad4UrYBa6C3eB62B2+Du+Am2BPuAX2gu/A3nAH7APfh33hbtgf7ocD4EGYAI/CQfBjmARPwmR4Cg6BZ2EKPAeHwwswDVL3VL132Pl9oAfDsTAP
*/