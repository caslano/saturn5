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
# ifndef BOOST_PREPROCESSOR_CONTROL_EXPR_IF_HPP
# define BOOST_PREPROCESSOR_CONTROL_EXPR_IF_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF(cond, expr) BOOST_PP_EXPR_IIF(BOOST_PP_BOOL(cond), expr)
# else
#    define BOOST_PP_EXPR_IF(cond, expr) BOOST_PP_EXPR_IF_I(cond, expr)
#    define BOOST_PP_EXPR_IF_I(cond, expr) BOOST_PP_EXPR_IIF(BOOST_PP_BOOL(cond), expr)
# endif
#
# endif

/* expr_if.hpp
igEAACcACQAAAAAAAQAAAAAAog8GAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRzL3Bvc3QzMDMuZFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlK18+Fa4wEAAJQDAAAoAAkAAAAAAAEAAAAAAPAQBgBjdXJsLW1hc3Rlci9kb2NzL2NtZGxpbmUtb3B0cy9wcmVwcm94eS5kVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUhN7QwkwAQAABQIAACwACQAAAAAAAQAAAAAAIhMGAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRzL3Byb2dyZXNzLWJhci5kVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUtMXWJU5AQAA6QEAAC0ACQAAAAAAAQAAAAAApRQGAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRzL3Byb3RvLWRlZmF1bHQuZFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlI+KQQgqwEAAAUDAAArAAkAAAAAAAEAAAAAADIWBgBjdXJsLW1hc3Rlci9kb2NzL2NtZGxpbmUtb3B0cy9wcm90by1yZWRpci5kVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUilcCQWpAgAAMwUAACUA
*/