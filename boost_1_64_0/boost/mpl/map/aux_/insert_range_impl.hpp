
#ifndef BOOST_MPL_MAP_AUX_INSERT_RANGE_IMPL_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_INSERT_RANGE_IMPL_HPP_INCLUDED

// Copyright Bruno Dutra 2015
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/insert_range_fwd.hpp>
#include <boost/mpl/map/aux_/tag.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/insert.hpp>

namespace boost { namespace mpl {

template<>
struct insert_range_impl< aux::map_tag >
{
    template<
          typename Sequence
        , typename /*Pos*/
        , typename Range
        >
    struct apply
        : fold<Range, Sequence, insert<_1, _2> >
    {
    };
};

}}

#endif // BOOST_MPL_MAP_AUX_INSERT_RANGE_IMPL_HPP_INCLUDED

/* insert_range_impl.hpp
40rxQIVyGi0lyAvBXdZaoqnSMyvjXo9iC6UYVXYYV60fOD1WlfL+yQJC4OozKvoZz6ts32HtA+cR5cVUseU4/DoclrQMbqwLcR2XtX9b66UeGnYnY1AO+/xtvvpE11UWdkXZqYDEXMllTTAox3csl+UZNVP2wu0WcNUApdzIiEEQIUOnGJjAhdFgxM/Lmm4hkjhh453RRdh6WApiTsFERfiKH6rGWxTWusshR79wDAq2bxrkCR6S8t5/qn3QLwSEEr1gzzWrlz8W+qUeoj151g2VkqCA2Mp0ejSIpS/Kz83E2UjFAsqoNHjFk+0cx3xylLXQ+Ap60Daj5ISsk/9j0pLMpStzdxR1R97lTuB10kGXYZET6rZpeK/lXRo3od9fRL3DQ83gcXGGtYmx1oVonxFdKBScZ9eOpJV5VaX5W35PoV/B6sThLEEPIealU28OhOQp/ufcTC+LPcpI8hR5UeKmsr/6FN4/35JloQlcP5A/04ReytLD2DX2Z34yfsacH7dunAgsYuK5uxCPGkF7FfyxisfbmuU5gIDVwDxqLS9ftDLTA1t7F2aHJA==
*/