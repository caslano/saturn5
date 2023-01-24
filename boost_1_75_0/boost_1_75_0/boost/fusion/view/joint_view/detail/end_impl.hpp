/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_END_IMPL_07162005_0128)
#define FUSION_END_IMPL_07162005_0128

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/mpl/if.hpp>

namespace boost { namespace fusion
{
    struct joint_view_tag;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        template <>
        struct end_impl<joint_view_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename Sequence::concat_last_type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& s)
                {
                    return s.concat_last();
                }
            };
        };
    }
}}

#endif

/* end_impl.hpp
WLQJx2sg25040XzSNPjqW36PwJf/eYiU1S4Kv8PZQe4nMjzbTXyLUtO5PIz7voNAKa0K6VdU8KUYZoavqjbVp0C9JM0mxvTGdiBoRZ+sd4QvHvR01ziM9z1BL8856MuuFvUSqZ7sYtgz2V2p+FBZ5yOz8674MxHeCtyPbmQKCXZl+iDBiaclgxTs2414n3QNFcg0nbSw5xJhLVlkLjEHEY3FxkdekyXACAOmyQBmSHJ4srGxuBcsahG1n2C4A79B91IqSCByQiDgo3/i/pmxy44uRo75x3pxoBVkdgW8rKXS1ojxLq3j0/I3SBFEbitEEBtqo72cixXnDRoGsB9sf2NOyUbv6QF33pQnzrR5dbENLbzbwtHy0g36jqOn5QCV7Yw+PhiMRd0WxaOmJYnciLD0i2MZU4tdvFPpd3GkR/ZlKE3DsyOP6Pbypd5wKW5dQviKDNRnJnB48AHvz1Cy4yEmDDBWjUUfSSUr2w/9xN/EkhmNDIW/0xStnAthejAaY45RRilQU3QGwzbi+8CyB/QXPRCjgti7zcZv5DU0x+VjtNp8q4zvhRmFEO2/aX3my0nzAWOZC9u2VvML3iJXq6JTW/EI5l1un0egX/ONO1DFr8YzzEdtaAwpHMMetsJtcZwpdvbD3d4f9ZDjOfFHIqhivIVfKAZ5QrxPHC2Lxzs2BzxPhp99wyc+VPPb0J6PpHzwn3rrrhxr9nCs
*/