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
# ifndef BOOST_PREPROCESSOR_LIST_CAT_HPP
# define BOOST_PREPROCESSOR_LIST_CAT_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/list/adt.hpp>
# include <boost/preprocessor/list/fold_left.hpp>
#
# /* BOOST_PP_LIST_CAT */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_CAT(list) BOOST_PP_LIST_FOLD_LEFT(BOOST_PP_LIST_CAT_O, BOOST_PP_LIST_FIRST(list), BOOST_PP_LIST_REST(list))
# else
#    define BOOST_PP_LIST_CAT(list) BOOST_PP_LIST_CAT_I(list)
#    define BOOST_PP_LIST_CAT_I(list) BOOST_PP_LIST_FOLD_LEFT(BOOST_PP_LIST_CAT_O, BOOST_PP_LIST_FIRST(list), BOOST_PP_LIST_REST(list))
# endif
#
# define BOOST_PP_LIST_CAT_O(d, s, x) BOOST_PP_CAT(s, x)
#
# /* BOOST_PP_LIST_CAT_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_CAT_D(d, list) BOOST_PP_LIST_FOLD_LEFT_ ## d(BOOST_PP_LIST_CAT_O, BOOST_PP_LIST_FIRST(list), BOOST_PP_LIST_REST(list))
# else
#    define BOOST_PP_LIST_CAT_D(d, list) BOOST_PP_LIST_CAT_D_I(d, list)
#    define BOOST_PP_LIST_CAT_D_I(d, list) BOOST_PP_LIST_FOLD_LEFT_ ## d(BOOST_PP_LIST_CAT_O, BOOST_PP_LIST_FIRST(list), BOOST_PP_LIST_REST(list))
# endif
#
# endif

/* cat.hpp
l5ECAADCBQAALAAJAAAAAAABAAAAAABf4QwAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ01ha2VMaXN0cy50eHRVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSvnCxj/0EAAA1CwAANQAJAAAAAAABAAAAAABD5AwAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTElORk9fQUNUSVZFU09DS0VULjNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSxnYaM5YEAADpCQAAOAAJAAAAAAABAAAAAACc6QwAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTElORk9fQVBQQ09OTkVDVF9USU1FLjNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSnC1pXsIEAABRCgAAOgAJAAAAAAABAAAAAACR7gwAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTElORk9fQVBQQ09OTkVDVF9USU1FX1QuM1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlI/u04kYAUAAOcLAAAxAAkAAAAAAAEAAAAAALTzDABjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJM
*/