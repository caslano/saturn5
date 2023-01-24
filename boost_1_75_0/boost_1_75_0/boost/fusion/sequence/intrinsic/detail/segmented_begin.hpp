/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEGMENTED_BEGIN_HPP_INCLUDED)
#define BOOST_FUSION_SEGMENTED_BEGIN_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/detail/segmented_begin_impl.hpp>
#include <boost/fusion/iterator/segmented_iterator.hpp>
#include <boost/fusion/view/iterator_range.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/sequence/intrinsic/empty.hpp>
#include <boost/fusion/container/list/cons.hpp>

namespace boost { namespace fusion { namespace detail
{
    //auto segmented_begin( seq )
    //{
    //    return make_segmented_iterator( segmented_begin_impl( seq, nil_ ) );
    //}

    template <typename Sequence, typename Nil_ = fusion::nil_>
    struct segmented_begin
    {
        typedef
            segmented_iterator<
                typename segmented_begin_impl<Sequence, Nil_>::type
            >
        type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type call(Sequence& seq)
        {
            return type(
                segmented_begin_impl<Sequence, Nil_>::call(seq, Nil_()));
        }
    };

}}}

#endif

/* segmented_begin.hpp
MywJI91/WQHPX+5GJ0P8x9AI2+spuPOHmRX/WqqC1iXwN7/KfxHGPoDLDfFYdSdMBnUtr/oyqOJWXvW4bprLDQjo56EBqdo6FB6ZeAe0sZlifid4yc9V51f7piMM90MtLw9Eo1tdF8N8a5XY15FcAGDNQM3/5WQqt8R/Dw/fHEh2+Gp7Mn/3lfZuGzzcCA+5cbnXq3AJNeV/7UvE1qwFy6rJiai9LVs/knBSrCA/Oco0h24Vf+vCnQitstR955UnnJlOp+9W2v9U7Wu74LkkT+Z4xx4XC7mb9nsyqkTZrbJQxvaMaktIUmvcFnh+lEyyEquGS8lSw0IYZbBRDNhMXigUUMz+Y7iRSennuT/9PVVt57lJ1suvQq+rIQcHHlE9lq3ce14MVOA0ljJDcrEVeLQXdwPQpRfmz4KubllKcwnriztBoy42flCyC4Td5UxMdubXT0tkt9gsm/HqclENoRHSlb992jd89rTh7JmKs2daVfBSTEdpwXSVlq2RQ+3jREJHnYTZRC5Ml6BBZTj5IRIRbdUJyDoRT2BYflfgCX//JmemBE/mV1v7d+XeNf6EDd1N6KLEU49uVx4AQcyTFtVRxCMg7/UptPXLadCBvQbW8E3Wm7P5SPDNVRhIXG0AvH4Jcel7l+AAaIIpNNKTBsBLl2gDQJbM5AjJ4IH/+4B1GZb0p7KUxfTl+MwcJRkwUq7ndXaDb4t5nbdT
*/