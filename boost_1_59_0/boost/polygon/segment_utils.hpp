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
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
*/