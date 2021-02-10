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
hnq3AQdv3ryGFrx4fvC6CUeEM5qCrymfU7lowtvI7vyVkLs7V9F3TaAaSOruCJwmTIESsV4RSQHfUxZSrmgEREFEVSjZHBeMg04oxCyl0B2NL/vD901YJSxMSjlrkYNKRJ5GkJBbCpKGlN0WYjIiNYgYJaD8iCmNMnPNBHdRPQVN5VKVYgwIkioB5JawlMxRHdGQaJ2pTrsd5jJFS9qRCFU7rFzhJnr5wKpLRLMkaxCZBi0gV7QJhr4JSxGx2DzRRbiZ5fOUqaS5hYUKedQWEhRN01IcsjKqChMo+KW3moYSMkTPtHkowZXRtkrEcocQ3VoKinPJUR26BekigY5vQs4jKi29dUSlpfSydfkPQrbFHoHgiApqng99vwZzophqwkV/ejI6n8KFN5l4w+kljI7BG16W8k77wyPMDYZaJdC7TFKFKCSwZZYyGu0o/6mV7rjTE+ieTwaj8XR20R8cdb3J0Zk37Z7AS6gd/A5/59wk9281qKVsbqIPr9yXr9znuGFWM0rUeqaoNnHGC1NKoVT/BIbeWc95XHTQAsptZkUMs1QLuYYVS6OQSAyLJFzFGEsrxb8cjsZ+33d+YTxM84jCW6O2yMPknWM1hAL3H6Kpmy+wn2CGpJgojyJpQir4AiMm4rjxh1V41PO7
*/