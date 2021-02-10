/*=============================================================================
    Copyright (c) 2012 Nathan Ridge

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DEFINE_STRUCT_INLINE_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DEFINE_STRUCT_INLINE_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/fusion/adapted/struct/detail/define_struct_inline.hpp>

#define BOOST_FUSION_DEFINE_TPL_STRUCT_INLINE(                                  \
    TEMPLATE_PARAMS_SEQ, NAME, ATTRIBUTES)                                      \
                                                                                \
    BOOST_FUSION_DEFINE_TPL_STRUCT_INLINE_IMPL(                                 \
        TEMPLATE_PARAMS_SEQ,                                                    \
        NAME,                                                                   \
        ATTRIBUTES)

#define BOOST_FUSION_DEFINE_STRUCT_INLINE(NAME, ATTRIBUTES)                     \
    BOOST_FUSION_DEFINE_STRUCT_INLINE_IMPL(NAME, ATTRIBUTES)                    \

#endif

/* define_struct_inline.hpp
ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9QVF9XUklURURBVEEuM1VUBQABtkgkYK1WXU/jOBR9z6+46j4UUCaFYbQss2i0oZQhO6GtmnTYSpUiN3EaL0nctR1KJX78XtspUECChym0aWLfe84998P15h04+GUvx9Pu4N1XYt4JvvC6NRoL/i9N1dsGSfIA9g8N53j9AFQPnqwekn34kNUD7BmrpMU609+T5ANwc01Sf/S08TzRX/GJtWzt+3y1EWxZKNjr78PR6ekf8Ak+H34+dOGC1IyWEClaL6hYunCWmSd/FeT+3pP0mwtUASm9HYdxwSRInqs1ERTwe8lSWkuaAZGQUZkKtsAbVoMqKOSspNAfjWfB8LsL64KlRetnwxuQBW/KDApyR0HQlLI762ZFhAKeowf0nzGp0GejGK89hKegqKhk60aTIKXkQO4IK8kC4YiCQqmV/NrrpY0oMZJexlPZS7dSeIWqXkQ1QzYV2QBfKVAcGkld0PtdqHjGcn1FifDhqlmUTBbuEy0ErLMeFyBpWbbu0JRRaUOgELVquXonrJA9U/oieS012rrg1c5GlLV1lDeiRjiUBfdlHIV3oakzKsx+I8QWpVXZSP5Oyp64Z8BrZAUdP4Ig6sCCSCZduAniq9E0hht/
*/