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
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
*/