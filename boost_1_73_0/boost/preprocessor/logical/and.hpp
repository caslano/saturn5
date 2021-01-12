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
# ifndef BOOST_PREPROCESSOR_LOGICAL_AND_HPP
# define BOOST_PREPROCESSOR_LOGICAL_AND_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/logical/bool.hpp>
# include <boost/preprocessor/logical/bitand.hpp>
#
# /* BOOST_PP_AND */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_AND(p, q) BOOST_PP_BITAND(BOOST_PP_BOOL(p), BOOST_PP_BOOL(q))
# else
#    define BOOST_PP_AND(p, q) BOOST_PP_AND_I(p, q)
#    define BOOST_PP_AND_I(p, q) BOOST_PP_BITAND(BOOST_PP_BOOL(p), BOOST_PP_BOOL(q))
# endif
#
# endif

/* and.hpp
FYgeOsQG04xAQY1P5QzuDwo/oVNlsr6GfjeBUE7UhAnWn1KFsu8qoa8VlZV+jl9JZ1PIamycS+9wEhg79fYQBQ/DwyE/nofjafawn5kg1riMzNIwRaWEwoWFSHx50QCWQGBdDh6Lw7JSFGZ39EEI2tsZadwGIR+66vIapiR9FK/4mM/Y9CStKD5HMNpD6eqzUPxZykKR/ijvlpmdos4gYcL84nuDoZHPZicyhH8uJVeAlgu8
*/