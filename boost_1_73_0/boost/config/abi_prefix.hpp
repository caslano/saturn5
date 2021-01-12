//  abi_prefix header  -------------------------------------------------------//

// (c) Copyright John Maddock 2003
   
// Use, modification and distribution are subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CONFIG_ABI_PREFIX_HPP
# define BOOST_CONFIG_ABI_PREFIX_HPP
#else
# error double inclusion of header boost/config/abi_prefix.hpp is an error
#endif

#include <boost/config.hpp>

// this must occur after all other includes and before any code appears:
#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

#if defined( __BORLANDC__ )
#pragma nopushoptwarn
#endif


/* abi_prefix.hpp
nl92kW873Avzwf2wIDwi5+0Y7AQ/ht3hJ7AXPAH7wZMwHn4Gk+DncCg8DdPgGZgFz8LR8BwcC8/DCfDvcAr8Gk6HF+Ej8Fv4GPwePgkvwfnwMlwIr8j98Ce4HF6Fq+Ev8DX4K3wT2uxcT6Ad7oBO+D4MgPtgEDwEg+ExmAd+CkPhaZgXnoP54AVYAH4Pw+GPsBD8FUZA834VCUNgEZgPFoOFYBQsCovDErAELAtLwUqwNKwO
*/