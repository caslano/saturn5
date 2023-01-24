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
# ifndef BOOST_PREPROCESSOR_COMPARISON_LESS_HPP
# define BOOST_PREPROCESSOR_COMPARISON_LESS_HPP
#
# include <boost/preprocessor/comparison/less_equal.hpp>
# include <boost/preprocessor/comparison/not_equal.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/iif.hpp>
# include <boost/preprocessor/logical/bitand.hpp>
# include <boost/preprocessor/tuple/eat.hpp>
#
# /* BOOST_PP_LESS */
#
# if BOOST_PP_CONFIG_FLAGS() & (BOOST_PP_CONFIG_MWCC() | BOOST_PP_CONFIG_DMC())
#    define BOOST_PP_LESS(x, y) BOOST_PP_BITAND(BOOST_PP_NOT_EQUAL(x, y), BOOST_PP_LESS_EQUAL(x, y))
# elif ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LESS(x, y) BOOST_PP_IIF(BOOST_PP_NOT_EQUAL(x, y), BOOST_PP_LESS_EQUAL, 0 BOOST_PP_TUPLE_EAT_2)(x, y)
# else
#    define BOOST_PP_LESS(x, y) BOOST_PP_LESS_I(x, y)
#    define BOOST_PP_LESS_I(x, y) BOOST_PP_IIF(BOOST_PP_NOT_EQUAL(x, y), BOOST_PP_LESS_EQUAL, 0 BOOST_PP_TUPLE_EAT_2)(x, y)
# endif
#
# /* BOOST_PP_LESS_D */
#
# if BOOST_PP_CONFIG_FLAGS() & (BOOST_PP_CONFIG_MWCC() | BOOST_PP_CONFIG_DMC())
#    define BOOST_PP_LESS_D(d, x, y) BOOST_PP_BITAND(BOOST_PP_NOT_EQUAL(x, y), BOOST_PP_LESS_EQUAL_D(d, x, y))
# elif ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LESS_D(d, x, y) BOOST_PP_IIF(BOOST_PP_NOT_EQUAL(x, y), BOOST_PP_LESS_EQUAL_D, 0 BOOST_PP_TUPLE_EAT_3)(d, x, y)
# else
#    define BOOST_PP_LESS_D(d, x, y) BOOST_PP_LESS_D_I(d, x, y)
#    define BOOST_PP_LESS_D_I(d, x, y) BOOST_PP_IIF(BOOST_PP_NOT_EQUAL(x, y), BOOST_PP_LESS_EQUAL_D, 0 BOOST_PP_TUPLE_EAT_3)(d, x, y)
# endif
#
# endif

/* less.hpp
RZVpTbwM+omnDD4y1Q0bRfe0iTobbG0aDobFLIOp4MYtDYzfeZ87/8rmlw8SlFFr/PxUgZhnxND4yL5AIzvPyIXTYk/l1MPD4+WjkKAEmP2NvyP04Glie5Qt5GZztJXzJBBkfJ8k8XDSG0SC22euTnd5VC7dVhTNa1VKuqMG72gzmmKbCiAKLOirQaU8cirIHeYeED0m/cyghqGF7vCDwoy9lkCvxujzAirlj8k/jDvim9ObyP3vAUQ6ZCoRzMy0F31MdL8sLSx2ddQ4Hcms4XzTL9+LmmVTg0y1vfR9RNaQ87cND9saLHNl4dr6GX/9KnyLilF04Wz3nYhi0EpB8m/xsSTx2x8coXfZKSeir7ydDJiQumtYIvdt90+64jYOpUT8e7d/HKyKboaDh//G0tMF1lStuKffLj8kF/vHVwAdDG9viR/h+pkKPztBurVX8jxJb+5RdMfIR4Ad+36OHjcR97R3ZSljx7VuMSxIY8hUdcBlTbvEDX9Hi8dLQ0k+Mzu/5fPG4iPdAVboCKii+LkqN63Ty3+/e68QmmvYieAwOIDCJ6v/2AqtuzQ9IWW5WpBQfReJWox/gtf7rxUcR3TvUwm0lWC5YPAfgvylgf3PYrWaV2tkFuRXr2opvTVKG6w59gI+0++gZH8m3kHLDEZ8xp3BoULJRVv7EfKHtneaX7IRnfoz0w6m6A/yHeuRrKV5Ax2BPfo/PH/U
*/