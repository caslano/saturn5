/*=============================================================================
    Copyright (c) 2009-2010 Hartmut Kaiser
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_DETAIL_STRUCT_NAMESPACE_HPP
#define BOOST_FUSION_ADAPTED_DETAIL_STRUCT_NAMESPACE_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/preprocessor/dec.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/seq/seq.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/tuple/eat.hpp>

#define BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_BEGIN_I(R,DATA,ELEM)                \
    namespace ELEM {
#define BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_END_I(Z,I,DATA) }
#define BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_DECLARATION_I(Z,I,ELEM) ELEM::

#define BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_DEFINITION_BEGIN(NAMESPACE_SEQ)     \
    BOOST_PP_IF(                                                                \
        BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(NAMESPACE_SEQ)),                         \
        BOOST_PP_SEQ_FOR_EACH_R,                                                \
        BOOST_PP_TUPLE_EAT(4))(                                                 \
            1,                                                                  \
            BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_BEGIN_I,                        \
            _,                                                                  \
            BOOST_PP_SEQ_TAIL(NAMESPACE_SEQ))

#define BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_DEFINITION_END(NAMESPACE_SEQ)       \
    BOOST_PP_REPEAT_1(                                                          \
        BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(NAMESPACE_SEQ)),                         \
        BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_END_I,                              \
        _)

#define BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_DECLARATION(NAMESPACE_SEQ)          \
    BOOST_PP_IF(                                                                \
        BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(NAMESPACE_SEQ)),                         \
        BOOST_PP_SEQ_FOR_EACH_R,                                                \
        BOOST_PP_TUPLE_EAT(4))(                                                 \
            1,                                                                  \
            BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_DECLARATION_I,                  \
            _,                                                                  \
            BOOST_PP_SEQ_TAIL(NAMESPACE_SEQ))

#endif

/* namespace.hpp
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
*/