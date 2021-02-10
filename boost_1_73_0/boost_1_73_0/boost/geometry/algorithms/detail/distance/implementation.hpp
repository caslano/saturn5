// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2014, 2018.
// Modifications copyright (c) 2014-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_IMPLEMENTATION_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_IMPLEMENTATION_HPP

// the implementation details
#include <boost/geometry/algorithms/detail/distance/point_to_geometry.hpp>
#include <boost/geometry/algorithms/detail/distance/multipoint_to_geometry.hpp>
#include <boost/geometry/algorithms/detail/distance/linear_to_linear.hpp>
#include <boost/geometry/algorithms/detail/distance/linear_or_areal_to_areal.hpp>
#include <boost/geometry/algorithms/detail/distance/linear_to_box.hpp>
#include <boost/geometry/algorithms/detail/distance/geometry_to_segment_or_box.hpp>
#include <boost/geometry/algorithms/detail/distance/segment_to_segment.hpp>
#include <boost/geometry/algorithms/detail/distance/segment_to_box.hpp>
#include <boost/geometry/algorithms/detail/distance/box_to_box.hpp>

#include <boost/geometry/algorithms/detail/distance/backward_compatibility.hpp>

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_IMPLEMENTATION_HPP

/* implementation.hpp
EJYuYV/vO11XxL6U2GGJ+rEuzp+eINKLksgkHuSkhnOwXXuAhjKemokdPK4mPl0ajVeuIxvsZ+rHrnIJSvv5/S6BWycudA3mZbULJZXdWRG5eYC312/a3Q+n5ycXH7qY+KJGKzGXYIRXOxdyC+AWhpoW58Wx2PjbUxZI5Ofgd5cl0+lqKJT+H7OEpEVU4vBCsAclacmoqJz4T9A1cHNzSbY51NObOuA8gMTU2wzwoaRTZODhbDxy/bRxlQeRlDmUicWZTufwMTlZtFBRsK+0NsTZlCVoriGuJXRk1RKPpNQWG1WO3p02GYzQLO127ZWiIIZEyvOWS1LsK+aDD5+IblYCUryTd3Os2JKdc4+8xG1OH7QE8WLP1LAU2OrEg5Nqpgu7jQ0VDbDmyUxXGXYCZ0wjJ0+cTmjCbJPkl/Mzx9CZOV3mpRVZLqUIz7tFbMxqVboCgqnAcxW2mgk/CSq18XMUnU5NmFUuKwnoaKuaA8OQcg7JBB3qMZ6Yj7RVSTyMrki2p19xe7gXlsPXvksGGOmsCeXbo04X2LPu2cXx0ZlL8PyXdPkItbnMfc1qud9MR41JCMKhWucEUZs1NFmeMJINHvFYrMjz0M9j3u7qz1fzX/TDuwqzYd/6Xfp6trZUaNEEmogRAfWtyq2I
*/