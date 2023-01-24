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
9VBZAucf0ghI/KEh5mzGLhdH6LFdV+ixKynVw9s9jpfQ8B6KnLT0HPKTba1TLhjBbVn6m3TUQgDvWlpD0nK85ccUJ08OsNaJ2zLHsBq7/aKsfjO71RpIY15x0JjbfJeI03Hhixrsa0azKZErP86xyjt/04xlEut7kubLnIzf1fu387s0vR7YLKBR6mWA8hLr86DzLHFj6OLYGPsB2vh2SvH1vHqSt/u5GEbe/S/JK+pvxXa09r23hQa8Z8D4F/PFzfhi48OaY2x+ICucgKgvALxf5AzuLLkd++ZkUKoRp9RG5x43kb434lytuLQP1ZFdBLXK+zxltCV7m7kNXTW84B93xpfulFxC+ALDuyOfuHd5XVgBUdtiZ8QeiP5qaPZbvXozpgTfBXuVLrSczcjT+2tuVrEhtHp+szmW/JeVEZoHD793yKswtzEAonXJzY/hKQGwPuMvUwCYC8+rrs2fN28Vjxr4bx55L+wvtCdSRBkXiTTAO+hvQq90TM8PUhO1Pq+h4peR7ofea/nZfbF5pBWK79LRuY9m29ppTLmPddADmNFKX++M9g0GNhA4YC3uiAT2hdmxjDmfvQhdoHct6ENXSaH3Zg8dC0eNhNi/VdqFE1L8utF8vOlS9WlSRd+jxLN55bv1gKXiueHXyD0rXd3+2q1/nY6u3XoQ1xGgAcc1ld/eJ8QDOQsPnTFeOV4f99gYX6/GUO21dmHG
*/