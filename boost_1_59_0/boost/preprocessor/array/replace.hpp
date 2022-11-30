# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2002.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_ARRAY_REPLACE_HPP
# define BOOST_PREPROCESSOR_ARRAY_REPLACE_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_STRICT()
#
# include <boost/preprocessor/arithmetic/inc.hpp>
# include <boost/preprocessor/array/elem.hpp>
# include <boost/preprocessor/array/push_back.hpp>
# include <boost/preprocessor/comparison/not_equal.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/deduce_d.hpp>
# include <boost/preprocessor/control/iif.hpp>
# include <boost/preprocessor/control/while.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
#
# /* BOOST_PP_ARRAY_REPLACE */
#
# define BOOST_PP_ARRAY_REPLACE(array, i, elem) BOOST_PP_ARRAY_REPLACE_I(BOOST_PP_DEDUCE_D(), array, i, elem)
# define BOOST_PP_ARRAY_REPLACE_I(d, array, i, elem) BOOST_PP_ARRAY_REPLACE_D(d, array, i, elem)
#
# /* BOOST_PP_ARRAY_REPLACE_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ARRAY_REPLACE_D(d, array, i, elem) BOOST_PP_TUPLE_ELEM(5, 3, BOOST_PP_WHILE_ ## d(BOOST_PP_ARRAY_REPLACE_P, BOOST_PP_ARRAY_REPLACE_O, (0, i, elem, (0, ()), array)))
# else
#    define BOOST_PP_ARRAY_REPLACE_D(d, array, i, elem) BOOST_PP_ARRAY_REPLACE_D_I(d, array, i, elem)
#    define BOOST_PP_ARRAY_REPLACE_D_I(d, array, i, elem) BOOST_PP_TUPLE_ELEM(5, 3, BOOST_PP_WHILE_ ## d(BOOST_PP_ARRAY_REPLACE_P, BOOST_PP_ARRAY_REPLACE_O, (0, i, elem, (0, ()), array)))
# endif
#
# define BOOST_PP_ARRAY_REPLACE_P(d, state) BOOST_PP_NOT_EQUAL(BOOST_PP_TUPLE_ELEM(5, 0, state), BOOST_PP_ARRAY_SIZE(BOOST_PP_TUPLE_ELEM(5, 4, state)))
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_STRICT()
#    define BOOST_PP_ARRAY_REPLACE_O(d, state) BOOST_PP_ARRAY_REPLACE_O_I state
# else
#    define BOOST_PP_ARRAY_REPLACE_O(d, state) BOOST_PP_ARRAY_REPLACE_O_I(BOOST_PP_TUPLE_ELEM(5, 0, state), BOOST_PP_TUPLE_ELEM(5, 1, state), BOOST_PP_TUPLE_ELEM(5, 2, state), BOOST_PP_TUPLE_ELEM(5, 3, state), BOOST_PP_TUPLE_ELEM(5, 4, state))
# endif
#
# define BOOST_PP_ARRAY_REPLACE_O_I(n, i, elem, res, arr) (BOOST_PP_INC(n), i, elem, BOOST_PP_ARRAY_PUSH_BACK(res, BOOST_PP_IIF(BOOST_PP_NOT_EQUAL(n, i), BOOST_PP_ARRAY_ELEM(n, arr), elem)), arr)
#
# else
#
# include <boost/preprocessor/arithmetic/inc.hpp>
# include <boost/preprocessor/array/elem.hpp>
# include <boost/preprocessor/array/push_back.hpp>
# include <boost/preprocessor/comparison/not_equal.hpp>
# include <boost/preprocessor/control/deduce_d.hpp>
# include <boost/preprocessor/control/iif.hpp>
# include <boost/preprocessor/control/while.hpp>
# if BOOST_PP_LIMIT_TUPLE == 256
# include <boost/preprocessor/logical/not.hpp>
# endif
# include <boost/preprocessor/tuple/elem.hpp>
#
# /* BOOST_PP_ARRAY_REPLACE */
#
# define BOOST_PP_ARRAY_REPLACE(array, i, elem) BOOST_PP_ARRAY_REPLACE_I(BOOST_PP_DEDUCE_D(), array, i, elem)
# define BOOST_PP_ARRAY_REPLACE_I(d, array, i, elem) BOOST_PP_ARRAY_REPLACE_D(d, array, i, elem)
#
# /* BOOST_PP_ARRAY_REPLACE_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
# if BOOST_PP_LIMIT_TUPLE == 256
#    define BOOST_PP_ARRAY_REPLACE_D(d, array, i, elem) BOOST_PP_ARRAY_REPLACE_ZERO_D(d, array, i, elem, BOOST_PP_NOT(i))
# else
#    define BOOST_PP_ARRAY_REPLACE_D(d, array, i, elem) BOOST_PP_TUPLE_ELEM(5, 3, BOOST_PP_WHILE_ ## d(BOOST_PP_ARRAY_REPLACE_P, BOOST_PP_ARRAY_REPLACE_O, (0, i, elem, (0, ()), array)))
# endif
# else
#    define BOOST_PP_ARRAY_REPLACE_D(d, array, i, elem) BOOST_PP_ARRAY_REPLACE_D_I(d, array, i, elem)
# if BOOST_PP_LIMIT_TUPLE == 256
#    define BOOST_PP_ARRAY_REPLACE_D_I(d, array, i, elem) BOOST_PP_ARRAY_REPLACE_ZERO_D(d, array, i, elem, BOOST_PP_NOT(i))
# else
#    define BOOST_PP_ARRAY_REPLACE_D_I(d, array, i, elem) BOOST_PP_TUPLE_ELEM(5, 3, BOOST_PP_WHILE_ ## d(BOOST_PP_ARRAY_REPLACE_P, BOOST_PP_ARRAY_REPLACE_O, (0, i, elem, (0, ()), array)))
# endif
# endif
#
# if BOOST_PP_LIMIT_TUPLE == 256
# define BOOST_PP_ARRAY_REPLACE_ZERO_D(d, array, i, elem, zero) \
         BOOST_PP_TUPLE_ELEM(5, 3, BOOST_PP_WHILE_ ## d(BOOST_PP_ARRAY_REPLACE_P, BOOST_PP_ARRAY_REPLACE_O, \
         (1, i, elem, BOOST_PP_IIF(zero,(1, (elem)),(1, (BOOST_PP_ARRAY_ELEM(0,array)))), array)))
