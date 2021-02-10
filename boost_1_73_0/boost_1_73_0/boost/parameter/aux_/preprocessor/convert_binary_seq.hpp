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
ta+0eexpVZC1DqpFq0KHEY91YUorMgHnbIpueqoH3esh7gkHwsqzrNaNYiyLMbW2LCr4OOMyvsNAljq6TugATig4VhuwXE71BqN7XLTLgcJzYRmmN+R5DVvQlco6NNO4njYBlehioiDMgabpW/srgg0IhmIkPGfHFUZDMZsEq7o8iwUjRUBdVBUEsCOqhZfnS1HlF25a4RFdtG3JtNACNStUzXKam2ZCwqKs3MZiVBz7e1CUBKDy0mOvRaUHxqRaeCbIsxSspk9vj2jViarFbErMgKTLUqFbc3PaKOraN0oCdLbkC1WMFMSOWOxxD79tACBRzbfKcagzRnG6AXqVAo60KCUobLRT33YgKwNRgXdzB/h5CH7tp2kjBwYnUmYV5dZZT+nQs8IJjdyV/OiBJVSQQJjxxRLyLWEBrYEAigjiKIA7ahB0rSKzweD2zn0TbP9rf/t/3w7Hg6uLSTXYGV/ZyI6gN+4dCd0Uhm8EIOYejIdGe9qqQUOo7QAeGGRzDBmqHgjOUIMezxjl1/0Xz54+e/Kd8egheHHQ2HmVjMTGn7ULoWB7EIZUiKd6p9ZcyFDqgeIU99jyDFyNvfcBxAQRpT7QAPAXbiNAnAN/hLsyDq3aGEfgwgCL1mnpNUPIQKQINWoA4Gcyf3Hx
*/