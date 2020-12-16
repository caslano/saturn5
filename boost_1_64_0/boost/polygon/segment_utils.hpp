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
PUgEXvLbEr8VaGhVez4m7dlV4TfmnZGxzCXzmkS3efkWMdtEzpHyOuu+zDbGWVZ81GU7DkUcTMfuKedz3M7Ge/9Qm5V9W9juK6E+iNEyLlj71iHpW4/K2LAtuD/bH7/a7FvBiKw2jUlOKOVh25+LJJa/UTRXimZRWJNzTevjJYxyOL3mEdGcIJrZpI1slx4eQ3yNAX+bzg8VPmk38k1vv6VdBCLbhcwlFGnTaolTP3weNglvx6aWNNOmBmJZjPiGVoxrG4eGx61lQ832b/ax/PC60WbfDq8z+2xaeJ3Z73qE12Wo/lQxxBzz4vYnHxVIDJsZExkg8dsL7MtK6s9fIfP7qL+TJGZYbU94EcXjr6+z9iXpf6E+cfRC9LoYPkyvBm219B2KmDkupD9Y5l45mWyZz1r4aezZOkjViRkj1+p6mRKqTynHtNg6+Pfg2Dp4e3BsHfx6cGwdjBj88XXwTMrp6+BEuEzbXObvW8o8uv8F62Bd0M832aiD+wefvg6GSx34Lo6N2Xsulf5hXC8FY34+Nnamh5TFs+znKGEPmRf7jUzDhj2p1nmx48UbxIuriRdnEi+eoe3zMtvHjcSLS4kXTxIvTiZe/Ea8eJu2x3W0Nc7HPv7kDOJ22hifYx+n1PZ5uu3jrOLF87Q9bqcpFIdz+Zvpq3dsvK35iVMDH7vshym3tn1ecvFT4R487Ie1NcpPJSNJ/JthZ5gF34NNpGWy372y38UwIPt9R/xt9sI0+AIcD1+E18F9cB78PiyBL8Fa+DKsh/thAL4Cm+AP4Ub4I3gXfNX0V5J7ZrhB7LD6K/1R7HgDDoVH4TD4ptjxFsyHb8O58C+wGP4VOuFxses9eAv8G1wPT1j0W06j/xPRf03K4WdSDj8X/V9I/l+HpfCXkv9fwZXw13AV/A28Ff5O9A9Dox7kPhdusamHf4r+v+Bg+AEcA/8Np8KTMBd+KHacgpXwI+iHScG4DnAevBt2gJ+DHeFm2AkafnRyDwuXix1WP7pPdMAOeBEcCrvAsTAZjocXwzzYFZbCbtAFU2AV7C46NUlyryplvDXqm91bJL8Pw15wGxwCH4Ej4Jek/B+Tet8JZ8NvQDd8HNbAJ6R893aUe0u510QvdK36VEdpX0nSvmAv+BYcAt+GmfAYnAD/AmfAv8K58B14A3wX3gb/BjfBE/AR+Hf4JPwH/C58H/4Y/gv+HH4Afw0/hL+Hp+Ap+BH8RNBY7L8SdoCjYEeYBc+HE+AFcDLsDHPhhbAYdoEOmAxdsCushd2gH6bAtbA7vA32gJ+DPeFmeAncBnvDx2AqfBL2gbthX/g92A++BC+DB+AA+DocCI/CQfAdmAY/gkPg+ZT9UHgxvBz2h1fANHglHAaHwXHwKpgHh8MSOBJWwKthNbwG1sJ06IcZ8EaYCW+CWXA9HA1vh9lwMxwLH4Tj4dfhBPgEnAhb4HXwZ3AyPAKnwLfgVNiBNjMNfgLmwEtgLsyCM+BkOBPmwHw4HxZAJyyEjfB6uBaWwFthKbwXlsH7YTl8FC6GT8Il8AXogH+FTngSVsBT0AWTOW+7YVdYDfvDGjgGeuBYuALmQi8shithGfTDpTAAa2EjvBGughvhDXAzXA23wzVwF1wL98Ab4X64Dv4Z3gSPwk/CCzjvNsHOcAPsBu+E3WEzTIX3wGHwc3A4vA/mwc1wNnwAmt9HuFrm3SRtjfI7nCH9OB/2hLNgXzgbXgXnwAw4F06GBbAQFkIHLIK1cB68ERbD2+F8uAWWwm1wAVTjWJHY02gzjmWLPWPhYDgeXgknwInwWjgFXgcL4CS4FE6BXjgNroTTzXgIub+FE0TPGg/xtIybu2F/+BzMgs/DbPg=
*/