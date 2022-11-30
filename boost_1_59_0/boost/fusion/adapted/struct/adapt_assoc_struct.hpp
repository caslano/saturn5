/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman
    Copyright (c) 2007 Dan Marsden
    Copyright (c) 2009-2011 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_ADAPT_ASSOC_STRUCT_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_ADAPT_ASSOC_STRUCT_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/empty.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/comparison/less.hpp>

#include <boost/fusion/adapted/struct/detail/extension.hpp>
#include <boost/fusion/adapted/struct/detail/adapt_base.hpp>
#include <boost/fusion/adapted/struct/detail/adapt_base_assoc_attr_filler.hpp>
#include <boost/fusion/adapted/struct/detail/at_impl.hpp>
#include <boost/fusion/adapted/struct/detail/is_view_impl.hpp>
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

#define BOOST_FUSION_ADAPT_ASSOC_STRUCT_C_BASE(                                 \
    TEMPLATE_PARAMS_SEQ,NAME_SEQ,IS_VIEW,I,PREFIX,ATTRIBUTE)                    \
                                                                                \
    BOOST_FUSION_ADAPT_STRUCT_C_BASE(                                           \
        TEMPLATE_PARAMS_SEQ,                                                    \
        NAME_SEQ,                                                               \
        IS_VIEW,                                                                \
        I,                                                                      \
        BOOST_PP_IIF(IS_VIEW, BOOST_FUSION_PROXY_PREFIX, BOOST_PP_EMPTY),       \
        BOOST_FUSION_ADAPT_STRUCT_WRAPPEDATTR(ATTRIBUTE),                       \
        BOOST_FUSION_ADAPT_STRUCT_WRAPPEDATTR_SIZE(ATTRIBUTE),                  \
        BOOST_PP_LESS(                                                          \
            BOOST_FUSION_ADAPT_STRUCT_WRAPPEDATTR_SIZE(ATTRIBUTE),3))           \
                                                                                \
    template<                                                                   \
        BOOST_FUSION_ADAPT_STRUCT_UNPACK_TEMPLATE_PARAMS(TEMPLATE_PARAMS_SEQ)   \
    >                                                                           \
    struct struct_assoc_key<BOOST_FUSION_ADAPT_STRUCT_UNPACK_NAME(NAME_SEQ), I> \
    {                                                                           \
        typedef                                                                 \
          BOOST_FUSION_ADAPT_ASSOC_STRUCT_WRAPPEDATTR_GET_KEY(ATTRIBUTE) type;  \
    };

#define BOOST_FUSION_ADAPT_ASSOC_STRUCT_C(                                      \
    TEMPLATE_PARAMS_SEQ,NAME_SEQ,IS_VIEW, I, ATTRIBUTE)                         \
                                                                                \
    BOOST_FUSION_ADAPT_ASSOC_STRUCT_C_BASE(                                     \
        TEMPLATE_PARAMS_SEQ,NAME_SEQ,IS_VIEW,I,BOOST_PP_EMPTY,ATTRIBUTE)


#define BOOST_FUSION_ADAPT_ASSOC_TPL_STRUCT(                                    \
    TEMPLATE_PARAMS_SEQ, NAME_SEQ, ATTRIBUTES)                                  \
                                                                                \
    BOOST_FUSION_ADAPT_STRUCT_BASE(                                             \
        (1)TEMPLATE_PARAMS_SEQ,                                                 \
        (1)NAME_SEQ,                                                            \
        assoc_struct_tag,                                                       \
        0,                                                                      \
        BOOST_PP_CAT(                                                           \
            BOOST_FUSION_ADAPT_ASSOC_STRUCT_FILLER_0(0,0,0)ATTRIBUTES,_END),    \
        BOOST_FUSION_ADAPT_ASSOC_STRUCT_C)

#define BOOST_FUSION_ADAPT_ASSOC_STRUCT(NAME, ATTRIBUTES)                       \
    BOOST_FUSION_ADAPT_STRUCT_BASE(                                             \
        (0),                                                                    \
        (0)(NAME),                                                              \
        assoc_struct_tag,                                                       \
        0,                                                                      \
        BOOST_PP_CAT(                                                           \
            BOOST_FUSION_ADAPT_ASSOC_STRUCT_FILLER_0(0,0,0)ATTRIBUTES,_END),    \
        BOOST_FUSION_ADAPT_ASSOC_STRUCT_C)

#define BOOST_FUSION_ADAPT_ASSOC_STRUCT_AS_VIEW(NAME, ATTRIBUTES)               \
    BOOST_FUSION_ADAPT_STRUCT_BASE(                                             \
        (0),                                                                    \
        (0)(NAME),                                                              \
        assoc_struct_tag,                                                       \
        1,                                                                      \
        BOOST_PP_CAT(                                                           \
            BOOST_FUSION_ADAPT_ASSOC_STRUCT_FILLER_0(0,0,0)ATTRIBUTES,_END),    \
        BOOST_FUSION_ADAPT_ASSOC_STRUCT_C)

#endif

/* adapt_assoc_struct.hpp
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
*/