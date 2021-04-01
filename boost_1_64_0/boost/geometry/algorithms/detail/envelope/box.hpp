// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2015-2018.
// Modifications copyright (c) 2015-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_BOX_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_BOX_HPP


#include <boost/geometry/core/tags.hpp>

// For backward compatibility
#include <boost/geometry/strategies/cartesian/envelope_box.hpp>
#include <boost/geometry/strategies/spherical/envelope_box.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename Box>
struct envelope<Box, box_tag>
{
    template<typename BoxIn, typename BoxOut, typename Strategy>
    static inline void apply(BoxIn const& box_in, BoxOut& mbr, Strategy const& )
    {
        Strategy::apply(box_in, mbr);
    }
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_BOX_HPP

/* box.hpp
mgTwynHFA+mHG64KqLZdJVscaBlZRHK+SajCl5kgmcedc3XRxEo6UBODQn2hE4L6cD4xKyoIQ9lje9L/OaUUiP/czGbmC1Rp/PCQNQ7Sgg15UoSYkIUZTznrwEUrsfCMZs2LoLLMfqQCzSN7Q+r2xSm1ZJO00tUa2pDFSazFBqKT62sF54xKybczN86oTvkzI8uB97eqot0WUN1giiRqRE5bR72VfG/t0W1dfx+ZryP5Pdp3pk8MitE584Uq8X+nJJ9qsLqvmVZiQTF5buW1MfibHZpOaXaniaXEv9U/wf3WwoHUd8UK21S87brwMdw62XXirD7BZ1tgFh+l3wQ151wq5NJ0+WadZb8/WDn+HcFbctdoZJ+QG18eIMXS/MMnWeAQ6bUJQ53W8z7EF0bSNUv5A2jjxfQbiI8U9GW/80r9lnirEMLHQKLYFULyI8xegqtlT4Pb35+YiFX4b27nCHIER6z8JZx2VU5tMC2NsJIDwberDMOOHLc1E9eTWHJXVPcLiJ4ZQCBpWsI4Edj5cJL1+66uHFlJpdLtAoGO+GLY88crRSheI5yRig==
*/