# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2015.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_SEQ_DETAIL_IS_EMPTY_HPP
# define BOOST_PREPROCESSOR_SEQ_DETAIL_IS_EMPTY_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/arithmetic/dec.hpp>
# include <boost/preprocessor/logical/bool.hpp>
# include <boost/preprocessor/logical/compl.hpp>
# include <boost/preprocessor/seq/size.hpp>
#
/* An empty seq is one that is just BOOST_PP_SEQ_NIL */
#
# define BOOST_PP_SEQ_DETAIL_IS_EMPTY(seq) \
    BOOST_PP_COMPL \
        ( \
        BOOST_PP_SEQ_DETAIL_IS_NOT_EMPTY(seq) \
        ) \
/**/
#
# define BOOST_PP_SEQ_DETAIL_IS_EMPTY_SIZE(size) \
    BOOST_PP_COMPL \
        ( \
        BOOST_PP_SEQ_DETAIL_IS_NOT_EMPTY_SIZE(size) \
        ) \
/**/
#
# define BOOST_PP_SEQ_DETAIL_IS_NOT_EMPTY(seq) \
    BOOST_PP_SEQ_DETAIL_IS_NOT_EMPTY_SIZE(BOOST_PP_SEQ_DETAIL_EMPTY_SIZE(seq)) \
/**/
#
# define BOOST_PP_SEQ_DETAIL_IS_NOT_EMPTY_SIZE(size) \
    BOOST_PP_BOOL(size) \
/**/
#
# define BOOST_PP_SEQ_DETAIL_EMPTY_SIZE(seq) \
    BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(seq (nil))) \
/**/
#
# endif

/* is_empty.hpp
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
*/