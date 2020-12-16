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
UU9y4mOysDZbLic/7Che3FaEt/lJ4vZGcTcrzULOM+Mt6qFcYpUxvEJycnP/T+L9rCaGV9hcBPf/vIJi/ka3WdA9hD0/lxPvJ1HXcqN+TanDDO7OSquItu/H2n4l2UXqouog8Lrm87/EbY3k1h4ZjFxE29l5z76K/Jcinx3C31kWE29VVLtxYQvrc+7/upDiiFVFcOtTAYJ9vBcS9/tR490e8jXD/Gd3CbTBjrya1vRE9bllmrm4oIiSi6lzfgLOO4//RHU4NH4dwl7B/COvoTi81XH5A2GvzecVmId1MfFPjN9+PM5d2ikQce2xPsi8Vj/61fh9AHoxOXpYHywh/jX98ovPl5N5HeVYZDYVLTwwbBtBXALuoJD5KMZ9HXF/NtPIjbifYY+CO4CQtTV8/F9PMUcjuN1ETgmBw4kf/8OJ/xLi37yv36dX2OaDIvFt5vHPFtH7XI2Rs1FYvArG20W8ptpoXlj9BfBy//cbqI+rjLxKq9/udelOHYnnZuOrk7hNEdxOX7Mf3lRBm0PUvY36HDdYiplp5Be4boy1u4N459dF8WrnG0smm3xCrmvW7u+I/1FjuwWuWWO8/hspjqWVeCdXTsFTrEUJiM1D9SHxHldp4J1ePF2UvYv7f99Ec7g1UbyYP52nvUEmPm8Cj/9B3KdXxnKLGNuM13Iz5Y6P4hVl1xrO/KCJt2kW4y2zhaGBizi/PP/tEno3MnAGcQXP8wWEXr/LiPdRK+fVcnphylLIXEs6ex+4hfKh9rVXyLsff/4TX6+hne6gbb4SSHxO41zm93Ar6Vx9bdTuyoEG56jRuflIU4+JJNtYRCVMfD9z/xeqw5qN1mFU9hgBdWB9v/NttB6wr++FvWez8dVJnK56zikkJyRr4wbiq+/jE7bmj+e/XEpzUH2cQm0JrK0fEu9zhvPp8OY63AJiYDFO6+0UU9HI6QapQM5VxDmEP39KylVrhYj1P4yz6A7KMWLgpLB+Cefk8c+J02XkDClBbUW4gNxEjDfvTsq1ZuQNenFL8oYaBFw3fP0D8SYZeGlCPRxSEysK4Ob+38v0o6dEcWuJPNvw1x70ieDn/t/EPz6a36u0ipgvZ7wZd1EeLEskr6h4Ptz/j3ifjuSloS2ON+Vuml+I4tUszALb20m8Z9cZeW1BqL9C1hTx5x/xPlkVwdusCMw75b+HxlR1BCcm3BNvR+L6H3GWVkZwwo3XqzgFxGbiz7/l5H9j4BWVC5Q//4jzSquB0x8W4svIn3/3km9hZQRnUMR6ML7+kzhvMrZTewol/pnLODPvo5gJdUZOnxAdk3H2EGeeoW9F3fcZ5+D7Sf8w3AdF20rOJM5XDZxkChMeVyi5l3xEjecVI0mdSBe5fnoB8W5lPLeNm+adJukB/ehJEdyb7p2mnfh/thj5xb9brCfeLyN4xT/jPQ9SrJe+MUYT93YhuWR4/kPifd/QXlG2ONbWmof0o7MqjZxwzRA8h7KKeM0RvDZHuKFBSPxL7v/8MOXrMT6LXOFmv+aOIiYPNDu/vcSdZmizqPsWu3dMeoRsGAZOPVATHkz6HUSIDYX193LiX20c02RE8djF5Mbl/j+P0lqGiLbjGnbYnXMFx91bQtx+I3dBUZFZ0HwV4x35GPnYR/MKslkx3h7ibY/m1U524v3V2TlOW0H6wkziLZhRW1YIl1E7Fn3O8TlEjC92bV1C3OZIbloEFsDdBDUQMP/N2r7zSnrfjOSvLiixCPOPz2fnm7inxOfWO6HJ7m1U4CnuSryNK5et/Xyc3o02Ug9c8ULqwNd/Uh3Gx9ZB6DoBdu2lPUG5hKs5fxkWioTgXurOFeB3xnjPJd5FsbxosjgbwTZPUl4=
*/