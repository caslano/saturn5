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