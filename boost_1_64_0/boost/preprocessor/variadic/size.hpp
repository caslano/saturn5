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
akdwYmxNwQF8wjG9XqnjCNrwc29uVdetCq2xHbMBZE12/6Xt89AAuNt8bhpbmrz4Y4pNYDfGNc0GdAcQn+sJurYMj+YPahVSuYEZjWmXgI1LCT3Wwa5DnSU8cb1l7lHK06CuNpXWtsHiWvS9vM8hJ63aF3zBawaZB9WCJJWWX8ZhxoZzlxCkh5zthoFfT+gswxzN4CGYo2FinGqICBmzk0Yow1ojzoTPOiI9hcloYlD3PptWXBL4hRqVkzsVoJQEiWaBbY56/KxgsNwSAjAF+Q5HtXSIKQliy/aB4TRUKW/qOa8g8PClVPB+GUeHR48JO2Ks3hNxVA8Pyhcv8bAo2qXkDXPo7jXaABi+cjnQFeDu2sDvZpMO3CSQpcTfr3srf2H8hia4dDmsjTYJSJXpGBWLzdj1dKnLdeovrW3qXQPe2jSnuVC56HMCgfc/Ly7IsJD6tw+9WUxno+XUt4VeNVBKgUjfr1Qxyd4ahDmUWAklBk01ktBkQ0q6CHM0Rb4DhmSsrUtjoTYCv5YZMdW642yI4PHWEBEYaD2EKiWarJ1zTFxfVv/zBffl6Q==
*/