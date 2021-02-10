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
fQoc4m21XLKEFqMXhm5aNprY1qWsHxliWbeOik41SIdlQbtcYuFd6JqcK2tvC7Fj2VbZlvyFlj3EnoNsMCoY+DFM4gGsmBbahS+T5CJcJPDFjyJ/llxBeA7+7Grr79NkdobaEMiqgN+2imuMQoGo20rw/BH5D510x0suYLyIpuE8SS+D6DSMAziCweEv8GfXkKzfDmBQiRX1Hd55R++8AzygfylnepNqbqjD+EUxafQXX8DM/xw4T50u32A7DdxwtZKakwg4Vmoki8Ji4qtZOI8nsfOTaLKqw5cnRNLrrfzgWH8ZgZ5yD+kN7JeohAoF8YTXhUo218iERHvvLdVZEI+jyTyZhDMnxpCo1ctiYk2WxZxmhdXckCIkHNJPzb5ya4aFUExtqN1theJm6J3mytmlJZpCqppRMYCtZGdAGOwkStOeaRKHnUEk7CNGRg8uOTrFESm6CtCBsyv4dg5aJY3MZIXbYNVdXwtMiHRvZasNPuJJP8jPxOGsRVXBimP5GzuK2iBMuaQvygmFy1ltm7NGAVJkuxrGyVkQRcOjPQrScWikS6byagMciWDNyKEdBQTjfsI48y6zydt5p41k2VlVS02bb8022uIci1uXvLFWNrGR4q3EPYVucOvUGikT2e+ia7s3KxvwQzWY
*/