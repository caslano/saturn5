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
Sau5SX+Eh6Xevv8zsy9IniYBDJ7G0stK8izrnp6Y7QUkSyRQ2ODiNQinhD4iBISgjLLfxHwviJY72ry7f7NEkyLQBBItUs/S5HO7LDzXV99a/4FQl12P+UFAmEgmd+RMU/kvM60+uzSP83bdWA2+Qjqm2OGO1JN15Jxkyrtpvm2RcXFIgnhe68+ietjE/fu4TmfhnE0jNdo6nUmhFWkJFp7w1UXM6rMN3Jp88FJA3iCbIRuWiAejiYATZ/ZdLdj3RRGSsx1jlhUS4iFTKqC7nNk8PYvsYpUB6C/BaatrAouyEd0bklcdF0M7qlDzAuHMnzX1lS3uoN0YuvkTOv5xIrgPHQ2hfNyvrT7bVgKNg4FNVADNomdm0Sx72BQwSXiEQNrrzkdvQz38DQwAlEC9DpbjS509OyP9qoudjsDiMAMtQmEvPGO4FMTXMohUADUty11XfY1KmGW6K4rk0eMy7tjwWr6RKcKYEfLVvwY7/MhEhHOlkn8kKJIhEhFaBqwBOe3XIv7ATDSnd1zo4PxzLE5pb53tMD0lN9SorDAL1rBoWZWgKqOYz+FeZg==
*/