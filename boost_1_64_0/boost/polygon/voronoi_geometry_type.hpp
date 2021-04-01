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
yIvEBYgpLZtvT8WS9q6vNdW11lE4wIBhaylcE1zS11WKy5HNEz5yEzPPbhiKuvnRKQVuWJr4BrOXsnE7b8W5EKXzCx9F3Ewf+TGa1o76mNjw5u+tE8JdmDKhxZVQHi/AT8Nw7kYIGLV0IpRjPpIRI7zs+60denS0EU3gTiP3E+F+0o2ye9VSbfnP77/K1/izgBdtzkR28SwnOqFHqXCmCChj6ALiqVqiVaTfktAC+1Gu23x1bC7dApRoIf7OspmQ++uAlPEHWlBgBhhdx8bzcfOsyPIofmbFYduHJsPJ2/BFwKUUy+/tKS7JIwJxoCvnm2uFK1M8A2Oe6sRXvgSL4AKUi1eAuZ5NctLxUzMRgAmLbUD/1i9wO6b2aGBt9aPiNrO2LnJnqhY3JCH/5L1mWWb+gtmPiLHwpAl7tvzwdK+nuvJKcRXnwnIKP7fZ/ighqQbh/qGgwnox+obhFTmwsO4QVDiC9b/p9SfE65QS6pw8e9izIq8aXuNZmeh3aJSQ2LXd5nMsrxp+BvatRVMwo3pyh32MATr/3DNJwFyIRze2NGcYEGaiuehaKg==
*/