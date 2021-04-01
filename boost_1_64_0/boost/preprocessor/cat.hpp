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
# ifndef BOOST_PREPROCESSOR_CAT_HPP
# define BOOST_PREPROCESSOR_CAT_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_CAT */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_CAT(a, b) BOOST_PP_CAT_I(a, b)
# else
#    define BOOST_PP_CAT(a, b) BOOST_PP_CAT_OO((a, b))
#    define BOOST_PP_CAT_OO(par) BOOST_PP_CAT_I ## par
# endif
#
# if (~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()) || (defined(__INTEL_COMPILER) && __INTEL_COMPILER >= 1700)
#    define BOOST_PP_CAT_I(a, b) a ## b
# else
#    define BOOST_PP_CAT_I(a, b) BOOST_PP_CAT_II(~, a ## b)
#    define BOOST_PP_CAT_II(p, res) res
# endif
#
# endif

/* cat.hpp
o5QBE3ENxQb9J8eaCWJdpQdtf4iZuREH29ANvCueI9z2+IXw05NcU3BBoDssmN0IEZ8aHWrGzOXhW9eyTAkLUJx5Ncbke/koIYiVwibU2G1nf9bKJtdlRuYW3QNJBcvzkIDPsrvUuqc4vXy/q0Rvz9d7YWax9vc+NsJ1e1tsF/taXZNTh9KjeCtvSf/XoSq189y7MRniuyRag4p+0Z39m3r9nhCByEUohp+YLO0qNXVhq39Psr9wAl4sHS+E7B+vvhGr7DDD+vw3sWZMNCQ3p84rLqrTMGXSgTXay+0xpQB14lxygk/OgBGbtbLpfDCa/EET77fxsQnHLG+u8Gvv8ay7EnjePhC9KqgpnepRXq44zzaQo55AMg17WLAZSWjb0IK0jvmivAWeRzRutJNcoIQnLEvEzHhmPxIQmJPbtuPZ4ZpvnLSQ5E8tn783i7xWaXow+Kr6tTExYOmA7oXppUwAqbh4CqS9qMNxHIMlVUy3V7yXpJLe1JwOOMKIXezvTZY9ztN1pNTjDo8+TnGcz5320+aiSRuEC+Q854wjToXHq23LERNmls7KAg==
*/