# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_ARITHMETIC_MOD_HPP
# define BOOST_PREPROCESSOR_ARITHMETIC_MOD_HPP
#
# include <boost/preprocessor/arithmetic/detail/div_base.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
#
# /* BOOST_PP_MOD */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_MOD(x, y) BOOST_PP_TUPLE_ELEM(3, 1, BOOST_PP_DIV_BASE(x, y))
# else
#    define BOOST_PP_MOD(x, y) BOOST_PP_MOD_I(x, y)
#    define BOOST_PP_MOD_I(x, y) BOOST_PP_TUPLE_ELEM(3, 1, BOOST_PP_DIV_BASE(x, y))
# endif
#
# /* BOOST_PP_MOD_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_MOD_D(d, x, y) BOOST_PP_TUPLE_ELEM(3, 1, BOOST_PP_DIV_BASE_D(d, x, y))
# else
#    define BOOST_PP_MOD_D(d, x, y) BOOST_PP_MOD_D_I(d, x, y)
#    define BOOST_PP_MOD_D_I(d, x, y) BOOST_PP_TUPLE_ELEM(3, 1, BOOST_PP_DIV_BASE_D(d, x, y))
# endif
#
# endif

/* mod.hpp
CU7tz4kAyegSiCqEzN8xUcAPyXuC0/Bcap7ngMxW8l9T4OIWrCeA9+YvO6jNkz5XLi+BHlZMpa2TzJkwpB49PIfBK5MMy9lkKqSY9GFWikWC2obncUjTUlMrmsFpseIQQP/8JBxzNNJPlvt5d5XyJWZ6nIIdihoFYvXZHYLNL2roHearOKN4z4kbSDaSASKkmKm7uiUe+AOMoUTDkvaWD2OExfK47Tw3fg9KdBjwQD2VLdATGVcl7ycOb6IN42Ob0n46uloYlWskm739I3+yDDff5TV8gMn2/PPfvc5Tdxanjj2ZO/EytyEsM1wH8ELSjtFrsNdV1IWF0mgJz3q+T3EaXZ8wc8KbDC5P5mLQ/VksJXoTImbiaMW6oRzup9uHD58Rpj8+B/QbQMVNg4yh9vT78XE+hK+pN8AUaMKuOBpFv9CTJoasCJxuWZ5bMDg4ORF6zUWOo5wD5FoI6ZtJ6xmF/CBdYdTFCNy4GJ/o24mALWLGWWj/GGGcQwAuKRi+ZDNSEUJgKHBe+lY8PidJH7CL2u9vxgrp5SxCBTchirpvAFI1kqg5FRFI+w==
*/