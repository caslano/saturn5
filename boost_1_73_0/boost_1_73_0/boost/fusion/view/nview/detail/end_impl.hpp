/*=============================================================================
    Copyright (c) 2009 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_NVIEW_END_IMPL_SEP_24_2009_0140PM)
#define BOOST_FUSION_NVIEW_END_IMPL_SEP_24_2009_0140PM

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>

namespace boost { namespace fusion
{
    struct nview_tag;

    template <typename Sequence, typename Pos>
    struct nview_iterator;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        // Unary Version
        template <>
        struct end_impl<nview_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename Sequence::index_type index_type;

                typedef nview_iterator<Sequence,
                    typename result_of::end<index_type>::type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Sequence& s)
                {
                    return type(s);
                }
            };
        };
    }

}}

#endif



/* end_impl.hpp
1h9E/AOz3sPfJiYnZDPlD6tNmqf8QVp8iiW5vMLvltXE6D3Khv87wZnvLfwKLTANZ/aD8DFy71YxafXb5Oz77/9BjsmL0xdnHTKwfZd6xIipP6fRXYe8cnjLP1f2p09dRi87hMbE9rqSlLlyGWHBMn6wI0rgu+cuqM+oQ2xGHMoWkTuHB9cn8YqSpetR0tcnt8Pxmw55WLmLFRJ5DBLCVkHiOWRl31MS0QV17wWN0I5iEixhOhB3XBYDwSR2A78LvCmJabRmSAPZ2x4LiH1vu549B0Z2TFZxHLLzk5NFEnkg/YkTLNjJQi2/u4rX6UpuQYi1/UiCMCZxQBJGOwRHdsg6cNwl/gWFQGOYzD2XrTobaYCV75wEEWHU85AWzHMpE2JTYkj1dHAYCUFiN8Y/LPAZsnpYBevcQNAjUlkmkQ+MQA8wyAlAzR2S+A6N+GC+csVC6pQruHJrNvI6JPBBGHLYM8jQOCRzm7msQ34emm/1mUl+7k2nvbF5S/Qr0hvfIrHr4XgAW+8Cs4jQT2FEGTCPiLsOPZc6kufTfU4ODr5x/YWXOJQc4u5ZjMZJ2F0dZjpeYYfY29VldgK0OHZs4+hN4x2NXX8Z5Ekc3sceO8H/5QcvAt8Hv4dGcgIOgwLAfNmKZFptAkJuJoRR
*/