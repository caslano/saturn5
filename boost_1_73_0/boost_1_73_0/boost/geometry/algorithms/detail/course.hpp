// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2014.
// Modifications copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_COURSE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_COURSE_HPP

#include <boost/geometry/algorithms/detail/azimuth.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

/// Calculate course (bearing) between two points.
///
/// NOTE: left for convenience and temporary backward compatibility
template <typename ReturnType, typename Point1, typename Point2>
inline ReturnType course(Point1 const& p1, Point2 const& p2)
{
    return azimuth<ReturnType>(p1, p2);
}

} // namespace detail
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_COURSE_HPP

/* course.hpp
IuYcYvMd8PayrOQB70bBVShqq2TpKGSUywqWlYfnl0ZmzQ3Si6lquB69tP24YZgeTqST64v0Vo7JPJGrkWKsL/Ij+L0c+VCt6bj+Nr1kd5i2X4O2kOCtH9onk/YiKyKWzVIj5mAW9FEIf48pHY/54Du9GtSzKh7CjRpfd5CL0F8boieq2013cXh7lvJMI3GXHJZvOEC/wt4WO+A9CrYONSp2mGo0tv173OpzH8H1frwBoGa66NEqk3do7wBcrBE=
*/