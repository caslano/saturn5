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