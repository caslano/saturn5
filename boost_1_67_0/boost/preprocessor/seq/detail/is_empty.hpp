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