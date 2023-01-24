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
NxQj0wo96IgztwOL1cAGHcDKPLVdO+7YhJ1fuxa5t3uvYeXVRImYgterQ9AYewSR/vc/4Dt3kDKdgMiKWZnoAQgxVibW6/Q8C5YtVHMzdpibsYM1I9fWB9jqyRdRDltbb35rFru3m/104NGYJUtNf3bglTbWh0qNk1gdltVhFp42BKO8/HWzDB3pA9AdUr898wBZW1fI5cporPq0HdiR5bwrxfu6r9K/KpgdCmf5QhvDedm5EV92qz8nGA75sub5fRmLhdzqvMn553DuXYK0lBzd4hbFflVzxd0xMkPm5EcjVDXncqU5ReRsIGuhhJy5TBfhng28WAAu/wDBpX4O2Ym0dUP5829zelCO2AaXvZ+5Uc4sDLE2chEehMtwcsl+UIf1EFKwo8rF7VfTgD+jmGIHU+neV/tsHZcGInsgPD07YZfbnmts2xZTu9z9s612udNF52FhjlgDvFpMiOBK+JjGz6YlsOedfbDnP5/NbT4CLQGU9NNMNPynDEsn5adWw84rydpxmFWui/OxkEpsYUtFb4JvG/hsdNVPOdbNLIicgvAxhDDTERRzy3Mu9xlLCFs02k2yPUdHvkw5NiaT8XMTiWP/XB9tdMpu05vt45IxCmX91ShU53/ne9DLjslJWFwoZchNSo16HqYXn3OVqx3k2Dnucm+tb6I/J+N8MAu60Rdkl0aOSE5xKWok/YfsvujIUBkaP8uUBjIf
*/