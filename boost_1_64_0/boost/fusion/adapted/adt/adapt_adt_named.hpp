/*=============================================================================
    Copyright (c) 2001-2009 Joel de Guzman
    Copyright (c) 2009-2010 Hartmut Kaiser
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ADT_ADAPT_ADT_NAMED_HPP
#define BOOST_FUSION_ADAPTED_ADT_ADAPT_ADT_NAMED_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/adt/adapt_adt.hpp>
#include <boost/fusion/adapted/struct/detail/proxy_type.hpp>

#define BOOST_FUSION_ADAPT_ADT_NAMED_NS(                                        \
    WRAPPED_TYPE, NAMESPACE_SEQ, NAME, ATTRIBUTES)                              \
                                                                                \
    BOOST_FUSION_ADAPT_STRUCT_DEFINE_PROXY_TYPE_IMPL(                           \
        WRAPPED_TYPE,(0)NAMESPACE_SEQ,NAME)                                     \
                                                                                \
    BOOST_FUSION_ADAPT_ADT_AS_VIEW(                                             \
        BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_DECLARATION((0)NAMESPACE_SEQ)NAME,  \
        ATTRIBUTES)

#define BOOST_FUSION_ADAPT_ADT_NAMED(WRAPPED_TYPE, NAME, ATTRIBUTES)            \
   BOOST_FUSION_ADAPT_ADT_NAMED_NS(                                             \
        WRAPPED_TYPE,(boost)(fusion)(adapted),NAME,ATTRIBUTES)

#endif

/* adapt_adt_named.hpp
10iTE5Fwb1yrzTa/b5a+cnEUoooOKWSpDuuMwi8JvRO88UmIbb0x4nZJAr2wKxNiyuIcFYGK4WT6/VOwd8Oc3uJaLgJ/uvcnablXX4PBwxFrCEev5GuYJGPlRDbrH/scWesFuWfhwJTCH8OOyuIFrFoA+cDRyjkNA4+0ZzWOBS7GYO1cp5YFwuUgy+Xwe0NN6d4pxVa8Je0ZfT+gC1OF+FVYzLAwSqyiQk8wsPvpxstbtIsMJRHFVbEW1x0pT/x+FrCK44TZTPDjxtWJMNzEzm0qB9ig4cVxwB2g4yGlXvN5O7a6Z+rUpxcWLxQs6xuOGCH8rf6McxA3Kh8UtXxGA4TqEwTnsZe4Upd37+UrRE0uG6PffswTEyV0ocsfKvq11dz5829G/x7RwCdrc0maObqoe+RVrJpgXIQaSPPQ6N6J5TzWMMwHxjxnxrSibjFE1roLNO0qoNF3pjOigGRPsP9tJoU2yUY2YuBs10cP02/oly7B3q/G7HCNe7PCU5UFxMaWPp08SNqR8rDRlnUjl/B/BGW5mFmLPsLRQVgk0VhxJxg5gj1bWH4s8g==
*/