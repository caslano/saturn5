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
# ifndef BOOST_PREPROCESSOR_ITERATION_LOCAL_HPP
# define BOOST_PREPROCESSOR_ITERATION_LOCAL_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/slot/slot.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
#
# /* BOOST_PP_LOCAL_ITERATE */
#
# define BOOST_PP_LOCAL_ITERATE() <boost/preprocessor/iteration/detail/local.hpp>
#
# define BOOST_PP_LOCAL_C(n) (BOOST_PP_LOCAL_S) <= n && (BOOST_PP_LOCAL_F) >= n
# define BOOST_PP_LOCAL_R(n) (BOOST_PP_LOCAL_F) <= n && (BOOST_PP_LOCAL_S) >= n
#
# endif

/* local.hpp
Ye7//XasE/AZmAmtFOafvnBir7L/wALQ9sB88rpq2JtYB7nlymGeuqS6SjY7Z/tg/rHlAJzjsHycvS4s1/yuZHnMv4YJ160n35XKkAfLeQv2Jbecr2BfgxnQugv2DWeBgrWCmXF7vQRjjUbmh9ZHsC6N6jr7CtaVs36C+YN5ow0QrCeYL9pAwSzcOgcL1p+zIYINAOuFFiaYlVtulGATwYxoowWL5ixcsOsa1X00RrDpXNnH
*/