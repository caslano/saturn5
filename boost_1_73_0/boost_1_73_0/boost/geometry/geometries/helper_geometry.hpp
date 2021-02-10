// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2015-2017, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_GEOMETRIES_HELPER_GEOMETRY_HPP
#define BOOST_GEOMETRY_GEOMETRIES_HELPER_GEOMETRY_HPP

#include <boost/mpl/assert.hpp>

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/point.hpp>

#include <boost/geometry/algorithms/not_implemented.hpp>


namespace boost { namespace geometry
{

namespace detail { namespace helper_geometries
{

template
<
    typename Point,
    typename NewCoordinateType,
    typename NewUnits,
    typename CS_Tag = typename cs_tag<Point>::type
>
struct helper_point
{
    typedef model::point
        <
            NewCoordinateType,
            dimension<Point>::value,
            typename cs_tag_to_coordinate_system<NewUnits, CS_Tag>::type
        > type;
};


}} // detail::helper_geometries


namespace detail_dispatch
{


template
<
    typename Geometry,
    typename NewCoordinateType,
    typename NewUnits,
    typename Tag = typename tag<Geometry>::type>
struct helper_geometry : not_implemented<Geometry>
{};


template <typename Point, typename NewCoordinateType, typename NewUnits>
struct helper_geometry<Point, NewCoordinateType, NewUnits, point_tag>
{
    typedef typename detail::helper_geometries::helper_point
        <
            Point, NewCoordinateType, NewUnits
        >::type type;
};


template <typename Box, typename NewCoordinateType, typename NewUnits>
struct helper_geometry<Box, NewCoordinateType, NewUnits, box_tag>
{
    typedef model::box
        <
            typename helper_geometry
                <
                    typename point_type<Box>::type, NewCoordinateType, NewUnits
                >::type
        > type;
};


} // detail_dispatch


// Meta-function that provides a new helper geometry of the same kind as
// the input geometry and the same coordinate system type,
// but with a possibly different coordinate type and coordinate system units
template
<
    typename Geometry,
    typename NewCoordinateType = typename coordinate_type<Geometry>::type,
    typename NewUnits = typename detail::cs_angular_units<Geometry>::type
>
struct helper_geometry
{
    typedef typename detail_dispatch::helper_geometry
        <
            Geometry, NewCoordinateType, NewUnits
        >::type type;
};


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_GEOMETRIES_HELPER_GEOMETRY_HPP

/* helper_geometry.hpp
l2EiDJP0QTCjJoeo9ZUIEtW1ReQztuXhf37tBrDmMPEH2XsLdOKfTguA3ssUhDxaDhN/j4lZa16wJxqXNFkht4ZKw666T6gPpPskVynPt23JUp1khEinsMsZcSRjuewsS/oH6qg8+BJazhvjPOVYwGJTlzCXimid9yts+5BVt7VMBPr9aTKi1z86vein68ulClIQxiHuhNo3Yx0U8TiDsiGCWRjLXr5sn/b3NzY34X/2mrxdpFHZ2yKyk9YkKn762yps61aK7BJT4xpBl+ztcV+C6KeHIEfpjP+uPdv5JV+hoxLbyHPHuTmbSTzFaMkljJiJpxrlWyuUbLOTOADGoFCK1zvw/ReU1/xLNSEub5xfnpBpUy86AGyBLj3CY976QRCR9BQr197SaSCsrVuwDku54k6Mx8NjEA9RXBzn38KBzkKcltnLOCRCaME5BnMIRM7uQKg1xsOsSfpaDnk2dfVyEdzNp/PhmKwTSAR2wfEwvDmHyI4/AbU3xDPpCz6SB7wx6qOMk+eiaQQiTsXOphfccPS/MLrOzrjHKVFssSQY3WpqjHojXvQRMhP4qtDhBL58FWp2Vc0irLmXlULkDc2qEj1qqyLADRDZbGOfpfUgJn1NGeHQjrbxvIC8B9z8ZAY7dkc0RFfuPN8Q
*/