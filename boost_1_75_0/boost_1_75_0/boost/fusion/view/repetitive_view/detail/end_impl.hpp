/*=============================================================================
    Copyright (c) 2007 Tobias Schwinger

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_REPETITIVE_VIEW_END_IMPL_HPP_INCLUDED)
#define BOOST_FUSION_REPETITIVE_VIEW_END_IMPL_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/view/repetitive_view/repetitive_view_fwd.hpp>

namespace boost { namespace fusion
{
    struct repetitive_view_tag;

    template <typename Sequence, typename Pos>
    struct repetitive_view_iterator;

    namespace extension
    {
        template<typename Tag>
        struct end_impl;

        template<>
        struct end_impl<repetitive_view_tag>
        {
            template<typename View>
            struct apply
            {
                typedef typename View::sequence_type sequence_type;

                typedef repetitive_view_iterator<sequence_type,
                    typename result_of::end<sequence_type>::type > type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(View const& v)
                {
                    return type(v.seq,end(v.seq));
                }
            };
        };

    }

}}

#endif


/* end_impl.hpp
yOn4f/WKSKx7qDg2Na8vYqXvIoLEpUocJlyMCBrJk6yUD8Leh1wqQt7gcrwwxU7M7gXYRZcjP6TKVDogv0aCAy9wRfGj0p/xL2DHyNOfi3T97ua1uX38duAYOZuyEcfgBsXaaTcLyqIy7hEVa+4iZUM/OgK5aooe1u268dm2S7LeSefNZzSWMp0LPe7ffTTGwozg5HcYts7ya3CnbpS0skIJ3YSBKeUx+ewEJzXJ6JkTbgfTT3aVFxIKylwPCqt+XrYLsidN6PiFLnVZ6Rm7wyY64h9lDAMNV/9aNOKLDBZKQEpzeTqxNvvgf2H3zo37PCK4fPCMH0vtnleT96uX7DXoxF5YitSXyDPZ7z/yrztCZv0lFi0HGBadunb9vgGmKie9/mJWXvBfC+zd1r1rOHNdU/ki9O3iXTuzvT5cVgDqR1/XsDxj5JR0+TwdphR3ZY+4ey0K9+4XswinenVMs+CmEk6J7u4998xQ5TL7XPvpHYWK8bPbZs5aHM8fz354uzPxzInpA5Seh6Y2Fc4mdUuzrlyRWdanq9CrI7DPh36bKUiVH3vd/sNP61U/Yh8+XkrphNVuG5XS1GhSrMjlIu/BoXzIk55W36oB9f33tu48OLAEf1AFfnNy8fYtkPhqG4+s384bEc/cqkVU4PTHQile+gt3l+E6jsMCQeo12JnRF5GjKFFrWGOUZYTGC9H+nkbHT46qlruTPRUZ
*/