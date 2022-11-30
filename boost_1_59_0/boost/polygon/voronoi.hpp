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
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
*/