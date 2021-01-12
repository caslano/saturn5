// Boost.Polygon library point_traits.hpp header file

// Copyright (c) Intel Corporation 2008.
// Copyright (c) 2008-2012 Simonson Lucanus.
// Copyright (c) 2012-2012 Andrii Sydorchuk.

// See http://www.boost.org for updates, documentation, and revision history.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_POLYGON_POINT_TRAITS_HPP
#define BOOST_POLYGON_POINT_TRAITS_HPP

#include "isotropy.hpp"

namespace boost {
namespace polygon {

template <typename PointType>
struct point_traits {
  typedef PointType point_type;
  typedef typename point_type::coordinate_type coordinate_type;

  static coordinate_type get(
      const point_type& point, orientation_2d orient) {
    return point.get(orient);
  }
};

template <typename PointType>
struct point_mutable_traits {
  typedef PointType point_type;
  typedef typename point_type::coordinate_type coordinate_type;

  static void set(
      point_type& point, orientation_2d orient, coordinate_type value) {
    point.set(orient, value);
  }

  static point_type construct(coordinate_type x, coordinate_type y) {
    return point_type(x, y);
  }
};
}  // polygon
}  // boost

#endif  // BOOST_POLYGON_POINT_TRAITS_HPP

/* point_traits.hpp
mq9+2o9/rfcn1XX/36Bjqv+qmg5a36J1fDNQxyMV9fgP9L5l9zptl9iHzFH80Ov8pIZpz6uA9gNVtDxrOb9XV5fn1PbkmD3+3EWGTb+aOg71tZ/XTml7uFevY462A2m1fFXScdMYbVeqan0eIPb6n2q/4mXXD6uv7cBXdnmdxdreBWh/5a3/jtB0H2vXC+ip5UfLcXxhTc/22t5oft47q/23ntcorZfFdVxT8bX2d9f1+Hq8
*/