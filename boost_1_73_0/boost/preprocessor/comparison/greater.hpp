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
# ifndef BOOST_PREPROCESSOR_COMPARISON_GREATER_HPP
# define BOOST_PREPROCESSOR_COMPARISON_GREATER_HPP
#
# include <boost/preprocessor/comparison/less.hpp>
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_GREATER */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_GREATER(x, y) BOOST_PP_LESS(y, x)
# else
#    define BOOST_PP_GREATER(x, y) BOOST_PP_GREATER_I(x, y)
#    define BOOST_PP_GREATER_I(x, y) BOOST_PP_LESS(y, x)
# endif
#
# /* BOOST_PP_GREATER_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_GREATER_D(d, x, y) BOOST_PP_LESS_D(d, y, x)
# else
#    define BOOST_PP_GREATER_D(d, x, y) BOOST_PP_GREATER_D_I(d, x, y)
#    define BOOST_PP_GREATER_D_I(d, x, y) BOOST_PP_LESS_D(d, y, x)
# endif
#
# endif

/* greater.hpp
Jgr4PGwJ3FMwSnEoh/Su41fguyheYtFy++jl5v70oqxceKttTpaHAmGAyVpqZsuxPjwF8+Hmjx6U9EWWhHGwwLyTO+MA/cmc3CyP3WQywJT1uJkNwjg8DXPvgYfvlEr6OmvBc2OMu+8tcO1kYo4jd6FHooH9a4iHP8ZjL8xvO9R5hqSvsSDl3Onm84Yjw/n4Ykauhw4QA0zNEAcrxqHC2U4kvYRjZrzK6pRxotx8zkhJXZwM
*/