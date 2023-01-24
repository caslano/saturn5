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
4PY8V+LD0VE9kipEjpom4A3oqHg/eV/Hf3KGqBW3YwbIAuy5Pe4tIqWwNs8FfqF2Yn5RTin95H9KVUKg3HjMH5CyVR+Sn5qv01rFX8CpOD/pbZg/apjayukeuJgcyubUfp5xZj/NFurfMmpI8uMsIZjyD+hoP7Qg1VLJKBkz4SjlPTB9sdTgj6Wl6keFMvzAvZWlGERajnQ54lvnB+NCzCvLh9eGhdDpFImi6l4v1TRfo0IJ6WrZnxkn1h3H3BSWhi0DSdnetn45553xbLJE7iNMP3G0MlZeA5ONChYPhq7QgLvcVEElLTBM/tduyle7kSVnuB4SuBZviU2HZB68JOW/fpUWC8ikzV9dQmJ+s2ULacoqk6Vxn4R6d1y5+4hJx4Fzu4Kszl6tV81w7adazAo8ED1lQIq6SkC5t2JGN4DHZpIHEpsu6Q7shq+nyJ7BPq3oO4NtX45ql0a8QrxeJxX7TnIZwAIqiXTUPFoe7vctg61x28OGku/jdBAzXsfGc/nILR2yDpd80eK0e3MYPPa/W2CqPDSBMgEVYEez8WPiqz+Cxd34AQ6Yq69WkMvMF0mYu4h9UIw9N3xvYOgIL/+yA9HJxWlxv05E0yNHxwTTZMxd2QXlCF9RdYKYNDByR3eunGGyIFAZplKWPlL304lxskBKJUd6WSVH1hRGAP04yeOL7RmveG9sDRM7esc4WW9kBTM4kmacDMww
*/