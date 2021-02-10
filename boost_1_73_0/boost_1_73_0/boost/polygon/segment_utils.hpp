/*
  Copyright 2012 Lucanus Simonson
 
  Use, modification and distribution are subject to the Boost Software License,
  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt).
*/

#ifndef BOOST_POLYGON_SEGMENT_UTILS_HPP
#define BOOST_POLYGON_SEGMENT_UTILS_HPP

#include <iterator>
#include <set>
#include <vector>

#include "detail/scan_arbitrary.hpp"
#include "isotropy.hpp"
#include "rectangle_concept.hpp"
#include "segment_concept.hpp"

namespace boost {
namespace polygon {

template <typename Segment, typename SegmentIterator>
typename enable_if<
  typename gtl_and<
    typename gtl_if<
      typename is_segment_concept<
        typename geometry_concept<
          typename std::iterator_traits<SegmentIterator>::value_type
        >::type
      >::type
    >::type,
    typename gtl_if<
      typename is_segment_concept<
        typename geometry_concept<Segment>::type
      >::type
    >::type
  >::type,
  void
>::type
intersect_segments(
    std::vector<std::pair<std::size_t, Segment> >& result,
    SegmentIterator first, SegmentIterator last) {
  typedef typename segment_traits<Segment>::coordinate_type Unit;
  typedef typename scanline_base<Unit>::Point Point;
  typedef typename scanline_base<Unit>::half_edge half_edge;
  typedef int segment_id;
  std::vector<std::pair<half_edge, segment_id> > half_edges;
  std::vector<std::pair<half_edge, segment_id> > half_edges_out;
  segment_id id_in = 0;
  half_edges.reserve(std::distance(first, last));
  for (; first != last; ++first) {
    Point l, h;
    assign(l, low(*first));
    assign(h, high(*first));
    half_edges.push_back(std::make_pair(half_edge(l, h), id_in++));
  }
  half_edges_out.reserve(half_edges.size());
  // Apparently no need to pre-sort data when calling validate_scan.
  if (half_edges.size() != 0) {
    line_intersection<Unit>::validate_scan(
        half_edges_out, half_edges.begin(), half_edges.end());
  }

  result.reserve(result.size() + half_edges_out.size());
  for (std::size_t i = 0; i < half_edges_out.size(); ++i) {
    std::size_t id = (std::size_t)(half_edges_out[i].second);
    Point l = half_edges_out[i].first.first;
    Point h = half_edges_out[i].first.second;
    result.push_back(std::make_pair(id, construct<Segment>(l, h)));
  }
}

template <typename SegmentContainer, typename SegmentIterator>
typename enable_if<
  typename gtl_and<
    typename gtl_if<
      typename is_segment_concept<
        typename geometry_concept<
          typename std::iterator_traits<SegmentIterator>::value_type
        >::type
      >::type
    >::type,
    typename gtl_if<
      typename is_segment_concept<
        typename geometry_concept<
          typename SegmentContainer::value_type
        >::type
      >::type
    >::type
  >::type,
  void
>::type
intersect_segments(
    SegmentContainer& result,
    SegmentIterator first,
    SegmentIterator last) {
  typedef typename SegmentContainer::value_type segment_type;
  typedef typename segment_traits<segment_type>::coordinate_type Unit;
  typedef typename scanline_base<Unit>::Point Point;
  typedef typename scanline_base<Unit>::half_edge half_edge;
  typedef int segment_id;
  std::vector<std::pair<half_edge, segment_id> > half_edges;
  std::vector<std::pair<half_edge, segment_id> > half_edges_out;
  segment_id id_in = 0;
  half_edges.reserve(std::distance(first, last));
  for (; first != last; ++first) {
    Point l, h;
    assign(l, low(*first));
    assign(h, high(*first));
    half_edges.push_back(std::make_pair(half_edge(l, h), id_in++));
  }
  half_edges_out.reserve(half_edges.size());
  // Apparently no need to pre-sort data when calling validate_scan.
  if (half_edges.size() != 0) {
    line_intersection<Unit>::validate_scan(
        half_edges_out, half_edges.begin(), half_edges.end());
  }

  result.reserve(result.size() + half_edges_out.size());
  for (std::size_t i = 0; i < half_edges_out.size(); ++i) {
    Point l = half_edges_out[i].first.first;
    Point h = half_edges_out[i].first.second;
    result.push_back(construct<segment_type>(l, h));
  }
}

template <typename Rectangle, typename SegmentIterator>
typename enable_if<
  typename gtl_and<
    typename gtl_if<
      typename is_rectangle_concept<
        typename geometry_concept<Rectangle>::type
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
  bool
>::type
envelope_segments(
    Rectangle& rect,
    SegmentIterator first,
    SegmentIterator last) {
  for (SegmentIterator it = first; it != last; ++it) {
    if (it == first) {
      set_points(rect, low(*it), high(*it));
    } else {
      encompass(rect, low(*it));
      encompass(rect, high(*it));
    }
  }
  return first != last;
}
}  // polygon
}  // boost

#endif  // BOOST_POLYGON_SEGMENT_UTILS_HPP

/* segment_utils.hpp
VBUZk76gslg2HjmLmsY/BuCCk5hrPejKn15/NP7dCtWgUiT5vgYdRjyjENCYY35FUkjJsjkaV5kuNF0zbcAoEHc7GXvelev5rje88QwD5TxLn1S8AiEkfKBZpLZMzBC6KbBQlYqLLFTrXYBOSlwOiRq3LsY6u5q47jc8SZ5f2b+612OvaWzCxJLRzR6TajNFXEWF+ymbCx2ozuHGhltGucbqFqkUelPNOY90JmPcV36RpVj5xghL4oc0l/62CA1ztVrZdE1wRVA75AvTggNT0zL2jylTwztm82M1vfVD7G4t9nq9PsCjrZaHs1oe4gN+zHk1/LwWvNPv2p3epd2224q8/3qUeqGoGyyLT2akOt9gBmS/fKdgrffk3Wq53aqK4awG5M10AkLswxpscOeVuMN6Kt4x1kWN0ErEMXmvWq5+fQ/x6/9IztskbyGXPw7ZMvqVjFK5W1vt2otrp6mxIE9vl5JRvSqPnHZHSXppqoMbz2e4mgz/wCtmPPurVxHhYHDWvbwYkH4cD2J63hsEvU7ffL2b3zYzppft48JtOPVOlNOg9yOoEYU+gfSq/oA3HouNba8vK3VP4fv2BgR9a6fsgep/AQf6Ktq7TKcz4z9QSwMECgAAAAgALWdKUlwtpQ3QAwAAcAwAACEA
*/