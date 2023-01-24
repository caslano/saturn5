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
# ifndef BOOST_PREPROCESSOR_COMPARISON_LESS_EQUAL_HPP
# define BOOST_PREPROCESSOR_COMPARISON_LESS_EQUAL_HPP
#
# include <boost/preprocessor/arithmetic/sub.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/logical/not.hpp>
#
# /* BOOST_PP_LESS_EQUAL */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LESS_EQUAL(x, y) BOOST_PP_NOT(BOOST_PP_SUB(x, y))
# else
#    define BOOST_PP_LESS_EQUAL(x, y) BOOST_PP_LESS_EQUAL_I(x, y)
#    define BOOST_PP_LESS_EQUAL_I(x, y) BOOST_PP_NOT(BOOST_PP_SUB(x, y))
# endif
#
# /* BOOST_PP_LESS_EQUAL_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LESS_EQUAL_D(d, x, y) BOOST_PP_NOT(BOOST_PP_SUB_D(d, x, y))
# else
#    define BOOST_PP_LESS_EQUAL_D(d, x, y) BOOST_PP_LESS_EQUAL_D_I(d, x, y)
#    define BOOST_PP_LESS_EQUAL_D_I(d, x, y) BOOST_PP_NOT(BOOST_PP_SUB_D(d, x, y))
# endif
#
# endif

/* less_equal.hpp
d966UAmiZr/KxVCx33o/MI3aJRyEea2/47ND5WIykRMTvfLzWRKvQPxV5yt/7L/QiTYZI71JvPWP938Rf37T+iqa/cSvzEVU0AL26ql/qO7EjNvRW6rXxb3U1mLhSrp/NOHX8i/CAcmCCDXeOaE/Pbl2VpwDET+uXed+4b1lspxVp09NF3S7c7fj5LoQkJTqj5iSpiM7U2WM9o7jyj3h/hlhNXEiQkTJa5E/Ei9Cgj3E6Buy+7EwOlqWXvbj7PI7SsXYD7QZN4ObIfBCARIezDezK9LbPEMDo2YWb8s/WszWarSpHj/GSuVt/xV35m9i2mAy3K10ovHinXgt7S4dA3itPIRpFrcSn6CGeBQzSzC4P9IUy5de4Xw6xxncw+bZ5wNgJu36LxH/LbjP9wEePOAXo0fVF4tJLzW6E/+dl0S1tWD/0mxDzcDd5G9UfDRuMVrd6xX7+fK8Njmtl/KiRHjhoHP+YxlSLEkpIpZNysi4sBBi13bz/M8WdI7uGFh4gL/+ZrJ7GjtkVSaS/KskBjYLy4CpPbq2SwSIBgw5twi0eoFdBDMNjyKgMZTo6Ydwbq7HqPx8K7YRy9lvH5/2I9ToRhlKflsaz67Iqxlgl3uHROQ1Z7lHbD3kcQf4A0sq2mZ3L2EwvhbPS4hbmzHWo7Ah9WRA1RZZ3PLs3pnj2Y3gHT83i2ZHUoQ0bx8gT+N4JydkNPhV3M3PTLv3
*/