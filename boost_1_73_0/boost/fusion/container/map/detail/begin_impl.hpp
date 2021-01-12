/*=============================================================================
    Copyright (c) 2005-2013 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_MAP_BEGIN_IMPL_02042013_0857)
#define BOOST_FUSION_MAP_BEGIN_IMPL_02042013_0857

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/map/map_iterator.hpp>

namespace boost { namespace fusion
{
    struct map_tag;

    namespace extension
    {
        template<typename T>
        struct begin_impl;

        template<>
        struct begin_impl<map_tag>
        {
            template<typename Sequence>
            struct apply
            {
                typedef map_iterator<Sequence, 0> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Sequence& seq)
                {
                    return type(seq);
                }
            };
        };
    }
}}

#endif

/* begin_impl.hpp
VmtmhnJCx4YGh47hdyCUy/MxEGxBD3nQHw4lMZqV7TwYQx2CDcIMvZpn393Ec48+++6FmNh0mPWNx0o6brZm1ErrxIKprrpRLH4G8k2eq27YxG2U1YS/aHs+yZTj4XJ+FmsO/OoWCbMGec21PMq/yPUC8VPAky7XjMeMFDfWsePamb516f8mr378/0R6E9Ico/0y9fjuQ86e5dLdTzC6vSXHL5BrItwGf+t883mUk9L8yRRi
*/