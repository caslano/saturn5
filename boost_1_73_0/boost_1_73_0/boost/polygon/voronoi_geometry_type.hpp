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
jTqWFL5tn3PTPm6PVNuZr8qPXm2VXqnL5aZeR3BHktZTqAxdmDANmVn8/tOPf5ClzMhqq7jogRF/ceWe93DTbK6wwjY7bYysnBkcem0PGnHDSRQUMsUc6dxK9VYeSZMq9aXIN3o88u87teGyxOg8jjKW54+qD0fIqn/VFN5oBd+v3lXkQw24bg0zPLkwLdQxEp8VKaO5jskXCTyP2C58TrisLYAKsZPh1KyxRm21FvZm0G5smc4CN9wsDzER7gVPP9STYdBddDFv4y2kRYNwtE5FgbUtWJpelWrpJZPKDetD0lPi3Aignr/eg+ZfC+z/Hq3K6pUpsD3LxZbJMt1J25zDi5XpLk2Os9HQ9wczv2y5rXWr31Qg8XPS2p4B2B2xBTkcPnaQi6q9dm+pCkQenNzyvgrxrtcbEnYhasTsgjRjsQO0juut752KzaCpzRg8fd8BLxr4cpDAzgn9tOx1NFfh+VEZ0OaMfFofkqP+p8HH8fjD2cQV2h3I0/FoNDj174P1J5MHIifTgY/nzNn7wfQ+qMurGhjRt3b+SqjaNtY05de6mhupj2l7J4F3J8AzOHwwCYf/JxIwZvj9Vmi+Vf849JXEDoNnIPp8KL/ntLHYfJYqZPRNBnNsQNbyLKcOQq12n061JIGfPPYS
*/