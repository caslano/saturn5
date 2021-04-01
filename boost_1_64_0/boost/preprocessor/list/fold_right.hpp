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
# ifndef BOOST_PREPROCESSOR_LIST_FOLD_RIGHT_HPP
# define BOOST_PREPROCESSOR_LIST_FOLD_RIGHT_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/control/while.hpp>
# include <boost/preprocessor/debug/error.hpp>
# include <boost/preprocessor/detail/auto_rec.hpp>
#
# if 0
#    define BOOST_PP_LIST_FOLD_RIGHT(op, state, list)
# endif
#
# define BOOST_PP_LIST_FOLD_RIGHT BOOST_PP_CAT(BOOST_PP_LIST_FOLD_RIGHT_, BOOST_PP_AUTO_REC(BOOST_PP_WHILE_P, 256))
#
# define BOOST_PP_LIST_FOLD_RIGHT_257(o, s, l) BOOST_PP_ERROR(0x0004)
#
# define BOOST_PP_LIST_FOLD_RIGHT_D(d, o, s, l) BOOST_PP_LIST_FOLD_RIGHT_ ## d(o, s, l)
# define BOOST_PP_LIST_FOLD_RIGHT_2ND BOOST_PP_LIST_FOLD_RIGHT
# define BOOST_PP_LIST_FOLD_RIGHT_2ND_D BOOST_PP_LIST_FOLD_RIGHT_D
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    include <boost/preprocessor/list/detail/edg/fold_right.hpp>
# else
#    include <boost/preprocessor/list/detail/fold_right.hpp>
# endif
#
# endif

/* fold_right.hpp
/yLskNCpZGDG6dPi2uWK6XPe0Zb+Bal1kYPtb6AeDABlqzo5lwQ8FqAU6f3/r5G6CS/3JsYu4+3bPyTdVSrrijLWksihduSBTCgIlkPbIzu83pLJFFhFvjDFKSlHOo1khdeKOvminkncWfn4XY9N9LEvrQB2JsXaR+TVSEl9DN9kM/ehryviYS5AWR8v0/SyRguCxz3XXQrQrOD4VLXxfO1t0swKGGDA9JjXJJrMpFCFoxmKmk3BT+/fWS1GlJRrjCf1pkFZwHs1gUkMQjsZBEAF9VeRMJQSyTaCLlzWyiTSCmz5oEkiLSp/4XrWK50MHRxQJSFeYt45Z9OTioDHFRzXCKqgNqau9KlCXARYhfgQoCFCczMp3/K5F9CqyhYFP+i5kRMp6i5coHD9rRw0f41HsONFkHuCYA4d08cZuF1+Xwh0TF4bGALiS9m702ym0+9lp96lHXweHGcGIE9mSuUAcWP9WMBDC33y8zBvA85/GnpmcBF9UrrqfULVsjmYgCsGc0Wh08VPoy4ltIlP73U3fC+4yXxpHYuBZKolOMGzXVMJEeky/WwtCw==
*/