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