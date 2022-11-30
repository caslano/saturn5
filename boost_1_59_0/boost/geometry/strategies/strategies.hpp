// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.
// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2014-2020.
// Modifications copyright (c) 2014-2020 Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_STRATEGIES_HPP
#define BOOST_GEOMETRY_STRATEGIES_STRATEGIES_HPP


#include <boost/geometry/strategies/tags.hpp>

#include <boost/geometry/strategies/azimuth.hpp>
#include <boost/geometry/strategies/buffer.hpp>
#include <boost/geometry/strategies/centroid.hpp>
#include <boost/geometry/strategies/compare.hpp>
#include <boost/geometry/strategies/convex_hull.hpp>
#include <boost/geometry/strategies/covered_by.hpp>
#include <boost/geometry/strategies/densify.hpp>
#include <boost/geometry/strategies/disjoint.hpp>
#include <boost/geometry/strategies/distance.hpp>
#include <boost/geometry/strategies/intersection.hpp>
#include <boost/geometry/strategies/intersection_strategies.hpp> // for backward compatibility
#include <boost/geometry/strategies/side.hpp>
#include <boost/geometry/strategies/transform.hpp>
#include <boost/geometry/strategies/within.hpp>

#include <boost/geometry/strategies/cartesian/azimuth.hpp>
#include <boost/geometry/strategies/cartesian/box_in_box.hpp>
#include <boost/geometry/strategies/cartesian/buffer_end_flat.hpp>
#include <boost/geometry/strategies/cartesian/buffer_end_round.hpp>
#include <boost/geometry/strategies/cartesian/buffer_join_miter.hpp>
#include <boost/geometry/strategies/cartesian/buffer_join_round.hpp>
#include <boost/geometry/strategies/cartesian/buffer_join_round_by_divide.hpp>
#include <boost/geometry/strategies/cartesian/buffer_point_circle.hpp>
#include <boost/geometry/strategies/cartesian/buffer_point_square.hpp>
#include <boost/geometry/strategies/cartesian/buffer_side_straight.hpp>
#include <boost/geometry/strategies/cartesian/centroid_average.hpp>
#include <boost/geometry/strategies/cartesian/centroid_bashein_detmer.hpp>
#include <boost/geometry/strategies/cartesian/centroid_weighted_length.hpp>
#include <boost/geometry/strategies/cartesian/densify.hpp>
#include <boost/geometry/strategies/cartesian/disjoint_segment_box.hpp>
#include <boost/geometry/strategies/cartesian/distance_pythagoras.hpp>
#include <boost/geometry/strategies/cartesian/distance_pythagoras_point_box.hpp>
#include <boost/geometry/strategies/cartesian/distance_pythagoras_box_box.hpp>
#include <boost/geometry/strategies/cartesian/distance_projected_point.hpp>
#include <boost/geometry/strategies/cartesian/distance_projected_point_ax.hpp>
#include <boost/geometry/strategies/cartesian/distance_segment_box.hpp>
#include <boost/geometry/strategies/cartesian/intersection.hpp>
#include <boost/geometry/strategies/cartesian/point_in_box.hpp>
#include <boost/geometry/strategies/cartesian/point_in_point.hpp>
#include <boost/geometry/strategies/cartesian/point_in_poly_franklin.hpp>
#include <boost/geometry/strategies/cartesian/point_in_poly_crossings_multiply.hpp>
#include <boost/geometry/strategies/cartesian/point_in_poly_winding.hpp>
#include <boost/geometry/strategies/cartesian/line_interpolate.hpp>

#include <boost/geometry/strategies/spherical/azimuth.hpp>
#include <boost/geometry/strategies/spherical/densify.hpp>
#include <boost/geometry/strategies/spherical/disjoint_segment_box.hpp>
#include <boost/geometry/strategies/spherical/distance_haversine.hpp>
#include <boost/geometry/strategies/spherical/distance_cross_track.hpp>
#include <boost/geometry/strategies/spherical/distance_cross_track_box_box.hpp>
#include <boost/geometry/strategies/spherical/distance_cross_track_point_box.hpp>
#include <boost/geometry/strategies/spherical/distance_segment_box.hpp>
#include <boost/geometry/strategies/spherical/compare.hpp>
#include <boost/geometry/strategies/spherical/intersection.hpp>
#include <boost/geometry/strategies/spherical/point_in_point.hpp>
#include <boost/geometry/strategies/spherical/point_in_poly_winding.hpp>
#include <boost/geometry/strategies/spherical/line_interpolate.hpp>
#include <boost/geometry/strategies/spherical/ssf.hpp>

