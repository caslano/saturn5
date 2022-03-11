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