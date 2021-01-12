/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_BEGIN_IMPL_05062005_1226)
#define FUSION_BEGIN_IMPL_05062005_1226

#include <boost/fusion/support/config.hpp>

namespace boost { namespace fusion
{
    struct iterator_range_tag;

    namespace extension
    {
        template <typename Tag>
        struct begin_impl;

        template <>
        struct begin_impl<iterator_range_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename Sequence::begin_type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& s)
                {
                    return s.first;
                }
            };
        };
    }
}}

#endif



/* begin_impl.hpp
223wMfOxPY3j9sHvh6cBSsjFrsWmtnmyk4cS+0g4gliDR8UDvR54bq/YMs2iHA1Iq767tSf2EDt1HcE2cpiHnGxQeb/C8VNhgUVR4iNreJ5O9HHf4TisfDMV1VpAMVj+YrDTZaa6/XmnbhO8QR7hSfOWYVRb+6tMIwuwoennYc0yO1VXl0hj+2dkW0OnG8K11eL1rh38UWxcvLbgCdHYUmxKwbYlk1YX2dH4Z6TdeRn2J9Cv
*/