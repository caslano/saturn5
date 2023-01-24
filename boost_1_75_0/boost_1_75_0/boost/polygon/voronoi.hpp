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
l+vJeD5ZkSRPnSTG5vkxAk2S+i2c1s4VTWDmJZMCeW+nGKzpx7vxPcJPUHXkcWIyyNnzcWdnI9VN9mlwZtZe2XDv3eOfy3yNe4O+1+mw25NYUS/hDRcO3cDpE2g2bFcGfntC4eWbPQm44IDGvtvPBWLAMr/K2Yc9rhNUxSgnTjZjbZmXadyvVVby7oLGW1oCwp/YboSy4pYXG2Sp9L+XDegNQ29q8l/d09ArVZQXP6JTToowGdBXbRW6Z+q3P6sXDUOPhGhe+3NARQzKnoxVFeGTi8H/wFP4V3gQ+lfPbmDCrPELauTDr1jdcn9MTQhq0u/WGFdeO6BQv2hEuf6AUoNiw9CysPRH4jU/StwL0SBiE5Kp12LYx2g3SH6RoFXcE5QbFMevVC5Iat2WSb5IgLPvId2J3W//ML9bFIw1j5AwP299g9g+b4s5nw1DYNwxRbt0bd52I6i6UbLQgEGADy8nSH3R/th3131d/IPVC72ZwnnzAozmQYuEGoTrQkyKJsd7mGmvCtgi04rzU/ObxwYZD5eLCMQtboD8PRQ87zryJMGaWFeHKxoal/AV4P3s5u21rZiLyi1OKdDl6sA6Z+YhGMVJ+4jmVePLkFYvEUItlKH5eJO2Q4wwjwboT0jJYUb1RtW92INN0xCF1EGIdCD4EPOm/uApTxJVphgVbmJMtz/n0SC0vyjvh11aMCTW80Lr7U94R22ZuFwF
*/