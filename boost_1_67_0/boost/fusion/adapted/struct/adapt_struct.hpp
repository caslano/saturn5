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