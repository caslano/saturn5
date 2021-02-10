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
# ifndef BOOST_PREPROCESSOR_LOGICAL_OR_HPP
# define BOOST_PREPROCESSOR_LOGICAL_OR_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/logical/bool.hpp>
# include <boost/preprocessor/logical/bitor.hpp>
#
# /* BOOST_PP_OR */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_OR(p, q) BOOST_PP_BITOR(BOOST_PP_BOOL(p), BOOST_PP_BOOL(q))
# else
#    define BOOST_PP_OR(p, q) BOOST_PP_OR_I(p, q)
#    define BOOST_PP_OR_I(p, q) BOOST_PP_BITOR(BOOST_PP_BOOL(p), BOOST_PP_BOOL(q))
# endif
#
# endif

/* or.hpp
AB6WDwBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX0ZJTEVUSU1FLjNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSKzF0S/8DAAAvCQAANAAJAAAAAAABAAAAAADAmg8AY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9QVF9GTk1BVENIX0RBVEEuM1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlLf/ExCXgQAAIoKAAA4AAkAAAAAAAEAAAAAABqfDwBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX0ZOTUFUQ0hfRlVOQ1RJT04uM1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlK5xSHmLQYAAKENAAA2AAkAAAAAAAEAAAAAANejDwBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX0ZPTExPV0xPQ0FUSU9OLjNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSwPnwnhgEAADTCAAANAAJAAAAAAABAAAAAABhqg8AY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9QVF9GT1JCSURfUkVVU0UuM1VUBQAB
*/