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
dAWSF6d5L7GMLIO6L6onf3B315Q4gt1/v/HOmYGqIbaoKa0EpcXUoKpjvGguGVEJFH7Fqx+82vWRy2W4HfGJW21yVAGuB3iZOVn/zbPIgq8uVzLoPWuJa4frgRdB3l9ukiUG3gsfq/v3V6oXs1LLjz5tr6Z9b3EN83R7CsU6v//fpPbRV5rhcZXuxwozuVRFRv7eHGqZeMfOok2JHr04rgRj4XfBwIVFJmVXrtXzaTAR3mEUGv39UkiKE0dk2dV4RKrEqVFuo1Y4J0rlQ60mNyDZJBqc2EfLkuMZmnbR8NI5raMd27ceqZLntdy5E9ec3VlQ77IFHBrv9MTL9uMf13q0F3kTyWBQnbXL71ph+5dN9+cw7xpF/WuvQCxiWEsW65SgbI4qzw4B6buDxq5p2F3fcS2uTK9EAdFLt65gXcQkoG3I3kZnxVV3AM7GGFsVgsNZRLrWIjxyoJhgOVCtnu/igieicon3IEKhJNSXRHR3FOu2mT+nspGryrVCALycp0ew12XmTMHWWOLqiEsLvSOO6BgKOldNq6lvt+SCr8/dG0AtjuzVn/TggQ==
*/