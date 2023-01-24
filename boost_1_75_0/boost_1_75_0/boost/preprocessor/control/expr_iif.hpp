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
7gz1m5a2oMOnBAiUrsePu79d+wGJKxlAWXgwTRlkmNXRXTHYtQg+o7hbqjHTuVh76czWYUX+rI01HQ2af6p/krpvhcRCpGoK/lJy1B98UEXvgt/W9CDP2sEO143upB04/OfX0LYODTjqTriwMR0SzvL8bC9uqTeFKGY01pEFRaydD9o9yzwgSV4o/+l4bpfCs++E/2A65/9zPOP/dryaK9DW1drN7V+ID/DWXPYJmm7Ce0HDeyspj4Ia0YvNn8o5ZCbuqK8jE9LbC8hnyCC6G9RhVap2D/2uoaFPAK6X5iqkdRDgLdIfqeczkOLOdHbQaLYxbCl2WGI/bS92WJtzMs7iowlY8lQueJka7kolNdTbenk7PQ8Vr5lqOz5HCB7nQkXk7gdrAP63msdpQeGufSqsv724i3iZPsWxkOUnqkmJ9ySNWk1cTNT0k5IGYi9xOkctCpLRH1mKkxuhATDSgsd7Sf+hRXi5s3Op5Eui/Vgg9UtQGIIE7Z1ViScOHcG8/KVGvABbkcV5zjH08HIMJyFIncyv/rx7pes7NI6eg4tyjl3JyoTLQz0Z84s4rZ9AoyBOTB/d8AeJuV7Rm+WkoXpwRsSUUZmvcrFhJ83q4nL77OJJTtvkaj7aDXm8v4ANaw9uZ+JXeEfmtqODKwgIavJnXQjEesizRlYb94NR78EiIFdgdighq7mEKc8/bmdvLRSUC4QW3Z3bMPWY
*/