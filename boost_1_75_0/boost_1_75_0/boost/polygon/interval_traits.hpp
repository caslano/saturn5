// Boost.Polygon library interval_traits.hpp header file

// Copyright (c) Intel Corporation 2008.
// Copyright (c) 2008-2012 Simonson Lucanus.
// Copyright (c) 2012-2012 Andrii Sydorchuk.

// See http://www.boost.org for updates, documentation, and revision history.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_POLYGON_INTERVAL_TRAITS_HPP
#define BOOST_POLYGON_INTERVAL_TRAITS_HPP

#include "isotropy.hpp"

namespace boost {
namespace polygon {

template <typename Interval>
struct interval_traits {
  typedef Interval interval_type;
  typedef typename interval_type::coordinate_type coordinate_type;

  static coordinate_type get(const interval_type& interval, direction_1d dir) {
    return interval.get(dir);
  }
};

template <typename Interval>
struct interval_mutable_traits {
  typedef Interval interval_type;
  typedef typename interval_type::coordinate_type coordinate_type;

  static void set(
      interval_type& interval, direction_1d dir, coordinate_type value) {
    interval.set(dir, value);
  }

  static interval_type construct(coordinate_type low, coordinate_type high) {
    return interval_type(low, high);
  }
};
}  // polygon
}  // boost

#endif  // BOOST_POLICY_INTERVAL_TRAITS_HPP

/* interval_traits.hpp
GceSApWZ/qrew7PlTpSp8pXQyydOPkuHjbfHd04Au78xgamoj4CGrc4EHDGBVfXYM63C85bLirYMVNdmtsagMNzp8q59JLpA3VJp0hVmnNKJxUwczYJDbRC2eLIuZ4BjaRl5jQNfrRBwNFkPZ9i2zQvFc3AGRxlES9JzOsL9LXEkmUeEZOPilhi794d138y4tGBG0eRlqm3BRW748nhMfW+aGYA53Hl/vwIzL2txm/U6e7qCb1Sp6PALiuAgS17F3qtjV8waoZOAluAEaVxLvngOPQVujaoDpb4cByDBlvtf3LNyepJVrnb6WSK5k/3Z02iY01nKAPof3KKPDj+5IoQwnH7gqpHeHyTZMnvloMlYg3l8KNAwSLYCFRY2ce7z0Y7oRKFYKrh+DCXXJgRsBKLKaCFUmDtv27FoCQ7KtG060UuIwEbwd3BmlEmygOvaKL54bJ0GsucSmFI3e7jzzAEnnCEw7ifM9SgycQXXUERcu9/L0saTO/A96y7xLQn8bYBynAiz29LMDYwfLrSKCx7lYlu6krJ5oD14sOwgzlmY01bRkmsFV3t0jiyAyT0yyx/04J1oz+soGz1Kd7OBHqKBqRRi2JTcRIGkGpuyiQZ2DoQmGhQ/z7/q207yMznjc7p0BhQGfR4RSWTIQYPjXYBgDMJoU6IlhT9OPOD8wgmz9FGg173AsoNM2Bfhb70/jYtKQ4LCZrZYp/u0
*/