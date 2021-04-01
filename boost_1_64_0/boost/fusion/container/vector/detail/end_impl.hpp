/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_END_IMPL_05042005_1142)
#define FUSION_END_IMPL_05042005_1142

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/vector_iterator.hpp>

namespace boost { namespace fusion
{
    struct vector_tag;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        template <>
        struct end_impl<vector_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename Sequence::size size;
                typedef vector_iterator<Sequence, size::value> type;

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

/* end_impl.hpp
oqJi0Dh8Bs70Gqo36RggiM/2FO5JtrNs8zHkA+LIOlYehN0mpZ2+NHY//IbJ3yiyHSpoChfnzbTve92ni/lIZ5XqR5RXP9IqfdhbtS2oiQwrKGwmT8YPPNMLaNa725f9AsQpTO2avyvI52bVzgYZTKfZbLoo/kHV58jNA7Rrj72jJPjO0MUMUziViYy5D0Dpltmfy0VXrUGMrDMj929F0HgKchFJpL2cVHg2aXwV+nojQ2cVQOshRauxqCVG//2ffMc/bXspRIcShYFRDD4wxcP5aAT3T2g7nIKP5OLCgq+B4dAmlHAzbFXuqBKKTrZGj6NIDsP2pLH8K1AcONznPbeKKPj9WjWnMp/uTyIjY20j34GJ708kk9Qcc1YIu97kAdNMIBztM0FU6B2KmGRYR1xFQT3K8DSU/kAox90FC/53fI1X2+aDaMClVNHTq83EKt9y3I6ZHKi/D2rK3be2fUK0KHTX9+zanvjYlKR2nKxaJZcxAyFZsSCp/OKdB+DhQVsk2bT9O1BNI4j8Yrm+XYLeqz3+SyBv4tn18NX884sgRxeQhZue/a6/HQ==
*/