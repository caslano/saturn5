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
# ifndef BOOST_PREPROCESSOR_LIST_REVERSE_HPP
# define BOOST_PREPROCESSOR_LIST_REVERSE_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/list/fold_left.hpp>
#
# /* BOOST_PP_LIST_REVERSE */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_REVERSE(list) BOOST_PP_LIST_FOLD_LEFT(BOOST_PP_LIST_REVERSE_O, BOOST_PP_NIL, list)
# else
#    define BOOST_PP_LIST_REVERSE(list) BOOST_PP_LIST_REVERSE_I(list)
#    define BOOST_PP_LIST_REVERSE_I(list) BOOST_PP_LIST_FOLD_LEFT(BOOST_PP_LIST_REVERSE_O, BOOST_PP_NIL, list)
# endif
#
# define BOOST_PP_LIST_REVERSE_O(d, s, x) (x, s)
#
# /* BOOST_PP_LIST_REVERSE_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_REVERSE_D(d, list) BOOST_PP_LIST_FOLD_LEFT_ ## d(BOOST_PP_LIST_REVERSE_O, BOOST_PP_NIL, list)
# else
#    define BOOST_PP_LIST_REVERSE_D(d, list) BOOST_PP_LIST_REVERSE_D_I(d, list)
#    define BOOST_PP_LIST_REVERSE_D_I(d, list) BOOST_PP_LIST_FOLD_LEFT_ ## d(BOOST_PP_LIST_REVERSE_O, BOOST_PP_NIL, list)
# endif
#
# endif

/* reverse.hpp
bBmUd2c9G3XwQh6e+HDItg+OWTodRAZWtGvHbVuOdxei0RyBJ1+fSNeljnTFQvAUiA33HQ0eh35hpfgHLa5nOPyJakUzKpH0JYcTQpYxp62iJJLoWoas8JfZeYhzIjQCzcdCrInn6XymwH3DyUFn+hUH5x4Rz+W2DRLyWylzhkkJ3GmXjjM3JeyD5nbA3k8Le7+jgzAEO7ip3OK37rjNvxZ2OTXqqU3eJOz+U3BGcNLZwccl
*/