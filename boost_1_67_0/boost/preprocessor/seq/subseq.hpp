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
# ifndef BOOST_PREPROCESSOR_SEQ_SUBSEQ_HPP
# define BOOST_PREPROCESSOR_SEQ_SUBSEQ_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/seq/first_n.hpp>
# include <boost/preprocessor/seq/rest_n.hpp>
#
# /* BOOST_PP_SEQ_SUBSEQ */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_SUBSEQ(seq, i, len) BOOST_PP_SEQ_FIRST_N(len, BOOST_PP_SEQ_REST_N(i, seq))
# else
#    define BOOST_PP_SEQ_SUBSEQ(seq, i, len) BOOST_PP_SEQ_SUBSEQ_I(seq, i, len)
#    define BOOST_PP_SEQ_SUBSEQ_I(seq, i, len) BOOST_PP_SEQ_FIRST_N(len, BOOST_PP_SEQ_REST_N(i, seq))
# endif
#
# endif

/* subseq.hpp
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
*/