//  (C) Copyright John Maddock 2008.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// The aim of this header is just to include <cmath> but to do
// so in a way that does not result in recursive inclusion of
// the Boost TR1 components if boost/tr1/tr1/cmath is in the
// include search path.  We have to do this to avoid circular
// dependencies:
//

#ifndef BOOST_CONFIG_CMATH
#  define BOOST_CONFIG_CMATH

#  ifndef BOOST_TR1_NO_RECURSION
#     define BOOST_TR1_NO_RECURSION
#     define BOOST_CONFIG_NO_CMATH_RECURSION
#  endif

#  include <cmath>

#  ifdef BOOST_CONFIG_NO_CMATH_RECURSION
#     undef BOOST_TR1_NO_RECURSION
#     undef BOOST_CONFIG_NO_CMATH_RECURSION
#  endif

#endif

/* cmath.hpp
98mxMYRvTjLr16snpV+vOzKMN2T7d162KLZdISwtVLIejcvrMjwb8ZeL9BbMPN5j0/s0lp+yT0MeFxm6zpmMOqf8lH0hqfD/1md4v13PfV2EJnIS2vjy5NxXMryKfyXiv+KU+M30y3y6EPk0IbkHQ83PybAjUDZtF4rePeHkuwtU3pT3mTdKt5r3GC9yEa/DGm+hTWTdZcqq3zu637UlXy8sWXk80/8f//UVHa6kHAlJSK5QjhyrFHIfpeaaa1RyE+bYtxKV+77NFbkz5Jwl5WblWoSJWAyLGW0z+3023396fNbr83q9X8/j9Xp/Hg/va7SW5DUZyprm4eZEESFu5wE3Uk48olr6bkyxb6fKp8gPYxrtD+JbA7iTac8knWrZzU6FfkV8kJYd870BUq72bBKaHL8UnQ6RjZ6yycIc+5qoHrpOoGmjb/mbfjgU0QCLG8wsrenX587fVeijUa23HF/uuh9TH82oXJJfscbSv+nWhV2wrn3tVoR5IPHmhOOE/mQAwbWzYsVl8OzoauzENbf7/pHI32mUfi8bRrAhYyK6vpXYUmKDxmT7Bb/qpIs1UOl/XK4SJyT0swkvJ1WKJg9FF+2ll9UEJeSkyMyl/eztVgl9U4Dg/tHdgzqvibV/jrTPy/NMkP6xI9sicHrLtrRpffaVe2JeLEosw8f8W8CwOfRd6/K7RbXufd/omcR3G00VLVjpRccqw1yP
*/