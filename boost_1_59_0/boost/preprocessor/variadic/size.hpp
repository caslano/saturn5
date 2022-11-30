# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2011.                                    *
#  *     (C) Copyright Paul Mensonides 2011.                                  *
#  *     Distributed under the Boost Software License, Version 1.0. (See      *
#  *     accompanying file LICENSE_1_0.txt or copy at                         *
#  *     http://www.boost.org/LICENSE_1_0.txt)                                *
#  *                                                                          *
#  ************************************************************************** */
#
# /* Revised by Edward Diener (2020) */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_VARIADIC_SIZE_HPP
# define BOOST_PREPROCESSOR_VARIADIC_SIZE_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/iif.hpp>
# include <boost/preprocessor/facilities/check_empty.hpp>
#
# /* BOOST_PP_VARIADIC_SIZE */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_STRICT()
#
#    if BOOST_PP_VARIADIC_HAS_OPT()
#       if BOOST_PP_VARIADICS_MSVC
#           define BOOST_PP_VARIADIC_SIZE_NOT_EMPTY(...) BOOST_PP_CAT(BOOST_PP_VARIADIC_SIZE_I(__VA_ARGS__, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1,),)
#       else
#           define BOOST_PP_VARIADIC_SIZE_NOT_EMPTY(...) BOOST_PP_VARIADIC_SIZE_I(__VA_ARGS__, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1,)
#       endif
#       define BOOST_PP_VARIADIC_SIZE_EMPTY(...) 0
#       define BOOST_PP_VARIADIC_SIZE(...) BOOST_PP_IIF(BOOST_PP_CHECK_EMPTY(__VA_ARGS__),BOOST_PP_VARIADIC_SIZE_EMPTY,BOOST_PP_VARIADIC_SIZE_NOT_EMPTY)(__VA_ARGS__)
#    elif BOOST_PP_VARIADICS_MSVC
#       define BOOST_PP_VARIADIC_SIZE(...) BOOST_PP_CAT(BOOST_PP_VARIADIC_SIZE_I(__VA_ARGS__, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1,),)
#    else
#       define BOOST_PP_VARIADIC_SIZE(...) BOOST_PP_VARIADIC_SIZE_I(__VA_ARGS__, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1,)
#    endif
#    define BOOST_PP_VARIADIC_SIZE_I(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43, e44, e45, e46, e47, e48, e49, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e60, e61, e62, e63, size, ...) size
#
# else
#
#    if BOOST_PP_VARIADIC_HAS_OPT()
#       define BOOST_PP_VARIADIC_SIZE_EMPTY(...) 0
#       define BOOST_PP_VARIADIC_SIZE(...) BOOST_PP_IIF(BOOST_PP_CHECK_EMPTY(__VA_ARGS__),BOOST_PP_VARIADIC_SIZE_EMPTY,BOOST_PP_VARIADIC_DO_SIZE)(__VA_ARGS__)
#    else
#       define BOOST_PP_VARIADIC_SIZE(...) BOOST_PP_VARIADIC_DO_SIZE(__VA_ARGS__)
#    endif
#
# include <boost/preprocessor/config/limits.hpp>
#
# if BOOST_PP_LIMIT_VARIADIC == 64
# include <boost/preprocessor/variadic/limits/size_64.hpp>
# elif BOOST_PP_LIMIT_VARIADIC == 128
# include <boost/preprocessor/variadic/limits/size_128.hpp>
# elif BOOST_PP_LIMIT_VARIADIC == 256
# include <boost/preprocessor/variadic/limits/size_256.hpp>
# else
# error Incorrect value for the BOOST_PP_LIMIT_TUPLE limit
# endif
#
# endif
#
# endif

/* size.hpp
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
*/