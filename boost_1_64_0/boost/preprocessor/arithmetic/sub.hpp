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
# ifndef BOOST_PREPROCESSOR_ARITHMETIC_SUB_HPP
# define BOOST_PREPROCESSOR_ARITHMETIC_SUB_HPP
#
# include <boost/preprocessor/arithmetic/dec.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/while.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
#
# /* BOOST_PP_SUB */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SUB(x, y) BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_WHILE(BOOST_PP_SUB_P, BOOST_PP_SUB_O, (x, y)))
# else
#    define BOOST_PP_SUB(x, y) BOOST_PP_SUB_I(x, y)
#    define BOOST_PP_SUB_I(x, y) BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_WHILE(BOOST_PP_SUB_P, BOOST_PP_SUB_O, (x, y)))
# endif
#
# define BOOST_PP_SUB_P(d, xy) BOOST_PP_TUPLE_ELEM(2, 1, xy)
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_SUB_O(d, xy) BOOST_PP_SUB_O_I xy
# else
#    define BOOST_PP_SUB_O(d, xy) BOOST_PP_SUB_O_I(BOOST_PP_TUPLE_ELEM(2, 0, xy), BOOST_PP_TUPLE_ELEM(2, 1, xy))
# endif
#
# define BOOST_PP_SUB_O_I(x, y) (BOOST_PP_DEC(x), BOOST_PP_DEC(y))
#
# /* BOOST_PP_SUB_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SUB_D(d, x, y) BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_WHILE_ ## d(BOOST_PP_SUB_P, BOOST_PP_SUB_O, (x, y)))
# else
#    define BOOST_PP_SUB_D(d, x, y) BOOST_PP_SUB_D_I(d, x, y)
#    define BOOST_PP_SUB_D_I(d, x, y) BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_WHILE_ ## d(BOOST_PP_SUB_P, BOOST_PP_SUB_O, (x, y)))
# endif
#
# endif

/* sub.hpp
JwhmPEypjXYxPyUhcQhHwnog6ixz0VldFAA12pETCXTNgJbr3K4Ybpj9m3K+nFOvbEJ7kHEurEb4hDX4foxnluPxfZpHhbw10+yM0ldh9+EQhp43YRP7Ba4J0Yv4/OEgB4b4qiHP/QvzKP5S3qxF3nO1qCbzQkgbKcaGcBqItbqlSjrQIoAYsMuPfbvl4e6wgLopC96ZK9eYYjuFzq4GzoR/qTAYlOOpsyQ9PoZRIMxa9rqu2DcFd7IY9PbdpP9t8NUwM6h1tYK0sX9IHe3bc8oA9Hw+lzSR5Fs/w6sn7izzIOeR9d6gRP1K/DTpkzwHQCR1YpjVAPmOvVqmcaUJhuESSfPyRUnnN1gP0s+12Jvu9Cv/g4OtePbq1N9JhZ+4XAqdTyo4zdBn3L3uzvPRkUu3betCPZbczmHm1KmxC3a4YGYd7C/mM5OioaByg5GdiUC3joroSrE/zdoYSFwv+oZA/lXQn5R1W/WeMGHeR7ovyTGbPSPL745j8M+bI3ZUTcvvl4edd6sxVGXrqsLRLWaeKrRk+2iXZZc4x+XglfElfL0y/Bi+XISQ1g==
*/