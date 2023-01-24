// Copyright Cromwell D. Enage 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PREPROCESSOR_CONVERT_BINARY_SEQ_HPP
#define BOOST_PARAMETER_AUX_PREPROCESSOR_CONVERT_BINARY_SEQ_HPP

#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/seq/push_back.hpp>

#define BOOST_PARAMETER_AUX_PP_AUGMENT_BINARY_SEQ_INDEX_FOLD_OP(s, seq, idx) \
    BOOST_PP_SEQ_PUSH_BACK(seq, (idx, BOOST_PP_SEQ_SIZE(seq)))
/**/

#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/tuple/elem.hpp>

#define BOOST_PARAMETER_AUX_PP_CONVERT_BINARY_SEQ_FOLD_OP(s, seq, elem) \
    ( \
        BOOST_PP_SEQ_PUSH_BACK( \
            BOOST_PP_SEQ_ELEM(0, seq) \
          , BOOST_PP_IIF( \
                BOOST_PP_TUPLE_ELEM(2, 0, elem) \
              , BOOST_PP_SEQ_ELEM(2, seq) \
              , BOOST_PP_SEQ_ELEM(1, seq) \
            )(BOOST_PP_TUPLE_ELEM(2, 1, elem), BOOST_PP_SEQ_ELEM(3, seq)) \
        ) \
    )(BOOST_PP_SEQ_ELEM(1, seq))(BOOST_PP_SEQ_ELEM(2, seq)) \
    (BOOST_PP_SEQ_ELEM(3, seq))
/**/

#include <boost/parameter/aux_/preprocessor/seq_enum.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/seq/seq.hpp>
#include <boost/preprocessor/seq/fold_left.hpp>

#define BOOST_PARAMETER_AUX_PP_CONVERT_BINARY_SEQ(seq, macro0, macro1, data) \
    BOOST_PARAMETER_SEQ_ENUM( \
        BOOST_PP_SEQ_ELEM( \
            0 \
          , BOOST_PP_SEQ_FOLD_LEFT( \
                BOOST_PARAMETER_AUX_PP_CONVERT_BINARY_SEQ_FOLD_OP \
              , (BOOST_PP_SEQ_NIL)(macro0)(macro1)(data) \
              , BOOST_PP_SEQ_FOLD_LEFT( \
                    BOOST_PARAMETER_AUX_PP_AUGMENT_BINARY_SEQ_INDEX_FOLD_OP \
                  , BOOST_PP_EMPTY() \
                  , seq \
                ) \
            ) \
        ) \
    )
/**/

#endif  // include guard


/* convert_binary_seq.hpp
wmeRcgQlr9tS21KwDlzigTpG08YtZFyw+HV1mmiBKOvkhNVnRZJn/nP2g4ZrIT4kwTP38FkpuIBQ5YHfNO/e6R/d9W8BGYg4BDm3wzVeOo4jXMp/bir6W3PtpNah3SaHolEZsBhYCCwFFgDHrtyMgpWW81MEGtewRO4kjqQPRTnmtYwluNqZc9yU+MtIZSG0kBKF4dYTBYsXQRVx7qi5lSxBoiO02RNAHkWLb1gxI/oDAay0S0a3u36zNnhCJvH2kniu8qUnMtyK9bCY+UO6/TL+ho3sm9KspGmvAN8tRPt1P7vn4EXnupe0AxNXJJQrU4BIxnJaifzQnA4nboGz3UiZk9riNNB/UrOSOkfWbPT8KDaaCfXLiCzkK+VcQtKeWuQP8lNzSg9XTo6MrVY0sxEaZTp82ZJaIkXx9evR1hsSYT6OuNF3phF2HySJl1Hc8+PphGJHyFY5U2IF3v26XiKFXh2qq/82G3WGyaa6NeyOTsu/ssB1ZVo/fHLayTT73SqDxyOWnMAbqiOP+YOgznF6KWPkqI16rAFV9+Ath/K3/WTbUZaQ7bwZZd1D6SnM4uygH2aoAjlJusHu1W4lvQqZdqT4Oo+9B+bRfcXZvT+K1TX/mHn77s46ADNJXuRo5o+fbL3TfxB8/FPcaylcgJj03z+bOZy+892xNb/QYJZLZXWa6ugpp+7FoEyJhNRHHfY9hpvhgy0anEGG
*/