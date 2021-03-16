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
8O1T8NPe4meBeD49BfzpFvyfxHPHFPAdLfiFMeUnWtbm88POsDHnKY0WxSg8u8yGM2Fr0a2ARZ6XmR4BK/9nZyuyj+qXTrfHuA0tiXGd1ellir6ZZPerRUtFv2WiH+J2cN5lFJ+p6dehOwWeu2K2P/WolbDve0Qb8pVg/0Kq8am+teneWHBvVXCe1dF4Un2OoxWCl8UxZcv3ad/vFTHF8Hu17bji0SqB50HRV841a2fxhX0mZZlz/TfRZ7VG7zY=
*/