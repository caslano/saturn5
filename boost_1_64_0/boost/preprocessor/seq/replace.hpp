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
# ifndef BOOST_PREPROCESSOR_SEQ_REPLACE_HPP
# define BOOST_PREPROCESSOR_SEQ_REPLACE_HPP
#
# include <boost/preprocessor/arithmetic/dec.hpp>
# include <boost/preprocessor/arithmetic/inc.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/comparison/equal.hpp>
# include <boost/preprocessor/control/iif.hpp>
# include <boost/preprocessor/seq/first_n.hpp>
# include <boost/preprocessor/seq/rest_n.hpp>
# include <boost/preprocessor/seq/size.hpp>
#
# /* BOOST_PP_SEQ_REPLACE */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_REPLACE(seq, i, elem) BOOST_PP_SEQ_FIRST_N(i, seq) (elem) BOOST_PP_SEQ_REPLACE_DETAIL_REST(seq, i)
# else
#    define BOOST_PP_SEQ_REPLACE(seq, i, elem) BOOST_PP_SEQ_REPLACE_I(seq, i, elem)
#    define BOOST_PP_SEQ_REPLACE_I(seq, i, elem) BOOST_PP_SEQ_FIRST_N(i, seq) (elem) BOOST_PP_SEQ_REPLACE_DETAIL_REST(seq, i)
# endif
#
#    define BOOST_PP_SEQ_REPLACE_DETAIL_REST_EMPTY(seq, i)
#    define BOOST_PP_SEQ_REPLACE_DETAIL_REST_VALID(seq, i) BOOST_PP_SEQ_REST_N(BOOST_PP_INC(i), seq)
#    define BOOST_PP_SEQ_REPLACE_DETAIL_REST(seq, i) \
        BOOST_PP_IIF \
            ( \
            BOOST_PP_EQUAL(i,BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(seq))), \
            BOOST_PP_SEQ_REPLACE_DETAIL_REST_EMPTY, \
            BOOST_PP_SEQ_REPLACE_DETAIL_REST_VALID \
            ) \
        (seq, i) \
/**/
#
# endif

/* replace.hpp
HaWN50d3DRqOGjIEBWoPAYxtTa0xypXhlIrjvo3GCLC9dTO9EswAVsK7tEktZo2EhFJ0jQpQyLTyZP+pQSE8AQ3uwY34fq997tXWyYTq4jnpAf3qKFN/krtogl/QhtW3D5oLr2ES3uJw/Y4Zej7FBy7LTzmv4D6NhhN/bWrb5SBW389y6O50LVrNsPhbhbU/c+XDWi6XtuzNB5SNSd86Jd7/xBiCPFcxtrqPUVFOT6CW2EG2tTQZMzX6dbndwSw+/LLnefd8oBs85GAg+BJE4EBLEcw9elAsUVshJyrn+4s3VoJzTWUFaiIE5TTR3Ecibe4Ak02rCUFdXEoqq/fpCbT/rs302vR8ptSuJ9eXh1hg95UBa9VLDWxHXbRnXrCAW3l5OprMZG2wxTaeb97d3UnTk76uMvSbqy4w+8m+U+1nPi1yRxf4BpU4Wr5ed3yVPM4FETAaUuuuzk90SxCGSKW50RZJPaL8DAhurTMGgqN1axLEL5DjdjEKXdLYUepENUesQNFqvUSYknVRpqNvkEPsp7+whf0nnfbsHH0fQI/yzooucYPNpK9HxQ==
*/