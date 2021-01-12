/*=============================================================================
    Copyright (c) 2010-2011 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_ADAPT_ASSOC_STRUCT_NAMED_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_ADAPT_ASSOC_STRUCT_NAMED_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/struct/adapt_assoc_struct.hpp>
#include <boost/fusion/adapted/struct/detail/proxy_type.hpp>

#define BOOST_FUSION_ADAPT_ASSOC_STRUCT_NAMED_NS(                               \
    WRAPPED_TYPE, NAMESPACE_SEQ, NAME, ATTRIBUTES)                              \
                                                                                \
    BOOST_FUSION_ADAPT_STRUCT_DEFINE_PROXY_TYPE_IMPL(                           \
        WRAPPED_TYPE,(0)NAMESPACE_SEQ,NAME)                                     \
                                                                                \
    BOOST_FUSION_ADAPT_ASSOC_STRUCT_AS_VIEW(                                    \
        BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_DECLARATION((0)NAMESPACE_SEQ)NAME,  \
        ATTRIBUTES)

#define BOOST_FUSION_ADAPT_ASSOC_STRUCT_NAMED(WRAPPED_TYPE, NAME, ATTRIBUTES)   \
    BOOST_FUSION_ADAPT_ASSOC_STRUCT_NAMED_NS(                                   \
        WRAPPED_TYPE,(boost)(fusion)(adapted),NAME,ATTRIBUTES)

#endif

/* adapt_assoc_struct_named.hpp
8HK4Aw6CH8DBUI6YguXhUFgFDoNBf6wI7kt0Wb+tRDx5YTVYCdaAjWEt2BbWhpfBunA4rA/HwiYwCzaH2bCF1pOt4BrYDj4O28MRPuZReGmXvR5rN5uY5tzusVYjV1/sse5Gxn+BZ5EVdCA2IbuQI8iqtzzWZqQ6CzkJdIKbIWk0Vj/XoR6agXt1aQeoDHvQ8Obxey2/X0XW9cUt1Psxk0mnLWEe42o2Vuxno8XqdR6r/wVO
*/