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
# ifndef BOOST_PREPROCESSOR_PUNCTUATION_COMMA_IF_HPP
# define BOOST_PREPROCESSOR_PUNCTUATION_COMMA_IF_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/if.hpp>
# include <boost/preprocessor/facilities/empty.hpp>
# include <boost/preprocessor/punctuation/comma.hpp>
#
# /* BOOST_PP_COMMA_IF */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_COMMA_IF(cond) BOOST_PP_IF(cond, BOOST_PP_COMMA, BOOST_PP_EMPTY)()
# else
#    define BOOST_PP_COMMA_IF(cond) BOOST_PP_COMMA_IF_I(cond)
#    define BOOST_PP_COMMA_IF_I(cond) BOOST_PP_IF(cond, BOOST_PP_COMMA, BOOST_PP_EMPTY)()
# endif
#
# endif

/* comma_if.hpp
6YrbyiIygVYxESWDdOSr2ByjJGQpiyacppTgP3YeKmQqm2c0szOHKUAGEqHFQQAkwETtW9wHgAHGDw8k5vdTvWIGEU94yymgObh4YABWgD3dCJKMucQCwNIdy8dCtpTLIwCukXjVGVu0xG5YbhA+kK/IWzQs44VQoNIVD62NRLpQVEOZCihAqwGduQvhySZQSk2jRU7DfOFvfzPjhg8YDaWiHm4TThU1cX6v0c0bWfrs69BE
*/