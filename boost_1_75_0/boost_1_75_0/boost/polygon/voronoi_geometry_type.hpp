// Boost.Polygon library voronoi_geometry_type.hpp header file

//          Copyright Andrii Sydorchuk 2010-2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_POLYGON_VORONOI_GEOMETRY_TYPE
#define BOOST_POLYGON_VORONOI_GEOMETRY_TYPE

#include <cstddef>

namespace boost {
namespace polygon {
// Represents topology type of the voronoi site.
enum GeometryCategory {
  GEOMETRY_CATEGORY_POINT = 0x0,
  GEOMETRY_CATEGORY_SEGMENT = 0x1
};

// Represents category of the input source that forms Voronoi cell.
enum SourceCategory {
  // Point subtypes.
  SOURCE_CATEGORY_SINGLE_POINT = 0x0,
  SOURCE_CATEGORY_SEGMENT_START_POINT = 0x1,
  SOURCE_CATEGORY_SEGMENT_END_POINT = 0x2,

  // Segment subtypes.
  SOURCE_CATEGORY_INITIAL_SEGMENT = 0x8,
  SOURCE_CATEGORY_REVERSE_SEGMENT = 0x9,

  SOURCE_CATEGORY_GEOMETRY_SHIFT = 0x3,
  SOURCE_CATEGORY_BITMASK = 0x1F
};

inline bool belongs(
    SourceCategory source_category,
    GeometryCategory geometry_category) {
  return (static_cast<std::size_t>(source_category) >>
              SOURCE_CATEGORY_GEOMETRY_SHIFT) ==
         static_cast<std::size_t>(geometry_category);
}
}  // polygon
}  // boost

#endif  // BOOST_POLYGON_VORONOI_GEOMETRY_TYPE

/* voronoi_geometry_type.hpp
liytWby1kFJWDB0sRyLNOHL6s7LowMeaNTdXPbeS36xGiHuDl8ASg2gJ4WJW3sFPbFtgJC8kz+FfeHdJPMafCwwbzORG3tMcactBePGqB0gbpBDz+Q7lpNWjqNqRNcmn4ZO/sL/grGFyr6hdM7dpjWlFJodhs118JjITjJ/8nlDxs057jP00h+CyIIFc5l6737lcKUipD1pFWY/XUCUZqxNfjSJiiAERzVct32c6B7Gv1CYs5J6O/ug0GFMvhcecK2usuEkbi3E6RoQG0jyj3Rmgz+c7Fs05FLo2KWVlXPDxRdmU2zgv4XNipIZVblpu1rr4Nn97z5J7QwiECXr055qzzGWHeEz5hjxrTdlfpQZDJvJLUZ+80cYpGI7GwKUNkw6Kss287WIGyX+4UoQaxDSlPn0CnjIw8XF8RO6Q188dsLKZlETHNVJ1EkHNTs6fpC5WrdctdC7qI0UJ32cGOjQoCNkKl5uxLSk1fnd8l8iarrgMs/wZ/MtFPLmON6yF0Giwgp1PPVBcbAT7V0juaxtsaVnk+xlPXz9VyqK4aUC9hSjwiQW4YgPlSxti2mcQl2qb2hO0sWS7glnzR8cPg62xqkrTK6dGCA0LbL9Pv5E7QJ9a4dD7oHhmavRln3HQg69laM24tv2DuUePeONBPjx4NzQ06p1ZFvPVj6kntKUYrQDnIsef0gJ2Q9zKFKUjw02Jehp1n5MMfzf+
*/