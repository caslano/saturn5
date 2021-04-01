
#ifndef BOOST_MPL_LIST_AUX_PUSH_FRONT_HPP_INCLUDED
#define BOOST_MPL_LIST_AUX_PUSH_FRONT_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/push_front_fwd.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/list/aux_/item.hpp>
#include <boost/mpl/list/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct push_front_impl< aux::list_tag >
{
    template< typename List, typename T > struct apply
    {
        typedef l_item<
              typename next<typename List::size>::type
            , T
            , typename List::type
            > type;
    };
};

}}

#endif // BOOST_MPL_LIST_AUX_PUSH_FRONT_HPP_INCLUDED

/* push_front.hpp
BIYF1TwAXacLTkxd0MnyeC9gm2fIb+rTXncRiVQmNdUZ6OcEogZpR937ShW7QYk61cnc5b4HLOem4Sx59Msiw4Dr1Je8SatwdFQmCzn13MRueEUD8Dd83HQYABtcoLLUF400ILDV6NC3kSzQfwXsA4yXOOv7fHIyXeY8aJDs2f6DG/vxsf3NJo3L4NOUxb/Ud+mL1XQlUMnbixa29XCVLrxAQaY8CYV4Gw3Xn9E06Vnog+YrzTJ7ddMk/FvIHsevArvTg5IElRYf9HXVSBJmUwn87+Ro7+l3sn7UcTB0woXdRb3k8eUT/Q1KngV82vg07LOtVp9w5u8bYvB5ubRdkDis0Ixa1DONCNIAJ5SkQK/rO++xHrswEwKcRo9zq6ST0CzkJEWDkk6B/KiHzSfU9e4f4p1MwWqyo7pFLvdKgssNBCljFTdjc5Xu7EVBC9wExQCxyvYqkoRjAVnkZ+xaUxgMmHCv/2ExXHQqZYONcrHWMdA+hk3qjBDiVQc3KngSMLVriBPjzjtSeg+49lHGwO5e1pPOCFDDjkW76a08sbputSziiaKCT4MWvg==
*/