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
aoobDLOWM++MpeKl8bBztWznunX5+pNrnhN1GQ4xSONbeIc+oo8kH/Vsfn2d5Heqo66jkQTZmRyaLjROUpghKdcHlXlrYijfdk8ujwe97iW8noPL7sVpKanctsjrHj3jepIhaoZYjQXSO6h94WUGGIymX5mySqjY35Lb0Ei1jo7c0foEOZ1W8+fjbpuBfqia5hQG8WRaPLCGyM9e6vbar55myJJHkbvVfl5gr79z5y/PV2mRkdnkiQ2qGXd3Sube5SboQL1JAn3A+ku1J1Ed24nQsNtwGF4eUFyXTaj2jsISsZRLJc5ZY6hlCFpJ24YYb6qNqhHZzrXBmjbU4XG1XdvPCT7UWfI+oN8S9SPsxizIlLkby23rbscc/uaGmOOCOZSXiISfChmnwfVo0lFxQ3IBs8950pBn56wgpgBBObQK5+RTcfYhCUVwRN7GupsdYwkK7P7qKEBbCp5+TLTCCdU3zB9JlXLsnMgPOCSMtU2KjbHJTc3AwkfTDbTVPlzVA/GIeRV/OD2wTc1CQ6JC39RTCZzHbvg8aAjnHIzDwiNv5AJgP+qmHZYvGUVmkmVz0RXS3d2btNoV0j3NTVKPuEO68zusnL3z/e+xnBV32v3D1u+2dt/XXbO6C7bgOj36Iq1+JLWY/07ntLAb
*/