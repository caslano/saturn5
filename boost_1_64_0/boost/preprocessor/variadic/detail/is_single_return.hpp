# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2014.                                    *
#  *     Distributed under the Boost Software License, Version 1.0. (See      *
#  *     accompanying file LICENSE_1_0.txt or copy at                         *
#  *     http://www.boost.org/LICENSE_1_0.txt)                                *
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_VARIADIC_DETAIL_IS_SINGLE_RETURN_HPP
# define BOOST_PREPROCESSOR_VARIADIC_DETAIL_IS_SINGLE_RETURN_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_VARIADIC_IS_SINGLE_RETURN */
#
# if BOOST_PP_VARIADICS && BOOST_PP_VARIADICS_MSVC
# include <boost/preprocessor/control/iif.hpp>
# include <boost/preprocessor/facilities/is_1.hpp>
# include <boost/preprocessor/variadic/size.hpp>
# define BOOST_PP_VARIADIC_IS_SINGLE_RETURN(sr,nsr,...) \
    BOOST_PP_IIF(BOOST_PP_IS_1(BOOST_PP_VARIADIC_SIZE(__VA_ARGS__)),sr,nsr) \
    /**/
# endif /* BOOST_PP_VARIADICS && BOOST_PP_VARIADICS_MSVC */
#
# endif /* BOOST_PREPROCESSOR_VARIADIC_DETAIL_IS_SINGLE_RETURN_HPP */

/* is_single_return.hpp
o6MUXzSrcg3WXrLjXZdGgx47YRH+bIZVQLyD7OVomr4f2H84En9g5hZiYD4LAn2EPfSSNG8M9TKt0wYSNyTGYj9F7l0mKUm9LpPNNqZhz9HNYBbzRWQ6hdVItRgMs/BNcWA8krKHHKGeAz3OGUBCGCm2bsCSzF8WJ9806wNGGS9YxHyDF6tQi4EYzisBLWAmtJ+cbXKhyHg6jKde3eAdzd0ENyrqCL0Ak2focm9XBZmZhs0Jxt2A+EwMPSAk5Kp+j12vvs8UkLItU6BM7HhwA6h28hcHVP19LOdGRJkWYEZ6weEz9p6kzs4t5HSKPmh4BLQLyUcDMVqXDti/p3cgs60Oull1lczkGCI8jIAPysiqirUa03x2EBTPNozhbg0VYu09pRKYQm9iD7aaB26Mu9tUoBSuSiy153yrIH0o6aU6NyXwnKlKx6f8mDp5vE9Al9R7oQYP2hZoC5i4iaD0g6iH8R2XMpbNlHEW8IDFCuY4booxqpDH4cyGCSp3Qj81mo5+kFGG6dWYK2N8fELM4QOgAbc9caqjdgffczz+Es5oKwjYeVOP9/Z/3A==
*/