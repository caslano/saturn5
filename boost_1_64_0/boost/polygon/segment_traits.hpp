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
j7dTdH4sOi2i81M4CR6E8+DP4EL4C7gI/hIuh7+CXngIroK/gWvhb6Xefweb4e/h/fANuB0ehTvgm/BZ+BbcA4/BX8B34K/gcbNfyfsLeJGUk7VfzZD6nA1lXDDHtybZ73rZzzq+5cr4NgMOhDNhBsyD02E+LISzLOfJ43K8G23qa5PYcZ+U4/1wEHwAjoRfhFPhFlgKH4L18GG4Bm6F6EB55wB7Sn11Dx5fdLrIeNANjoApMBP2gpNgKlwJ+8JbYD94OxwIt8NB8HE4GO6FafAHcAj8ORwKj8IR8CQcCZOx4xrYDaZD7KS/yPsHuFHKIxl6xc6VUr5+2BMGYCq8AQ6Ba2AWXAvHwXWwGN4EK+DNsAF+Bt4MN8A74O3QbBdZUk427WJRR/ThYtgdLjGvk+WdApwk+1nPU1lSvmPhYDgOXg4nwgx4HRwDp8IJcJrFnuNy3B429ozthD1wHEyBE6DsJ8/9OSfY7Hcd23WCk+BwOBmqOMUi2W+yTZxiofTreTANFsOrYCkcDxfAKbAMLoELoQeWQx9cAm+GS+FGuAzeB53wEeiC34RuuAdWw4OwBv4ZeuD7cLmM3ytgKvTCfrAeDoU+mA1XwmthgxmnKO8GYN/zYuMUL5Vy6Qt7wn4wD14Gy+BguAqmwc/CIfApOBy+CkfCP8OrYTLHT4ddYQbsAbNgKhwN5TqEldbxJPI6pEDaWyEcAIvgcHg9HA1L4Aw4H86CC2AhLINy3pJ3ANgae97ih8Rlwv7wEjgQ9obmHNSy/yabdv03GZ8+hIPhKZgFO5xHucHzYS28AN4LO0M5rjyvp69ajxt1/1cI+8MiOBpeD2fAedAL58PVsNRy3BY57t02x90o48UmOBjeB6+BX5TjPgQd8GF4C9wBjXKUZ+eQ/chH6+dO3tuKuUAXb+yQtI407gH7OUE332ofn1r2QIf2GNUExqh6KU+7ONWmBzr8T8Sqts8RenaxqpupR7t41aRXTx+zuvOBDm2KWx36autiV/dy3EOkk6T+X6D/k8pIAdIm0l7SMVIyD2ZHkopIXtJG0lOkg6QTpP5bOiRNJLlITaTtpBbS+6ReD3Jc0mLSatJm0h7SYVLnhzguKY+0jNRE2kk6QDpGSn6Yvz/cHlvbvrQv7Uv70r60L+1L+/L/vuiL/yeQ2gET8P3/vvjXfyH4bddQ/H+tO1BT7/IHj+0zYv+JZzb9VfufF+vD/jD7Fl0T8oebll/oqAru2hrfRGvsxUE57r3id3kXaSvHXRY+Ll6wEtIQFCDMq66OAG/RSY6nI7EBBzmOfLMz+tvdEssvsfdu+U6n/EbJ8NmU3xgQ4b/rk0v6DWL3etK2YFmmR9jNYVrvCy12RfiuSoC72GaxVWzrIrZa/UkHdYyyTcq0JcI2a2G2rixnZLStLFXZIRJdthE+5gfE3i1i72bSl7C3KUPZK7YS3ydx/A6Pq/XliqbpH5osv6sssS2P9uO3BLeJzz/r2EfWWX1n53SK/Z74esSKMq22mp7CrfYTDrWxKJsqRN/qA58ssexe0a8h3c+2e0eFv2/r9Hor8E+VsJvWx3uJDdExMKbf9H3BcvKF2yL72rVFaQuSB79h/yixv0YqbOIF2C+8O1jXl4ftx+yQzelJHx8rtH1EZKzQ0KjfLcPDsUP3DFdxP2Myk2TdhvC6DLWuJrwuXa17/SozZmi8WvdseN1Yte6u8Lpste7m8Loxal1deN1otS41vC5LrftgmLnOtG+fuS7LtOUz4XXj1Lr54XWmLZnhdaYtl4XXmbZcGF5n2vLGleY6s1xmmOsyzeONC68zj9cnvM4s+yNXmOvM433XXJdhlumT4XXZKubrn5ebMV6tbr8=
*/