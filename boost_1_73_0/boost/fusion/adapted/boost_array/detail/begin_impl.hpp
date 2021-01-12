/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_BEGIN_IMPL_27122005_1117)
#define BOOST_FUSION_BEGIN_IMPL_27122005_1117

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/boost_array/array_iterator.hpp>

namespace boost { namespace fusion {

    struct boost_array_tag;

    namespace extension
    {
        template<typename T>
        struct begin_impl;

        template <>
        struct begin_impl<boost_array_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef array_iterator<Sequence, 0> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& v)
                {
                    return type(v);
                }
            };
        };
    }
}}

#endif

/* begin_impl.hpp
iPvLPPKM+s0/Z1x9CumSSRhO4Zq0+EYy4JIEM7R950wXNnnjCn2PRN2NUncRO9LyUNwdarydUne8mfzUuZslv6pkyhl4KizjxlcMrIm3iqJoyXZo4wfijn/ZZm4QjT9TomOXIL5AXfF+sbcr8f7ELLOvReZxUj7a2YTwSKST9Z2pK9wq9m+wxsqun7nm/T10pPRBeT2TJiwptccPpb66kzA8IuePT47WESuOd8ynUAu/he+8
*/