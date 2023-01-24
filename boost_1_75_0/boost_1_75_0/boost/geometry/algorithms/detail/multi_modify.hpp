// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2017.
// Modifications copyright (c) 2017 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_MULTI_MODIFY_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_MULTI_MODIFY_HPP


#include <boost/range.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{


template <typename MultiGeometry, typename Policy>
struct multi_modify
{
    static inline void apply(MultiGeometry& multi)
    {
        typedef typename boost::range_iterator<MultiGeometry>::type iterator_type;
        for (iterator_type it = boost::begin(multi);
            it != boost::end(multi);
            ++it)
        {
            Policy::apply(*it);
        }
    }

    template <typename Strategy>
    static inline void apply(MultiGeometry& multi, Strategy const& strategy)
    {
        typedef typename boost::range_iterator<MultiGeometry>::type iterator_type;
        for (iterator_type it = boost::begin(multi);
            it != boost::end(multi);
            ++it)
        {
            Policy::apply(*it, strategy);
        }
    }
};


} // namespace detail
#endif


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_MULTI_MODIFY_HPP

/* multi_modify.hpp
rek//sTix2i0tPSeOedwu7xGWavWamv1QhzQC9RcOS7lkD1oOfEo1Mo/kNTVOWN/tXxis4s9BpnXPuEy21PWW5jq71WsfvhP4lHfsJeVcR34getC/nvdWVa6S/3SFo46VVkV1zvZ606AH9T3k1Gnu/ueBvM5auO6GjKPijqst+rA5CpHsfo8WUxXVP493cT8absubBAuAdHz0xAKfWr2mcDKE9y6DevKIfLgfdbnU2ua1sNg7aVET+LjJC4Vyg1KiRrVJuulakIZqdfgBhaxbTx3ldJjii5klDkpZZR1UHAfqhd8AIgOSD0+s89bmyRSmCPwWSkiAKQlozizA53L3Lmc25lDwpFiTwy5MntgmLyfWx+5BL9Ep2R02jX8mXQZK++oI7WR+lhjGvYbrbjCOKx+hI1L6e75nne9y2GG+hcEjgTHh98PRvwBb8ANDOJ892Zjkr5FfR4FSblle6Lrxhq66VEDqYARjrljt7YfaPpM6E23AjHkHyFUASlP4bGZefsIFi4tCdvPOMPOylTWXDyMc0ct73ceKIDD1adiAUa4Zrr43zLO14jN34ZWL5iytlAGxtHYsH+ErDVtYG422j50cTrGN6QyuUwpUxdoX+NJ2mF5BNYuuvS5LqPWfcHT5h2GfY3+I4HxwWuBiC/gyTVCGN9vDHSFK3JaIitwNFKSOzZneTgAzZnQzskbIjNxbkW0LLY72phsWyp6
*/