// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2014-2015 Samuel Debionne, Grenoble, France.

// This file was modified by Oracle on 2015-2018.
// Modifications copyright (c) 2015-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_EXPAND_POINT_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_EXPAND_POINT_HPP


#include <boost/geometry/algorithms/dispatch/expand.hpp>

#include <boost/geometry/core/tags.hpp>

// For backward compatibility
#include <boost/geometry/strategies/cartesian/expand_point.hpp>
#include <boost/geometry/strategies/spherical/expand_point.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


// Box + point -> new box containing also point
template
<
    typename BoxOut, typename Point
>
struct expand
    <
        BoxOut, Point,
        box_tag, point_tag
    >
{
    template <typename Strategy>
    static inline void apply(BoxOut& box,
                             Point const& point,
                             Strategy const& )
    {
        Strategy::apply(box, point);
    }
};



} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_EXPAND_POINT_HPP

/* point.hpp
1Gkc+4aRm7tB38ZMTcSNio3IO37iKtVXNLrYpZkyrUhPxQchRZeoJCRXKPrXtpp7MKVQL5GlNDcYBDSGCWw5wuJwutrFfNjO2koi8W+W4zkvMWlUvaSYLzlFZUHqAayvSGm8Ie10qATi6yaXb+4TqDyGb3EP923Nwk961GQPNF3e5H5V3S+pisK9drZ9CgxUyzIclyUsxXKF2IHYhvd4/pk+TEGNyEHUh0IVHV8+Vf7Nmn+9bPeUrwulioOPDcd3DDxXMk579fvu02cwfKHdaZYrX/V7IJHlT1itgU62RsZF/9V7Nqn3YnDcUoMLFdGHyNmeLfXoDHwtvRVV+pPc1ij2LQqidSnoKZqJrwUoFUPKlrIICYHRGvuzaf6PNbma6l2sm4/6qzdb0Z6FWmeaHw3SLA7WLV+BpQxQtnU08CfZXdoPho3ne2pL9Chtv3NSaIvM1Gw2nzdXecV8Wyh4j5f+8Y2yTk44lJJ719m/w729R9bRQT4xG86r6wnaxJ5JF1BP3rNeI5cjTOLHIsOpaaTeOeT/jRk9lcieROSdUPWssdLETEbK/24ppw==
*/