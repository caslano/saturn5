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
Bn3+sigT6y7uIf1ofYGvd4Q89jZj8QhZNItP2eWxVDbM/A2QKJfnfDdId6hK+D/QdU+yw4OEdIv3UsYaeeSF61V5aSz42CTdi8OZ96bp7nlh+zgN11vg89im7nlJEviaizaNxXdwM+aPtfwtx6V8RqHeSG1bmVqIti0v0Nb+62nbSrS9ykMr01guaN7jofVq0aaNaNNW+Ci2tUTma39z7qZ35jk1Nb5iDL/tE3PK5bF2eb5fLbfmsSwUGG82sMs=
*/