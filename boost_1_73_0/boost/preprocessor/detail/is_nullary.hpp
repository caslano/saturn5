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
# ifndef BOOST_PREPROCESSOR_DETAIL_IS_NULLARY_HPP
# define BOOST_PREPROCESSOR_DETAIL_IS_NULLARY_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/detail/check.hpp>
#
# /* BOOST_PP_IS_NULLARY */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_IS_NULLARY(x) BOOST_PP_CHECK(x, BOOST_PP_IS_NULLARY_CHECK)
# else
#    define BOOST_PP_IS_NULLARY(x) BOOST_PP_IS_NULLARY_I(x)
#    define BOOST_PP_IS_NULLARY_I(x) BOOST_PP_CHECK(x, BOOST_PP_IS_NULLARY_CHECK)
# endif
#
# define BOOST_PP_IS_NULLARY_CHECK() 1
# define BOOST_PP_CHECK_RESULT_BOOST_PP_IS_NULLARY_CHECK 0, BOOST_PP_NIL
#
# endif

/* is_nullary.hpp
42H+YN77/5Rtg7+6vQkwDzPsLJftJFgo7gcrzH29X71LKV83uD7FmE2C9OSAwWjS8zd/wuUmw/w+06qvZGsGw7ict7El4bgc5BFMzks0zMPG73xNtrgAtXxTxDoP0WswSnY9pH8dvv1bJS69YJu4nHPdQ6KM8DHu9yvUvMxgsI6YBS8qdRcsAsswU9zvvdV8zoZ5+X1Z78mWAnY5LhcP8wHf3LRTtjywBlxuPsx3rVp+TrEg
*/