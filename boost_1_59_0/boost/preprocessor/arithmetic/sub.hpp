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
# /* Revised by Edward Diener (2020) */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_ARITHMETIC_SUB_HPP
# define BOOST_PREPROCESSOR_ARITHMETIC_SUB_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_STRICT()
#
# include <boost/preprocessor/arithmetic/dec.hpp>
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
# else
#
# include <boost/preprocessor/arithmetic/dec.hpp>
# include <boost/preprocessor/control/iif.hpp>
# include <boost/preprocessor/control/while.hpp>
# include <boost/preprocessor/facilities/identity.hpp>
# include <boost/preprocessor/logical/and.hpp>
# include <boost/preprocessor/logical/bitor.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
# include <boost/preprocessor/arithmetic/detail/is_maximum_number.hpp>
# include <boost/preprocessor/arithmetic/detail/is_minimum_number.hpp>
#
# /* BOOST_PP_SUB */
#
#    define BOOST_PP_SUB(x, y) BOOST_PP_IIF(BOOST_PP_BITOR(BOOST_PP_DETAIL_IS_MAXIMUM_NUMBER(y),BOOST_PP_DETAIL_IS_MINIMUM_NUMBER(x)),BOOST_PP_IDENTITY_N(0,2),BOOST_PP_SUB_DO)(x,y)
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SUB_DO(x, y) BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_WHILE(BOOST_PP_SUB_P, BOOST_PP_SUB_O, (x, y)))
# else
#    define BOOST_PP_SUB_DO(x, y) BOOST_PP_SUB_I(x, y)
#    define BOOST_PP_SUB_I(x, y) BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_WHILE(BOOST_PP_SUB_P, BOOST_PP_SUB_O, (x, y)))
# endif
#
# define BOOST_PP_SUB_P(d, xy) BOOST_PP_AND(BOOST_PP_TUPLE_ELEM(2, 1, xy),BOOST_PP_TUPLE_ELEM(2, 0, xy))
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
#    define BOOST_PP_SUB_D(d, x, y) BOOST_PP_IIF(BOOST_PP_BITOR(BOOST_PP_DETAIL_IS_MAXIMUM_NUMBER(y),BOOST_PP_DETAIL_IS_MINIMUM_NUMBER(x)),BOOST_PP_IDENTITY_N(0,3),BOOST_PP_SUB_DO_D)(d,x,y)
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SUB_DO_D(d, x, y) BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_WHILE_ ## d(BOOST_PP_SUB_P, BOOST_PP_SUB_O, (x, y)))
# else
#    define BOOST_PP_SUB_DO_D(d, x, y) BOOST_PP_SUB_D_I(d, x, y)
#    define BOOST_PP_SUB_D_I(d, x, y) BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_WHILE_ ## d(BOOST_PP_SUB_P, BOOST_PP_SUB_O, (x, y)))
# endif
#
# endif
#
# endif

/* sub.hpp
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
*/