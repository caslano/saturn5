/*=============================================================================
    Copyright (c) 2010-2011 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DEFINE_ASSOC_STRUCT_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DEFINE_ASSOC_STRUCT_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/struct/adapt_assoc_struct.hpp>
#include <boost/fusion/adapted/struct/detail/define_struct.hpp>
#include <boost/preprocessor/cat.hpp>

#define BOOST_FUSION_DEFINE_ASSOC_STRUCT_FILLER_0(X, Y, Z)                      \
    ((X, Y, Z)) BOOST_FUSION_DEFINE_ASSOC_STRUCT_FILLER_1
#define BOOST_FUSION_DEFINE_ASSOC_STRUCT_FILLER_1(X, Y, Z)                      \
    ((X, Y, Z)) BOOST_FUSION_DEFINE_ASSOC_STRUCT_FILLER_0
#define BOOST_FUSION_DEFINE_ASSOC_STRUCT_FILLER_0_END
#define BOOST_FUSION_DEFINE_ASSOC_STRUCT_FILLER_1_END

#define BOOST_FUSION_DEFINE_ASSOC_TPL_STRUCT(                                   \
    TEMPLATE_PARAMS_SEQ, NAMESPACE_SEQ, NAME, ATTRIBUTES)                       \
                                                                                \
    BOOST_FUSION_DEFINE_TPL_STRUCT_IMPL(                                        \
        TEMPLATE_PARAMS_SEQ,                                                    \
        (0)NAMESPACE_SEQ,                                                       \
        NAME,                                                                   \
        BOOST_PP_CAT(                                                           \
            BOOST_FUSION_DEFINE_ASSOC_STRUCT_FILLER_0(0,0,0)ATTRIBUTES,_END),   \
        3)                                                                      \
                                                                                \
    BOOST_FUSION_ADAPT_ASSOC_TPL_STRUCT(                                        \
        TEMPLATE_PARAMS_SEQ,                                                    \
        (BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_DECLARATION((0)NAMESPACE_SEQ) NAME)\
            TEMPLATE_PARAMS_SEQ,                                                \
        ATTRIBUTES)

#define BOOST_FUSION_DEFINE_ASSOC_STRUCT(NAMESPACE_SEQ, NAME, ATTRIBUTES)       \
    BOOST_FUSION_DEFINE_STRUCT_IMPL(                                            \
        (0)NAMESPACE_SEQ,                                                       \
        NAME,                                                                   \
        BOOST_PP_CAT(                                                           \
            BOOST_FUSION_DEFINE_ASSOC_STRUCT_FILLER_0(0,0,0)ATTRIBUTES,_END),   \
        3)                                                                      \
                                                                                \
    BOOST_FUSION_ADAPT_ASSOC_STRUCT(                                            \
        BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_DECLARATION((0)NAMESPACE_SEQ) NAME, \
        ATTRIBUTES)

#endif

/* define_assoc_struct.hpp
wDB6VMnaVfPP2G2ZPP9CC63tRUbiCPsm6hxAFuGz6uNpOsHvv4IIisZilO+/bfl2u9rYhFaNghRHHya+yo6wdh09Ws70/063W4wJZKOL0VSlNxjIxuJ7CqD1rZb1EYcfvnIF3xkpsoxlHJtj4MQIqiqL4EzrkappNZ5KRJJPNRH8b68Y5beFhBR8dQ2hoUnwQ6Cti8LNExE863WZbscE9rkX7JMg6ac3qHbVzSLZHNjotg6KdA55EE2TWqVrkqpd5QVlY8IRrFctv9EcY6ypTN/kXGB/bOutj2ImCrt8TL1a71Csz+mUIKTFpJk75uY1WliS+ZktNR1ZUFiMU/TWXUWNSFlhDPriJtP5rYcdPj5lwJYmOVSXjg/Rl3e6PpAIoedx6H28wN++DQC8IEl3OJh9kZGPHr0MVmneJca1inqvQ8GXkVUHhB8q+xPtx9qaw5HR1f30IvpBNbCNlkOA6Sf+RmKL6sh/rfdqcA2H5qAqpUQb+Wm6p+brkRaoPeRt5BrhbWlP057Sp2WJ468vEslEJhkofXq42CZGK/4i3V543myRt8zKgGrlog==
*/