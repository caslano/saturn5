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
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_VARIADIC_SIZE_HPP
# define BOOST_PREPROCESSOR_VARIADIC_SIZE_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_VARIADIC_SIZE */
#
# if BOOST_PP_VARIADICS
#    if BOOST_PP_VARIADICS_MSVC
#        define BOOST_PP_VARIADIC_SIZE(...) BOOST_PP_CAT(BOOST_PP_VARIADIC_SIZE_I(__VA_ARGS__, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1,),)
#    else
#        define BOOST_PP_VARIADIC_SIZE(...) BOOST_PP_VARIADIC_SIZE_I(__VA_ARGS__, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1,)
#    endif
#    define BOOST_PP_VARIADIC_SIZE_I(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43, e44, e45, e46, e47, e48, e49, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e60, e61, e62, e63, size, ...) size
# endif
#
# endif

/* size.hpp
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
*/