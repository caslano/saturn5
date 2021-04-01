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
s310T+77wJP2tzGh9kpg+F8AdkZTZx1yp0YcaY37k+5bxGuckZ381etWZgD+6+GjrVzifJ7tExk59RYKQ3ZWHpTOiSiQmpAGDrKckOvqLPVE5EhG1V4iOKqBuvs3KkEg6cMF9R4xjdlSPtU8H2/r0KUx+BwbCJRp6TOFz1pxAO9iDucYV6syNeiNCytzc+LOWlmYgrtf69AZCQr27/+jrYQJyjxsW/caeg5YcVk3ghvvYmspYE6cIqie21dDh2/o8yOqJJiO1pNXP8q7BT6ETF7DQbKwAmx9hKatesCqKaA0ShblyUOg5UiMrhNkhmVZcgr+Ydfa+W7Y9eBpRRpt96pPJSRR6RIkyDjmoxc95qLekmayXk0ccCs8wMzg5g4clurGOAGQgGI0E8bwoPH02IOfZJxMjsGIjkb942Bk6BDmOJar/NEGB3gV7pF+bCeLW8oNcbQuxJjJR26slARPQXPhyK7GxxeUGKiTVSknOFGgjroRPii5sflZ3WtOPDlW9US+MKKnb054hEQ9mKXybDtBur53WCrRV5lh120CTKGeSs7GXpMuqd3clA==
*/