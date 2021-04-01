# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_PUNCTUATION_COMMA_IF_HPP
# define BOOST_PREPROCESSOR_PUNCTUATION_COMMA_IF_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/if.hpp>
# include <boost/preprocessor/facilities/empty.hpp>
# include <boost/preprocessor/punctuation/comma.hpp>
#
# /* BOOST_PP_COMMA_IF */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_COMMA_IF(cond) BOOST_PP_IF(cond, BOOST_PP_COMMA, BOOST_PP_EMPTY)()
# else
#    define BOOST_PP_COMMA_IF(cond) BOOST_PP_COMMA_IF_I(cond)
#    define BOOST_PP_COMMA_IF_I(cond) BOOST_PP_IF(cond, BOOST_PP_COMMA, BOOST_PP_EMPTY)()
# endif
#
# endif

/* comma_if.hpp
+B2XRA1Gc42IGNx8LHk/3Bcm+BUxhvUdi7QYj4s1IYlM7LoM0lT42oMVNOcibUQ9mp0kP6H3pap+Z2Nx50BdS4p5ATHqfxOY1HWQdofH6QOTVy6WygOdm8Nc19NeIJJ0tDIdH3AOv6O3E5cQwFdmO/lxvnHpbXsBIsFq3EqYlYAkUUR8JNwxpa2Z5x1yZ1hb90PWS9Lb+zIOkhZSAVX5ooilVerhbNV5H5gq9CuQZwp8SgXZDCxHFYMXgpdYMIQzs6mcXx6dRqE89RMGGLtyVO//QVa9fcEI7QMb1lfqHVAXFUEF/t75EB8gHsScjIBU4A+8eTS0/gy2bdKO4m2N8mCuQC2WEfKiRECkvWBpBfjyzdL7IMp5ZkCIr40OvqbuMeLXEJvsOD2GFX2jAt+OgaOueV0jr+DdqrijXWraWA4K12bpwNfh7XTNivgocPZy2nMpyJQAbaLKsC7Ta4u5YosVwHPLBVjkEJNs9Hl8U/rdJNaLFF1rV0PZS9LgfjIIjOmL5gSq9s4E3zn8YFUUvGED0nC07kJmB8IBkyPjmkHTovY6VazYuhwG2A==
*/