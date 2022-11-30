/*=============================================================================
    Copyright (c) 2010-2011 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DEFINE_ASSOC_STRUCT_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DEFINE_ASSOC_STRUCT_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/struct/adapt_assoc_struct.hpp>
#include <boost/fusion/adapted/struct/detail/define_struct.hpp>
#include <boost/preprocessor/cat.hpp>

#define BOOST_FUSION_DEFINE_ASSOC_STRUCT_FILLER_0(X, Y, Z)                      \
    ((X, Y, Z)) BOOST_FUSION_DEFINE_ASSOC_STRUCT_FILLER_1
#define BOOST_FUSION_DEFINE_ASSOC_STRUCT_FILLER_1(X, Y, Z)                      \
    ((X, Y, Z)) BOOST_FUSION_DEFINE_ASSOC_STRUCT_FILLER_0
#define BOOST_FUSION_DEFINE_ASSOC_STRUCT_FILLER_0_END
#define BOOST_FUSION_DEFINE_ASSOC_STRUCT_FILLER_1_END

#define BOOST_FUSION_DEFINE_ASSOC_TPL_STRUCT(                                   \
    TEMPLATE_PARAMS_SEQ, NAMESPACE_SEQ, NAME, ATTRIBUTES)                       \
                                                                                \
    BOOST_FUSION_DEFINE_TPL_STRUCT_IMPL(                                        \
        TEMPLATE_PARAMS_SEQ,                                                    \
        (0)NAMESPACE_SEQ,                                                       \
        NAME,                                                                   \
        BOOST_PP_CAT(                                                           \
            BOOST_FUSION_DEFINE_ASSOC_STRUCT_FILLER_0(0,0,0)ATTRIBUTES,_END),   \
        3)                                                                      \
                                                                                \
    BOOST_FUSION_ADAPT_ASSOC_TPL_STRUCT(                                        \
        TEMPLATE_PARAMS_SEQ,                                                    \
        (BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_DECLARATION((0)NAMESPACE_SEQ) NAME)\
            TEMPLATE_PARAMS_SEQ,                                                \
        ATTRIBUTES)

#define BOOST_FUSION_DEFINE_ASSOC_STRUCT(NAMESPACE_SEQ, NAME, ATTRIBUTES)       \
    BOOST_FUSION_DEFINE_STRUCT_IMPL(                                            \
        (0)NAMESPACE_SEQ,                                                       \
        NAME,                                                                   \
        BOOST_PP_CAT(                                                           \
            BOOST_FUSION_DEFINE_ASSOC_STRUCT_FILLER_0(0,0,0)ATTRIBUTES,_END),   \
        3)                                                                      \
                                                                                \
    BOOST_FUSION_ADAPT_ASSOC_STRUCT(                                            \
        BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_DECLARATION((0)NAMESPACE_SEQ) NAME, \
        ATTRIBUTES)

#endif

/* define_assoc_struct.hpp
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
*/