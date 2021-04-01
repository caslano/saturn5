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
# ifndef BOOST_PREPROCESSOR_PUNCTUATION_PAREN_IF_HPP
# define BOOST_PREPROCESSOR_PUNCTUATION_PAREN_IF_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/if.hpp>
# include <boost/preprocessor/facilities/empty.hpp>
# include <boost/preprocessor/punctuation/paren.hpp>
#
# /* BOOST_PP_LPAREN_IF */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LPAREN_IF(cond) BOOST_PP_IF(cond, BOOST_PP_LPAREN, BOOST_PP_EMPTY)()
# else
#    define BOOST_PP_LPAREN_IF(cond) BOOST_PP_LPAREN_IF_I(cond)
#    define BOOST_PP_LPAREN_IF_I(cond) BOOST_PP_IF(cond, BOOST_PP_LPAREN, BOOST_PP_EMPTY)()
# endif
#
# /* BOOST_PP_RPAREN_IF */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_RPAREN_IF(cond) BOOST_PP_IF(cond, BOOST_PP_RPAREN, BOOST_PP_EMPTY)()
# else
#    define BOOST_PP_RPAREN_IF(cond) BOOST_PP_RPAREN_IF_I(cond)
#    define BOOST_PP_RPAREN_IF_I(cond) BOOST_PP_IF(cond, BOOST_PP_RPAREN, BOOST_PP_EMPTY)()
# endif
#
# endif

/* paren_if.hpp
DGYrlt2nQ6W1JF4aME9JapKR+ZLFgQ94cEOcRX2EkGarnTAqdY5o7gNERBKJPfctcEf2nARl+ySfAHLR5oMRlvRr8TLJPnuamKMPAx6KJyXMkjG16DM8bN5kaWGdeohNH3HPh+l0SYn3Zog5nG4jR4qXDMCn9Q3IQ180KDou5wzAb6gXLI6mLzL+W/6oLVbzUI52PQz75MXmORUNRFowFtHl/YCqQTu6Hj3cdTnfQZZDksZKx8f+GKE515mMxeiR9tqaTN05u7CpWRbCypQOHZTzW2QITFjVPFUBAcDjWJWg1HclYz2EPduh+nCjqsdxw+QMZaoGODc+ysRp2WHFHKyTYAsin8++1Q621lnSCkDXUCxc6lKF51k5rYgVbmljmcmBZMhKqY4E1w9JXHY220o1jZ/GHZUDqhi4rLSQ1ns6ZFp+DkWcrgT1bBCtHI94F0aJXgpNVL8Qh5Rt8jthEDpsh7ekDniFOXZJT157UhXQ17Q81YS09iIzYBnZa1+8GkM/xzgAOS+MSkdx+Dr1ez4IQa5JqfRADtVaRISTOPIEvAliK2D4VPQ9IA==
*/