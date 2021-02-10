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
k/542h8NHR+rNYj79nMQj03GHACLbaWtCLeJXcGFZZ5qlqVFhSogYShkxFA6EhHHli0nS4qlqDHLysIrFxBixswpqIyGLGYPa5Y6iKIyAB/1lw0Dp3A3pq8yalBCzJdEh0krZTdb0XU/wTKCcbF0zgwF0jeqhpISpTe6jMvqG6wN13EO19iDYoLGobPKDMBiVsA0XtzIJOk2estSvE1duqRck6LNYD9wjJWZFLcMw4U+lCBWfMsR5zw0tDBfP7T5eGjDNTs+H3ZNZHYcgCA9mEtGY4NHiigvxKA5BqNaI4Y7iEWaipXqOO7Ed9z+GGr72Lc9f9qb9P3TmhP8GusMGxy9Iwa5G4plW4klbaMfk3YQH+67+k4brfUYK5OgS3G9pyCWZa+RQmhnk9ANF0Y8RUtWGH6FbmLqRpXNFYFgiFdY7mUM1L3EANNJ+AJrftLbgv0TwX447/nGejjzJoj4Q06VNXRJ5E3hRpN3fA11NCLUqFxw2oAwIRKXVKKjfmhllggt/nS/ZHSBtu5iuEIMhxOve9qbQu/TeNLzfURTc0wipzTWGAQS3lDTB3B+Admsy462GTf/7iA3LbzykJ1cDhdFJWBiLSlOUJNO/DvyeiRMHvmADSZSVSYV47oiMvoqb91z1D0/4djAeJQ+
*/