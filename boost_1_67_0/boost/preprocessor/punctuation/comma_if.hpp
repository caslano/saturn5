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
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
*/