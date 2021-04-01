// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2014 Adam Wulkiewicz, Lodz, Poland

// This file was modified by Oracle on 2013-2018.
// Modifications copyright (c) 2013-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_EQUALS_POINT_POINT_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_EQUALS_POINT_POINT_HPP


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace equals
{

/*!
    \brief Internal utility function to detect of points are disjoint
    \note To avoid circular references
 */
template <typename Point1, typename Point2, typename Strategy>
inline bool equals_point_point(Point1 const& point1, Point2 const& point2,
                               Strategy const& )
{
    return Strategy::apply(point1, point2);
}

}} // namespace detail::equals
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_EQUALS_POINT_POINT_HPP

/* point_point.hpp
CprGbUNegmFy+aP7An1ZqBjVpn7C6iPqdN7aQxPFm/vGCr2z6gBa3ASwLnCTcZlRtmdytONFMLC3tC0h5rjOdUfdbNHx4AlyBO/txkD4iW9aEwx4Hm++zNI7d3w7LKm4Nj/Bb1Br2RpZu+hcIsfuAyvlqN43+OMDadnb9x5SzOcmoMU/8mkVQOfcPNUB1jYoDrx9ncqRY/A0kYO9JhPNGYAEP+tCsAo0Amm8+DswhRVGZzT0AQ3pcMq2Og5B6jhHFeomkUqWEFCVoArgbpZmDdzN3sJ/GjZjvZrZwmdYc4VsqKYgkABcj70QpyAfYQADTLYOTSyOtLgxz1CxF2ShMia3p25FpwtMlcKMOpaitGk3GYa4ZQm/baN7EbSD9f8Wya6u/fq1sNwwju+1q0iwi9ASid1atz8nIM17WuCZPWXaGNEO+MTvVsP88Ol+HfXxQG2UVXng4sWzNNlOsl59zvJ+SqJqXyZhzWtlY/60/c3NzL4SqskzizxAW32jFklwfH0rK5Z7BVj5RjnvLyFsReaklmAJ7RlLKkqI2/BugZtr4UQZss/McCZXeQ==
*/