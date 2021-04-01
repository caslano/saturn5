// Boost.Polygon library segment_traits.hpp header file

// Copyright (c) Intel Corporation 2008.
// Copyright (c) 2008-2012 Simonson Lucanus.
// Copyright (c) 2012-2012 Andrii Sydorchuk.

// See http://www.boost.org for updates, documentation, and revision history.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_POLYGON_SEGMENT_TRAITS_HPP
#define BOOST_POLYGON_SEGMENT_TRAITS_HPP

#include "isotropy.hpp"

namespace boost {
namespace polygon {

template <typename Segment>
struct segment_traits {
  typedef Segment segment_type;
  typedef typename segment_type::point_type point_type;
  typedef typename segment_type::coordinate_type coordinate_type;

  static point_type get(
      const segment_type& segment, direction_1d dir) {
    return segment.get(dir);
  }
};

template <typename Segment>
struct segment_mutable_traits {
  typedef Segment segment_type;
  typedef typename segment_type::point_type point_type;
  typedef typename segment_type::coordinate_type coordinate_type;

  static void set(
      segment_type& segment, direction_1d dir, const point_type& point) {
    segment.set(dir, point);
  }

  static segment_type construct(const point_type& low, const point_type& high) {
    return segment_type(low, high);
  }
};
}  // polygon
}  // boost

#endif  // BOOST_POLYGON_SEGMENT_TRAITS_HPP

/* segment_traits.hpp
uj7azucSMvkfcrtnvlBJwaLnmJU/OY3y+UaczUUoe/is8FFNmA24Z7+UaNmsuPis2LJhXOdDXNms01yXeAFm9fzoBuVO7TQMeyJUiDyCcywSerfNLhaV6t2vc6PCbyAAcN16hJlYuofAhg2kEvHDWifbWR7SunGb56Iwt2tu3GXO9fZpAydfx0q81wxlF8kQhNZUEsfDzwxti3fYy6x6OhwxSdLNUaKZUJaRgLJcJ1FA/vOqq7Hw/WQRa3501vGjwX2hIw3TpyMeF1RApvHGKGhgMKm+jUaeK6FJ/yk8FM2l7FV90RwPrVwJUYxyx0ZxXaMAFT1MoTPPdmjuRCVKMEKTwUR9FuepkStqLym7RlC9M3Z4K4oHQU8s4AFRsbbOQT2UuSS9VqojHpYso4D4/H+UVjedqfToiy6koymzuc7rKwglBm18z2MePfhIokKxg6laEX3H82RVkPEs70c+hb5Cmi/QngBo6javlkdmeQmv8rQhbbXcZ+x7hhH2xch3IuZoBg0YEKrHSHscNh9/2k7TshJJbsrgjvd/fyOfi3CxlDhD7rkFFQIXOQ==
*/