// Boost.Polygon library voronoi.hpp header file

//          Copyright Andrii Sydorchuk 2010-2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_POLYGON_VORONOI
#define BOOST_POLYGON_VORONOI

#include "isotropy.hpp"
#include "point_concept.hpp"
#include "segment_concept.hpp"

#include "voronoi_builder.hpp"
#include "voronoi_diagram.hpp"

// Public methods to compute Voronoi diagram of a set of points and segments.
// Coordinates of the points and of the endpoints of the segments should belong
// to the 32-bit signed integer range [-2^31, 2^31-1]. To use wider input
// coordinate range voronoi_builder configuration via coordinate type traits
// is required.
// Complexity - O(N*logN), memory usage - O(N), N - number of input objects.
namespace boost {
namespace polygon {

template <typename Point, typename VB>
typename enable_if<
  typename gtl_if<
    typename is_point_concept<
      typename geometry_concept<Point>::type
    >::type
  >::type,
  std::size_t
>::type insert(const Point& point, VB* vb) {
  return vb->insert_point(x(point), y(point));
}

template <typename PointIterator, typename VB>
typename enable_if<
  typename gtl_if<
    typename is_point_concept<
      typename geometry_concept<
        typename std::iterator_traits<PointIterator>::value_type
      >::type
    >::type
  >::type,
  void
>::type insert(const PointIterator first, const PointIterator last, VB* vb) {
  for (PointIterator it = first; it != last; ++it) {
    insert(*it, vb);
  }
}

template <typename Segment, typename VB>
typename enable_if<
  typename gtl_if<
    typename is_segment_concept<
      typename geometry_concept<Segment>::type
    >::type
  >::type,
  std::size_t
>::type insert(const Segment& segment, VB* vb) {
  return vb->insert_segment(
      x(low(segment)), y(low(segment)),
      x(high(segment)), y(high(segment)));
}

template <typename SegmentIterator, typename VB>
typename enable_if<
  typename gtl_if<
    typename is_segment_concept<
      typename geometry_concept<
        typename std::iterator_traits<SegmentIterator>::value_type
      >::type
    >::type
  >::type,
  void
>::type insert(const SegmentIterator first,
               const SegmentIterator last,
               VB* vb) {
  for (SegmentIterator it = first; it != last; ++it) {
    insert(*it, vb);
  }
}

template <typename PointIterator, typename VD>
typename enable_if<
  typename gtl_if<
    typename is_point_concept<
      typename geometry_concept<
        typename std::iterator_traits<PointIterator>::value_type
      >::type
    >::type
  >::type,
  void
>::type construct_voronoi(const PointIterator first,
                          const PointIterator last,
                          VD* vd) {
  default_voronoi_builder builder;
  insert(first, last, &builder);
  builder.construct(vd);
}

template <typename SegmentIterator, typename VD>
typename enable_if<
  typename gtl_if<
    typename is_segment_concept<
      typename geometry_concept<
        typename std::iterator_traits<SegmentIterator>::value_type
      >::type
    >::type
  >::type,
  void
>::type construct_voronoi(const SegmentIterator first,
                          const SegmentIterator last,
                          VD* vd) {
  default_voronoi_builder builder;
  insert(first, last, &builder);
  builder.construct(vd);
}

template <typename PointIterator, typename SegmentIterator, typename VD>
typename enable_if<
  typename gtl_and<
    typename gtl_if<
      typename is_point_concept<
        typename geometry_concept<
          typename std::iterator_traits<PointIterator>::value_type
        >::type
      >::type
    >::type,
    typename gtl_if<
      typename is_segment_concept<
        typename geometry_concept<
          typename std::iterator_traits<SegmentIterator>::value_type
        >::type
      >::type
    >::type
  >::type,
  void
>::type construct_voronoi(const PointIterator p_first,
                          const PointIterator p_last,
                          const SegmentIterator s_first,
                          const SegmentIterator s_last,
                          VD* vd) {
  default_voronoi_builder builder;
  insert(p_first, p_last, &builder);
  insert(s_first, s_last, &builder);
  builder.construct(vd);
}
}  // polygon
}  // boost

#endif  // BOOST_POLYGON_VORONOI

