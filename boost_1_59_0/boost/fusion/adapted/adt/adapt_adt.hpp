/*=============================================================================
    Copyright (c) 2001-2009 Joel de Guzman
    Copyright (c) 2009-2010 Hartmut Kaiser
    Copyright (c) 2010-2011 Christopher Schmidt
    Copyright (c) 2013-2014 Damien Buhl

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ADT_ADAPT_ADT_HPP
#define BOOST_FUSION_ADAPTED_ADT_ADAPT_ADT_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/empty.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/comparison/less.hpp>

#include <boost/fusion/adapted/struct/detail/extension.hpp>
#include <boost/fusion/adapted/struct/detail/adapt_base.hpp>
#include <boost/fusion/adapted/struct/detail/at_impl.hpp>
#include <boost/fusion/adapted/struct/detail/is_view_impl.hpp>
#include <boost/fusion/adapted/struct/detail/proxy_type.hpp>
#include <boost/fusion/adapted/struct/detail/is_sequence_impl.hpp>
#include <boost/fusion/adapted/struct/detail/value_at_impl.hpp>
#include <boost/fusion/adapted/struct/detail/category_of_impl.hpp>
#include <boost/fusion/adapted/struct/detail/size_impl.hpp>
#include <boost/fusion/adapted/struct/detail/begin_impl.hpp>
#include <boost/fusion/adapted/struct/detail/end_impl.hpp>
#include <boost/fusion/adapted/struct/detail/value_of_impl.hpp>
#include <boost/fusion/adapted/struct/detail/deref_impl.hpp>
#include <boost/fusion/adapted/adt/detail/extension.hpp>
#include <boost/fusion/adapted/adt/detail/adapt_base.hpp>
#include <boost/fusion/adapted/adt/detail/adapt_base_attr_filler.hpp>

#define BOOST_FUSION_ADAPT_ADT_C(                                               \
    TEMPLATE_PARAMS_SEQ, NAME_SEQ, IS_VIEW, I, ATTRIBUTE)                       \
        BOOST_FUSION_ADAPT_ADT_C_BASE(                                          \
            TEMPLATE_PARAMS_SEQ,                                                \
            NAME_SEQ,                                                           \
            I,                                                                  \
            BOOST_PP_IIF(IS_VIEW, BOOST_FUSION_PROXY_PREFIX, BOOST_PP_EMPTY),   \
            BOOST_FUSION_ADAPT_ADT_WRAPPEDATTR(ATTRIBUTE),                      \
            BOOST_FUSION_ADAPT_ADT_WRAPPEDATTR_SIZE(ATTRIBUTE),                 \
            BOOST_PP_LESS(                                                      \
                BOOST_FUSION_ADAPT_ADT_WRAPPEDATTR_SIZE(ATTRIBUTE), 4))         \

#define BOOST_FUSION_ADAPT_TPL_ADT(TEMPLATE_PARAMS_SEQ, NAME_SEQ , ATTRIBUTES)  \
    BOOST_FUSION_ADAPT_STRUCT_BASE(                                             \
        (1)TEMPLATE_PARAMS_SEQ,                                                 \
        (1)NAME_SEQ,                                                            \
        struct_tag,                                                             \
        0,                                                                      \
        BOOST_PP_CAT(BOOST_FUSION_ADAPT_ADT_FILLER_0(0,0,0,0)ATTRIBUTES,_END),  \
        BOOST_FUSION_ADAPT_ADT_C)

#define BOOST_FUSION_ADAPT_ADT(NAME, ATTRIBUTES)                                \
    BOOST_FUSION_ADAPT_STRUCT_BASE(                                             \
        (0),                                                                    \
        (0)(NAME),                                                              \
        struct_tag,                                                             \
        0,                                                                      \
        BOOST_PP_CAT(BOOST_FUSION_ADAPT_ADT_FILLER_0(0,0,0,0)ATTRIBUTES,_END),  \
        BOOST_FUSION_ADAPT_ADT_C)

#define BOOST_FUSION_ADAPT_ADT_AS_VIEW(NAME, ATTRIBUTES)                        \
    BOOST_FUSION_ADAPT_STRUCT_BASE(                                             \
        (0),                                                                    \
        (0)(NAME),                                                              \
        struct_tag,                                                             \
        1,                                                                      \
        BOOST_PP_CAT(BOOST_FUSION_ADAPT_ADT_FILLER_0(0,0,0,0)ATTRIBUTES,_END),  \
        BOOST_FUSION_ADAPT_ADT_C)

#endif

/* adapt_adt.hpp
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
*/