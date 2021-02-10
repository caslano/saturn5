# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2013.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_TUPLE_INSERT_HPP
# define BOOST_PREPROCESSOR_TUPLE_INSERT_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# if BOOST_PP_VARIADICS
#
# include <boost/preprocessor/array/insert.hpp>
# include <boost/preprocessor/array/to_tuple.hpp>
# include <boost/preprocessor/tuple/to_array.hpp>
#
# /* BOOST_PP_TUPLE_INSERT */
#
# define BOOST_PP_TUPLE_INSERT(tuple, i, elem) \
    BOOST_PP_ARRAY_TO_TUPLE(BOOST_PP_ARRAY_INSERT(BOOST_PP_TUPLE_TO_ARRAY(tuple), i, elem)) \
/**/
#
# /* BOOST_PP_TUPLE_INSERT_D */
#
# define BOOST_PP_TUPLE_INSERT_D(d, tuple, i, elem) \
    BOOST_PP_ARRAY_TO_TUPLE(BOOST_PP_ARRAY_INSERT_D(d, BOOST_PP_TUPLE_TO_ARRAY(tuple), i, elem)) \
/**/
#
# endif // BOOST_PP_VARIADICS
#
# endif // BOOST_PREPROCESSOR_TUPLE_INSERT_HPP

/* insert.hpp
aWIvZ2V0aW5mby5oVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUvU28TS9CAAAvxwAABgACQAAAAAAAQAAAAAAS7oaAGN1cmwtbWFzdGVyL2xpYi9nb3BoZXIuY1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlI0Z/SIMQIAAAEFAAAYAAkAAAAAAAEAAAAAAEfDGgBjdXJsLW1hc3Rlci9saWIvZ29waGVyLmhVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSjiDmw+cJAAC+IAAAFgAJAAAAAAABAAAAAAC3xRoAY3VybC1tYXN0ZXIvbGliL2hhc2guY1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlLA75EXVQQAAHANAAAWAAkAAAAAAAEAAAAAANvPGgBjdXJsLW1hc3Rlci9saWIvaGFzaC5oVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUmMy/nWyBgAAWxQAABYACQAAAAAAAQAAAAAAbdQaAGN1cmwtbWFzdGVyL2xpYi9obWFjLmNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSgAor/9AFAABCDwAAGgAJAAAAAAABAAAAAABc2xoAY3VybC1tYXN0ZXIvbGliL2hvc3Rhc3luLmNVVAUAAbZIJGBQ
*/