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
pFEq1QWCtGRoYwvBVHslmxYY5iiEPSNSvzg//vGLPV9+zpExMyotCoHxQGSoljwii5KHBybUOrx0b/tnhY6dm4IKH1gp+EKzgarGlniYjgHsksiD+hiBJAqedXwGe2J+gRWWusjaCSEmUq+P6/107LU3o3z0f6rLtSLYtCyJIXSfB0fN3KNjAWiJclKQsWFcdiOgoz1iRozRCVhp8T+FCw0wA2yKZFa1uB2z13tBuaSkJseHYcExV63qS5Zl7AJHYQ1hRzJPXCQTXzY8ilRHMuF4obGE3ZhCmcvQ+/C+7bZGJBEu58O6/kmu4kPJs0xFyINLpdeSejBasguUcwMxhyAeTODGQxp961jeKpSE+Mm60pmYZQ5nWckpUfBh3ou/+yft9DiOQTn2HqQqfwszO6sZgs6WB523EiXUiyja3kYKrbJ7aUCggbUg3gjUCEBktmm2ESy032idYPzWq2No6VUX+E453/aNuynE4N45OAkjOUkGuORxO2O673hXsBlME5Fs+zkKwcFn1aIzFg8aa0wE4YCP/JGaZSjjK1cYooTIgbNJPLBRbYZ88g==
*/