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