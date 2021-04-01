/*=============================================================================
    Copyright (c) 2009 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_NVIEW_DISTANCE_IMPL_SEP_23_2009_0328PM)
#define BOOST_FUSION_NVIEW_DISTANCE_IMPL_SEP_23_2009_0328PM

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/distance.hpp>

namespace boost { namespace fusion 
{
    struct nview_iterator_tag;

    namespace extension
    {
        template<typename Tag>
        struct distance_impl;

        template<>
        struct distance_impl<nview_iterator_tag>
        {
            template<typename First, typename Last>
            struct apply
              : result_of::distance<typename First::first_type, typename Last::first_type>
            {
                typedef typename result_of::distance<
                    typename First::first_type, typename Last::first_type
                >::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(First const& /*first*/, Last const& /*last*/)
                {
                    return type();
                }
            };
        };
    }

}}

#endif

/* distance_impl.hpp
H/aULLk9T4WeFn+FGnP1fq+WP2i1aqG0LgtncgSr0ExZxMkpfWwwAzl/OMY+Y5TFvQak702XV6Tgu4CDnsyGpH6Lf+BWg94DHVZ8JWG4+5Lok+jJK1jTwu1BlFLIOlgl3lhhKIoR4blOOlh7PZ4JMWeTLag/y9mYsd3vl2ql7G8QNudlEJxKQOYfg/70xpYO0RdO35MV6jlfFfLWwy+u04pHdsPpKvDZnTWrfn7JZg4jC4Qyey728hPCWC1ZvGxgje7+f3dwPH6oiJayLB4tYgebxqnMj3u2p9DxALSr34lGrA8tJRXh47VJQrrq+nUfSYNFCnm0ABm/TC6uGyjEfmbRx04L8SGbFnIMcCl66ON4IVW3kdJVmY8BZILg0RSe9mnMrIcAhHDIo8xzd8wYfbsmz4z2evVGOmS5+T41ixVFs+zVPtp1dp49Vo/3D7ZRdj2n9IAXJ1ASO1Wy4hrCLl+o0A1+rVvajaX5jImbGRzQ/3THeagAi2b0x0J8FChqdJ5RHuM1SUqxBKf4VQN1kCKCEGcDjTnu9Q5fDpNg+D55cPAEZil4kdj6JQ==
*/