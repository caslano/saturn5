//  (C) Copyright John Maddock 2005.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// The aim of this header is just to include <functional> but to do
// so in a way that does not result in recursive inclusion of
// the Boost TR1 components if boost/tr1/tr1/functional is in the
// include search path.  We have to do this to avoid circular
// dependencies:
//

#ifndef BOOST_CONFIG_FUNCTIONAL
#  define BOOST_CONFIG_FUNCTIONAL

#  ifndef BOOST_TR1_NO_RECURSION
#     define BOOST_TR1_NO_RECURSION
#     define BOOST_CONFIG_NO_FUNCTIONAL_RECURSION
#  endif

#  include <functional>

#  ifdef BOOST_CONFIG_NO_FUNCTIONAL_RECURSION
#     undef BOOST_TR1_NO_RECURSION
#     undef BOOST_CONFIG_NO_FUNCTIONAL_RECURSION
#  endif

#endif

/* functional.hpp
E063+GvZTt73kp6tEk6LhAxTVnmFhUVz9Mt9eRk9i7t7xF2ThMrG7Gdo2dwk+X4xrg79a2fUBahL2Pf7Bf1rtl2TWsqz7/XUtD5DtfO29ZbwHvgr1Mu8hfeKy7ZmxiVYK1E3oZx6fPNH9/H+GVo3j0n+Vsenc1rsIuJaYw2zvoHpxNXcvsvabze1G3trWl29p1hXw7u8RzxPEN/uwCTrzLia1oy4P1hnxJ/AAvYE0ze2lD64
*/