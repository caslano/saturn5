// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2015 Adam Wulkiewicz, Lodz, Poland

// This file was modified by Oracle on 2013, 2014, 2015, 2017, 2018.
// Modifications copyright (c) 2013-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_POINT_POINT_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_POINT_POINT_HPP

#include <cstddef>

#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/dispatch/disjoint.hpp>

// For backward compatibility
#include <boost/geometry/strategies/disjoint.hpp>
#include <boost/geometry/strategies/cartesian/point_in_point.hpp>
#include <boost/geometry/strategies/spherical/point_in_point.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace disjoint
{


/*!
    \brief Internal utility function to detect of points are disjoint
    \note To avoid circular references
 */
template <typename Point1, typename Point2, typename Strategy>
inline bool disjoint_point_point(Point1 const& point1, Point2 const& point2,
                                 Strategy const& )
{
    return ! Strategy::apply(point1, point2);
}


}} // namespace detail::disjoint
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename Point1, typename Point2, std::size_t DimensionCount>
struct disjoint<Point1, Point2, DimensionCount, point_tag, point_tag, false>
{
    template <typename Strategy>
    static inline bool apply(Point1 const& point1, Point2 const& point2,
                             Strategy const& )
    {
        return ! Strategy::apply(point1, point2);
    }
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_POINT_POINT_HPP

/* point_point.hpp
p/ku0u9chSvgmt9lkzfsWV7cVJODj32ud+8jL+RZh6G0voF6pGH66Pb6bTZ9t4j+NqGp0RlX4LZXwY4Ph9OZrMn2c66v2G3Uo/iOfJv+M38lntEGP76vAaP09sWOiZ2FYpvd62ej2+OETarJzRx80jSkx+XDZdyj8xOb6v1b0dGXDpE/amTWO8TCFHqvuQ/pCpca819e3NS6cyU8bjIeNPdu+DFGPLThV/rSRGOeONQc0+Q+u2R/hyYhZ5dcGqXf+/GxPvAYLWWMGCnAlrVg4BL9ToM8bCUOZ8rJLLSpD5bB08fM+2x2u52WWNo5jjuf8943AM+b79jGIdTKZT+vHCuyAK5Haie8+E7e7NplXn+g+/aF8SfUX7Gz01hnGWMv/n31LppbHbH2IQw5CjKS9FPvqI+rcS01rhk8f4em8upaa8F63yKf07L83Sbeq3fAObs616NBH+DzXe4/cb4KK1xLL14qP+zCP7tcS6O7SE2EdQ9+ZL803tK3rFyHz8vl8i+wZbp6csla46Djz+PbFtfx3T58P08in/FvtTPRF15ZDVdvYl3sLfVWf7y+Nq4mhnp14u99Yh9mvq+G3Jnq93rzEfLm8xj/JOv3XftsXHaOWpRvsjo2HV5dr55swhXlxGrnq3SvPsZxFfUkx8Xpu8tp1HSofIlar56WFb9ntMOdhtOm/PuC+BxIl0/tZey04ba36EUvw10HwyJaRQ65N2AZPAWonw+AVeeKXbZerjdr3h8vC3hJjG5Ql3ZYhw5UUR6XsC+gOAzMJnYedCzcutn3atIx72lsf6t8Ky7P7isCxzv6OT/topya0VeNVms+qEUfVGcnmdenD+Es1irKVFKzK1gHhBW7q8My379+BJyabU2oBW2ilNxsBZ/7irtu8hLu7+ton0b3RG+II9MeajdS89m7pNwswx6FZqhBS3CQK+xZYrfya3H1t9QseP/p5JP97F0fu0/tPnWiO55A182FU+WqFKXHfbd++nd65CWDxDWOsrGVPrWLnKwkX3Hg39Ks7w3nR2Ob6JiradRf0KFKm+cJXKYZzl3xNvNKwh/38xdbrMrhM/Hc/hPX2iG+almzgS9NyvD/XlhvDksOuT7cL/kxnb6d/M4l1p+EWT1pqRfqK2Dv5frBXnzYrArNyc9H6IfD+eMBvK1PU72vXiiSDy/hz/FR8r41vURdHa0mHSthX86rekR2zQFLtrSyNrIRV5dXZ+JyVdXF+8X82Wmw/CHzh3MvrErscVKrxX5X19mnhnyJz+z8Ts6Y81mOe+t2+R2nN99Du73SGK/RV4jPbXB4vpi5JpIP+uiR5nCcxjReL36r2KxHx9+d6CdwpimJ/V593P+0kV5qn3lmWt0g+DiBvjTpPnE0Xqys0Ud/LYcd1wSv6GSe5ewZzQ0HijeF3TTT2Ex87jzxpk+s/IA4yxzScynX3TDmZnF7TqSnVwPf5sNPYPsN7OCelrdH0skT95SZW2VxU+GEnnUCTJK32b41Ptfd0yeuiFoLsf+gGv1lzRra20r6jJ+v0/d3fB/2wsOGeqqyvWDJa66F8/XbIwf4cdz5eGh//Ywx3PmOmDeu9+vKv23x9H3fe8VfpS70kcx8msvn/Hsu3W3CCXtTxtGF1bzU22h9MLBjA+udYn/kKGvm9NK0M9TLxvTkofZr2UOQ8zpYM149bsen+P8l9ku3aS7mxtDt+HrPrXCxG/wQ7xdOwycSuhQ8rIKn1P9F7DWmPZ4pdrbqWxubnzleY37XfwjjWp28h2QJH505U9348qS+vOFTa6pN1CP7NpclxktbSqXvvCJPuteGRz/DJ7GW2KOZIg9fkicN1Z4+I+RLff4erTUtiOd8pZc=
*/