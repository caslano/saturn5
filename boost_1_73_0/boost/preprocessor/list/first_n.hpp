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
TPIVmMCPw3DliTBAWGwst/xSKormzswutN7kFFL+ZVAq3yu+A0pP33Zgg+J8sLbsdgY8/RnHa3Ddwj/DK35t4moDzmT1t/pb/a3+Vn+rv9Xf/8av7Uu7a/bzz4qTa84i5IaP1ZPvojOvJwT/11GE7I/w4++47oqKfdBJbcc6er4KB6nprBEca0kz3LlhUdNRxtbVz8fqOjhHPT1fiQO+iwx55I/UvVG495G6ztoNdUB84VgE
*/