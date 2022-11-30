/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman
    Copyright (c) 2009-2011 Christopher Schmidt
    Copyright (c) 2013-2014 Damien Buhl

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_ADAPT_STRUCT_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_ADAPT_STRUCT_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/preprocessor/config/config.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/empty.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/comparison/less.hpp>
#include <boost/preprocessor/seq/seq.hpp>
#include <boost/preprocessor/variadic/to_seq.hpp>

#include <boost/fusion/adapted/struct/detail/extension.hpp>
#include <boost/fusion/adapted/struct/detail/adapt_base.hpp>
#include <boost/fusion/adapted/struct/detail/adapt_base_attr_filler.hpp>
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

#define BOOST_FUSION_ADAPT_STRUCT_C(                                            \
    TEMPLATE_PARAMS_SEQ, NAME_SEQ, IS_VIEW, I, ATTRIBUTE)                       \
        BOOST_FUSION_ADAPT_STRUCT_C_BASE(                                       \
            TEMPLATE_PARAMS_SEQ,                                                \
            NAME_SEQ,                                                           \
            IS_VIEW,                                                            \
            I,                                                                  \
            BOOST_PP_IIF(IS_VIEW, BOOST_FUSION_PROXY_PREFIX, BOOST_PP_EMPTY),   \
            BOOST_FUSION_ADAPT_STRUCT_WRAPPEDATTR(ATTRIBUTE),                   \
            BOOST_FUSION_ADAPT_STRUCT_WRAPPEDATTR_SIZE(ATTRIBUTE),              \
            BOOST_PP_LESS(                                                      \
                BOOST_FUSION_ADAPT_STRUCT_WRAPPEDATTR_SIZE(ATTRIBUTE), 2))



#if BOOST_PP_VARIADICS

#   define BOOST_FUSION_ADAPT_TPL_STRUCT(TEMPLATE_PARAMS_SEQ,NAME_SEQ, ...)     \
        BOOST_FUSION_ADAPT_STRUCT_BASE(                                         \
            (1)TEMPLATE_PARAMS_SEQ,                                             \
            (1)NAME_SEQ,                                                        \
            struct_tag,                                                         \
            0,                                                                  \
            BOOST_FUSION_ADAPT_STRUCT_ATTRIBUTES_FILLER(                        \
                BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)),                         \
            BOOST_FUSION_ADAPT_STRUCT_C)

#   define BOOST_FUSION_ADAPT_STRUCT(...)                                       \
        BOOST_FUSION_ADAPT_STRUCT_BASE(                                         \
            (0),                                                                \
            (0)(BOOST_PP_SEQ_HEAD(BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))),      \
            struct_tag,                                                         \
            0,                                                                  \
            BOOST_FUSION_ADAPT_STRUCT_ATTRIBUTES_FILLER(                        \
              BOOST_PP_SEQ_TAIL(BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))),        \
            BOOST_FUSION_ADAPT_STRUCT_C)

#   define BOOST_FUSION_ADAPT_STRUCT_AS_VIEW(...)                               \
        BOOST_FUSION_ADAPT_STRUCT_BASE(                                         \
            (0),                                                                \
            (0)(BOOST_PP_SEQ_HEAD(BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))),      \
            struct_tag,                                                         \
            1,                                                                  \
            BOOST_FUSION_ADAPT_STRUCT_ATTRIBUTES_FILLER(                        \
              BOOST_PP_SEQ_TAIL(BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))),        \
            BOOST_FUSION_ADAPT_STRUCT_C)

#else // BOOST_PP_VARIADICS

#   define BOOST_FUSION_ADAPT_TPL_STRUCT(                                       \
        TEMPLATE_PARAMS_SEQ,NAME_SEQ, ATTRIBUTES)                               \
        BOOST_FUSION_ADAPT_STRUCT_BASE(                                         \
            (1)TEMPLATE_PARAMS_SEQ,                                             \
            (1)NAME_SEQ,                                                        \
            struct_tag,                                                         \
            0,                                                                  \
            BOOST_PP_CAT(                                                       \
                BOOST_FUSION_ADAPT_STRUCT_FILLER_0(0,0)ATTRIBUTES,_END),        \
            BOOST_FUSION_ADAPT_STRUCT_C)

#   define BOOST_FUSION_ADAPT_STRUCT(NAME, ATTRIBUTES)                          \
        BOOST_FUSION_ADAPT_STRUCT_BASE(                                         \
            (0),                                                                \
            (0)(NAME),                                                          \
            struct_tag,                                                         \
            0,                                                                  \
            BOOST_PP_CAT(                                                       \
                BOOST_FUSION_ADAPT_STRUCT_FILLER_0(0,0)ATTRIBUTES,              \
                _END),                                                          \
            BOOST_FUSION_ADAPT_STRUCT_C)

#   define BOOST_FUSION_ADAPT_STRUCT_AS_VIEW(NAME, ATTRIBUTES)                  \
        BOOST_FUSION_ADAPT_STRUCT_BASE(                                         \
            (0),                                                                \
            (0)(NAME),                                                          \
            struct_tag,                                                         \
            1,                                                                  \
            BOOST_PP_CAT(                                                       \
                BOOST_FUSION_ADAPT_STRUCT_FILLER_0(0,0)ATTRIBUTES,              \
                _END),                                                          \
            BOOST_FUSION_ADAPT_STRUCT_C)


#endif // BOOST_PP_VARIADICS

#endif

/* adapt_struct.hpp
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
*/