/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman
    Copyright (c) 2009-2010 Hartmut Kaiser
    Copyright (c) 2010-2011 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_ADAPT_STRUCT_NAMED_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_ADAPT_STRUCT_NAMED_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/fusion/adapted/struct/detail/proxy_type.hpp>
#include <boost/preprocessor/config/config.hpp>

#ifdef BOOST_PP_VARIADICS

#   define BOOST_FUSION_ADAPT_STRUCT_NAMED_NS(                                  \
        WRAPPED_TYPE, NAMESPACE_SEQ, NAME, ...)                                 \
                                                                                \
        BOOST_FUSION_ADAPT_STRUCT_DEFINE_PROXY_TYPE_IMPL(                       \
            WRAPPED_TYPE,(0)NAMESPACE_SEQ,NAME)                                 \
                                                                                \
        BOOST_FUSION_ADAPT_STRUCT_AS_VIEW(                                      \
            BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_DECLARATION(                    \
                (0)NAMESPACE_SEQ)NAME,                                          \
            __VA_ARGS__)

#   define BOOST_FUSION_ADAPT_STRUCT_NAMED(WRAPPED_TYPE, NAME, ...)             \
        BOOST_FUSION_ADAPT_STRUCT_NAMED_NS(                                     \
            WRAPPED_TYPE,(boost)(fusion)(adapted),NAME,__VA_ARGS__)


#else // BOOST_PP_VARIADICS

#   define BOOST_FUSION_ADAPT_STRUCT_NAMED_NS(                                  \
        WRAPPED_TYPE, NAMESPACE_SEQ, NAME, ATTRIBUTES)                          \
                                                                                \
        BOOST_FUSION_ADAPT_STRUCT_DEFINE_PROXY_TYPE_IMPL(                       \
            WRAPPED_TYPE,(0)NAMESPACE_SEQ,NAME)                                 \
                                                                                \
        BOOST_FUSION_ADAPT_STRUCT_AS_VIEW(                                      \
            BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_DECLARATION(                    \
                (0)NAMESPACE_SEQ)NAME,                                          \
            ATTRIBUTES)

#   define BOOST_FUSION_ADAPT_STRUCT_NAMED(WRAPPED_TYPE, NAME, ATTRIBUTES)      \
        BOOST_FUSION_ADAPT_STRUCT_NAMED_NS(                                     \
            WRAPPED_TYPE,(boost)(fusion)(adapted),NAME,ATTRIBUTES)

#endif

#endif

/* adapt_struct_named.hpp
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
*/