#include <boost/geometry/strategies/geographic/azimuth.hpp>
#include <boost/geometry/strategies/geographic/buffer_point_circle.hpp>
#include <boost/geometry/strategies/geographic/densify.hpp>
#include <boost/geometry/strategies/geographic/disjoint_segment_box.hpp>
#include <boost/geometry/strategies/geographic/distance.hpp>
#include <boost/geometry/strategies/geographic/distance_andoyer.hpp>
#include <boost/geometry/strategies/geographic/distance_cross_track.hpp>
#include <boost/geometry/strategies/geographic/distance_cross_track_box_box.hpp>
#include <boost/geometry/strategies/geographic/distance_cross_track_point_box.hpp>
#include <boost/geometry/strategies/geographic/distance_segment_box.hpp>
#include <boost/geometry/strategies/geographic/distance_thomas.hpp>
#include <boost/geometry/strategies/geographic/distance_vincenty.hpp>
#include <boost/geometry/strategies/geographic/distance_karney.hpp>
#include <boost/geometry/strategies/geographic/intersection.hpp>
//#include <boost/geometry/strategies/geographic/intersection_elliptic.hpp>
#include <boost/geometry/strategies/geographic/point_in_poly_winding.hpp>
#include <boost/geometry/strategies/geographic/line_interpolate.hpp>
#include <boost/geometry/strategies/geographic/side.hpp>
#include <boost/geometry/strategies/geographic/side_andoyer.hpp>
#include <boost/geometry/strategies/geographic/side_thomas.hpp>
#include <boost/geometry/strategies/geographic/side_vincenty.hpp>

#include <boost/geometry/strategies/agnostic/buffer_distance_symmetric.hpp>
#include <boost/geometry/strategies/agnostic/buffer_distance_asymmetric.hpp>
#include <boost/geometry/strategies/agnostic/point_in_box_by_side.hpp>
#include <boost/geometry/strategies/agnostic/point_in_point.hpp>
#include <boost/geometry/strategies/agnostic/point_in_poly_winding.hpp>
#include <boost/geometry/strategies/agnostic/simplify_douglas_peucker.hpp>

#include <boost/geometry/strategies/strategy_transform.hpp>

#include <boost/geometry/strategies/transform/matrix_transformers.hpp>
#include <boost/geometry/strategies/transform/map_transformer.hpp>
#include <boost/geometry/strategies/transform/inverse_transformer.hpp>

// TEMP

#include <boost/geometry/strategy/area.hpp>
#include <boost/geometry/strategy/envelope.hpp>
#include <boost/geometry/strategy/expand.hpp>
#include <boost/geometry/strategy/relate.hpp>

#include <boost/geometry/strategy/cartesian/area.hpp>
#include <boost/geometry/strategy/cartesian/envelope.hpp>
#include <boost/geometry/strategy/cartesian/envelope_box.hpp>
#include <boost/geometry/strategy/cartesian/envelope_multipoint.hpp>
#include <boost/geometry/strategy/cartesian/envelope_point.hpp>
#include <boost/geometry/strategy/cartesian/envelope_segment.hpp>
#include <boost/geometry/strategy/cartesian/expand_box.hpp>
#include <boost/geometry/strategy/cartesian/expand_point.hpp>
#include <boost/geometry/strategy/cartesian/expand_segment.hpp>
#include <boost/geometry/strategy/cartesian/side_by_triangle.hpp>
#include <boost/geometry/strategy/cartesian/side_robust.hpp>

#include <boost/geometry/strategy/geographic/area.hpp>
#include <boost/geometry/strategy/geographic/envelope.hpp>
#include <boost/geometry/strategy/geographic/envelope_segment.hpp>
#include <boost/geometry/strategy/geographic/expand_segment.hpp>

#include <boost/geometry/strategy/spherical/area.hpp>
#include <boost/geometry/strategy/spherical/envelope.hpp>
#include <boost/geometry/strategy/spherical/envelope_box.hpp>
#include <boost/geometry/strategy/spherical/envelope_multipoint.hpp>
#include <boost/geometry/strategy/spherical/envelope_point.hpp>
#include <boost/geometry/strategy/spherical/envelope_segment.hpp>
#include <boost/geometry/strategy/spherical/expand_box.hpp>
#include <boost/geometry/strategy/spherical/expand_point.hpp>
#include <boost/geometry/strategy/spherical/expand_segment.hpp>

#include <boost/geometry/strategies/cartesian.hpp>
#include <boost/geometry/strategies/geographic.hpp>
#include <boost/geometry/strategies/spherical.hpp>


#endif // BOOST_GEOMETRY_STRATEGIES_STRATEGIES_HPP

/* strategies.hpp
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
*/