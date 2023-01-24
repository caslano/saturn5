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
erzguNs3yCY5nNWaRjtBpzxGGe1yARsnDxiTo12uxdVzOhto8dZd4q2FMNphEu+RZULrsiPN8KgrYthAZDHGR+uYWI061GyWdjE8HJJANZevyNitajuHWI2oiwjohHTu1pbS/dubNAS+0FkalcLOZEw8fM2Dq/HGV8f9mIvvfjtgr2w27uTH/cXVGC+elhuPfwXDo4UvR4v6sNKAGD8MtjdaYAaXW8Tjf8KVGWcobvfbJ76HA+Kej3FAHPKknHE+EGHOOKe3MGec4/4UnDBagV7yPS11H3acb9p9+1jH+ZbZT7hFJmXpc53EI5Jmf32A2c9hs/9otOhPQbzQF6aXrCjQaS8gP6KHv8ZJB6jZD6BHo2G0jULrchfdHsu3t/Jtikpeb+z+ogX+dsrfb9JvcvBrhokSN5FTG5mRS4le849lS9wG35zhuybiY3Sr8zuaRcaKGf4aSFMEzx87ZkevQtgBvfXNOI1C9NJBwsnD37jy6xZA8qZ70bgtT2qlGbdcGKX5q8jDwT5QPMjAybXP8WQufcfYi6JE3+9wEdSlsagVHK3nXyNK+HOQTDmQCVXJxChk7mMylwsy3HfLf7fz4JhDq3iMDPxsC42EOLWC0FNrGPzpUhzb9tLlO7pspMsauoy+wlzLy7yBYpbWDMe5J0rMca4c75xGecyOVKZow0MVibyOJPKvd1EiKz9EiVz3uOyHnWGmREZHmhJZ
*/