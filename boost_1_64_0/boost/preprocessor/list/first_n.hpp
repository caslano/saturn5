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
# ifndef BOOST_PREPROCESSOR_LIST_FIRST_N_HPP
# define BOOST_PREPROCESSOR_LIST_FIRST_N_HPP
#
# include <boost/preprocessor/arithmetic/dec.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/while.hpp>
# include <boost/preprocessor/list/adt.hpp>
# include <boost/preprocessor/list/reverse.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
#
# /* BOOST_PP_LIST_FIRST_N */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_FIRST_N(count, list) BOOST_PP_LIST_REVERSE(BOOST_PP_TUPLE_ELEM(3, 2, BOOST_PP_WHILE(BOOST_PP_LIST_FIRST_N_P, BOOST_PP_LIST_FIRST_N_O, (count, list, BOOST_PP_NIL))))
# else
#    define BOOST_PP_LIST_FIRST_N(count, list) BOOST_PP_LIST_FIRST_N_I(count, list)
#    define BOOST_PP_LIST_FIRST_N_I(count, list) BOOST_PP_LIST_REVERSE(BOOST_PP_TUPLE_ELEM(3, 2, BOOST_PP_WHILE(BOOST_PP_LIST_FIRST_N_P, BOOST_PP_LIST_FIRST_N_O, (count, list, BOOST_PP_NIL))))
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_FIRST_N_P(d, data) BOOST_PP_TUPLE_ELEM(3, 0, data)
# else
#    define BOOST_PP_LIST_FIRST_N_P(d, data) BOOST_PP_LIST_FIRST_N_P_I data
#    define BOOST_PP_LIST_FIRST_N_P_I(c, l, nl) c
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_LIST_FIRST_N_O(d, data) BOOST_PP_LIST_FIRST_N_O_D data
# else
#    define BOOST_PP_LIST_FIRST_N_O(d, data) BOOST_PP_LIST_FIRST_N_O_D(BOOST_PP_TUPLE_ELEM(3, 0, data), BOOST_PP_TUPLE_ELEM(3, 1, data), BOOST_PP_TUPLE_ELEM(3, 2, data))
# endif
#
# define BOOST_PP_LIST_FIRST_N_O_D(c, l, nl) (BOOST_PP_DEC(c), BOOST_PP_LIST_REST(l), (BOOST_PP_LIST_FIRST(l), nl))
#
# /* BOOST_PP_LIST_FIRST_N_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_FIRST_N_D(d, count, list) BOOST_PP_LIST_REVERSE_D(d, BOOST_PP_TUPLE_ELEM(3, 2, BOOST_PP_WHILE_ ## d(BOOST_PP_LIST_FIRST_N_P, BOOST_PP_LIST_FIRST_N_O, (count, list, BOOST_PP_NIL))))
# else
#    define BOOST_PP_LIST_FIRST_N_D(d, count, list) BOOST_PP_LIST_FIRST_N_D_I(d, count, list)
#    define BOOST_PP_LIST_FIRST_N_D_I(d, count, list) BOOST_PP_LIST_REVERSE_D(d, BOOST_PP_TUPLE_ELEM(3, 2, BOOST_PP_WHILE_ ## d(BOOST_PP_LIST_FIRST_N_P, BOOST_PP_LIST_FIRST_N_O, (count, list, BOOST_PP_NIL))))
# endif
#
# endif

/* first_n.hpp
rhuL1rmYZI04UtNThByrygaX/IdoM+BoT6XNYmIAf7In0uMfvjhnp53iCQk8epaWN3G5pRUl2aUjOs40of7Kwuj1Y2yTP4FV/IVNV1O/5RYd1Ll4HqR7JHnGaUjTv5Gc3EqZMlwmW4Vl8D5uNRqXkvjOgj8KZdBo+mLZ590dGy0ge1+hzlGXOVa7+tEnwHKvgTpwNBMyUp6La1oO9fgqinxJdkSJ/Ocx9Whq7Fcthge8KZ+exoVNn4FGeSTi/I5jqzJjbA71M/PMI4k1AG7j30W3EzXKkEpOqZzcbn8M0BRHz2YWmUxH+DtJDwtFqCcJkMDkMg2HCIfe0SW36U9VHRilDlPo+S0cfqSIZ12Ln3k83uBAFsfIM++F6XhpeEpzADKtOdYyAHtv5JtRwf0DovAZILtuW6BjOLtyDCH8EBSOQPaTXK0a3aUXKoxPLUKoXNPn2vQZL+YsCsFGB18R+k5Jkblkk7T2OVhWMQOXvtPO+8dybWTFHlVkwFSSoGSiVBW/fFe5hhsnVxhgsM9/1qHDyZYgKbB1PlXzfFbWymucnI/sWfA+Gkc3Mw==
*/