/* voronoi.hpp
U+wYFtFXiksK5+Vqu8ZRZTBaviG4vzxWmwHK/OSvzxmo0XEfcYUqA7Gjv00ZMFAlXFeNDen9ZA7uhbG63nqni/9xlcWdlD/xeTfrX2xIs8k7HUBrHxwpEwrssql/Gj/Zr1/R6NOnv1P0Z5TZ63Olq6Xvme3/MrmHt9GfXlIW7APmU6sKDXaodrhb7HDFt0PbvbyyYeIAeSZ8Ghvcqx3BGZ+02bBXbPDFt0HGpMQ/K1Y25Aw0tl4V34Z0SqFOx7Md8/2P2DDK3gYtY6Lqk1MGyTO9ONqeOj3PNFX57xP9eXH0q93yFFujDXmDja2Xxrchw3gUoM+GA2LD8vg2pHNibnDW6rOhKM3Yuuw0NugqB9UeW8SG0fY2aDtHXqHawhCZbyKsL+/c+Qq4v0ab7l7RrVsQravnuljpjhsq/jux+XXpuBZQurtEd3esbmWtBl1pX8Qsy3cRI66B5hQWzp5fFKphh8ujY6wxr/9Ef4+dfpXHq/M8M+wKY+sX7LSZ5VDHsxrz/k+0ey8S7UifEm39Ok30+18p34tR/Wu+vvezqrw3i+aqpaJZPK/IUW250aouSLi2Ku8+w+R8YtWubHDzFNm4xvXwzmpa4vXVuWSL6Pss+vIgfUUdE5GSd+N0pqHOVfn3uUreDVttKDUu8KfxSMrlSHz+lfYm0d5goz1Vk7bp/zBcxnSr9nSnt9KxWpvmOtG8K0azMeGaqo2fFM11MZp+dwONPPiySseYovTXjZD38TH6xizJuvRVmR8X/Vtj9Kdp03SNFP/TGM2pCddUfemwaD5SqjTzpo7JyHSUNDjr/FX1DTrGENP/82qZBypKO1/TfZHp/ym6n7foZo0brU1XlfWcUcbWzRbdzDHZ56Ss94n2HZHa2vKsdCdeY2y93qqbqa+sTf9H0b3ZopsRLumE65r+jzKR9WqrLrnVcS2k8rpVNG9dJJrECIQe8IS+QpD4+5tM0R2aIedhq241uqucXo8r9LQX/zh8lzQ+890qNtxl2iDxEcoIDe+wVbn3yZRzZLS2Zv+VjaKbtFh08WeWFxzaNJOyxE9niUXT71mr455qlGg2ieZai6bpLONyB3W0jCEqzydE/4NFFn2qVkeelWaNTPJ1gbVugw+sNfQhpXlINMtLlebUghxHxZqA269Ns2iMsfVTi62avKnQULbm8y/RLFGaRblzQzN1Bz3xjUCMqfPLEq9vnv+zja1fKYunn3jtTJV30S63zTuNTGNsgLKhZKyx9TJbG5QBeq7rVRs4KDaULLSzIScvdN+soa+pc8accfKeNLoMNMU8mf5/otts1Z1aXJBhTIuuNRZlyni5zrfVTvz1icrzHtG9I1o3VOB64o5UnkdPkHsMW+3E66o87xLdrfNFt7CIp4DFcxz+FcErokYd5y6lPfJaY+ujZbHa/no975+V9g7R3r/ARrvGU6UjTiJT5Xui+N/YaXM5zEN3R1VjXaWO/Kv2tl1syCy3syHx73jN+Kfr5F2DTXvzNfq1+GCpsXyraHdYYKNd79P23Nu8/p8kvoH2+tp0m0X3CzZlXteY+HtbVd4pk+WZr52u+wa0vV6d5b1B9A/Fji9a3uOrNt5pirH1OJu+5anjeaiGe3sz/ku0d8aWubb2rbRPivYTdtqeOpcObVXXgakS02lT167GxPct1cZPiG7DwijdoLOGw5DRmW/vNIn3iy5zl0drXR8V3edLo3QrvW6emWnRVnleNl2emUWXObcDqzXEsqrz9hGluzhKd06e4R/Fu7Sg86LOe1JXjsRLl8Xa0OAmuNS9SkvZK/0jor+5PFafc4mD6/NaHb5yqu4X50ocyIIYfa1j+uuie1FsuWsb0zNVnmfIGGM=
*/