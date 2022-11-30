// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2015, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_VALIDITY_FAILURE_TYPE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_VALIDITY_FAILURE_TYPE_HPP


namespace boost { namespace geometry
{


/*!
\brief Enumerates the possible validity failure types for a geometry
\ingroup enum
\details The enumeration validity_failure_type enumerates the possible
    reasons for which a geometry may be found as invalid by the
    is_valid algorithm.
    Besides the values that indicate invalidity, there is an
    additional value (no_failure) that indicates validity.

\qbk{
[heading See also]
[link geometry.reference.algorithms.is_valid The is_valid
algorithm taking a reference to validity_failure_type as second argument]
}
*/
enum validity_failure_type
{
    /// The geometry is valid
    ///
    no_failure = 0,
    /// The geometry has a very small number of points, e.g., less
    /// than 2 for linestrings, less than 3 for open rings, a closed
    /// multi-polygon that contains a polygon with less than 4 points, etc.
    /// (applies to linestrings, rings, polygons, multi-linestrings
    /// and multi-polygons)
    failure_few_points = 10,
    /// The topological dimension of the geometry is smaller than its
    /// dimension, e.g., a linestring with 3 identical points, an open
    /// polygon with an interior ring consisting of 3 collinear points, etc.
    /// (applies to linear and areal geometries, including segments
    /// and boxes)
    failure_wrong_topological_dimension = 11,
    /// The geometry contains spikes
    /// (applies to linear and areal geometries)
    failure_spikes = 12,
    /// The geometry has (consecutive) duplicate points
    /// (applies to areal geometries only)
    failure_duplicate_points = 13,
    /// The geometry is defined as closed, the starting/ending points
    /// are not equal
    /// (applies to areal geometries only)
    failure_not_closed = 20, // for areal geometries
    /// The geometry has invalid self-intersections.
    /// (applies to areal geometries only)
    failure_self_intersections = 21, // for areal geometries
    /// The actual orientation of the geometry is different from the one defined
    /// (applies to areal geometries only)
    failure_wrong_orientation = 22, // for areal geometries
    /// The geometry contains interior rings that lie outside the exterior ring
    /// (applies to polygons and multi-polygons only)
    failure_interior_rings_outside = 30, // for (multi-)polygons
    /// The geometry has nested interior rings
    /// (applies to polygons and multi-polygons only)
    failure_nested_interior_rings = 31, // for (multi-)polygons
    /// The interior of the geometry is disconnected
    /// (applies to polygons and multi-polygons only)
    failure_disconnected_interior = 32, // for (multi-)polygons
    /// The multi-polygon contains polygons whose interiors are not disjoint
    /// (applies to multi-polygons only)
    failure_intersecting_interiors = 40, // for multi-polygons
    /// The top-right corner of the box is lexicographically smaller
    /// than its bottom-left corner
    /// (applies to boxes only)
    failure_wrong_corner_order = 50, // for boxes
    /// The geometry has at least one point with an invalid coordinate
    /// (for example, the coordinate is a NaN)
    failure_invalid_coordinate = 60
};


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_VALIDITY_FAILURE_TYPE_HPP

/* validity_failure_type.hpp
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
*/