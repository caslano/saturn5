/*=============================================================================
    Copyright (c) 2013-2014 Damien Buhl

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_ADAPT_BASE_ATTR_FILLER_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_ADAPT_BASE_ATTR_FILLER_HPP

#include <boost/config.hpp>

#include <boost/fusion/adapted/struct/detail/adapt_auto.hpp>
#include <boost/fusion/adapted/struct/detail/preprocessor/is_seq.hpp>

#include <boost/mpl/aux_/preprocessor/token_equal.hpp>

#include <boost/preprocessor/config/config.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/preprocessor/logical/compl.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/push_front.hpp>
#include <boost/preprocessor/facilities/expand.hpp>
#include <boost/preprocessor/facilities/is_empty.hpp>


#define BOOST_FUSION_ADAPT_STRUCT_FILLER_0(X, Y)                                \
    BOOST_FUSION_ADAPT_STRUCT_WRAP_ATTR(X,Y)                                    \
    BOOST_FUSION_ADAPT_STRUCT_FILLER_1

#define BOOST_FUSION_ADAPT_STRUCT_FILLER_1(X, Y)                                \
    BOOST_FUSION_ADAPT_STRUCT_WRAP_ATTR(X,Y)                                    \
    BOOST_FUSION_ADAPT_STRUCT_FILLER_0

#define BOOST_FUSION_ADAPT_STRUCT_FILLER_0_END
#define BOOST_FUSION_ADAPT_STRUCT_FILLER_1_END

#define BOOST_FUSION_ADAPT_STRUCT_WRAP_ATTR(X, Y)                               \
    BOOST_PP_IIF(BOOST_MPL_PP_TOKEN_EQUAL(auto, BOOST_PP_EXPAND(X)),            \
      ((1, (Y))),                                                               \
      ((2, (X,Y)))                                                              \
    )

#define BOOST_FUSION_ADAPT_STRUCT_WRAPPEDATTR_SIZE(ATTRIBUTE)                   \
  BOOST_PP_TUPLE_ELEM(2, 0, ATTRIBUTE)

#define BOOST_FUSION_ADAPT_STRUCT_WRAPPEDATTR(ATTRIBUTE)                        \
  BOOST_PP_TUPLE_ELEM(2, 1, ATTRIBUTE)


#if BOOST_PP_VARIADICS

#   define BOOST_FUSION_ADAPT_STRUCT_ATTRIBUTES_FILLER_OP(r, unused, elem)      \
        BOOST_PP_IIF(BOOST_FUSION_PP_IS_SEQ(elem),                              \
            BOOST_PP_CAT(BOOST_FUSION_ADAPT_STRUCT_FILLER_0 elem ,_END),        \
            BOOST_PP_EXPR_IIF(BOOST_PP_COMPL(BOOST_PP_IS_EMPTY(elem)),          \
                BOOST_FUSION_ADAPT_STRUCT_WRAP_ATTR(auto, elem)))

#   define BOOST_FUSION_ADAPT_STRUCT_ATTRIBUTES_FILLER(VA_ARGS_SEQ)             \
        BOOST_PP_SEQ_PUSH_FRONT(                                                \
            BOOST_PP_SEQ_FOR_EACH(                                              \
                BOOST_FUSION_ADAPT_STRUCT_ATTRIBUTES_FILLER_OP,                 \
                unused, VA_ARGS_SEQ),                                           \
            (0,0))

#endif // BOOST_PP_VARIADICS

#endif

/* adapt_base_attr_filler.hpp
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
*/