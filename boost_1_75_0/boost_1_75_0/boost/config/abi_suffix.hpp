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
dnlCqi6RQ8wxnKuuLhxPjBf3lewv/bCstLykzFeRLPNVtpVVVT1pry5dVlLtq0lW+5a3VQN9Ur266mxpe7E3vqvqQVzWTLMFVbfiAjPAruSyxrKmbS07WsvabsTtfR1LcWeiPdA63BxqKmncWRdUW3oqe+N9H3Sb32pZWbmqavUHlqb1Do2t3THcN7J/Xf76itHEusSwd2h0OH8oucarngUKhjwVQycwixlIVPNBh9tHT7O7NLcRAn4gpORpCUeJo1SrUsogVburvMSkqEVro0ZFnVqvtkpbq4041tN4eTncpzON//GPKro2AZe/hjQucEGoIKwWCrD5uSR5rgUu3zE9tzhLGCHPkdheHSy2F3l2iDy7Hi7bIE2K6YN9bJZLg7hELIA9CU1/7yh57+TM7w0QXfa05z8lz/8eLvNWZZ7n5heS1EerIWeqcsKwd0QfgX1jZEa+Og6vryS+PW+BTPlqFY0wk02JITSJyfJEEyUzabKdYtLUAYZoJtjPZtFMZ9eLlANl/q9hsZKfCcYGbxYeoj4rbXPooh8Q6In/xcIehic/oM9IbDut5yYn2Y9S99JTYuKPVFXPqlrKqrJZq5qy9zBpnbmqpdmWqgayn6THfjezquolvksw1DonZYZJb9p3MDhUVDc15wbmtjP7Scxal6ANEntM5OPmbNZlDOoU620bu1kv3q+z34SJtuQvTlk+0s4+kuH2xXbL
*/