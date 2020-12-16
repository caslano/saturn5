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
BJ/ALWr/hVom2DI7NPY4VCWeskryXYUzsaoD6feplV3JqTbbStRX9Jnhv7Tbcv4+1bKiEtdyisrd+nXPopxT3Oels54fYS0nu+75hWVnvrDszFcJ/fyaZPYl6ec3pJ/fJvx9mai7fk/+fhipruyYVknjTxaNP1u28JeELfy1BXfCFv5GtPxOfpcbnneVtJ+Oq9O2C9UN/rTo+MuiA408iw74adW3Tce4rZqO8Vob8kSvqokIsZxsGU6AcGwZTIh3WwYTUXwTk7/lho9PKqyJzThYcU0ax4XnmAeTJ2iYgmiYTDV6wQ+iYSoLP4GFb03gpyb8hISfhvDTGn8KY/g+fYLvM7TiTvB9RgpjJvK7dkNdDNM9BYsfiQ+2Xs5ipWVWi67ZEnTN3oo7QdccRNecVtomt8KYOxHGPK24E2HMS2HMZ4UxS4KnCyT0YkHCLGRh/kzk50USmEUJs5iFmTURzxKEQXwKsyRhlhpR/9o3HbNUavP2DTfrjBhuu0T2/isrry2T4MuyrbgTfFmO4l7eovcnqxz+OZHelQi/ItG+MuFXGZH2LbHPp16YHtFuuRibsZqlI6tb8l0jkY72VtyJdKxJdHQkeL1iQj6d5G9tK72rmWfEm8CvR/h1Kb3rE36DhL/JEvFsRP7GJPytm/DXRf42Mf60vbQxmxJmEaKhmzCbWZil6fnFcWhMQfUjVUJf2P1GPeWy7HnUbuBNIj+Tu7Yp2o6ivLb8ytZTr+fX4D30y3s+emqztl/ElQ8p2Fp3uXbSfLHcK3BQZoM+2ZhwuaXI1aIlvewQNyxMBCmFIe49xcoQNyx3kFvWGt92fHIJLQo142aFnd/Vyw75NpAP8oZyOw4s3q3HA9lgrX3fqeqVojHLLYxc5O4aVS8aW5oORdeW+DaxQ//M3Hbdy6pnbaXwOthonGzrVqst51DObV0TdimfpbRMrep0xXwpAJOMm4wPjUvlZo/pFNNBv2nHm7re2tQvu61F07RNlDlTI++Mp+yVrp+GNfVTjAvDnewJ/Jjvxp7sADcKAzLS9dxkGD22Hwoj6SdLeXVFK6+Or/O3webwrVeFZdlWYPsIi7gt+6fj2jFh//qjOhP82mEXE2Hjuwq71BrXz+epUz+vJOrjui8RcrRkOCPJrI3q55VWu99E7mto9bnGryP0/0U7SJWzBma5ADlS2bheN3pICGYcovhM2lW7R/MqtGRSpueon66K9wHcaKMqHho8NHywdZj2WIM0q7HD1pH6qFP5MjAKqx8Nbrdh6Nsdd5K+PfAuy9PAKk/30nijF3tT2iTG1ot94G78UPhJP/uRru2aKJdleAck9PJAvI9QJ5DjNhG3jINdbzzYSsMhVp3g0ETch7XiTsR9ONF5ROtI41LyaP7lIxrUix3/UVb8R1vxH5OI/9hW3In4j6P4jye/qw3PB7kQrySHEyNCEq5a94fHS9tvoMbB0ruTEvWQkxP1kFOI1lNN3X8EXuV7URTWyK7eBxP36XHceI75eWaCprOIpjOonnM20XTOiHVLnA5IB7xFxBgXq255nhXv+RTe5rB/cX0nI0dTS2EqLivXVWWlqqTmw75iVK7DDqKsTsW28YJWaQt1jHpcTtvDC217SLyTSIrJ5l3yA6hGOMPLG13Q6629VaqrfWy7sXn1PhgZXGzJ4GKLF5cmZHAZyeASksHlJIMrtL9h7F50QmlEink37ZKrCL9mIxnaWpVwjtJzYU39Y8CMwxuZKfkouSVkJmnSMrtaySzr2W6hkpMke2hZuKB01zI3fpdUbjnfI325BmGuYOnBSjTWfq2lB12iouc1pCx2WU4j91vJ8xLQk17ur1YirOVky/v6hFxvSOT3G0k=
*/