//  (C) Copyright John Maddock 2005.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// The aim of this header is just to include <memory> but to do
// so in a way that does not result in recursive inclusion of
// the Boost TR1 components if boost/tr1/tr1/memory is in the
// include search path.  We have to do this to avoid circular
// dependencies:
//

#ifndef BOOST_CONFIG_MEMORY
#  define BOOST_CONFIG_MEMORY

#  ifndef BOOST_TR1_NO_RECURSION
#     define BOOST_TR1_NO_RECURSION
#     define BOOST_CONFIG_NO_MEMORY_RECURSION
#  endif

#  include <memory>

#  ifdef BOOST_CONFIG_NO_MEMORY_RECURSION
#     undef BOOST_TR1_NO_RECURSION
#     undef BOOST_CONFIG_NO_MEMORY_RECURSION
#  endif

#endif

/* memory.hpp
sSB8a4vlgGaEsWcIfyCEd9CPhIhj/olwAyEJNDF8ki1COEXZhAgop3lHDNMdP+E+whDh94T5hD3onhQQwjmqkPA0G7FrYkHoTAhBowshPtVHEY4g7Ep4sc3rwMfGER5LeLWNQEMaP+HxhHBELyaka256EUJw7e1ImEQfwj8T9iWka4x1V2N0TUwlIYSyIYQ0VnMOIY0JAZMxRIzRfDqGmcwwjJfwXELqC7JirISwmvAMwhGOpHi4kPBSh+WGGNI=
*/