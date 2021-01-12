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
# ifndef BOOST_PREPROCESSOR_COMPARISON_EQUAL_HPP
# define BOOST_PREPROCESSOR_COMPARISON_EQUAL_HPP
#
# include <boost/preprocessor/comparison/not_equal.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/logical/compl.hpp>
#
# /* BOOST_PP_EQUAL */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EQUAL(x, y) BOOST_PP_COMPL(BOOST_PP_NOT_EQUAL(x, y))
# else
#    define BOOST_PP_EQUAL(x, y) BOOST_PP_EQUAL_I(x, y)
#    define BOOST_PP_EQUAL_I(x, y) BOOST_PP_COMPL(BOOST_PP_NOT_EQUAL(x, y))
# endif
#
# /* BOOST_PP_EQUAL_D */
#
# define BOOST_PP_EQUAL_D(d, x, y) BOOST_PP_EQUAL(x, y)
#
# endif

/* equal.hpp
TQyeZSY8CI5xMUhxR5uQ67mTgwGmuC1mlosxeKJNDJ5TYtDIxaDcTTHITl3usRicgRjsxxiUtYnBM9I1Ao7pI8fgHfccC54KgfQ+lQIzW4vXzLthvuDpZ7A5/Bsr9sU3jMBFdU93tovQR06EaXlyeoZnIoH9h63QNmIs9sD8jmvSHZLWswYMgBXOl4HujIVzKBYPXiskPar2oZ6E+cRZw49J+iYr8Mbn/41u7kPBSTIb7lh5
*/