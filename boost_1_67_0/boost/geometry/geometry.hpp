// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014-2018.
// Modifications copyright (c) 2014-2018 Oracle and/or its affiliates.

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
#include <boost/geometry/core/interior_type.hpp>
#include <boost/geometry/core/point_order.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tag_cast.hpp>
#include <boost/geometry/core/tags.hpp>

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
#include <boost/geometry/algorithms/buffer.hpp>
#include <boost/geometry/algorithms/centroid.hpp>
#include <boost/geometry/algorithms/clear.hpp>
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