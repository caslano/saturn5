// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014-2021.
// Modifications copyright (c) 2014-2021 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRY_HPP
#define BOOST_GEOMETRY_GEOMETRY_HPP

#if !defined(BOOST_GEOMETRY_DISABLE_DEPRECATED_03_WARNING)
#include <boost/config.hpp>
#if defined(BOOST_NO_CXX14_CONSTEXPR)
#include <boost/config/pragma_message.hpp>
BOOST_PRAGMA_MESSAGE("CAUTION: Boost.Geometry in Boost 1.73 deprecates support for C++03 and will require C++14 from Boost 1.75 onwards.")
BOOST_PRAGMA_MESSAGE("CAUTION: Define BOOST_GEOMETRY_DISABLE_DEPRECATED_03_WARNING to suppress this message.")
#endif
#endif

// Shortcut to include all header files

#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_system.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/geometry_types.hpp>
#include <boost/geometry/core/interior_type.hpp>
#include <boost/geometry/core/point_order.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tag_cast.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/visit.hpp>

// Core algorithms
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/radian_access.hpp>
#include <boost/geometry/core/radius.hpp>
#include <boost/geometry/core/topological_dimension.hpp>

#include <boost/geometry/arithmetic/arithmetic.hpp>
#include <boost/geometry/arithmetic/dot_product.hpp>

#include <boost/geometry/strategies/strategies.hpp>

#include <boost/geometry/algorithms/append.hpp>
#include <boost/geometry/algorithms/area.hpp>
#include <boost/geometry/algorithms/assign.hpp>
#include <boost/geometry/algorithms/azimuth.hpp>
#include <boost/geometry/algorithms/buffer.hpp>
#include <boost/geometry/algorithms/centroid.hpp>
#include <boost/geometry/algorithms/clear.hpp>
#include <boost/geometry/algorithms/closest_points.hpp>
#include <boost/geometry/algorithms/comparable_distance.hpp>
#include <boost/geometry/algorithms/convert.hpp>
#include <boost/geometry/algorithms/convex_hull.hpp>
#include <boost/geometry/algorithms/correct.hpp>
#include <boost/geometry/algorithms/covered_by.hpp>
#include <boost/geometry/algorithms/crosses.hpp>
#include <boost/geometry/algorithms/densify.hpp>
#include <boost/geometry/algorithms/difference.hpp>
#include <boost/geometry/algorithms/discrete_frechet_distance.hpp>
#include <boost/geometry/algorithms/discrete_hausdorff_distance.hpp>
#include <boost/geometry/algorithms/disjoint.hpp>
#include <boost/geometry/algorithms/distance.hpp>
#include <boost/geometry/algorithms/envelope.hpp>
#include <boost/geometry/algorithms/equals.hpp>
#include <boost/geometry/algorithms/expand.hpp>
#include <boost/geometry/algorithms/for_each.hpp>
#include <boost/geometry/algorithms/intersection.hpp>
#include <boost/geometry/algorithms/intersects.hpp>
#include <boost/geometry/algorithms/is_empty.hpp>
#include <boost/geometry/algorithms/is_simple.hpp>
#include <boost/geometry/algorithms/is_valid.hpp>
#include <boost/geometry/algorithms/length.hpp>
#include <boost/geometry/algorithms/line_interpolate.hpp>
#include <boost/geometry/algorithms/make.hpp>
#include <boost/geometry/algorithms/num_geometries.hpp>
#include <boost/geometry/algorithms/num_interior_rings.hpp>
#include <boost/geometry/algorithms/num_points.hpp>
#include <boost/geometry/algorithms/num_segments.hpp>
#include <boost/geometry/algorithms/overlaps.hpp>
#include <boost/geometry/algorithms/perimeter.hpp>
#include <boost/geometry/algorithms/relate.hpp>
#include <boost/geometry/algorithms/relation.hpp>
#include <boost/geometry/algorithms/remove_spikes.hpp>
#include <boost/geometry/algorithms/reverse.hpp>
#include <boost/geometry/algorithms/simplify.hpp>
#include <boost/geometry/algorithms/sym_difference.hpp>
#include <boost/geometry/algorithms/touches.hpp>
#include <boost/geometry/algorithms/transform.hpp>
#include <boost/geometry/algorithms/union.hpp>
#include <boost/geometry/algorithms/unique.hpp>
#include <boost/geometry/algorithms/within.hpp>

// check includes all concepts
#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/srs/srs.hpp>

#include <boost/geometry/util/for_each_coordinate.hpp>
#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/select_coordinate_type.hpp>
#include <boost/geometry/util/select_most_precise.hpp>

#include <boost/geometry/views/box_view.hpp>
#include <boost/geometry/views/closeable_view.hpp>
#include <boost/geometry/views/identity_view.hpp>
#include <boost/geometry/views/reversible_view.hpp>
#include <boost/geometry/views/segment_view.hpp>

#include <boost/geometry/io/io.hpp>
#include <boost/geometry/io/dsv/write.hpp>
#include <boost/geometry/io/svg/svg_mapper.hpp>
#include <boost/geometry/io/svg/write.hpp>
#include <boost/geometry/io/wkt/read.hpp>
#include <boost/geometry/io/wkt/write.hpp>

#endif // BOOST_GEOMETRY_GEOMETRY_HPP

/* geometry.hpp
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
*/