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