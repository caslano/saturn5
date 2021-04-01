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
# ifndef BOOST_PREPROCESSOR_LIST_SIZE_HPP
# define BOOST_PREPROCESSOR_LIST_SIZE_HPP
#
# include <boost/preprocessor/arithmetic/inc.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/while.hpp>
# include <boost/preprocessor/list/adt.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
#
# /* BOOST_PP_LIST_SIZE */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_SIZE(list) BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_WHILE(BOOST_PP_LIST_SIZE_P, BOOST_PP_LIST_SIZE_O, (0, list)))
# else
#    define BOOST_PP_LIST_SIZE(list) BOOST_PP_LIST_SIZE_I(list)
#    define BOOST_PP_LIST_SIZE_I(list) BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_WHILE(BOOST_PP_LIST_SIZE_P, BOOST_PP_LIST_SIZE_O, (0, list)))
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_SIZE_P(d, rl) BOOST_PP_LIST_IS_CONS(BOOST_PP_TUPLE_ELEM(2, 1, rl))
# else
#    define BOOST_PP_LIST_SIZE_P(d, rl) BOOST_PP_LIST_SIZE_P_I(BOOST_PP_TUPLE_REM_2 rl)
#    define BOOST_PP_LIST_SIZE_P_I(im) BOOST_PP_LIST_SIZE_P_II(im)
#    define BOOST_PP_LIST_SIZE_P_II(r, l) BOOST_PP_LIST_IS_CONS(l)
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_SIZE_O(d, rl) (BOOST_PP_INC(BOOST_PP_TUPLE_ELEM(2, 0, rl)), BOOST_PP_LIST_REST(BOOST_PP_TUPLE_ELEM(2, 1, rl)))
# else
#    define BOOST_PP_LIST_SIZE_O(d, rl) BOOST_PP_LIST_SIZE_O_I(BOOST_PP_TUPLE_REM_2 rl)
#    define BOOST_PP_LIST_SIZE_O_I(im) BOOST_PP_LIST_SIZE_O_II(im)
#    define BOOST_PP_LIST_SIZE_O_II(r, l) (BOOST_PP_INC(r), BOOST_PP_LIST_REST(l))
# endif
#
# /* BOOST_PP_LIST_SIZE_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_SIZE_D(d, list) BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_WHILE_ ## d(BOOST_PP_LIST_SIZE_P, BOOST_PP_LIST_SIZE_O, (0, list)))
# else
#    define BOOST_PP_LIST_SIZE_D(d, list) BOOST_PP_LIST_SIZE_D_I(d, list)
#    define BOOST_PP_LIST_SIZE_D_I(d, list) BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_WHILE_ ## d(BOOST_PP_LIST_SIZE_P, BOOST_PP_LIST_SIZE_O, (0, list)))
# endif
#
# endif

/* size.hpp
SMvVDefCmxbiU2IrV6qNATOy9PVNunBDNmLpmwEgsbaiZSaIQaykXMQt42oyl+h99YSLCADgGZV9Qs95SagLuLwZIl9gMkSynsKX4A2wu38soO4w63I3icwQXzlO4M8oKB2KyQ2cmnOfQR4AqdlhIfin2c9i8vW2/06BWPx3CsO49mpEvpc6KrQ+ZwXUUtr1TQTex2zJL38PBAWgP1UBEPzIE0W/RPq1J1pEnYt+hZq+Xc/1CxkB/WLVm78nkwMgo/RkIQfJTf93dqjQhU8vX7oFqdsrkbH6WOe/XMhQ3/BD5sAchk2FsQMv9biJ7EwWoMJ/5PdXhS7Tsyn2aMdcFCWFB5/fMEdCBv9Cp224ku1+7gVq6OemUzqt9GmSFjAvsqrU/RjyKwtqakN/VNXTdIT3YPd4ZHYnxcR6cC+I5UyTlu0zQvwhrxEn2iENz220QGKhR1SBqe0X4GErVMThEMXlmrSYD7o4BOFnvDGE6l0YIWpwN/5IuaYP2zp23h0U5v1NMB5Yq87UvcmotlC7pvrlHDS6NcLByAYpIvVHHrUQhedoef6DrDFbKw==
*/