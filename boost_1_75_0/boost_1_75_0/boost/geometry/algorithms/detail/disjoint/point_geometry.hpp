// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2015 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2013, 2014, 2015.
// Modifications copyright (c) 2013-2015, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_POINT_GEOMETRY_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_POINT_GEOMETRY_HPP

#include <boost/geometry/algorithms/covered_by.hpp>

#include <boost/geometry/algorithms/detail/disjoint/linear_linear.hpp>

#include <boost/geometry/algorithms/dispatch/disjoint.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace disjoint
{


struct reverse_covered_by
{
    template <typename Geometry1, typename Geometry2, typename Strategy>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Strategy const& strategy)
    {
        return ! geometry::covered_by(geometry1, geometry2, strategy);
    }
};


}} // namespace detail::disjoint
#endif // DOXYGEN_NO_DETAIL




#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template<typename Point, typename Linear, std::size_t DimensionCount>
struct disjoint<Point, Linear, DimensionCount, point_tag, linear_tag, false>
    : detail::disjoint::reverse_covered_by
{};


template <typename Point, typename Areal, std::size_t DimensionCount>
struct disjoint<Point, Areal, DimensionCount, point_tag, areal_tag, false>
    : detail::disjoint::reverse_covered_by
{};


template<typename Point, typename Segment, std::size_t DimensionCount>
struct disjoint<Point, Segment, DimensionCount, point_tag, segment_tag, false>
    : detail::disjoint::reverse_covered_by
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry



#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_POINT_GEOMETRY_HPP

/* point_geometry.hpp
jeUlSkReoTZpI7Ee1RYaTe58za8WyXGmNKlFpVhXDU03DLcusORMvI5+DK+D2T8P2P3/oPHtA8L/74BzfbyEyYt4S6+8xqIDYn/dviCEVkLjIdaHrKy39UH1odOJez8zvviVYm56YYaX7uvltH1ML0Hj72JMl7uNKR3j0aZdhfprf+DU0+oHTf8HqHwTSv3BFK5TW1+w0XZHA55n/baD1g781nuwA/tFniELpY3yPGWLWqdt00twrj5TBfaT7IfTdxnPV60ZeqwP3mzPQZtP7WFoPH+Q76XjB53zNcKlnCP/YAYqqy+nHfjDg7a5SjsURtcf4nOVecg5V6dc8lPUi7AUN1k2iv4wb6rD5lF+qBtu/zjaj8C0Zu+pX+o9NR0S+3oxVJrp97j6UJmKL6IofgbV4l5tsnsO2bB8D0PjeTHm44ec9DjTJZ/D+4F2BiybTzdd/If2vtJ+HUaZv+Z9UdouZRI0lpENgVcD675BMfM2MLyaAvh64ia4VECZ/GuGP8LOd4Y/MvbXTqXqeiy34hgpxlWsz27+2kvh23Ut9Cc1yG672kQ/30o/38fPqOU9z6hjv7bN+7PQ+It4jrO/dr7H97D8It4FtNbTK/0kT3TLV5AFH8iPwojKBWauST+tXEmJJ7qdEaPgA3YcRDnG7ryeGLuz7L9ZDI2fPMHH2/KEc7zXsPw60I1GNt7e+zpq7+v9P4bQKTrmD2EB
*/