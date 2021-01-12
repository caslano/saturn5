/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_VIEW_REVERSE_VIEW_DETAIL_AT_IMPL_HPP
#define BOOST_FUSION_VIEW_REVERSE_VIEW_DETAIL_AT_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/int.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct at_impl;

    template <>
    struct at_impl<reverse_view_tag>
    {
        template <typename Seq, typename N>
        struct apply
        {
            typedef mpl::minus<typename Seq::size, mpl::int_<1>, N> real_n;

            typedef typename
                result_of::at<typename Seq::seq_type, real_n>::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Seq& seq)
            {
                return fusion::at<real_n>(seq.seq);
            }
        };
    };
}}}

#endif

/* at_impl.hpp
wXzfj+C8ewM4LPGCvWfawMSU5oLR0tv/Ik9lWCkPfw4erxL28rwrcVySQbia82CjiPTw1zWOwXZthSejlPn7tnwPR+rBRc3DelWaWY1b1rgnA8fbaImZYpi5mfakkDb+nz+Q4lUx1t/iWu0ZEhyGK9Ox6+pv29pvDs5p4XSEp88hgoa8MVqFQ2xVWZ/SgiCDuWSLye0MJyXgHcRKujowxzHbhZwSB3eKA7kj5VyqxRwocMhQ
*/