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
# ifndef BOOST_PREPROCESSOR_DETAIL_IS_UNARY_HPP
# define BOOST_PREPROCESSOR_DETAIL_IS_UNARY_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/detail/check.hpp>
#
# /* BOOST_PP_IS_UNARY */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_IS_UNARY(x) BOOST_PP_CHECK(x, BOOST_PP_IS_UNARY_CHECK)
# else
#    define BOOST_PP_IS_UNARY(x) BOOST_PP_IS_UNARY_I(x)
#    define BOOST_PP_IS_UNARY_I(x) BOOST_PP_CHECK(x, BOOST_PP_IS_UNARY_CHECK)
# endif
#
# define BOOST_PP_IS_UNARY_CHECK(a) 1
# define BOOST_PP_CHECK_RESULT_BOOST_PP_IS_UNARY_CHECK 0, BOOST_PP_NIL
#
# endif

/* is_unary.hpp
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
*/