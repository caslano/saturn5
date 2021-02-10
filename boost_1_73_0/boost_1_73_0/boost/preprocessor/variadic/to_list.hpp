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
# ifndef BOOST_PREPROCESSOR_VARIADIC_TO_LIST_HPP
# define BOOST_PREPROCESSOR_VARIADIC_TO_LIST_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/tuple/to_list.hpp>
#
# /* BOOST_PP_VARIADIC_TO_LIST */
#
# if BOOST_PP_VARIADICS
#    define BOOST_PP_VARIADIC_TO_LIST(...) BOOST_PP_TUPLE_TO_LIST((__VA_ARGS__))
# endif
#
# endif

/* to_list.hpp
AABL3yAAY3VybC1tYXN0ZXIvbGliL3NvY2tldHBhaXIuY1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlJEbewLVAIAAD4FAAAcAAkAAAAAAAEAAAAAALXkIABjdXJsLW1hc3Rlci9saWIvc29ja2V0cGFpci5oVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUgUX1LgfHQAA3n4AABcACQAAAAAAAQAAAAAATOcgAGN1cmwtbWFzdGVyL2xpYi9zb2Nrcy5jVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUoM/RmIVBAAAjgsAABcACQAAAAAAAQAAAAAAqQQhAGN1cmwtbWFzdGVyL2xpYi9zb2Nrcy5oVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUnbUoqQ/EAAA604AAB4ACQAAAAAAAQAAAAAA/AghAGN1cmwtbWFzdGVyL2xpYi9zb2Nrc19nc3NhcGkuY1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlIhtPSghxEAAH5ZAAAcAAkAAAAAAAEAAAAAAIAZIQBjdXJsLW1hc3Rlci9saWIvc29ja3Nfc3NwaS5jVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUlCiaxdMBAAAOAoAABwACQAAAAAAAQAAAAAA
*/