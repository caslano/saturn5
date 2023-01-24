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
ERUnBe9kToVGESVgw1aXHldcFHu7mprCGmf2eIZUfr+K/evQN14JdX9mW/DmcKpLQUN/ja7zdv0t1fRXiul6AoPb0FiveQR0A6CP0HRq3HSh6l3fhW+A7nICpoZeRKAGXEHuI2PnIId5cjvNFRWcw9hAfg72D8SU1hUs6mXnglcPgflCyN1rhuQeHL6PzmPXQjpbE5YmWFVoOuiOwdHBzX0DGc4dc+olsKGjCN51BbdgJeYbdVyXCDlmFwxrSLO2hhFcVJ62qjZ5n6vseENzhaU7s2vzcxejqFGvdvIXdTom+zdmChsB9ANYn/eGiVLfDw+NXmxKDn4XsxXg2cQ+5dHuAVzHiW3DqhE0+csnRhkOI39UcdcmLl9t4hipYCACRExxPF/lHqcLIoVPerGWNObAUzkQsZktsc5cfOfsCLzjfIlzCo/tXrT7GFsi5CRATHAyHpl1A70uj0JD+mAu3jnfSByD2drWe0uexkLwPP60Y3A49WRJMxH0vPojCuoQgjzuE/szQMzW/2Awu8yc9vGcbXsKKqiGIT7m99mmEdlYs5jgiWqHlZB6xfMBZ8bdIvMPY/ljdr0fd2xbN0UHz5RbBlsieVhOrwRQXVA23nRhLeEaqXW1/BBAc1kAfR3sxGjDaCNdwr5GA/XRZJRQ3zpkrPueo3qjdoYEmaG8fXVrl7F6ga9yDEdaipjhLUdU7WoEgEWzYlb+HEka
*/