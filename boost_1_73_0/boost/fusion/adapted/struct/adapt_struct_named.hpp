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
ShTSFhmGrEA2I3uRn5HlubiJ1P6VsCB5yGpkJ3IQiWF3QhrSB8lBViF7kZNIAt+8X4T0R/Z/ynM4gu+R8pAVyJE04t0hEuP1WLWRDoivHu0M4d2FzI8lfyAbkcrod3D2q9cnPzSgTkC2ILuQI8h24mcVZtIx42tI2sLq8Gq4AmnG73VwM2aG8TsP2Yx6L+qd8BSsXB+z6O9GvRYehCcRXyJ+Qr0fqZiIHoxpRH3M75ZIDyQN
*/