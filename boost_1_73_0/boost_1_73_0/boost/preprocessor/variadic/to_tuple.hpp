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
# ifndef BOOST_PREPROCESSOR_VARIADIC_TO_TUPLE_HPP
# define BOOST_PREPROCESSOR_VARIADIC_TO_TUPLE_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_VARIADIC_TO_TUPLE */
#
# if BOOST_PP_VARIADICS
#    define BOOST_PP_VARIADIC_TO_TUPLE(...) (__VA_ARGS__)
# endif
#
# endif

/* to_tuple.hpp
YXN0ZXIvbGliL3N0cmR1cC5jVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUqY9VpdcAgAAJAUAABgACQAAAAAAAQAAAAAANU8hAGN1cmwtbWFzdGVyL2xpYi9zdHJkdXAuaFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlJLa3sr5x0AAH5mAAAaAAkAAAAAAAEAAAAAANBRIQBjdXJsLW1hc3Rlci9saWIvc3RyZXJyb3IuY1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlJqqsuYhgIAAMEFAAAaAAkAAAAAAAEAAAAAAPhvIQBjdXJsLW1hc3Rlci9saWIvc3RyZXJyb3IuaFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlKjzmb0zwMAAHsIAAAYAAkAAAAAAAEAAAAAAL9yIQBjdXJsLW1hc3Rlci9saWIvc3RydG9rLmNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSKF/joU4CAAAbBQAAGAAJAAAAAAABAAAAAADNdiEAY3VybC1tYXN0ZXIvbGliL3N0cnRvay5oVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUpxpZS5HCQAAoRYAABsACQAAAAAAAQAAAAAAWnkhAGN1cmwtbWFzdGVyL2xpYi9zdHJ0
*/