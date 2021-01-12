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
# ifndef BOOST_PREPROCESSOR_REPETITION_ENUM_TRAILING_PARAMS_HPP
# define BOOST_PREPROCESSOR_REPETITION_ENUM_TRAILING_PARAMS_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/repetition/repeat.hpp>
#
# /* BOOST_PP_ENUM_TRAILING_PARAMS */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ENUM_TRAILING_PARAMS(count, param) BOOST_PP_REPEAT(count, BOOST_PP_ENUM_TRAILING_PARAMS_M, param)
# else
#    define BOOST_PP_ENUM_TRAILING_PARAMS(count, param) BOOST_PP_ENUM_TRAILING_PARAMS_I(count, param)
#    define BOOST_PP_ENUM_TRAILING_PARAMS_I(count, param) BOOST_PP_REPEAT(count, BOOST_PP_ENUM_TRAILING_PARAMS_M, param)
# endif
#
# define BOOST_PP_ENUM_TRAILING_PARAMS_M(z, n, param) , param ## n
#
# /* BOOST_PP_ENUM_TRAILING_PARAMS_Z */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ENUM_TRAILING_PARAMS_Z(z, count, param) BOOST_PP_REPEAT_ ## z(count, BOOST_PP_ENUM_TRAILING_PARAMS_M, param)
# else
#    define BOOST_PP_ENUM_TRAILING_PARAMS_Z(z, count, param) BOOST_PP_ENUM_TRAILING_PARAMS_Z_I(z, count, param)
#    define BOOST_PP_ENUM_TRAILING_PARAMS_Z_I(z, count, param) BOOST_PP_REPEAT_ ## z(count, BOOST_PP_ENUM_TRAILING_PARAMS_M, param)
# endif
#
# endif

/* enum_trailing_params.hpp
fVnLUc6rXP8ghPTIpngrwpaS5zrSzad+yP/rrcQdoPzI9YSpem5T/X7TYc7pNp+8xqs9Wofxc4x2ZFV9tO7z6mNbBzGWGLMeW6iv6rNA+u+XVeiDg58+kfo/QB6n0JdC1GfBG8QJpV9oX4Yr40T1033kOEL5MVmZ+Ih89wqxvmc0xZ8gzcxO6Mg/0an5tGEadfhnx2nqU8vcC3aY/zL7Mo5V2U2UDJaQz8xl+IVl+Ixc99OG
*/