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