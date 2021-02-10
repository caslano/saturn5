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
ACUACQAAAAAAAQAAAAAAjgIEAGN1cmwtbWFzdGVyL2RvY3MvUkVMRUFTRS1QUk9DRURVUkUubWRVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pS3sFNsAkCAABWAwAAGwAJAAAAAAABAAAAAADxCAQAY3VybC1tYXN0ZXIvZG9jcy9ST0FETUFQLm1kVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUuLaeFaBCQAAchYAACQACQAAAAAAAQAAAAAAPAsEAGN1cmwtbWFzdGVyL2RvY3MvU0VDVVJJVFktUFJPQ0VTUy5tZFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlJspKW/JQcAANgPAAAgAAkAAAAAAAEAAAAAAAgVBABjdXJsLW1hc3Rlci9kb2NzL1NTTC1QUk9CTEVNUy5tZFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlJBdTCkJA0AAJUgAAAcAAkAAAAAAAEAAAAAAHQcBABjdXJsLW1hc3Rlci9kb2NzL1NTTENFUlRTLm1kVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUgFCTROnQAAAi4cAABcACQAAAAAAAQAAAAAA2ykEAGN1cmwtbWFzdGVyL2RvY3MvVEhBTktTVVQFAAG2SCRgUEsBAgAA
*/