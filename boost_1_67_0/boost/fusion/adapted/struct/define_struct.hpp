/*=============================================================================
    Copyright (c) 2010-2011 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DEFINE_STRUCT_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DEFINE_STRUCT_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/fusion/adapted/struct/detail/define_struct.hpp>
#include <boost/preprocessor/cat.hpp>

#define BOOST_FUSION_DEFINE_TPL_STRUCT(                                         \
    TEMPLATE_PARAMS_SEQ, NAMESPACE_SEQ, NAME, ATTRIBUTES)                       \
                                                                                \
    BOOST_FUSION_DEFINE_TPL_STRUCT_IMPL(                                        \
        TEMPLATE_PARAMS_SEQ,                                                    \
        (0)NAMESPACE_SEQ,                                                       \
        NAME,                                                                   \
        BOOST_PP_CAT(BOOST_FUSION_DEFINE_STRUCT_FILLER_0(0,0)ATTRIBUTES,_END),  \
        2)                                                                      \
                                                                                \
    BOOST_FUSION_ADAPT_TPL_STRUCT(                                              \
        TEMPLATE_PARAMS_SEQ,                                                    \
        (BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_DECLARATION((0)NAMESPACE_SEQ) NAME)\
            TEMPLATE_PARAMS_SEQ,                                                \
        ATTRIBUTES)

#define BOOST_FUSION_DEFINE_STRUCT(NAMESPACE_SEQ, NAME, ATTRIBUTES)             \
    BOOST_FUSION_DEFINE_STRUCT_IMPL(                                            \
        (0)NAMESPACE_SEQ,                                                       \
        NAME,                                                                   \
        BOOST_PP_CAT(BOOST_FUSION_DEFINE_STRUCT_FILLER_0(0,0)ATTRIBUTES,_END),  \
        2)                                                                      \
                                                                                \
    BOOST_FUSION_ADAPT_STRUCT(                                                  \
        BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_DECLARATION((0)NAMESPACE_SEQ) NAME, \
        ATTRIBUTES)

#endif

/* define_struct.hpp
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
*/