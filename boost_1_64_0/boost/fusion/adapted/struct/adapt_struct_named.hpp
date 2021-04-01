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
YCBGhegSah85E19FbNwC41ZWD7mXNsq4HjvgqX8gXRvznkz7uQtEJa0M4/Hra4EKuOS63vf22xDAV2A9wNFz0KgHqAlN3fC9F5CX6L+4MlO0KYcJF9AgxMc9qgqyVMEAFyAWUkQomgCMvze3s2p0l5fUxfYrblQxRediSkYG5tYu4ye/7+jIp/J1By8U3bwMfqyd4vzvKg/9NSxpGJxIdqdb0HYlieDloQPVfZjpuUZ07gCeIfYFJLYTJ83ehJBjbUeyj3pNFsZ9Lajo6XfZlAycnKjEIfbnbZyR4ZHbn/nDHEyiYODd3NGFLFqMD31dUadM3iqlIWwlr+OjJHWPaHj1ppy792rLRgSm9Ti7vUw/o1f46XNdsBQkQNWyu+nYknxRXbTFKtT/y5x12U9yQ1XaxPgbw3hne4NNC0KbZsqQT/Oxw36jzhnvujbWrjcpscMLoSV52cczTjulParRiefHV0zUV5rLeFti4Yt/RWtCCd5Ixn8P5zQ7ex6msX3vdAP9XrKht6vxF8v2/4GWUUgI9KUns1QEAzMaoHYDB4oDNqWurAwYfSOgvg==
*/