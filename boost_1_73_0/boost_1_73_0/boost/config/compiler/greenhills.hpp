//  (C) Copyright John Maddock 2001. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  Greenhills C++ compiler setup:

#define BOOST_COMPILER "Greenhills C++ version " BOOST_STRINGIZE(__ghs)

#include <boost/config/compiler/common_edg.hpp>

//
// versions check:
// we don't support Greenhills prior to version 0:
#if __ghs < 0
#  error "Compiler not supported or configured - please reconfigure"
#endif
//
// last known and checked version is 0:
#if (__ghs > 0)
#  if defined(BOOST_ASSERT_CONFIG)
#     error "boost: Unknown compiler version - please run the configure tests and report the results"
#  endif
#endif



/* greenhills.hpp
3UYAyUmhmtAYsVj6sg+Q61yca8PSGvRnt38MB+gdmhwqplnGEf5cu0uuTycDXujIyv70nNGBKgekDXUQ5uEs+wv6eY3ITy8F9685zmYL+P+2Iy1L4d302ZPfBKTw7lQ+wuWvCMj6wuMI/0B4TUBW8rg2INEZ1wVEup4SEAvazIBY0GYRvkl4U0ACsGcT4kmh1zynfowFxGM2TkgPjJkXEI9Zeq3HiglvJUQYMb3DY9ALJQOS4pFeyhzNkQqIVL0=
*/