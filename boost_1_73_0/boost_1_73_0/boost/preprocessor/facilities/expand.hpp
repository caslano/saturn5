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
# ifndef BOOST_PREPROCESSOR_FACILITIES_EXPAND_HPP
# define BOOST_PREPROCESSOR_FACILITIES_EXPAND_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC() && ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_DMC()
#    define BOOST_PP_EXPAND(x) BOOST_PP_EXPAND_I(x)
# else
#    define BOOST_PP_EXPAND(x) BOOST_PP_EXPAND_OO((x))
#    define BOOST_PP_EXPAND_OO(par) BOOST_PP_EXPAND_I ## par
# endif
#
# define BOOST_PP_EXPAND_I(x) x
#
# endif

/* expand.hpp
bXBsZXMvTWFrZWZpbGUubmV0d2FyZVVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlJx0dmZyQIAAGgFAAAjAAkAAAAAAAEAAAAAAHDxBgBjdXJsLW1hc3Rlci9kb2NzL2V4YW1wbGVzL1JFQURNRS5tZFVUBQABtkgkYFBLAQIXAwoAAAAIAC1nSlJPSd7tEQMAAFIHAAAnAAkAAAAAAAEAAADtgYP0BgBjdXJsLW1hc3Rlci9kb2NzL2V4YW1wbGVzL2FkZGRvY3NyZWYucGxVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSWTA0Lj0DAABRBwAAIgAJAAAAAAABAAAAAADi9wYAY3VybC1tYXN0ZXIvZG9jcy9leGFtcGxlcy9hbHRzdmMuY1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlJtDZZiVAgAAEwTAAAmAAkAAAAAAAEAAAAAAGj7BgBjdXJsLW1hc3Rlci9kb2NzL2V4YW1wbGVzL2FueWF1dGhwdXQuY1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlKRKjOwmA4AAIwcAAAnAAkAAAAAAAEAAAAAAAkEBwBjdXJsLW1hc3Rlci9kb2NzL2V4YW1wbGVzL2NhY2VydGlubWVtLmNVVAUAAbZIJGBQ
*/