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
# ifndef BOOST_PREPROCESSOR_COMPARISON_LESS_HPP
# define BOOST_PREPROCESSOR_COMPARISON_LESS_HPP
#
# include <boost/preprocessor/comparison/less_equal.hpp>
# include <boost/preprocessor/comparison/not_equal.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/iif.hpp>
# include <boost/preprocessor/logical/bitand.hpp>
# include <boost/preprocessor/tuple/eat.hpp>
#
# /* BOOST_PP_LESS */
#
# if BOOST_PP_CONFIG_FLAGS() & (BOOST_PP_CONFIG_MWCC() | BOOST_PP_CONFIG_DMC())
#    define BOOST_PP_LESS(x, y) BOOST_PP_BITAND(BOOST_PP_NOT_EQUAL(x, y), BOOST_PP_LESS_EQUAL(x, y))
# elif ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LESS(x, y) BOOST_PP_IIF(BOOST_PP_NOT_EQUAL(x, y), BOOST_PP_LESS_EQUAL, 0 BOOST_PP_TUPLE_EAT_2)(x, y)
# else
#    define BOOST_PP_LESS(x, y) BOOST_PP_LESS_I(x, y)
#    define BOOST_PP_LESS_I(x, y) BOOST_PP_IIF(BOOST_PP_NOT_EQUAL(x, y), BOOST_PP_LESS_EQUAL, 0 BOOST_PP_TUPLE_EAT_2)(x, y)
# endif
#
# /* BOOST_PP_LESS_D */
#
# if BOOST_PP_CONFIG_FLAGS() & (BOOST_PP_CONFIG_MWCC() | BOOST_PP_CONFIG_DMC())
#    define BOOST_PP_LESS_D(d, x, y) BOOST_PP_BITAND(BOOST_PP_NOT_EQUAL(x, y), BOOST_PP_LESS_EQUAL_D(d, x, y))
# elif ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LESS_D(d, x, y) BOOST_PP_IIF(BOOST_PP_NOT_EQUAL(x, y), BOOST_PP_LESS_EQUAL_D, 0 BOOST_PP_TUPLE_EAT_3)(d, x, y)
# else
#    define BOOST_PP_LESS_D(d, x, y) BOOST_PP_LESS_D_I(d, x, y)
#    define BOOST_PP_LESS_D_I(d, x, y) BOOST_PP_IIF(BOOST_PP_NOT_EQUAL(x, y), BOOST_PP_LESS_EQUAL_D, 0 BOOST_PP_TUPLE_EAT_3)(d, x, y)
# endif
#
# endif

/* less.hpp
ZXIvZG9jcy9jbWRsaW5lLW9wdHMvbWF4LWZpbGVzaXplLmRVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSc/0+L/MAAACVAQAAKgAJAAAAAAABAAAAAACsxgUAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvbWF4LXJlZGlycy5kVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUsfgg0xCAQAAGQIAACgACQAAAAAAAQAAAAAA8McFAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRzL21heC10aW1lLmRVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pS6lku5DYCAABzBAAAKAAJAAAAAAABAAAAAACByQUAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvbWV0YWxpbmsuZFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlJDveduXQEAAGMCAAApAAkAAAAAAAEAAAAAAAbMBQBjdXJsLW1hc3Rlci9kb2NzL2NtZGxpbmUtb3B0cy9uZWdvdGlhdGUuZFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlKb7YosBwEAAKABAAAqAAkAAAAAAAEAAAAAALPNBQBjdXJsLW1hc3Rlci9kb2NzL2Nt
*/