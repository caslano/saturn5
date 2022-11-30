// Boost.Polygon library segment_concept.hpp header file

// Copyright (c) Intel Corporation 2008.
// Copyright (c) 2008-2012 Simonson Lucanus.
// Copyright (c) 2012-2012 Andrii Sydorchuk.

// See http://www.boost.org for updates, documentation, and revision history.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_POLYGON_SEGMENT_CONCEPT_HPP
#define BOOST_POLYGON_SEGMENT_CONCEPT_HPP

#include "isotropy.hpp"
#include "segment_traits.hpp"
#include "rectangle_concept.hpp"

namespace boost {
namespace polygon {

struct segment_concept {};

template <typename ConceptType>
struct is_segment_concept {
  typedef gtl_no type;
};

template <>
struct is_segment_concept<segment_concept> {
  typedef gtl_yes type;
};

template <typename ConceptType>
struct is_mutable_segment_concept {
  typedef gtl_no type;
};

template <>
struct is_mutable_segment_concept<segment_concept> {
  typedef gtl_yes type;
};

template <typename GeometryType, typename BoolType>
struct segment_distance_type_by_concept {
  typedef void type;
};

template <typename GeometryType>
struct segment_distance_type_by_concept<GeometryType, gtl_yes> {
  typedef typename coordinate_traits<
    typename segment_traits<GeometryType>::coordinate_type
  >::coordinate_distance type;
};

template <typename GeometryType>
struct segment_distance_type {
  typedef typename segment_distance_type_by_concept<
    GeometryType,
    typename is_segment_concept<
      typename geometry_concept<GeometryType>::type
    >::type
  >::type type;
};

template <typename GeometryType, typename BoolType>
struct segment_point_type_by_concept {
  typedef void type;
};

template <typename GeometryType>
struct segment_point_type_by_concept<GeometryType, gtl_yes> {
  typedef typename segment_traits<GeometryType>::point_type type;
};

template <typename GeometryType>
struct segment_point_type {
  typedef typename segment_point_type_by_concept<
    GeometryType,
    typename is_segment_concept<
      typename geometry_concept<GeometryType>::type
    >::type
  >::type type;
};

template <typename GeometryType, typename BoolType>
struct segment_coordinate_type_by_concept {
  typedef void type;
};

template <typename GeometryType>
struct segment_coordinate_type_by_concept<GeometryType, gtl_yes> {
  typedef typename segment_traits<GeometryType>::coordinate_type type;
};

template <typename GeometryType>
struct segment_coordinate_type {
  typedef typename segment_coordinate_type_by_concept<
    GeometryType,
    typename is_segment_concept<
      typename geometry_concept<GeometryType>::type
    >::type
  >::type type;
};

struct y_s_get : gtl_yes {};

template <typename Segment>
typename enable_if<
  typename gtl_and<
    y_s_get,
    typename is_segment_concept<
      typename geometry_concept<Segment>::type
    >::type
  >::type,
typename segment_point_type<Segment>::type>::type
get(const Segment& segment, direction_1d dir) {
  return segment_traits<Segment>::get(segment, dir);
}

struct y_s_set : gtl_yes {};

template <typename Segment, typename Point>
typename enable_if<
  typename gtl_and_3<
    y_s_set,
    typename is_mutable_segment_concept<
      typename geometry_concept<Segment>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<Point>::type
    >::type
  >::type,
void>::type set(Segment& segment, direction_1d dir, const Point& point) {
  segment_mutable_traits<Segment>::set(segment, dir, point);
}

struct y_s_construct : gtl_yes {};

template <typename Segment, typename Point1, typename Point2>
typename enable_if<
  typename gtl_and_4<
    y_s_construct,
    typename is_mutable_segment_concept<
      typename geometry_concept<Segment>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<Point1>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<Point2>::type
    >::type
  >::type,
Segment>::type construct(const Point1& low, const Point2& high) {
  return segment_mutable_traits<Segment>::construct(low, high);
}

struct y_s_copy_construct : gtl_yes {};

template <typename Segment1, typename Segment2>
typename enable_if<
  typename gtl_and_3<
    y_s_copy_construct,
    typename is_mutable_segment_concept<
      typename geometry_concept<Segment1>::type
    >::type,
    typename is_segment_concept<
      typename geometry_concept<Segment2>::type
    >::type
  >::type,
Segment1>::type copy_construct(const Segment2& segment) {
  return construct<Segment1>(get(segment, LOW), get(segment, HIGH));
}

struct y_s_assign : gtl_yes {};

template <typename Segment1, typename Segment2>
typename enable_if<
  typename gtl_and_3<
    y_s_assign,
    typename is_mutable_segment_concept<
      typename geometry_concept<Segment1>::type
    >::type,
    typename is_segment_concept<
      typename geometry_concept<Segment2>::type
    >::type
  >::type,
Segment1>::type& assign(Segment1& segment1, const Segment2& segment2) {
  return segment1 = copy_construct<Segment1>(segment2);
}

struct y_s_equivalence : gtl_yes {};

template <typename Segment1, typename Segment2>
typename enable_if<
  typename gtl_and_3<
    y_s_equivalence,
    typename is_segment_concept<
      typename geometry_concept<Segment1>::type
    >::type,
    typename is_segment_concept<
      typename geometry_concept<Segment2>::type
    >::type
  >::type,
bool>::type equivalence(const Segment1& segment1, const Segment2& segment2) {
  return get(segment1, LOW) == get(segment2, LOW) &&
         get(segment1, HIGH) == get(segment2, HIGH);
}

struct y_s_low : gtl_yes {};

template <typename Segment>
typename enable_if<
  typename gtl_and<
    y_s_low,
    typename is_segment_concept<
      typename geometry_concept<Segment>::type
    >::type
  >::type,
typename segment_point_type<Segment>::type>::type low(const Segment& segment) {
  return get(segment, LOW);
}

struct y_s_high : gtl_yes {};

template <typename Segment>
typename enable_if<
  typename gtl_and<
    y_s_high,
    typename is_segment_concept<
      typename geometry_concept<Segment>::type
    >::type
  >::type,
typename segment_point_type<Segment>::type>::type high(const Segment& segment) {
  return get(segment, HIGH);
}

struct y_s_center : gtl_yes {};

template <typename Segment>
typename enable_if<
  typename gtl_and<
    y_s_center,
    typename is_segment_concept<
      typename geometry_concept<Segment>::type
    >::type
  >::type,
typename segment_point_type<Segment>::type>::type
center(const Segment& segment) {
  return construct<typename segment_point_type<Segment>::type>(
      (x(high(segment)) + x(low(segment)))/2,
      (y(high(segment)) + y(low(segment)))/2);
}

struct y_s_low2 : gtl_yes {};

template <typename Segment, typename Point>
typename enable_if<
  typename gtl_and_3<
    y_s_low2,
    typename is_mutable_segment_concept<
      typename geometry_concept<Segment>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<Point>::type
    >::type
  >::type,
void>::type low(Segment& segment, const Point& point) {
  set(segment, LOW, point);
}

struct y_s_high2 : gtl_yes {};

template <typename Segment, typename Point>
typename enable_if<
  typename gtl_and_3<
    y_s_high2,
    typename is_mutable_segment_concept<
      typename geometry_concept<Segment>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<Point>::type
    >::type
  >::type,
void>::type high(Segment& segment, const Point& point) {
  set(segment, HIGH, point);
}

struct y_s_orientation1 : gtl_yes {};

// -1 for CW, 0 for collinear and 1 for CCW.
template <typename Segment1, typename Segment2>
typename enable_if<
  typename gtl_and_3<
    y_s_orientation1,
    typename is_segment_concept<
      typename geometry_concept<Segment1>::type
    >::type,
    typename is_segment_concept<
      typename geometry_concept<Segment2>::type
    >::type
  >::type,
int>::type orientation(const Segment1& segment1, const Segment2& segment2) {
  typedef typename coordinate_traits<
    typename segment_traits<Segment1>::coordinate_type
  >::manhattan_area_type int_x2;
  typedef typename coordinate_traits<
    typename segment_traits<Segment1>::coordinate_type
  >::unsigned_area_type uint_x2;
  int_x2 a1 = (int_x2)x(high(segment1)) - (int_x2)x(low(segment1));
  int_x2 b1 = (int_x2)y(high(segment1)) - (int_x2)y(low(segment1));
  int_x2 a2 = (int_x2)x(high(segment2)) - (int_x2)x(low(segment2));
  int_x2 b2 = (int_x2)y(high(segment2)) - (int_x2)y(low(segment2));

  int sign1 = 0;
  int sign2 = 0;
  if (a1 && b2)
    sign1 = ((a1 > 0) ^ (b2 > 0)) ? -1 : 1;
  if (a2 && b1)
    sign2 = ((a2 > 0) ^ (b1 > 0)) ? -1 : 1;

  if (sign1 != sign2)
    return (sign1 < sign2) ? -1 : 1;
  uint_x2 a3 = (uint_x2)(a1 < 0 ? -a1 : a1) * (uint_x2)(b2 < 0 ? -b2 : b2);
  uint_x2 b3 = (uint_x2)(b1 < 0 ? -b1 : b1) * (uint_x2)(a2 < 0 ? -a2 : a2);
  if (a3 == b3)
    return 0;
  return ((a3 < b3) ^ (sign1 == 1)) ? 1 : -1;
}

struct y_s_orientation2 : gtl_yes {};

// -1 for right, 0 for collinear and 1 for left.
template <typename Segment, typename Point>
typename enable_if<
  typename gtl_and_3<
    y_s_orientation2,
    typename is_segment_concept<
      typename geometry_concept<Segment>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<Point>::type
    >::type
  >::type,
int>::type orientation(const Segment& segment, const Point& point) {
  Segment segment2 = construct<Segment>(high(segment), point);
  return orientation(segment, segment2);
}

struct y_s_contains : gtl_yes {};

template <typename Segment, typename Point>
typename enable_if<
  typename gtl_and_3<
    y_s_contains,
    typename is_segment_concept<
      typename geometry_concept<Segment>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<Point>::type
    >::type
  >::type,
bool>::type contains(const Segment& segment,
    const Point& point, bool consider_touch = true ) {
  if (orientation(segment, point))
    return false;
  rectangle_data<typename segment_coordinate_type<Segment>::type> rect;
  set_points(rect, low(segment), high(segment));
  if (!contains(rect, point, true))
    return false;
  if (!consider_touch &&
      (equivalence(low(segment), point) ||
       equivalence(high(segment), point)))
    return false;
  return true;
}

struct y_s_contains2 : gtl_yes {};

template <typename Segment1, typename Segment2>
typename enable_if<
  typename gtl_and_3<
    y_s_contains2,
    typename is_segment_concept<
      typename geometry_concept<Segment1>::type
    >::type,
    typename is_segment_concept<
      typename geometry_concept<Segment2>::type
    >::type
  >::type,
bool>::type contains(const Segment1& segment1,
    const Segment2& segment2, bool consider_touch = true) {
  return contains(segment1, get(segment2, LOW), consider_touch) &&
         contains(segment1, get(segment2, HIGH), consider_touch);
}

struct y_s_length : gtl_yes {};

template <typename Segment>
typename enable_if<
  typename gtl_and<
    y_s_length,
    typename is_segment_concept<
      typename geometry_concept<Segment>::type
    >::type
  >::type,
typename segment_distance_type<Segment>::type>::type
length(const Segment& segment) {
  return euclidean_distance(low(segment), high(segment));
}

struct y_s_scale_up : gtl_yes {};

template <typename Segment>
typename enable_if<
  typename gtl_and<
    y_s_scale_up,
    typename is_mutable_segment_concept<
      typename geometry_concept<Segment>::type
    >::type
  >::type,
Segment>::type& scale_up(Segment& segment,
    typename coordinate_traits<
      typename segment_coordinate_type<Segment>::type
    >::unsigned_area_type factor) {
  typename segment_point_type<Segment>::type l = low(segment);
  typename segment_point_type<Segment>::type h = high(segment);
  low(segment, scale_up(l, factor));
  high(segment, scale_up(h, factor));
  return segment;
}

struct y_s_scale_down : gtl_yes {};

template <typename Segment>
typename enable_if<
  typename gtl_and<
    y_s_scale_down,
    typename is_mutable_segment_concept<
      typename geometry_concept<Segment>::type
    >::type
  >::type,
Segment>::type& scale_down(Segment& segment,
    typename coordinate_traits<
      typename segment_coordinate_type<Segment>::type
    >::unsigned_area_type factor) {
  typename segment_point_type<Segment>::type l = low(segment);
  typename segment_point_type<Segment>::type h = high(segment);
  low(segment, scale_down(l, factor));
  high(segment, scale_down(h, factor));
  return segment;
}

struct y_s_scale : gtl_yes {};

template <typename Segment, typename Scale>
typename enable_if<
  typename gtl_and<
    y_s_scale,
    typename is_mutable_segment_concept<
      typename geometry_concept<Segment>::type
    >::type
  >::type,
Segment>::type& scale(Segment& segment, const Scale& sc) {
  typename segment_point_type<Segment>::type l = low(segment);
  typename segment_point_type<Segment>::type h = high(segment);
  low(segment, scale(l, sc));
  high(segment, scale(h, sc));
  return segment;
}

struct y_s_transform : gtl_yes {};

template <typename Segment, typename Transform>
typename enable_if<
  typename gtl_and<
    y_s_transform,
    typename is_mutable_segment_concept<
      typename geometry_concept<Segment>::type
    >::type
  >::type,
Segment>::type& transform(Segment& segment, const Transform& tr) {
  typename segment_point_type<Segment>::type l = low(segment);
  typename segment_point_type<Segment>::type h = high(segment);
  low(segment, transform(l, tr));
  high(segment, transform(h, tr));
  return segment;
}

struct y_s_move : gtl_yes {};

template <typename Segment>
typename enable_if<
  typename gtl_and<
    y_s_move,
    typename is_mutable_segment_concept<
      typename geometry_concept<Segment>::type
    >::type
  >::type,
Segment>::type& move(Segment& segment, orientation_2d orient,
    typename segment_coordinate_type<Segment>::type displacement) {
  typename segment_point_type<Segment>::type l = low(segment);
  typename segment_point_type<Segment>::type h = high(segment);
  low(segment, move(l, orient, displacement));
  high(segment, move(h, orient, displacement));
  return segment;
}

struct y_s_convolve : gtl_yes {};

template <typename Segment, typename Point>
typename enable_if<
  typename gtl_and_3<
    y_s_convolve,
    typename is_mutable_segment_concept<
      typename geometry_concept<Segment>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<Point>::type
    >::type
  >::type,
Segment>::type& convolve(Segment& segment, const Point& point) {
  typename segment_point_type<Segment>::type l = low(segment);
  typename segment_point_type<Segment>::type h = high(segment);
  low(segment, convolve(l, point));
  high(segment, convolve(h, point));
  return segment;
}

struct y_s_deconvolve : gtl_yes {};

template <typename Segment, typename Point>
typename enable_if<
  typename gtl_and_3<
    y_s_deconvolve,
    typename is_mutable_segment_concept<
      typename geometry_concept<Segment>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<Point>::type
    >::type
  >::type,
Segment>::type& deconvolve(Segment& segment, const Point& point) {
  typename segment_point_type<Segment>::type l = low(segment);
  typename segment_point_type<Segment>::type h = high(segment);
  low(segment, deconvolve(l, point));
  high(segment, deconvolve(h, point));
  return segment;
}

struct y_s_abuts1 : gtl_yes {};

template <typename Segment1, typename Segment2>
typename enable_if<
  typename gtl_and_3<
    y_s_abuts1,
    typename is_segment_concept<
      typename geometry_concept<Segment1>::type
    >::type,
    typename is_segment_concept<
      typename geometry_concept<Segment2>::type
    >::type
  >::type,
bool>::type abuts(const Segment1& segment1,
    const Segment2& segment2, direction_1d dir) {
  return dir.to_int() ? equivalence(low(segment2) , high(segment1)) :
                        equivalence(low(segment1) , high(segment2));
}

struct y_s_abuts2 : gtl_yes {};

template <typename Segment1, typename Segment2>
typename enable_if<
  typename gtl_and_3<
    y_s_abuts2,
    typename is_segment_concept<
      typename geometry_concept<Segment1>::type
    >::type,
    typename is_segment_concept<
      typename geometry_concept<Segment2>::type
    >::type
  >::type,
bool>::type abuts(const Segment1& segment1, const Segment2& segment2) {
  return abuts(segment1, segment2, HIGH) || abuts(segment1, segment2, LOW);
}

struct y_s_e_intersects : gtl_yes {};

template <typename Segment1, typename Segment2>
typename enable_if<
  typename gtl_and_3<
    y_s_e_intersects,
    typename is_segment_concept<
      typename geometry_concept<Segment1>::type
    >::type,
    typename is_segment_concept<
      typename geometry_concept<Segment2>::type
    >::type
  >::type,
bool
>::type intersects(const Segment1& segment1, const Segment2& segment2,
    bool consider_touch = true) {
  rectangle_data<typename segment_coordinate_type<Segment1>::type> rect1, rect2;
  set_points(rect1, low(segment1), high(segment1));
  set_points(rect2, low(segment2), high(segment2));
  // Check if axis-parallel rectangles containing segments intersect.
  if (!intersects(rect1, rect2, true))
    return false;
  int or1_1 = orientation(segment1, low(segment2));
  int or1_2 = orientation(segment1, high(segment2));
  if (or1_1 * or1_2 > 0)
    return false;
  int or2_1 = orientation(segment2, low(segment1));
  int or2_2 = orientation(segment2, high(segment1));
  if (or2_1 * or2_2 > 0)
    return false;
  if (consider_touch || (or1_1 && or1_2) || (or2_1 && or2_2))
    return true;
  if (or1_1 || or1_2)
    return false;
  return intersects(vertical(rect1), vertical(rect2), false) ||
         intersects(horizontal(rect1), horizontal(rect2), false);
}

struct y_s_e_dist : gtl_yes {};

template <typename Segment, typename Point>
typename enable_if<
  typename gtl_and_3<
    y_s_e_dist,
    typename is_segment_concept<
      typename geometry_concept<Segment>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<Point>::type
    >::type
  >::type,
typename segment_distance_type<Segment>::type>::type
euclidean_distance(const Segment& segment, const Point& point) {
  typedef typename segment_distance_type<Segment>::type Unit;
  Unit x1 = x(low(segment));
  Unit y1 = y(low(segment));
  Unit x2 = x(high(segment));
  Unit y2 = y(high(segment));
  Unit X = x(point);
  Unit Y = y(point);
  Unit A = X - x1;
  Unit B = Y - y1;
  Unit C = x2 - x1;
  Unit D = y2 - y1;
  Unit param = (A * C + B * D);
  Unit length_sq = C * C + D * D;
  if (param > length_sq) {
    return euclidean_distance(high(segment), point);
  } else if (param < 0.0) {
    return euclidean_distance(low(segment), point);
  }
  if (length_sq == 0.0)
    return 0.0;
  Unit denom = std::sqrt(length_sq);
  Unit result = (A * D - C * B) / denom;
  return (result < 0.0) ? -result : result;
}

struct y_s_e_dist2 : gtl_yes {};

template <typename Segment1, typename Segment2>
typename enable_if<
  typename gtl_and_3<
    y_s_e_dist2,
    typename is_segment_concept<
      typename geometry_concept<Segment1>::type
    >::type,
    typename is_segment_concept<
      typename geometry_concept<Segment2>::type
    >::type
  >::type,
typename segment_distance_type<Segment1>::type>::type
euclidean_distance(const Segment1& segment1, const Segment2& segment2) {
  if (intersects(segment1, segment2))
    return 0.0;
  typename segment_distance_type<Segment1>::type
      result1 = euclidean_distance(segment1, low(segment2)),
      result2 = euclidean_distance(segment1, high(segment2)),
      result3 = euclidean_distance(segment2, low(segment1)),
      result4 = euclidean_distance(segment2, high(segment1));
  if (result2 < result1)
    result1 = result2;
  if (result4 < result3)
    result3 = result4;
  return (result1 < result3) ? result1 : result3;
}
}  // polygon
}  // boost

#endif  // BOOST_POLYGON_SEGMENT_CONCEPT_HPP

/* segment_concept.hpp
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
*/