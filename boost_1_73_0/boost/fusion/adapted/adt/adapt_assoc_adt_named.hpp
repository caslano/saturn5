/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ADT_ADAPT_ASSOC_ADT_NAMED_HPP
#define BOOST_FUSION_ADAPTED_ADT_ADAPT_ASSOC_ADT_NAMED_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/adt/adapt_assoc_adt.hpp>
#include <boost/fusion/adapted/struct/detail/proxy_type.hpp>

#define BOOST_FUSION_ADAPT_ASSOC_ADT_NAMED_NS(                                  \
    WRAPPED_TYPE, NAMESPACE_SEQ, NAME, ATTRIBUTES)                              \
                                                                                \
    BOOST_FUSION_ADAPT_STRUCT_DEFINE_PROXY_TYPE_IMPL(                           \
        WRAPPED_TYPE,(0)NAMESPACE_SEQ,NAME)                                     \
                                                                                \
    BOOST_FUSION_ADAPT_ASSOC_ADT_AS_VIEW(                                       \
        BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_DECLARATION((0)NAMESPACE_SEQ)NAME,  \
        ATTRIBUTES)

#define BOOST_FUSION_ADAPT_ASSOC_ADT_NAMED(WRAPPED_TYPE, NAME, ATTRIBUTES)      \
    BOOST_FUSION_ADAPT_ASSOC_ADT_NAMED_NS(                                      \
        WRAPPED_TYPE,(boost)(fusion)(adapted),NAME,ATTRIBUTES)

#endif

/* adapt_assoc_adt_named.hpp
vIkUfvvvmwMasP5z3/+H/5a9/7IZN2qXQ1wQn6wGqyirKisoK6m08tDfTZrvFb1+frC0ECf5hXPnzFnAZWXOQAenn0j78tonaDnk1DVgPTgWv9c0qelXpUOoqKCKjsSh1XSHVf5i/5Y87X/bLfYvCTcjBhvy3YDc4E/2kQmvWvXCC818/c9byZg6++i1YNeeet59sE20n9n0F5YWFXELnDLz+e+osZN4PPuqzwsn6hyDqNuZ
*/