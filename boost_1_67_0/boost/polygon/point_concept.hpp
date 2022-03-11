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