/*=============================================================================
    Copyright (c) 2001-2009 Joel de Guzman
    Copyright (c) 2007 Dan Marsden
    Copyright (c) 2010-2011 Christopher Schmidt
    Copyright (c) 2013-2014 Damien Buhl

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ADT_ADAPT_ASSOC_ADT_HPP
#define BOOST_FUSION_ADAPTED_ADT_ADAPT_ASSOC_ADT_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/empty.hpp>
#include <boost/preprocessor/control/if.hpp>

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
#include <boost/fusion/adapted/struct/detail/deref_data_impl.hpp>
#include <boost/fusion/adapted/struct/detail/key_of_impl.hpp>
#include <boost/fusion/adapted/struct/detail/value_of_data_impl.hpp>
#include <boost/fusion/adapted/adt/detail/extension.hpp>
#include <boost/fusion/adapted/adt/detail/adapt_base.hpp>
#include <boost/fusion/adapted/adt/detail/adapt_base_assoc_attr_filler.hpp>

#define BOOST_FUSION_ADAPT_ASSOC_ADT_C(                                         \
    TEMPLATE_PARAMS_SEQ, NAME_SEQ, IS_VIEW, I, ATTRIBUTE)                       \
                                                                                \
        BOOST_FUSION_ADAPT_ADT_C_BASE(                                          \
            TEMPLATE_PARAMS_SEQ,                                                \
            NAME_SEQ,                                                           \
            I,                                                                  \
            BOOST_PP_IIF(IS_VIEW, BOOST_FUSION_PROXY_PREFIX, BOOST_PP_EMPTY),   \
            BOOST_FUSION_ADAPT_ADT_WRAPPEDATTR(ATTRIBUTE),                      \
            BOOST_FUSION_ADAPT_ADT_WRAPPEDATTR_SIZE(ATTRIBUTE),                 \
            BOOST_PP_LESS(                                                      \
                BOOST_FUSION_ADAPT_ADT_WRAPPEDATTR_SIZE(ATTRIBUTE), 5))         \
                                                                                \
    template<                                                                   \
        BOOST_FUSION_ADAPT_STRUCT_UNPACK_TEMPLATE_PARAMS(TEMPLATE_PARAMS_SEQ)   \
    >                                                                           \
    struct struct_assoc_key<BOOST_FUSION_ADAPT_STRUCT_UNPACK_NAME(NAME_SEQ), I> \
    {                                                                           \
        typedef BOOST_FUSION_ADAPT_ASSOC_ADT_WRAPPEDATTR_GET_KEY(ATTRIBUTE) type;\
    };

#define BOOST_FUSION_ADAPT_ASSOC_TPL_ADT(                                       \
    TEMPLATE_PARAMS_SEQ, NAME_SEQ, ATTRIBUTES)                                  \
                                                                                \
    BOOST_FUSION_ADAPT_STRUCT_BASE(                                             \
        (1)TEMPLATE_PARAMS_SEQ,                                                 \
        (1)NAME_SEQ,                                                            \
        assoc_struct_tag,                                                       \
        0,                                                                      \
        BOOST_PP_CAT(                                                           \
            BOOST_FUSION_ADAPT_ASSOC_ADT_FILLER_0(0,0,0,0,0)ATTRIBUTES,_END),   \
        BOOST_FUSION_ADAPT_ASSOC_ADT_C)

#define BOOST_FUSION_ADAPT_ASSOC_ADT(NAME, ATTRIBUTES)                          \
    BOOST_FUSION_ADAPT_STRUCT_BASE(                                             \
        (0),                                                                    \
        (0)(NAME),                                                              \
        assoc_struct_tag,                                                       \
        0,                                                                      \
        BOOST_PP_CAT(                                                           \
            BOOST_FUSION_ADAPT_ASSOC_ADT_FILLER_0(0,0,0,0,0)ATTRIBUTES,_END),   \
        BOOST_FUSION_ADAPT_ASSOC_ADT_C)

#define BOOST_FUSION_ADAPT_ASSOC_ADT_AS_VIEW(NAME, ATTRIBUTES)                  \
    BOOST_FUSION_ADAPT_STRUCT_BASE(                                             \
        (0),                                                                    \
        (0)(NAME),                                                              \
        assoc_struct_tag,                                                       \
        1,                                                                      \
        BOOST_PP_CAT(                                                           \
            BOOST_FUSION_ADAPT_ASSOC_ADT_FILLER_0(0,0,0,0,0)ATTRIBUTES,_END),   \
        BOOST_FUSION_ADAPT_ASSOC_ADT_C)

#endif

/* adapt_assoc_adt.hpp
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
*/