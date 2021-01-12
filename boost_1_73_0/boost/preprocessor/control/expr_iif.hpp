# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2002.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_CONTROL_EXPR_IIF_HPP
# define BOOST_PREPROCESSOR_CONTROL_EXPR_IIF_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_EXPR_IIF */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF(bit, expr) BOOST_PP_EXPR_IIF_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF(bit, expr) BOOST_PP_EXPR_IIF_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF_OO(par) BOOST_PP_EXPR_IIF_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF_I(bit, expr) BOOST_PP_EXPR_IIF_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF_0(expr)
# define BOOST_PP_EXPR_IIF_1(expr) expr
#
# endif

/* expr_iif.hpp
r5H9hnkZBPNnnv8CSot56WdkLVjnB0O6xwIHfIz7PcLI5mDMhkC6flXs90rM4AVBtXj8hUD65KLDR2UrmGpkb+NyQyEdETIWmhLcf9ONbAjuvyshnXB6x6PKOmONLAWXGwbp2gdi9itln2VkNwZKFgrpKQfv36fs20yjcqyMgPTxfzyaL1vYCiPbslqyMEgPfuxjSOHx7mNiPTEuI2Hex2teqrI9XxOzYvlGQXrVqfdfUPZt
*/