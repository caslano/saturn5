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
# ifndef BOOST_PREPROCESSOR_VARIADIC_TO_ARRAY_HPP
# define BOOST_PREPROCESSOR_VARIADIC_TO_ARRAY_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/tuple/to_array.hpp>
# if BOOST_PP_VARIADICS_MSVC
#    include <boost/preprocessor/variadic/size.hpp>
# endif
#
# /* BOOST_PP_VARIADIC_TO_ARRAY */
#
# if BOOST_PP_VARIADICS
#    if BOOST_PP_VARIADICS_MSVC
#        define BOOST_PP_VARIADIC_TO_ARRAY(...) BOOST_PP_TUPLE_TO_ARRAY_2(BOOST_PP_VARIADIC_SIZE(__VA_ARGS__),(__VA_ARGS__))
#    else
#        define BOOST_PP_VARIADIC_TO_ARRAY(...) BOOST_PP_TUPLE_TO_ARRAY((__VA_ARGS__))
#    endif
# endif
#
# endif

/* to_array.hpp
Z0pSq5cgsa8CAABDBgAAFwAJAAAAAAABAAAAAABXeyAAY3VybC1tYXN0ZXIvbGliL3NsaXN0LmhVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSE1jfP0caAABSdAAAFQAJAAAAAAABAAAAAABEfiAAY3VybC1tYXN0ZXIvbGliL3NtYi5jVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUptj07KJBwAAWBoAABUACQAAAAAAAQAAAAAAx5ggAGN1cmwtbWFzdGVyL2xpYi9zbWIuaFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlJGikxSDTUAAKLfAAAWAAkAAAAAAAEAAAAAAIygIABjdXJsLW1hc3Rlci9saWIvc210cC5jVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUngZIGhXBgAAhQ8AABYACQAAAAAAAQAAAAAA1tUgAGN1cmwtbWFzdGVyL2xpYi9zbXRwLmhVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pS86O40qACAAC7BQAAGgAJAAAAAAABAAAAAABq3CAAY3VybC1tYXN0ZXIvbGliL3NvY2thZGRyLmhVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pS3KvtQycFAABXDQAAHAAJAAAAAAABAAAA
*/