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
tmJmCm95KXydPf+zuSGvNhfgYJV/0hyTRj8bOjpdJhGVxlGW4tXveI282MJcyt9WiXXlUvONblngaRWBn/dSgfpMmjUTEP2lC3GAmE8sCz1TxZixg21ybiim4yiLD45+fCqfeTo+nY+3etz+8rcpG0WyH4lKR7X4HtqBzhY98Hs72WiTSOCq9/zQjZn6fljBoywUyz40GFUT56KuTWmeL3426mhhtFXFQNQKnr5STPuwNFNVX+Ckpr1iDyEeiKmpsb62SJ+x91ICiNZQavN7kWar2+vfq+m4Cja+rLi99fadAttfcTFmrLmdTMv1O0Ck7+XZA0GmcQVJY2AeZzr+yQqevp0Y9mFZ9rWwgpHqDPNOj1OMdk7P/Pm81w50jvYlI5YjUONYpziytBgPle8BR5HFUY6BH77Xw+vXenjWm4+8y3YF5WNw1JHq/EyUX/Guv+ZjZNCox25Dkuclod5IgitSrB+TS3FEVX0scHU+cugvjimHi+jdYc8sry6+b3caJfg2F95e6WK6YPmd3kbQ30V5vvz+YrxEpxo5hqIuKxlfrssM34dAGeNUhtBefme3D/mcLUuWOLkMrmEigPFKZf9aGFM62fgfhBuNwKzLC6ned8HanSN67nrPHqf7QpBEZUT6ox4tpkX6EatpS7gBBaeNXr3Pxc43zJgX6qGe3u2TzPuFxyO3URv2WyLQXOv9IkaEyPCJ/kIr8izC
*/