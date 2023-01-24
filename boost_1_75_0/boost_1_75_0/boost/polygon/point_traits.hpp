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
SHOGUIxqo2itn3ic+ABAhlYIisFDNCyl9QQ5LcF5dRDbu7fZM0Y3eftcd0bp/SIKjJz8IvMxlVtOgJ5FJ35VLt6ayRj6vPVvfUJmNEUPIC3qRVup9CzfCPzHSR/kNO+P9TXFM5Znde8TNkWoCITW5UWcccsbmK1AWKx4LR1mZpDg9IN4kucBlSSOE5j0JE/RHBTb9JiGN42cqDpoXNYhkZaM2u6JgaeY/uftsLlUgsNJ1EJ6HKkBbYzYlctAfR6N84o9pXPjjnBE0lsJ5AhzBt3w9lv6v9QMo/2MP3284IaTCC5yw3m8vtTc1ZzbXLa8FiBBOQ5UtOdtgushs0LgaDhqwi/FO8scThS6gq+mo2kEyacQ/RkyiQT2jUV1wtYmFUtrW4ZHjjYXoR2bUcMTfN+POPw0jcBuJvJ/1C8lcufHCyB3+R3eAB9/0JSL9HIUrcBA3QXe+So8AqfvMB+D2QJUnZq0GnVWZ2aF020eX4mNNQnpoc8+yODslwLpnX5PAa9BGu4STPxNHiF1h02kl2xzf4Jyjz+ccSeAigVoB8V9jnRgt0P2p1Nn4/SKZT09RjgrpmQ8RebxK7+WelrvcnYS10D4pWoBy3FmtKMY80ej1dthvD3+pN2u0Xw77Sn2k630Tre6XpxUGAkVg8F4z0NJPZoPMlN61Ni6iVRGb1eWuNJcavrrH2FDSeYEul1hc7+tUpa7mkv3+mzY
*/