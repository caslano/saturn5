//  (C) Copyright John Maddock 2005.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// The aim of this header is just to include <utility> but to do
// so in a way that does not result in recursive inclusion of
// the Boost TR1 components if boost/tr1/tr1/utility is in the
// include search path.  We have to do this to avoid circular
// dependencies:
//

#ifndef BOOST_CONFIG_UTILITY
#  define BOOST_CONFIG_UTILITY

#  ifndef BOOST_TR1_NO_RECURSION
#     define BOOST_TR1_NO_RECURSION
#     define BOOST_CONFIG_NO_UTILITY_RECURSION
#  endif

#  include <utility>

#  ifdef BOOST_CONFIG_NO_UTILITY_RECURSION
#     undef BOOST_TR1_NO_RECURSION
#     undef BOOST_CONFIG_NO_UTILITY_RECURSION
#  endif

#endif

/* utility.hpp
C60y1uQEznQGrS7L95bByjiuP0qsp1/BcYmSYaicp5NyWl9eFImCY51K3X9n0D+OouHUn8R+GFiTFM8ohZrTSmn1YME89MPnrgBbYXGVsm9vqxCdWKXSVdpUirI9ISgFzja0WsEW6zjjqAiitCSsm5Kg0tAgp0I3XZRhwRnjW5I7LaZGM9FJmpVo+Lkh0tileW4KAJlBxWGsiHRFr/00CxHwDREbSra7xrMo/MeUvuovignWeYUdZqWLBEmaTMM4HIbjyPJ0+eLK6C/vejIeWW5VWEY95w9Oh1ZU9ZBfWvT0Yh/+teAhkZqFVhXvdi+MnyQKlWZ82sMMJ3GCA5YzRtG2SN0BEjaIgot1C6MNEFI7jpLwCs7PtX2L/th1t9892lPS+XWfr8H4HgpALVA9Rc+O8ajewpFtQicX4fTaixMzDy8usExs9+jkNctt5wEd+HE8PTGXYx18xXqMV6t+74Hl0c6y3+X0xWrvAfZ7tk3vUFmMpBWaHg8OWO6Wd5x9sdyCmjP1Pnn+2Pvgj/14bnlGTyiUti0Yg+konk0D+OSNZyNrShT2XQlfiaBti217hZakbOqaC6W1q3t6azgLroLwJkhCU3LaqeKqVZkdjUbgjaMQ+8yH6eOjAhvF6YD9SDFfXzx1isbAtv4D
*/