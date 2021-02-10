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
# ifndef BOOST_PREPROCESSOR_ARRAY_ENUM_HPP
# define BOOST_PREPROCESSOR_ARRAY_ENUM_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
#
# /* BOOST_PP_ARRAY_ENUM */
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#    define BOOST_PP_ARRAY_ENUM(array) BOOST_PP_ARRAY_ENUM_I(BOOST_PP_TUPLE_REM_CTOR, array)
#    define BOOST_PP_ARRAY_ENUM_I(m, args) BOOST_PP_ARRAY_ENUM_II(m, args)
#    define BOOST_PP_ARRAY_ENUM_II(m, args) BOOST_PP_CAT(m ## args,)
# elif BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_ARRAY_ENUM(array) BOOST_PP_ARRAY_ENUM_I(array)
#    define BOOST_PP_ARRAY_ENUM_I(array) BOOST_PP_TUPLE_REM_CTOR ## array
# else
#    define BOOST_PP_ARRAY_ENUM(array) BOOST_PP_TUPLE_REM_CTOR array
# endif
#
# endif

/* enum.hpp
AAEAAAAAAAQsBQBjdXJsLW1hc3Rlci9kb2NzL2NtZGxpbmUtb3B0cy9jb25uZWN0LXRvLmRVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSmYvBcmsBAABwAgAAKwAJAAAAAAABAAAAAABWLgUAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvY29udGludWUtYXQuZFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlIfbrKYCgIAAOwDAAAqAAkAAAAAAAEAAAAAABMwBQBjdXJsLW1hc3Rlci9kb2NzL2NtZGxpbmUtb3B0cy9jb29raWUtamFyLmRVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSJdLdYoUDAABNBwAAJgAJAAAAAAABAAAAAABuMgUAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvY29va2llLmRVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSXUNDWR4BAAATAgAAKwAJAAAAAAABAAAAAABANgUAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvY3JlYXRlLWRpcnMuZFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlLEvyfdDgEAAJwBAAAwAAkAAAAAAAEAAAAAALA3
*/