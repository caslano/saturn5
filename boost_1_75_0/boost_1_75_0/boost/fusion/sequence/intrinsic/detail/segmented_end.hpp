/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEGMENTED_END_HPP_INCLUDED)
#define BOOST_FUSION_SEGMENTED_END_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/detail/segmented_end_impl.hpp>
#include <boost/fusion/iterator/segmented_iterator.hpp>
#include <boost/fusion/container/list/cons.hpp>

namespace boost { namespace fusion { namespace detail
{
    //auto segmented_end( seq )
    //{
    //    return make_segmented_iterator( segmented_end_impl( seq ) );
    //}

    template <typename Sequence, typename Nil_ = fusion::nil_>
    struct segmented_end
    {
        typedef
            segmented_iterator<
                typename segmented_end_impl<Sequence, Nil_>::type
            >
        type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type call(Sequence & seq)
        {
            return type(
                segmented_end_impl<Sequence, Nil_>::call(seq, Nil_()));
        }
    };

}}}

#endif

/* segmented_end.hpp
CxLC5M3/4tj0S0vFBd+YGr3yH02gfopbLfTY/7OHwdckAwOfpx7DdtaZq9S+Dwq4rz2Rfq+52Gw6S/tqw7n9vdW+01p9LMnLcMIJp5fCyELlZFwR+ZzRflwZYDw2NXquBMTyPakeVsUm2DC1OZ7fVq6/8gwpsYnoo4JR6VJX4HadSZdFOffwlHpG1em86vRzVV1AVf8r69xVp/Oq5WW5iMGtj+L8xLEZ+WgrbLQms87VZDo1ef+FNcmr5vEDoOaJWWyELeiCKsa0rv/OVKzMLrEvUCQpiTiSOqw3i6ply9IR+uMPESYryBDwCF2jPheeyq9X4/V9/PoFur6PrjF0R7j4vo7oKJ2vs6coj/a/IDrKy/Bh+OgkahJTs4a/49fFeH2AXxfgdehhusZ5IfwRvy7E67f59VS65uVR5wi/zK8r8frp2PofjJY58GBH6M06F3olhN6Kfv8/sekUZch5qjbYlDBIiOmJd34X7blnOdFL6Pp3rbAs4KBMPRcoUwiUP/c9NygFOijUTPpD/9MomaKMOE8zHOOCIq3Sjbmk23pLlL/sJFdl8l3kDPCPVwEGxuH524PGNeiDqeH5re7TwlNb3aeHH7o32mXK23RN42c8f56F19K90ecv3R9lqswHO8L9nNQuJAkxKvMCqU1NfvZAlNfFP9I1Castr0SH9RslHYFy3iFrUz7N+G/k4416M0XGwHEVSBjiWZK9
*/