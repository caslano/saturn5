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
# ifndef BOOST_PREPROCESSOR_VARIADIC_TO_SEQ_HPP
# define BOOST_PREPROCESSOR_VARIADIC_TO_SEQ_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/tuple/to_seq.hpp>
#
# /* BOOST_PP_VARIADIC_TO_SEQ */
#
# if BOOST_PP_VARIADICS
#    define BOOST_PP_VARIADIC_TO_SEQ(...) BOOST_PP_TUPLE_TO_SEQ((__VA_ARGS__))
# endif
#
# endif

/* to_seq.hpp
SishAGN1cmwtbWFzdGVyL2xpYi9zcGVlZGNoZWNrLmNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pS4HXtWEgCAAAjBQAAHAAJAAAAAAABAAAAAADZLyEAY3VybC1tYXN0ZXIvbGliL3NwZWVkY2hlY2suaFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlLWUVtljgkAAAQeAAAXAAkAAAAAAAEAAAAAAGQyIQBjdXJsLW1hc3Rlci9saWIvc3BsYXkuY1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlIayOMuQgMAAJ4JAAAXAAkAAAAAAAEAAAAAADA8IQBjdXJsLW1hc3Rlci9saWIvc3BsYXkuaFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlJkCG7PTQcAAEUXAAAZAAkAAAAAAAEAAAAAALA/IQBjdXJsLW1hc3Rlci9saWIvc3RyY2FzZS5jVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUoh7waNRAwAA6AcAABkACQAAAAAAAQAAAAAAPUchAGN1cmwtbWFzdGVyL2xpYi9zdHJjYXNlLmhVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSIhX0cygEAAC/CgAAGAAJAAAAAAABAAAAAADOSiEAY3VybC1t
*/