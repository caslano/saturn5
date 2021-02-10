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
# ifndef BOOST_PREPROCESSOR_TUPLE_PUSH_BACK_HPP
# define BOOST_PREPROCESSOR_TUPLE_PUSH_BACK_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# if BOOST_PP_VARIADICS
#
# include <boost/preprocessor/array/push_back.hpp>
# include <boost/preprocessor/array/to_tuple.hpp>
# include <boost/preprocessor/tuple/to_array.hpp>
#
# /* BOOST_PP_TUPLE_PUSH_BACK */
#
# define BOOST_PP_TUPLE_PUSH_BACK(tuple, elem) \
    BOOST_PP_ARRAY_TO_TUPLE(BOOST_PP_ARRAY_PUSH_BACK(BOOST_PP_TUPLE_TO_ARRAY(tuple), elem)) \
/**/
#
# endif // BOOST_PP_VARIADICS
#
# endif // BOOST_PREPROCESSOR_TUPLE_PUSH_BACK_HPP

/* push_back.hpp
AAAAAADELRwAY3VybC1tYXN0ZXIvbGliL2h0dHAyLmhVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSW3u1l3kMAAAfLgAAIAAJAAAAAAABAAAAAACfMhwAY3VybC1tYXN0ZXIvbGliL2h0dHBfYXdzX3NpZ3Y0LmNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSMurbblICAAAHBQAAIAAJAAAAAAABAAAAAABfPxwAY3VybC1tYXN0ZXIvbGliL2h0dHBfYXdzX3NpZ3Y0LmhVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSoFGkt5EOAADCKgAAHQAJAAAAAAABAAAAAAD4QRwAY3VybC1tYXN0ZXIvbGliL2h0dHBfY2h1bmtzLmNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSrM5a5hcGAACYDQAAHQAJAAAAAAABAAAAAADNUBwAY3VybC1tYXN0ZXIvbGliL2h0dHBfY2h1bmtzLmhVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSjhF+L5cHAAA9FAAAHQAJAAAAAAABAAAAAAAoVxwAY3VybC1tYXN0ZXIvbGliL2h0dHBfZGlnZXN0LmNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pS0r8sitYCAAAR
*/