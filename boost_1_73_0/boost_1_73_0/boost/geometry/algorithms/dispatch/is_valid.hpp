// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DISPATCH_IS_VALID_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DISPATCH_IS_VALID_HPP

#include <boost/geometry/core/tag.hpp>

#include <boost/geometry/algorithms/not_implemented.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template
<
    typename Geometry,
    typename Tag = typename tag<Geometry>::type,
    // for multi-geometries: determines if empty multi-geometries are allowed
    bool AllowEmptyMultiGeometries = true
>
struct is_valid
    : not_implemented<Geometry>
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DISPATCH_IS_VALID_HPP

/* is_valid.hpp
Gb7ehSDvBYnkEXTvw4z+sMf7BCMS7K1jRHy9WxmRRO8ORgTSi3MT4nibGJFR71mQj+DQhrL8AhJd6l9B9gF5HCSyjhMg0Z4BQfZiVwN59k7BIQoyH+QakEg8oQzemQpPD+nnoyCrFfqrEe8KkOtBrlVo/8i7DuSTWE6QG0C+ABJca28DyKNYPpDPggS3B0m89zhIcLO9Rmgr4BteM8jnQVpAvgyyN8hXQF4L8lUsN8jXQI4ECYTfi238BsiJIN8=
*/