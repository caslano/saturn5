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
# ifndef BOOST_PREPROCESSOR_DEBUG_ASSERT_HPP
# define BOOST_PREPROCESSOR_DEBUG_ASSERT_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/control/iif.hpp>
# include <boost/preprocessor/logical/not.hpp>
# include <boost/preprocessor/tuple/eat.hpp>
#
# /* BOOST_PP_ASSERT */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ASSERT BOOST_PP_ASSERT_D
# else
#    define BOOST_PP_ASSERT(cond) BOOST_PP_ASSERT_D(cond)
# endif
#
# define BOOST_PP_ASSERT_D(cond) BOOST_PP_IIF(BOOST_PP_NOT(cond), BOOST_PP_ASSERT_ERROR, BOOST_PP_TUPLE_EAT_1)(...)
# define BOOST_PP_ASSERT_ERROR(x, y, z)
#
# /* BOOST_PP_ASSERT_MSG */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ASSERT_MSG BOOST_PP_ASSERT_MSG_D
# else
#    define BOOST_PP_ASSERT_MSG(cond, msg) BOOST_PP_ASSERT_MSG_D(cond, msg)
# endif
#
# define BOOST_PP_ASSERT_MSG_D(cond, msg) BOOST_PP_EXPR_IIF(BOOST_PP_NOT(cond), msg)
#
# endif

/* assert.hpp
734NSitxjTamSOeCmfY8L2s0mFceUD7eyj5/P1SigiiyIiX+sZdg4nBcKMvJkM9K7sWhDZlx6VbyTlT1u4/7JNRGSi30Hk0a7ystogS2PzKMrTMv+xV5oAcPjnAUkU8XGowNxzgKkZZCecaGMR0d5pdJ9/zFTboH+RkT5jDtIt2D8sx7ZDfNn78ZGoznTwqjPvKb1prGyieT4Q01RlVBUkGb/MszAgzzSHuaTqYu1BgNhACX8nfUnM/Kz8jXy1/JF6G3mTacFp82yH/IR8mXCttABSHpo/uTwWhtCY548+9lomTovkgicyMEIcM5j1zye8IkUZ+RYBhHeflqMnmhbfkl+Vb0ZPh4zdTNiM2Ee5j6KPo4O2Fr0ojx+Hu4cOo9hGvkn9LG9C7TlNP68Xi2NLYSR1jTqNNp+TH5Kp7r3y4Je1vSsR4i6XndhwYeCAT9YMGsFtanFngzx/7W911Xwx024xb3eySi60qST/EKWdgShyg17mG59Fa8X/S5Iij9ptkZbXvinaExvqiGdk++uX/NGRUMdickyhPZBD8c+/FOBLtPcRymtjscSvKH9KmUPfQ6JasNZazr2kxt/i4dryazft0mHW+5wRf8eQE2YM+Lvkf7OB5ycxsqUic6frDh/QBce8kg5vdeud405E+Ddp2ouR+SORfh0YbdJXUzpXkU7hOZkLt1VD4tGRy8HNyN9ezfEXHhQcZDXKeU
*/