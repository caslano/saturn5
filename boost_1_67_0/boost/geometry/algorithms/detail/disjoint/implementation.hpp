// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2013-2017.
// Modifications copyright (c) 2013-2017, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_IMPLEMENTATION_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_IMPLEMENTATION_HPP


#include <boost/geometry/algorithms/detail/disjoint/areal_areal.hpp>
#include <boost/geometry/algorithms/detail/disjoint/linear_areal.hpp>
#include <boost/geometry/algorithms/detail/disjoint/linear_linear.hpp>
#include <boost/geometry/algorithms/detail/disjoint/point_geometry.hpp>
#include <boost/geometry/algorithms/detail/disjoint/multipoint_geometry.hpp>
#include <boost/geometry/algorithms/detail/disjoint/point_point.hpp>
#include <boost/geometry/algorithms/detail/disjoint/point_box.hpp>
#include <boost/geometry/algorithms/detail/disjoint/box_box.hpp>
#include <boost/geometry/algorithms/detail/disjoint/segment_box.hpp>
#include <boost/geometry/algorithms/detail/disjoint/linear_segment_or_box.hpp>


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_IMPLEMENTATION_HPP

/* implementation.hpp
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
*/