# endif
#
# define BOOST_PP_ARRAY_REPLACE_P(d, state) BOOST_PP_NOT_EQUAL(BOOST_PP_TUPLE_ELEM(5, 0, state), BOOST_PP_ARRAY_SIZE(BOOST_PP_TUPLE_ELEM(5, 4, state)))
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_STRICT()
#    define BOOST_PP_ARRAY_REPLACE_O(d, state) BOOST_PP_ARRAY_REPLACE_O_I state
# else
#    define BOOST_PP_ARRAY_REPLACE_O(d, state) BOOST_PP_ARRAY_REPLACE_O_I(BOOST_PP_TUPLE_ELEM(5, 0, state), BOOST_PP_TUPLE_ELEM(5, 1, state), BOOST_PP_TUPLE_ELEM(5, 2, state), BOOST_PP_TUPLE_ELEM(5, 3, state), BOOST_PP_TUPLE_ELEM(5, 4, state))
# endif
#
# define BOOST_PP_ARRAY_REPLACE_O_I(n, i, elem, res, arr) (BOOST_PP_INC(n), i, elem, BOOST_PP_ARRAY_PUSH_BACK(res, BOOST_PP_IIF(BOOST_PP_NOT_EQUAL(n, i), BOOST_PP_ARRAY_ELEM(n, arr), elem)), arr)
#
# endif
#
# endif

/* replace.hpp
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
*/