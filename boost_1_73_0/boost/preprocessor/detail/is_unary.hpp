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
xlrQboJ5eGzMG7IV9YGYotlg/nbPxBTZLH1hQkuC+bgXf4AmCOsSmBX30RJI16958lHZ6vqpZUiD+bdN/abKFgwr7I9lWAbzsF0ffqjsB7B4XM4uxKUKrAC3lwnpkFNpsP+wDHBgJeFyG2H+6cG/hSv7b6Bqm2F+9+Wj75EtH0xuC7YL2ysAgzYALM66U7ByMLnN2i1YBdh2tD0w/37cIwGyZQXD/SesE04b+WDzHGUfDZLe
*/