// Boost.Polygon library point_concept.hpp header file

// Copyright (c) Intel Corporation 2008.
// Copyright (c) 2008-2012 Simonson Lucanus.
// Copyright (c) 2012-2012 Andrii Sydorchuk.

// See http://www.boost.org for updates, documentation, and revision history.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_POLYGON_POINT_CONCEPT_HPP
#define BOOST_POLYGON_POINT_CONCEPT_HPP

#include "isotropy.hpp"
#include "point_traits.hpp"

namespace boost {
namespace polygon {

struct point_concept {};

template <typename ConceptType>
struct is_point_concept {
  typedef gtl_no type;
};

template <>
struct is_point_concept<point_concept> {
  typedef gtl_yes type;
};

template <typename ConceptType>
struct is_mutable_point_concept {
  typedef gtl_no type;
};

template <>
struct is_mutable_point_concept<point_concept> {
  typedef gtl_yes type;
};

template <typename GeometryType, typename BoolType>
struct point_coordinate_type_by_concept {
  typedef void type;
};

template <typename GeometryType>
struct point_coordinate_type_by_concept<GeometryType, gtl_yes> {
  typedef typename point_traits<GeometryType>::coordinate_type type;
};

template <typename GeometryType>
struct point_coordinate_type {
  typedef typename point_coordinate_type_by_concept<
    GeometryType,
    typename is_point_concept<
      typename geometry_concept<GeometryType>::type
    >::type
  >::type type;
};

template <typename GeometryType, typename BoolType>
struct point_difference_type_by_concept {
  typedef void type;
};

template <typename GeometryType>
struct point_difference_type_by_concept<GeometryType, gtl_yes> {
  typedef typename coordinate_traits<
    typename point_traits<GeometryType>::coordinate_type
  >::coordinate_difference type;
};

template <typename GeometryType>
struct point_difference_type {
  typedef typename point_difference_type_by_concept<
    GeometryType,
    typename is_point_concept<
      typename geometry_concept<GeometryType>::type
    >::type
  >::type type;
};

template <typename GeometryType, typename BoolType>
struct point_distance_type_by_concept {
  typedef void type;
};

template <typename GeometryType>
struct point_distance_type_by_concept<GeometryType, gtl_yes> {
  typedef typename coordinate_traits<
    typename point_coordinate_type<GeometryType>::type
  >::coordinate_distance type;
};

template <typename GeometryType>
struct point_distance_type {
  typedef typename point_distance_type_by_concept<
    GeometryType,
    typename is_point_concept<
      typename geometry_concept<GeometryType>::type
    >::type
  >::type type;
};

struct y_pt_get : gtl_yes {};

template <typename PointType>
typename enable_if<
  typename gtl_and<
    y_pt_get,
    typename is_point_concept<
      typename geometry_concept<PointType>::type
    >::type
  >::type,
  typename point_coordinate_type<PointType>::type
>::type get(const PointType& point, orientation_2d orient) {
  return point_traits<PointType>::get(point, orient);
}

struct y_pt_set : gtl_yes {};

template <typename PointType>
typename enable_if<
  typename gtl_and<
    y_pt_set,
    typename is_mutable_point_concept<
      typename geometry_concept<PointType>::type
    >::type
  >::type,
  void
>::type set(PointType& point, orientation_2d orient,
    typename point_mutable_traits<PointType>::coordinate_type value) {
  point_mutable_traits<PointType>::set(point, orient, value);
}

struct y_pt_construct : gtl_yes {};

template <typename PointType>
typename enable_if<
  typename gtl_and<
    y_pt_construct,
    typename is_mutable_point_concept<
      typename geometry_concept<PointType>::type
    >::type
  >::type,
PointType>::type construct(
    typename point_mutable_traits<PointType>::coordinate_type x,
    typename point_mutable_traits<PointType>::coordinate_type y) {
  return point_mutable_traits<PointType>::construct(x, y);
}

struct y_pt_assign : gtl_yes {};

template <typename PointType1, typename PointType2>
typename enable_if<
  typename gtl_and_3<
    y_pt_assign,
    typename is_mutable_point_concept<
      typename geometry_concept<PointType1>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<PointType2>::type
    >::type
>::type,
PointType1>::type& assign(PointType1& lvalue, const PointType2& rvalue) {
  set(lvalue, HORIZONTAL, get(rvalue, HORIZONTAL));
  set(lvalue, VERTICAL, get(rvalue, VERTICAL));
  return lvalue;
}

struct y_p_x : gtl_yes {};

template <typename PointType>
typename enable_if<
  typename gtl_and<
    y_p_x,
    typename is_point_concept<
      typename geometry_concept<PointType>::type
    >::type
  >::type,
  typename point_coordinate_type<PointType>::type
>::type x(const PointType& point) {
  return get(point, HORIZONTAL);
}

struct y_p_y : gtl_yes {};

template <typename PointType>
typename enable_if<
  typename gtl_and<
    y_p_y,
    typename is_point_concept<
      typename geometry_concept<PointType>::type
    >::type
  >::type,
  typename point_coordinate_type<PointType>::type
>::type y(const PointType& point) {
  return get(point, VERTICAL);
}

struct y_p_sx : gtl_yes {};

template <typename PointType>
typename enable_if<
  typename gtl_and<
    y_p_sx,
    typename is_mutable_point_concept<
      typename geometry_concept<PointType>::type
    >::type
  >::type,
void>::type x(PointType& point,
    typename point_mutable_traits<PointType>::coordinate_type value) {
  set(point, HORIZONTAL, value);
}

struct y_p_sy : gtl_yes {};

template <typename PointType>
typename enable_if<
  typename gtl_and<
    y_p_sy,
    typename is_mutable_point_concept<
      typename geometry_concept<PointType>::type
    >::type
  >::type,
void>::type y(PointType& point,
    typename point_mutable_traits<PointType>::coordinate_type value) {
  set(point, VERTICAL, value);
}

struct y_pt_equiv : gtl_yes {};

template <typename PointType1, typename PointType2>
typename enable_if<
  typename gtl_and_3<
    y_pt_equiv,
    typename is_point_concept<
      typename geometry_concept<PointType1>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<PointType2>::type
    >::type
  >::type,
bool>::type equivalence(
    const PointType1& point1, const PointType2& point2) {
  return (x(point1) == x(point2)) && (y(point1) == y(point2));
}

struct y_pt_man_dist : gtl_yes {};

template <typename PointType1, typename PointType2>
typename enable_if<
  typename gtl_and_3<
    y_pt_man_dist,
    typename is_point_concept<
      typename geometry_concept<PointType1>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<PointType2>::type
    >::type
  >::type,
typename point_difference_type<PointType1>::type>::type
manhattan_distance(const PointType1& point1, const PointType2& point2) {
  return euclidean_distance(point1, point2, HORIZONTAL) +
         euclidean_distance(point1, point2, VERTICAL);
}

struct y_pt_ed1 : gtl_yes {};

template <typename PointType1, typename PointType2>
typename enable_if<
  typename gtl_and_3<
    y_pt_ed1,
    typename is_point_concept<
      typename geometry_concept<PointType1>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<PointType2>::type
    >::type
  >::type,
typename point_difference_type<PointType1>::type>::type
euclidean_distance(
    const PointType1& point1,
    const PointType2& point2,
    orientation_2d orient) {
  typename point_difference_type<PointType1>::type dif =
      get(point1, orient) - get(point2, orient);
  return (dif < 0) ? -dif : dif;
}

struct y_pt_eds : gtl_yes {};

template <typename PointType1, typename PointType2>
typename enable_if<
  typename gtl_and_3<
    y_pt_eds,
    typename is_point_concept<
      typename geometry_concept<PointType1>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<PointType2>::type
    >::type
  >::type,
typename point_difference_type<PointType1>::type>::type
distance_squared(const PointType1& point1, const PointType2& point2) {
  typename point_difference_type<PointType1>::type dx =
      euclidean_distance(point1, point2, HORIZONTAL);
  typename point_difference_type<PointType1>::type dy =
      euclidean_distance(point1, point2, VERTICAL);
  dx *= dx;
  dy *= dy;
  return dx + dy;
}

struct y_pt_ed2 : gtl_yes {};

template <typename PointType1, typename PointType2>
typename enable_if<
  typename gtl_and_3<
    y_pt_ed2,
    typename is_point_concept<
      typename geometry_concept<PointType1>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<PointType2>::type
    >::type
  >::type,
typename point_distance_type<PointType1>::type>::type
euclidean_distance(const PointType1& point1, const PointType2& point2) {
  return (std::sqrt)(
      static_cast<double>(distance_squared(point1, point2)));
}

struct y_pt_convolve : gtl_yes {};

template <typename PointType1, typename PointType2>
typename enable_if<
  typename gtl_and_3<
    y_pt_convolve,
    typename is_mutable_point_concept<
      typename geometry_concept<PointType1>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<PointType2>::type
    >::type
  >::type,
PointType1>::type& convolve(PointType1& lvalue, const PointType2& rvalue) {
  x(lvalue, x(lvalue) + x(rvalue));
  y(lvalue, y(lvalue) + y(rvalue));
  return lvalue;
}

struct y_pt_deconvolve : gtl_yes {};

template <typename PointType1, typename PointType2>
typename enable_if<
  typename gtl_and_3<
    y_pt_deconvolve,
    typename is_mutable_point_concept<
      typename geometry_concept<PointType1>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<PointType2>::type
    >::type
  >::type,
PointType1>::type& deconvolve(PointType1& lvalue, const PointType2& rvalue) {
  x(lvalue, x(lvalue) - x(rvalue));
  y(lvalue, y(lvalue) - y(rvalue));
  return lvalue;
}

struct y_pt_scale_up : gtl_yes {};

template <typename PointType, typename CType>
typename enable_if<
  typename gtl_and<
    y_pt_scale_up,
    typename is_mutable_point_concept<
      typename geometry_concept<PointType>::type
    >::type
  >::type,
PointType>::type& scale_up(PointType& point, CType factor) {
  typedef typename point_coordinate_type<PointType>::type Unit;
  x(point, x(point) * (Unit)factor);
  y(point, y(point) * (Unit)factor);
  return point;
}

struct y_pt_scale_down : gtl_yes {};

template <typename PointType, typename CType>
typename enable_if<
  typename gtl_and<
    y_pt_scale_down,
    typename is_mutable_point_concept<
      typename geometry_concept<PointType>::type
    >::type
  >::type,
PointType>::type& scale_down(PointType& point, CType factor) {
  typedef typename point_coordinate_type<PointType>::type Unit;
  typedef typename coordinate_traits<Unit>::coordinate_distance dt;
  x(point, scaling_policy<Unit>::round((dt)(x(point)) / (dt)factor));
  y(point, scaling_policy<Unit>::round((dt)(y(point)) / (dt)factor));
  return point;
}

struct y_pt_scale : gtl_yes {};

template <typename PointType, typename ScaleType>
typename enable_if<
  typename gtl_and<
    y_pt_scale,
    typename is_mutable_point_concept<
      typename geometry_concept<PointType>::type
    >::type
  >::type,
PointType>::type& scale(PointType& point, const ScaleType& scaling) {
  typedef typename point_coordinate_type<PointType>::type Unit;
  Unit x_coord(x(point));
  Unit y_coord(y(point));
  scaling.scale(x_coord, y_coord);
  x(point, x_coord);
  y(point, y_coord);
  return point;
}

struct y_pt_transform : gtl_yes {};

template <typename PointType, typename TransformType>
typename enable_if<
  typename gtl_and<
    y_pt_transform,
    typename is_mutable_point_concept<
      typename geometry_concept<PointType>::type
    >::type
  >::type,
PointType>::type& transform(PointType& point, const TransformType& transform) {
  typedef typename point_coordinate_type<PointType>::type Unit;
  Unit x_coord(x(point));
  Unit y_coord(y(point));
  transform.transform(x_coord, y_coord);
  x(point, x_coord);
  y(point, y_coord);
  return point;
}

struct y_pt_move : gtl_yes {};

template <typename PointType>
typename enable_if<
  typename gtl_and<
    y_pt_move,
    typename is_mutable_point_concept<
      typename geometry_concept<PointType>::type
    >::type
  >::type,
PointType>::type& move(PointType& point, orientation_2d orient,
    typename point_coordinate_type<PointType>::type displacement) {
  typedef typename point_coordinate_type<PointType>::type Unit;
  Unit coord = get(point, orient);
  set(point, orient, coord + displacement);
  return point;
}
}  // polygon
}  // boost

#endif  // BOOST_POLYGON_POINT_CONCEPT_HPP

/* point_concept.hpp
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
*/