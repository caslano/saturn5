//  (C) Copyright John Maddock 2001 - 2002. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  SGI C++ compiler setup:

#define BOOST_COMPILER "SGI Irix compiler version " BOOST_STRINGIZE(_COMPILER_VERSION)

#include <boost/config/compiler/common_edg.hpp>

//
// Threading support:
// Turn this on unconditionally here, it will get turned off again later
// if no threading API is detected.
//
#define BOOST_HAS_THREADS
#define BOOST_NO_TWO_PHASE_NAME_LOOKUP

#undef BOOST_NO_SWPRINTF
#undef BOOST_DEDUCED_TYPENAME

//
// version check:
// probably nothing to do here?



/* sgi_mipspro.hpp
XAYD4NswGL4Hw+B+mB9ehgWgEco9EBaBRWEVWBrWh+VhU1gBtoKV4P2wOpwFa8CnYU24GNaC62A0XA/rwo2wAXwXNoQHYCP4GWwM/w6bwO9hc/gjbAFtYbzDhkVhK1gKtoZlYFtYA7aDTWEH2Ap2gu1hF9gNdoW9YXeYAu+Ac2E8fAoWg0tgFFwJi8NV8AfKcwu8At+C5+AO+DV8Dx6Cu6FZv9R9xNXukXbeYiRA7jOGjLOp
*/