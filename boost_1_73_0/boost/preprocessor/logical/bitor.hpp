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
# ifndef BOOST_PREPROCESSOR_LOGICAL_BITOR_HPP
# define BOOST_PREPROCESSOR_LOGICAL_BITOR_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_BITOR */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_BITOR(x, y) BOOST_PP_BITOR_I(x, y)
# else
#    define BOOST_PP_BITOR(x, y) BOOST_PP_BITOR_OO((x, y))
#    define BOOST_PP_BITOR_OO(par) BOOST_PP_BITOR_I ## par
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#    define BOOST_PP_BITOR_I(x, y) BOOST_PP_BITOR_ ## x ## y
# else
#    define BOOST_PP_BITOR_I(x, y) BOOST_PP_BITOR_ID(BOOST_PP_BITOR_ ## x ## y)
#    define BOOST_PP_BITOR_ID(id) id
# endif
#
# define BOOST_PP_BITOR_00 0
# define BOOST_PP_BITOR_01 1
# define BOOST_PP_BITOR_10 1
# define BOOST_PP_BITOR_11 1
#
# endif

/* bitor.hpp
J7AvGtqGiYyCps7qnITdCZ3Q/rOADeBEI4iWEaM8Yl7BmodAdJDpAeaZMFQjCdu4F80EMNbuixnu8gBLV0GILbBslxz9+PyibQI1GrA2TDQH3kPbId8x4Y9/sIvql8mT4LLySyEcrDf0aM922HJQQqlIr5hJb5ldzAH9DoS2jb5swVDLHrFxptMv7dcJhoGz9I53Q8KdmiaCz7J8aacK01DQTSGoqjtjdPoQXYJfRwOaR2hs
*/