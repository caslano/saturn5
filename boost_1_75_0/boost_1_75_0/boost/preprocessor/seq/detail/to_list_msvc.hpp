# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2016.                                    *
#  *     Distributed under the Boost Software License, Version 1.0. (See      *
#  *     accompanying file LICENSE_1_0.txt or copy at                         *
#  *     http://www.boost.org/LICENSE_1_0.txt)                                *
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_SEQ_DETAIL_TO_LIST_MSVC_HPP
# define BOOST_PREPROCESSOR_SEQ_DETAIL_TO_LIST_MSVC_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/arithmetic/dec.hpp>
# include <boost/preprocessor/control/while.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
#
# define BOOST_PP_SEQ_DETAIL_TO_LIST_MSVC_STATE_RESULT(state) \
    BOOST_PP_TUPLE_ELEM(2, 0, state) \
/**/
# define BOOST_PP_SEQ_DETAIL_TO_LIST_MSVC_STATE_SIZE(state) \
    BOOST_PP_TUPLE_ELEM(2, 1, state) \
/**/
# define BOOST_PP_SEQ_DETAIL_TO_LIST_MSVC_PRED(d,state) \
    BOOST_PP_SEQ_DETAIL_TO_LIST_MSVC_STATE_SIZE(state) \
/**/
# define BOOST_PP_SEQ_DETAIL_TO_LIST_MSVC_OP(d,state) \
    ( \
    BOOST_PP_CAT(BOOST_PP_SEQ_DETAIL_TO_LIST_MSVC_STATE_RESULT(state),), \
    BOOST_PP_DEC(BOOST_PP_SEQ_DETAIL_TO_LIST_MSVC_STATE_SIZE(state)) \
    ) \
/**/
#
# /* BOOST_PP_SEQ_DETAIL_TO_LIST_MSVC */
#
# define BOOST_PP_SEQ_DETAIL_TO_LIST_MSVC(result,seqsize) \
    BOOST_PP_SEQ_DETAIL_TO_LIST_MSVC_STATE_RESULT \
        ( \
        BOOST_PP_WHILE \
            ( \
            BOOST_PP_SEQ_DETAIL_TO_LIST_MSVC_PRED, \
            BOOST_PP_SEQ_DETAIL_TO_LIST_MSVC_OP, \
            (result,seqsize) \
            ) \
        ) \
/**/
# endif // BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#
# endif // BOOST_PREPROCESSOR_SEQ_DETAIL_TO_LIST_MSVC_HPP

/* to_list_msvc.hpp
K7ZFf+C8yxHpijNQFiSFUy5Iiv3sSyt51VmrfeCxXv+Hyx+MG4UuRBVNjy3yl3OfTCIbOp5El57oljr0Ajf/uBPatwqGMbyBwNp7QOUXcdWbVaW5fQUR6tlCrgyijpHjuFjbkRaQ4G3Xrd/t8wT4fMHgXNGVEERTRZ+huLgkPI+czkRJRH8pG8joZ8d+kBzTZIrl5/zpWaY1kTh5B51Vj2lw047AYiRpHE7IbpGsWLiSTKgpub1YicyBVbIXJh1EiAHtIWl+pn3/EazcNyAQ9JGcYoFhslfKyEesv1InyXbtHjIZxKNUITKEGF6gORlUEl4gMef67Eq+v2grpiX2Reow/FBKpDfQ11MAOwHwU2SfiLwkFiu9EH77Jypqqbh6QLX3l9EDTUSChz9WpB2KVGZ+56K42z0lopufn3fcdLGs6h3k0qPaHP+hz1hjI7zGdmTGdmQesCbmHerVmCgrvwaTHrNtL9zh57mrOLraoqeYLI8nKXjmDwZCxFIhCW9id8EpPimmlH7IfjkHxkcd8ju20JSDfBvyVJ9sPKUdY/+snj5HcxoWOTJb6vs1DEdew8GMZhFvXMMRZ/O/UI35IsGCUXtW3Qf8WFdaw7HmiuWhc0MJzClrZj0x6lIP44ze44682LXP3txTNmjr7uVc4NhjlJ/rtyztodvjK82CjmKGoytZbxVfh8BN1EqWYk+kaxbFwa7R7Ph8Scis
*/