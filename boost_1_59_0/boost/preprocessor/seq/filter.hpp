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
# ifndef BOOST_PREPROCESSOR_SEQ_FILTER_HPP
# define BOOST_PREPROCESSOR_SEQ_FILTER_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_if.hpp>
# include <boost/preprocessor/facilities/empty.hpp>
# include <boost/preprocessor/seq/fold_left.hpp>
# include <boost/preprocessor/seq/seq.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
#
# /* BOOST_PP_SEQ_FILTER */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_FILTER(pred, data, seq) BOOST_PP_SEQ_TAIL(BOOST_PP_TUPLE_ELEM(3, 2, BOOST_PP_SEQ_FOLD_LEFT(BOOST_PP_SEQ_FILTER_O, (pred, data, (nil)), seq)))
# else
#    define BOOST_PP_SEQ_FILTER(pred, data, seq) BOOST_PP_SEQ_FILTER_I(pred, data, seq)
#    define BOOST_PP_SEQ_FILTER_I(pred, data, seq) BOOST_PP_SEQ_TAIL(BOOST_PP_TUPLE_ELEM(3, 2, BOOST_PP_SEQ_FOLD_LEFT(BOOST_PP_SEQ_FILTER_O, (pred, data, (nil)), seq)))
# endif
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_STRICT()
#    define BOOST_PP_SEQ_FILTER_O(s, st, elem) BOOST_PP_SEQ_FILTER_O_IM(s, BOOST_PP_TUPLE_REM_3 st, elem)
#    define BOOST_PP_SEQ_FILTER_O_IM(s, im, elem) BOOST_PP_SEQ_FILTER_O_I(s, im, elem)
# else
#    define BOOST_PP_SEQ_FILTER_O(s, st, elem) BOOST_PP_SEQ_FILTER_O_I(s, BOOST_PP_TUPLE_ELEM(3, 0, st), BOOST_PP_TUPLE_ELEM(3, 1, st), BOOST_PP_TUPLE_ELEM(3, 2, st), elem)
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_DMC()
#   define BOOST_PP_SEQ_FILTER_O_I(s, pred, data, res, elem) (pred, data, res BOOST_PP_EXPR_IF(pred(s, data, elem), (elem)))
# else
#   define BOOST_PP_SEQ_FILTER_O_I(s, pred, data, res, elem) (pred, data, res BOOST_PP_EXPR_IF(pred##(s, data, elem), (elem)))
# endif
#
# /* BOOST_PP_SEQ_FILTER_S */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_FILTER_S(s, pred, data, seq) BOOST_PP_SEQ_TAIL(BOOST_PP_TUPLE_ELEM(3, 2, BOOST_PP_SEQ_FOLD_LEFT_ ## s(BOOST_PP_SEQ_FILTER_O, (pred, data, (nil)), seq)))
# else
#    define BOOST_PP_SEQ_FILTER_S(s, pred, data, seq) BOOST_PP_SEQ_FILTER_S_I(s, pred, data, seq)
#    define BOOST_PP_SEQ_FILTER_S_I(s, pred, data, seq) BOOST_PP_SEQ_TAIL(BOOST_PP_TUPLE_ELEM(3, 2, BOOST_PP_SEQ_FOLD_LEFT_ ## s(BOOST_PP_SEQ_FILTER_O, (pred, data, (nil)), seq)))
# endif
#
# endif

/* filter.hpp
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
*/