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
# ifndef BOOST_PREPROCESSOR_LIST_FOLD_RIGHT_HPP
# define BOOST_PREPROCESSOR_LIST_FOLD_RIGHT_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/control/while.hpp>
# include <boost/preprocessor/debug/error.hpp>
# include <boost/preprocessor/detail/auto_rec.hpp>
#
# if 0
#    define BOOST_PP_LIST_FOLD_RIGHT(op, state, list)
# endif
#
# define BOOST_PP_LIST_FOLD_RIGHT BOOST_PP_CAT(BOOST_PP_LIST_FOLD_RIGHT_, BOOST_PP_AUTO_REC(BOOST_PP_WHILE_P, 256))
#
# define BOOST_PP_LIST_FOLD_RIGHT_257(o, s, l) BOOST_PP_ERROR(0x0004)
#
# define BOOST_PP_LIST_FOLD_RIGHT_D(d, o, s, l) BOOST_PP_LIST_FOLD_RIGHT_ ## d(o, s, l)
# define BOOST_PP_LIST_FOLD_RIGHT_2ND BOOST_PP_LIST_FOLD_RIGHT
# define BOOST_PP_LIST_FOLD_RIGHT_2ND_D BOOST_PP_LIST_FOLD_RIGHT_D
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    include <boost/preprocessor/list/detail/edg/fold_right.hpp>
# else
#    include <boost/preprocessor/list/detail/fold_right.hpp>
# endif
#
# endif

/* fold_right.hpp
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
*/