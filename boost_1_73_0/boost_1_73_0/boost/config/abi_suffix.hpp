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
b4xKOHvLjkH2AbJPqf/OwhOXkjxrt3RZjFRR3tFwbBmywejpNnPuCdb/w+JOJMheAhpU8lDsgWEGnxyK01HtASr5KUsuWAg2fu3A+Zl9ofi7La61HkPBnbgGpqj2WGXf4vjRovi+QI8C6OqsUGKcAWVdhuck5hgP1GQNheotjn5lVP0tdZGDGahZLktwgycU/dEMLCwzqH6ie84GtnugjgqMUNRhhuO+3X/zFPp2h2I3eIJwH/lHAguHQ9rRCac=
*/