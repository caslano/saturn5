/*
  Copyright 2008 Intel Corporation

  Use, modification and distribution are subject to the Boost Software License,
  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt).
*/
#ifndef BOOST_POLYGON_RECTANGLE_CONCEPT_HPP
#define BOOST_POLYGON_RECTANGLE_CONCEPT_HPP

#include "isotropy.hpp"

//point
#include "point_data.hpp"
#include "point_traits.hpp"
#include "point_concept.hpp"

//interval
#include "interval_data.hpp"
#include "interval_traits.hpp"
#include "interval_concept.hpp"

#include "rectangle_data.hpp"
#include "rectangle_traits.hpp"

namespace boost { namespace polygon{
  struct rectangle_concept {};

  template <typename T>
  struct is_rectangle_concept { typedef gtl_no type; };
  template <>
  struct is_rectangle_concept<rectangle_concept> { typedef gtl_yes type; };

  template <typename T>
  struct is_mutable_rectangle_concept { typedef gtl_no type; };
  template <>
  struct is_mutable_rectangle_concept<rectangle_concept> { typedef gtl_yes type; };

  template <>
  struct geometry_domain<rectangle_concept> { typedef manhattan_domain type; };

  template <typename T, typename CT>
  struct rectangle_interval_type_by_concept { typedef void type; };
  template <typename T>
  struct rectangle_interval_type_by_concept<T, gtl_yes> { typedef typename rectangle_traits<T>::interval_type type; };

  template <typename T>
  struct rectangle_interval_type {
      typedef typename rectangle_interval_type_by_concept<T, typename is_rectangle_concept<typename geometry_concept<T>::type>::type>::type type;
  };

  template <typename T, typename CT>
  struct rectangle_coordinate_type_by_concept { typedef void type; };
  template <typename T>
  struct rectangle_coordinate_type_by_concept<T, gtl_yes> { typedef typename rectangle_traits<T>::coordinate_type type; };

  template <typename T>
  struct rectangle_coordinate_type {
      typedef typename rectangle_coordinate_type_by_concept<T, typename is_rectangle_concept<typename geometry_concept<T>::type>::type>::type type;
  };

  template <typename T, typename CT>
  struct rectangle_difference_type_by_concept { typedef void type; };
  template <typename T>
  struct rectangle_difference_type_by_concept<T, gtl_yes> {
     typedef typename coordinate_traits<typename rectangle_traits<T>::coordinate_type>::coordinate_difference type; };

  template <typename T>
  struct rectangle_difference_type {
    typedef typename rectangle_difference_type_by_concept<
      T, typename is_rectangle_concept<typename geometry_concept<T>::type>::type>::type type;
  };

  template <typename T, typename CT>
  struct rectangle_distance_type_by_concept { typedef void type; };
  template <typename T>
  struct rectangle_distance_type_by_concept<T, gtl_yes> {
    typedef typename coordinate_traits<typename rectangle_coordinate_type<T>::type>::coordinate_distance type; };

  template <typename T>
  struct rectangle_distance_type {
    typedef typename rectangle_distance_type_by_concept<
      T, typename is_rectangle_concept<typename geometry_concept<T>::type>::type>::type type;
  };

  struct y_r_get_interval : gtl_yes {};

  template <typename T>
  typename enable_if< typename gtl_and<y_r_get_interval, typename is_rectangle_concept<typename geometry_concept<T>::type>::type>::type,
                      typename rectangle_interval_type<T>::type>::type
  get(const T& rectangle, orientation_2d orient) {
    return rectangle_traits<T>::get(rectangle, orient);
  }

  struct y_r_h : gtl_yes {};

  template <typename T>
  typename enable_if< typename gtl_and<y_r_h, typename is_rectangle_concept<typename geometry_concept<T>::type>::type>::type,
                       typename rectangle_interval_type<T>::type>::type
  horizontal(const T& rectangle) {
    return rectangle_traits<T>::get(rectangle, HORIZONTAL);
  }

  struct y_r_v : gtl_yes {};

  template <typename T>
  typename enable_if< typename gtl_and<y_r_v, typename is_rectangle_concept<typename geometry_concept<T>::type>::type>::type,
                       typename rectangle_interval_type<T>::type>::type
  vertical(const T& rectangle) {
    return rectangle_traits<T>::get(rectangle, VERTICAL);
  }

  struct y_r_set : gtl_yes {};

  template <orientation_2d_enum orient, typename T, typename T2>
  typename enable_if< typename gtl_and_3<y_r_set, typename is_mutable_rectangle_concept<typename geometry_concept<T>::type>::type,
                                        typename is_interval_concept<typename geometry_concept<T2>::type>::type>::type,
                       void>::type
  set(T& rectangle, const T2& interval) {
    rectangle_mutable_traits<T>::set(rectangle, orient, interval);
  }

  struct y_r_set2 : gtl_yes {};

  template <typename T, typename T2>
  typename enable_if< typename gtl_and_3<y_r_set2, typename is_mutable_rectangle_concept<typename geometry_concept<T>::type>::type,
                                        typename is_interval_concept<typename geometry_concept<T2>::type>::type>::type,
                       void>::type
  set(T& rectangle, orientation_2d orient, const T2& interval) {
    rectangle_mutable_traits<T>::set(rectangle, orient, interval);
  }

  struct y_r_h2 : gtl_yes {};

  template <typename T, typename T2>
  typename enable_if< typename gtl_and_3<y_r_h2, typename is_mutable_rectangle_concept<typename geometry_concept<T>::type>::type,
                                        typename is_interval_concept<typename geometry_concept<T2>::type>::type>::type,
                       void>::type
  horizontal(T& rectangle, const T2& interval) {
    rectangle_mutable_traits<T>::set(rectangle, HORIZONTAL, interval);
  }

  struct y_r_v2 : gtl_yes {};

  template <typename T, typename T2>
  typename enable_if<
    typename gtl_and_3<y_r_v2, typename is_mutable_rectangle_concept<typename geometry_concept<T>::type>::type,
                     typename is_interval_concept<typename geometry_concept<T2>::type>::type>::type, void>::type
  vertical(T& rectangle, const T2& interval) {
    rectangle_mutable_traits<T>::set(rectangle, VERTICAL, interval);
  }

  struct y_r_construct : gtl_yes {};

  template <typename T, typename T2, typename T3>
  typename enable_if< typename gtl_and<y_r_construct, typename is_mutable_rectangle_concept<typename geometry_concept<T>::type>::type>::type,
                       T>::type
  construct(const T2& interval_horizontal,
            const T3& interval_vertical) {
    return rectangle_mutable_traits<T>::construct(interval_horizontal, interval_vertical); }

  struct y_r_construct2 : gtl_yes {};

  template <typename T, typename coord_type>
  typename enable_if< typename gtl_and<y_r_construct2, typename is_mutable_rectangle_concept<typename geometry_concept<T>::type>::type>::type,
                       T>::type
  construct(coord_type xl, coord_type yl, coord_type xh, coord_type yh) {
    return rectangle_mutable_traits<T>::construct(interval_data<coord_type>(xl, xh),
                                                  interval_data<coord_type>(yl, yh));
  }

  struct y_r_cconstruct : gtl_yes {};

  template <typename T, typename T2>
  typename enable_if<
    typename gtl_and_3<y_r_cconstruct,
      typename is_mutable_rectangle_concept<typename geometry_concept<T>::type>::type,
      typename is_rectangle_concept<typename geometry_concept<T2>::type>::type>::type,
    T>::type
  copy_construct(const T2& rectangle) {
    return construct<T> (get(rectangle, HORIZONTAL), get(rectangle, VERTICAL));
  }

  struct y_r_assign : gtl_yes {};

  template <typename rectangle_type_1, typename rectangle_type_2>
  typename enable_if<
    typename gtl_and_3< y_r_assign,
      typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
      typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
    rectangle_type_1>::type &
  assign(rectangle_type_1& lvalue, const rectangle_type_2& rvalue) {
    set(lvalue, HORIZONTAL, get(rvalue, HORIZONTAL));
    set(lvalue, VERTICAL, get(rvalue, VERTICAL));
    return lvalue;
  }

  struct y_r_equiv : gtl_yes {};

  template <typename T, typename T2>
  typename enable_if<
    typename gtl_and_3< y_r_equiv,
      typename is_rectangle_concept<typename geometry_concept<T>::type>::type,
      typename is_rectangle_concept<typename geometry_concept<T2>::type>::type>::type,
    bool>::type
  equivalence(const T& rect1, const T2& rect2) {
    return equivalence(get(rect1, HORIZONTAL), get(rect2, HORIZONTAL)) &&
      equivalence(get(rect1, VERTICAL), get(rect2, VERTICAL));
  }

  struct y_r_get : gtl_yes {};

  template <typename rectangle_type>
  typename enable_if< typename gtl_and<y_r_get, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                       typename rectangle_coordinate_type<rectangle_type>::type>::type
  get(const rectangle_type& rectangle, orientation_2d orient, direction_1d dir) {
    return get(rectangle_traits<rectangle_type>::get(rectangle, orient), dir);
  }

  struct y_r_set3 : gtl_yes {};

  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_set3, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type, void>::type
  set(rectangle_type& rectangle, orientation_2d orient, direction_1d dir,
      typename rectangle_coordinate_type<rectangle_type>::type value) {
    typename rectangle_interval_type<rectangle_type>::type ivl = get(rectangle, orient);
    set(ivl, dir, value);
    set(rectangle, orient, ivl);
  }

  struct y_r_xl : gtl_yes {};

  template <typename rectangle_type>
  typename enable_if< typename gtl_and<y_r_xl, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                       typename rectangle_coordinate_type<rectangle_type>::type>::type
  xl(const rectangle_type& rectangle) {
    return get(rectangle, HORIZONTAL, LOW);
  }

  struct y_r_xl2 : gtl_yes {};

  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_xl2, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type, void>::type
      xl(rectangle_type& rectangle, typename rectangle_coordinate_type<rectangle_type>::type value) {
    return set(rectangle, HORIZONTAL, LOW, value);
  }

  struct y_r_xh : gtl_yes {};

  template <typename rectangle_type>
  typename enable_if< typename gtl_and<y_r_xh, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                       typename rectangle_coordinate_type<rectangle_type>::type>::type
  xh(const rectangle_type& rectangle) {
    return get(rectangle, HORIZONTAL, HIGH);
  }

  struct y_r_xh2 : gtl_yes {};

  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_xh2, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type, void>::type
  xh(rectangle_type& rectangle, typename rectangle_coordinate_type<rectangle_type>::type value) {
    return set(rectangle, HORIZONTAL, HIGH, value);
  }

  struct y_r_yl : gtl_yes {};

  template <typename rectangle_type>
  typename enable_if< typename gtl_and<y_r_yl, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                       typename rectangle_coordinate_type<rectangle_type>::type>::type
  yl(const rectangle_type& rectangle) {
    return get(rectangle, VERTICAL, LOW);
  }

  struct y_r_yl2 : gtl_yes {};

  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_yl2, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type, void>::type
      yl(rectangle_type& rectangle, typename rectangle_coordinate_type<rectangle_type>::type value) {
    return set(rectangle, VERTICAL, LOW, value);
  }

  struct y_r_yh : gtl_yes {};

  template <typename rectangle_type>
  typename enable_if< typename gtl_and<y_r_yh, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                       typename rectangle_coordinate_type<rectangle_type>::type>::type
  yh(const rectangle_type& rectangle) {
    return get(rectangle, VERTICAL, HIGH);
  }

  struct y_r_yh2 : gtl_yes {};

  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_yh2, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type, void>::type
      yh(rectangle_type& rectangle, typename rectangle_coordinate_type<rectangle_type>::type value) {
    return set(rectangle, VERTICAL, HIGH, value);
  }

  struct y_r_ll : gtl_yes {};

  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_ll,  typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                       point_data<typename rectangle_coordinate_type<rectangle_type>::type> >::type
  ll(const rectangle_type& rectangle) {
    return point_data<typename rectangle_coordinate_type<rectangle_type>::type> (xl(rectangle), yl(rectangle));
  }

  struct y_r_lr : gtl_yes {};

  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_lr,  typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                       point_data<typename rectangle_coordinate_type<rectangle_type>::type> >::type
  lr(const rectangle_type& rectangle) {
    return point_data<typename rectangle_coordinate_type<rectangle_type>::type> (xh(rectangle), yl(rectangle));
  }

  struct y_r_ul : gtl_yes {};

  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_ul,  typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                       point_data<typename rectangle_coordinate_type<rectangle_type>::type> >::type
  ul(const rectangle_type& rectangle) {
    return point_data<typename rectangle_coordinate_type<rectangle_type>::type> (xl(rectangle), yh(rectangle));
  }

  struct y_r_ur : gtl_yes {};

  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_ur,  typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                       point_data<typename rectangle_coordinate_type<rectangle_type>::type> >::type
  ur(const rectangle_type& rectangle) {
    return point_data<typename rectangle_coordinate_type<rectangle_type>::type> (xh(rectangle), yh(rectangle));
  }

  struct y_r_contains : gtl_yes {};

  template <typename rectangle_type, typename rectangle_type_2>
  typename enable_if< typename gtl_and_3<y_r_contains, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type,
                                         typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
                       bool>::type
  contains(const rectangle_type& rectangle, const rectangle_type_2 rectangle_contained,
           bool consider_touch = true) {
    return contains(horizontal(rectangle), horizontal(rectangle_contained), consider_touch) &&
      contains(vertical(rectangle), vertical(rectangle_contained), consider_touch);
  }

  struct y_r_contains2 : gtl_yes {};

  template <typename rectangle_type, typename point_type>
  typename enable_if< typename gtl_and_3<y_r_contains2, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type,
                                         typename is_point_concept<typename geometry_concept<point_type>::type>::type>::type, bool>::type
  contains(const rectangle_type& rectangle, const point_type point_contained,
           bool consider_touch = true) {
    return contains(horizontal(rectangle), x(point_contained), consider_touch) &&
      contains(vertical(rectangle), y(point_contained), consider_touch);
  }

  struct y_r_set_points : gtl_yes {};

  // set all four coordinates based upon two points
  template <typename rectangle_type, typename point_type_1, typename point_type_2>
  typename enable_if< typename gtl_and_4< y_r_set_points,
    typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type,
    typename is_point_concept<typename geometry_concept<point_type_1>::type>::type,
    typename is_point_concept<typename geometry_concept<point_type_2>::type>::type>::type,
                       rectangle_type>::type &
  set_points(rectangle_type& rectangle, const point_type_1& p1,
             const point_type_2& p2) {
    typedef typename rectangle_coordinate_type<rectangle_type>::type Unit;
    Unit x1(x(p1));
    Unit x2(x(p2));
    Unit y1(y(p1));
    Unit y2(y(p2));
    horizontal(rectangle, construct<typename rectangle_interval_type<rectangle_type>::type>(x1, x2));
    vertical(rectangle, construct<typename rectangle_interval_type<rectangle_type>::type>(y1, y2));
    return rectangle;
  }

  struct y_r_move : gtl_yes {};

  // move rectangle by delta in orient
  template <typename rectangle_type>
  typename enable_if< typename gtl_and<y_r_move, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                      rectangle_type>::type &
  move(rectangle_type& rectangle, orientation_2d orient,
       typename coordinate_traits<typename rectangle_coordinate_type<rectangle_type>::type>::coordinate_difference delta) {
    typename rectangle_interval_type<rectangle_type>::type ivl = get(rectangle, orient);
    move(ivl, delta);
    set(rectangle, orient, ivl);
    return rectangle;
  }

  struct y_r_convolve : gtl_yes {};

  // convolve this with b
  template <typename rectangle_type_1, typename rectangle_type_2>
  typename enable_if<
    typename gtl_and_3< y_r_convolve,
      typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
      typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
    rectangle_type_1>::type &
  convolve(rectangle_type_1& rectangle,
           const rectangle_type_2& convolution_rectangle) {
    typename rectangle_interval_type<rectangle_type_1>::type ivl = horizontal(rectangle);
    horizontal(rectangle, convolve(ivl, horizontal(convolution_rectangle)));
    ivl = vertical(rectangle);
    vertical(rectangle, convolve(ivl, vertical(convolution_rectangle)));
    return rectangle;
  }

  struct y_r_deconvolve : gtl_yes {};

  // deconvolve this with b
  template <typename rectangle_type_1, typename rectangle_type_2>
  typename enable_if< typename gtl_and_3< y_r_deconvolve,
    typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
    typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
                       rectangle_type_1>::type &
  deconvolve(rectangle_type_1& rectangle, const rectangle_type_2& convolution_rectangle) {
    typename rectangle_interval_type<rectangle_type_1>::type ivl = horizontal(rectangle);
    horizontal(rectangle, deconvolve(ivl, horizontal(convolution_rectangle)));
    ivl = vertical(rectangle);
    vertical(rectangle, deconvolve(ivl, vertical(convolution_rectangle)));
    return rectangle;
  }

  struct y_r_reconvolve : gtl_yes {};

  // reflectedConvolve this with b
  template <typename rectangle_type_1, typename rectangle_type_2>
  typename enable_if<
    typename gtl_and_3<y_r_reconvolve, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
                      typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
    rectangle_type_1>::type &
  reflected_convolve(rectangle_type_1& rectangle, const rectangle_type_2& convolution_rectangle) {
    typename rectangle_interval_type<rectangle_type_1>::type ivl = horizontal(rectangle);
    horizontal(rectangle, reflected_convolve(ivl, horizontal(convolution_rectangle)));
    ivl = vertical(rectangle);
    vertical(rectangle, reflected_convolve(ivl, vertical(convolution_rectangle)));
    return rectangle;
  }

  struct y_r_redeconvolve : gtl_yes {};

  // reflectedDeconvolve this with b
  // deconvolve this with b
  template <typename rectangle_type_1, typename rectangle_type_2>
  typename enable_if<
    typename gtl_and_3<y_r_redeconvolve, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
                      typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
    rectangle_type_1>::type &
  reflected_deconvolve(rectangle_type_1& rectangle, const rectangle_type_2& convolution_rectangle) {
    typename rectangle_interval_type<rectangle_type_1>::type ivl = horizontal(rectangle);
    horizontal(rectangle, reflected_deconvolve(ivl, horizontal(convolution_rectangle)));
    ivl = vertical(rectangle);
    vertical(rectangle, reflected_deconvolve(ivl, vertical(convolution_rectangle)));
    return rectangle;
  }

  struct y_r_convolve2 : gtl_yes {};

  // convolve with point
  template <typename rectangle_type, typename point_type>
  typename enable_if< typename gtl_and_3<y_r_convolve2, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type,
                                         typename is_point_concept<typename geometry_concept<point_type>::type>::type>::type,
                       rectangle_type>::type &
  convolve(rectangle_type& rectangle, const point_type& convolution_point) {
    typename rectangle_interval_type<rectangle_type>::type ivl = horizontal(rectangle);
    horizontal(rectangle, convolve(ivl, x(convolution_point)));
    ivl = vertical(rectangle);
    vertical(rectangle, convolve(ivl, y(convolution_point)));
    return rectangle;
  }

  struct y_r_deconvolve2 : gtl_yes {};

  // deconvolve with point
  template <typename rectangle_type, typename point_type>
  typename enable_if<
    typename gtl_and_3<y_r_deconvolve2, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type,
                      typename is_point_concept<typename geometry_concept<point_type>::type>::type>::type, rectangle_type>::type &
  deconvolve(rectangle_type& rectangle, const point_type& convolution_point) {
    typename rectangle_interval_type<rectangle_type>::type ivl = horizontal(rectangle);
    horizontal(rectangle, deconvolve(ivl, x(convolution_point)));
    ivl = vertical(rectangle);
    vertical(rectangle, deconvolve(ivl, y(convolution_point)));
    return rectangle;
  }

  struct y_r_delta : gtl_yes {};

  // get the magnitude of the interval range depending on orient
  template <typename rectangle_type>
  typename enable_if< typename gtl_and<y_r_delta, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                       typename rectangle_difference_type<rectangle_type>::type>::type
  delta(const rectangle_type& rectangle, orientation_2d orient) {
    return delta(get(rectangle, orient));
  }

  struct y_r_area : gtl_yes {};

  // get the area of the rectangle
  template <typename rectangle_type>
  typename enable_if< typename gtl_and<y_r_area, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                       typename coordinate_traits<typename rectangle_coordinate_type<rectangle_type>::type>::manhattan_area_type>::type
  area(const rectangle_type& rectangle) {
    typedef typename coordinate_traits<typename rectangle_coordinate_type<rectangle_type>::type>::manhattan_area_type area_type;
    return (area_type)delta(rectangle, HORIZONTAL) * (area_type)delta(rectangle, VERTICAL);
  }

  struct y_r_go : gtl_yes {};

  // returns the orientation of the longest side
  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_go, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                      orientation_2d>::type
  guess_orientation(const rectangle_type& rectangle) {
    return delta(rectangle, HORIZONTAL) >= delta(rectangle, VERTICAL) ?
      HORIZONTAL : VERTICAL;
  }

  struct y_r_half_p : gtl_yes {};

  // get the half perimeter of the rectangle
  template <typename rectangle_type>
  typename enable_if< typename gtl_and<y_r_half_p, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                       typename rectangle_difference_type<rectangle_type>::type>::type
  half_perimeter(const rectangle_type& rectangle) {
    return delta(rectangle, HORIZONTAL) + delta(rectangle, VERTICAL);
  }

  struct y_r_perimeter : gtl_yes {};

  // get the perimeter of the rectangle
  template <typename rectangle_type>
  typename enable_if< typename gtl_and<y_r_perimeter, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                      typename rectangle_difference_type<rectangle_type>::type>::type
  perimeter(const rectangle_type& rectangle) {
    return 2 * half_perimeter(rectangle);
  }

  struct y_r_intersects : gtl_yes {};

  // check if Rectangle b intersects `this` Rectangle
  //  [in]     b         Rectangle that will be checked
  //  [in]     considerTouch If true, return true even if b touches the boundary
  //  [ret]    .         true if `t` intersects b
  template <typename rectangle_type_1, typename rectangle_type_2>
  typename enable_if<
    typename gtl_and_3<y_r_intersects, typename is_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
                      typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
    bool>::type
  intersects(const rectangle_type_1& rectangle, const rectangle_type_2& b, bool consider_touch = true) {
    return intersects(horizontal(rectangle), horizontal(b), consider_touch) &&
      intersects(vertical(rectangle), vertical(b), consider_touch);
  }

  struct y_r_b_intersect : gtl_yes {};

  // Check if boundaries of Rectangle b and `this` Rectangle intersect
  //  [in]     b         Rectangle that will be checked
  //  [in]     considerTouch If true, return true even if p is on the foundary
  //  [ret]    .         true if `t` contains p
  template <typename rectangle_type_1, typename rectangle_type_2>
  typename enable_if<
    typename gtl_and_3<y_r_b_intersect, typename is_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
                      typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
    bool>::type
  boundaries_intersect(const rectangle_type_1& rectangle, const rectangle_type_2& b,
                       bool consider_touch = true) {
    return (intersects(rectangle, b, consider_touch) &&
            !(contains(rectangle, b, !consider_touch)) &&
            !(contains(b, rectangle, !consider_touch)));
  }

  struct y_r_b_abuts : gtl_yes {};

  // check if b is touching 'this' on the end specified by dir
  template <typename rectangle_type_1, typename rectangle_type_2>
  typename enable_if< typename gtl_and_3<y_r_b_abuts, typename is_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
                                         typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
                       bool>::type
  abuts(const rectangle_type_1& rectangle, const rectangle_type_2& b,
        direction_2d dir) {
    return
      abuts(get(rectangle, orientation_2d(dir)),
            get(b, orientation_2d(dir)),
            direction_1d(dir)) &&
      intersects(get(rectangle, orientation_2d(dir).get_perpendicular()),
                 get(b, orientation_2d(dir).get_perpendicular()), true);
  }

  struct y_r_b_abuts2 : gtl_yes {};

  // check if they are touching in the given orientation
  template <typename rectangle_type_1, typename rectangle_type_2>
  typename enable_if< typename gtl_and_3<y_r_b_abuts2, typename is_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
                                         typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
                       bool>::type
  abuts(const rectangle_type_1& rectangle, const rectangle_type_2& b,
        orientation_2d orient) {
    return
      abuts(get(rectangle, orient), get(b, orient)) &&
      intersects(get(rectangle, orient.get_perpendicular()),
                 get(b, orient.get_perpendicular()), true);
  }

  struct y_r_b_abuts3 : gtl_yes {};

  // check if they are touching but not overlapping
  template <typename rectangle_type_1, typename rectangle_type_2>
  typename enable_if< typename gtl_and_3<y_r_b_abuts3, typename is_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
                                         typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
                       bool>::type
  abuts(const rectangle_type_1& rectangle, const rectangle_type_2& b) {
    return abuts(rectangle, b, HORIZONTAL) || abuts(rectangle, b, VERTICAL);
  }

  struct y_r_b_intersect2 : gtl_yes {};

  // intersect rectangle with interval on orient
  template <typename rectangle_type, typename interval_type>
  typename enable_if<
    typename gtl_and_3<y_r_b_intersect2, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type,
                      typename is_interval_concept<typename geometry_concept<interval_type>::type>::type>::type,
    bool>::type
  intersect(rectangle_type& rectangle, const interval_type& b,
            orientation_2d orient, bool consider_touch = true) {
    typename rectangle_interval_type<rectangle_type>::type ivl = get(rectangle, orient);
    if(intersect(ivl, b, consider_touch)) {
      set(rectangle, orient, ivl);
      return true;
    }
    return false;
  }

  struct y_r_b_intersect3 : gtl_yes {};

  // clip rectangle to b
  template <typename rectangle_type_1, typename rectangle_type_2>
  typename enable_if< typename gtl_and_3<y_r_b_intersect3, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
                                         typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
                       bool>::type
  intersect(rectangle_type_1& rectangle, const rectangle_type_2& b, bool consider_touch = true) {
    if(intersects(rectangle, b)) {
      intersect(rectangle, horizontal(b), HORIZONTAL, consider_touch);
      intersect(rectangle, vertical(b), VERTICAL, consider_touch);
      return true;
    }
    return false;
  }

  struct y_r_g_intersect : gtl_yes {};

  // Sets this to the generalized intersection of this and the given rectangle
  template <typename rectangle_type_1, typename rectangle_type_2>
  typename enable_if< typename gtl_and_3<y_r_g_intersect,
    typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
    typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
                       rectangle_type_1>::type &
  generalized_intersect(rectangle_type_1& rectangle, const rectangle_type_2& b) {
    typename rectangle_interval_type<rectangle_type_1>::type ivl = get(rectangle, HORIZONTAL);
    generalized_intersect(ivl, horizontal(b));
    horizontal(rectangle, ivl);
    ivl = vertical(rectangle);
    generalized_intersect(ivl, vertical(b));
    vertical(rectangle, ivl);
    return rectangle;
  }

  struct y_r_bloat : gtl_yes {};

  // bloat the interval specified by orient by bloating
  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_bloat, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                      rectangle_type>::type &
  bloat(rectangle_type& rectangle, orientation_2d orient,
        typename rectangle_coordinate_type<rectangle_type>::type bloating) {
    typename rectangle_interval_type<rectangle_type>::type ivl = get(rectangle, orient);
    bloat(ivl, bloating);
    set(rectangle, orient, ivl);
    return rectangle;
  }

  struct y_r_bloat2 : gtl_yes {};

  // bloat the Rectangle by bloating
  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_bloat2, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                      rectangle_type>::type &
  bloat(rectangle_type& rectangle,
        typename rectangle_coordinate_type<rectangle_type>::type bloating) {
    bloat(rectangle, HORIZONTAL, bloating);
    return bloat(rectangle, VERTICAL, bloating);
  }

  struct y_r_bloat3 : gtl_yes {};

  // bloat the interval cooresponding to orient by bloating in dir direction
  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_bloat3, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                      rectangle_type>::type &
  bloat(rectangle_type& rectangle, direction_2d dir,
        typename rectangle_coordinate_type<rectangle_type>::type bloating) {
    typename rectangle_interval_type<rectangle_type>::type ivl = get(rectangle, orientation_2d(dir));
    bloat(ivl, direction_1d(dir), bloating);
    set(rectangle, orientation_2d(dir), ivl);
    return rectangle;
  }

  struct y_r_shrink : gtl_yes {};

  // shrink the interval specified by orient by bloating
  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_shrink, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                      rectangle_type>::type &
  shrink(rectangle_type& rectangle, orientation_2d orient,
         typename rectangle_coordinate_type<rectangle_type>::type shrinking) {
    return bloat(rectangle, orient, -shrinking);
  }

  struct y_r_shrink2 : gtl_yes {};

  // shrink the Rectangle by bloating
  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_shrink2, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                      rectangle_type>::type &
  shrink(rectangle_type& rectangle,
         typename rectangle_coordinate_type<rectangle_type>::type shrinking) {
    return bloat(rectangle, -shrinking);
  }

  struct y_r_shrink3 : gtl_yes {};

  // shrink the interval cooresponding to orient by bloating in dir direction
  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_shrink3, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                      rectangle_type>::type &
  shrink(rectangle_type& rectangle, direction_2d dir,
         typename rectangle_coordinate_type<rectangle_type>::type shrinking) {
    return bloat(rectangle, dir, -shrinking);
  }

  struct y_r_encompass : gtl_yes {};

  // encompass interval on orient
  template <typename rectangle_type, typename interval_type>
  typename enable_if<typename gtl_and_3<
        y_r_encompass,
        typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type,
        typename is_interval_concept<typename geometry_concept<interval_type>::type>::type>::type,
      bool>::type
  encompass(rectangle_type& rectangle, const interval_type& b, orientation_2d orient) {
    typename rectangle_interval_type<rectangle_type>::type ivl = get(rectangle, orient);
    if(encompass(ivl, b)) {
      set(rectangle, orient, ivl);
      return true;
    }
    return false;
  }

 struct y_r_encompass2 : gtl_yes {};

  // enlarge rectangle to encompass the Rectangle b
  template <typename rectangle_type_1, typename rectangle_type_2>
  typename enable_if< typename gtl_and_3<
        y_r_encompass2,
        typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
        typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type >::type,
      bool>::type
  encompass(rectangle_type_1& rectangle, const rectangle_type_2& b) {
    //note that operator | is intentional because both should be called regardless
    return encompass(rectangle, horizontal(b), HORIZONTAL) |
      encompass(rectangle, vertical(b), VERTICAL);
  }

  struct y_r_encompass3 : gtl_yes {};

  // enlarge rectangle to encompass the point b
  template <typename rectangle_type_1, typename point_type>
  typename enable_if<typename gtl_and_3<
        y_r_encompass3,
        typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
        typename is_point_concept<typename geometry_concept<point_type>::type>::type>::type,
      bool>::type
  encompass(rectangle_type_1& rectangle, const point_type& b) {
    typename rectangle_interval_type<rectangle_type_1>::type hivl, vivl;
    hivl = horizontal(rectangle);
    vivl = vertical(rectangle);
    //note that operator | is intentional because both should be called regardless
    bool retval = encompass(hivl, x(b)) | encompass(vivl, y(b));
    if(retval) {
      horizontal(rectangle, hivl);
      vertical(rectangle, vivl);
    }
    return retval;
  }

  struct y_r_center : gtl_yes {};

  // returns the center of the rectangle
  template <typename point_type, typename rectangle_type>
  typename enable_if<
    typename gtl_and_3<y_r_center, typename is_mutable_point_concept<typename geometry_concept<point_type>::type>::type,
                      typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
    bool>::type
  center(point_type& center_point, const rectangle_type& rectangle) {
    center_point = construct<point_type>(center(horizontal(rectangle)),
                                         center(vertical(rectangle)));
    return true;
  }

  struct y_r_get_corner : gtl_yes {};

  template <typename point_type, typename rectangle_type>
  typename enable_if<
    typename gtl_and_3<y_r_get_corner, typename is_mutable_point_concept<typename geometry_concept<point_type>::type>::type,
                      typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
    bool>::type
  get_corner(point_type& corner_point, const rectangle_type& rectangle, direction_2d direction_facing, direction_1d direction_turning) {
    typedef typename rectangle_coordinate_type<rectangle_type>::type Unit;
    Unit u1 = get(rectangle, direction_facing);
    Unit u2 = get(rectangle, direction_facing.turn(direction_turning));
    if(orientation_2d(direction_facing).to_int()) std::swap(u1, u2);
    corner_point = construct<point_type>(u1, u2);
    return true;
  }

  struct y_r_get_half : gtl_yes {};

  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_get_half, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                     rectangle_type>::type
  get_half(const rectangle_type& rectangle, direction_2d dir) {
    rectangle_type retval(rectangle);
    set(retval, orientation_2d(dir), get_half(get(rectangle, orientation_2d(dir)), direction_1d(dir)));
    return retval;
  }

  struct y_r_join_with : gtl_yes {};

  template <typename rectangle_type_1, typename rectangle_type_2>
  typename enable_if< typename gtl_and_3<y_r_join_with, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
                                         typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
                       bool>::type
  join_with(rectangle_type_1& rectangle, const rectangle_type_2& b) {
    typedef typename rectangle_interval_type<rectangle_type_1>::type Interval1;
    typedef typename rectangle_interval_type<rectangle_type_2>::type Interval2;
    Interval1 hi1 = get(rectangle, HORIZONTAL);
    Interval1 vi1 = get(rectangle, VERTICAL);
    Interval2 hi2 = get(b, HORIZONTAL), vi2 = get(b, VERTICAL);
    Interval1 temp;
    if (equivalence(hi1, hi2) && join_with(vi1, vi2)) {
      vertical(rectangle, vi1);
      return true;
    }
    if (equivalence(vi1, vi2) && join_with(hi1, hi2)) {
      horizontal(rectangle, hi1);
      return true;
    }
    return false;
  }

  struct y_r_eda2 : gtl_yes {};

  template <typename rectangle_type, typename point_type>
  typename enable_if< typename gtl_and_3<y_r_eda2,
    typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type,
    typename is_point_concept<typename geometry_concept<point_type>::type>::type>::type,
                      typename rectangle_difference_type<rectangle_type>::type>::type
  euclidean_distance(const rectangle_type& lvalue, const point_type& rvalue, orientation_2d orient) {
    return euclidean_distance(get(lvalue, orient), get(rvalue, orient));
  }

  struct y_r_eda : gtl_yes {};

  template <typename rectangle_type, typename rectangle_type_2>
  typename enable_if<
    typename gtl_and_3<y_r_eda,
      typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type,
                       typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
    typename rectangle_difference_type<rectangle_type>::type>::type
  euclidean_distance(const rectangle_type& lvalue, const rectangle_type_2& rvalue, orientation_2d orient) {
    return euclidean_distance(get(lvalue, orient), get(rvalue, orient));
  }

  struct y_r_sed : gtl_yes {};

  template <typename rectangle_type, typename point_type>
  typename enable_if< typename gtl_and_3<y_r_sed,
    typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type,
    typename is_point_concept<typename geometry_concept<point_type>::type>::type>::type,
                       typename rectangle_difference_type<rectangle_type>::type>::type
  square_euclidean_distance(rectangle_type& lvalue, const point_type& rvalue) {
    typename coordinate_traits<typename rectangle_coordinate_type<rectangle_type>::type>::coordinate_difference xdist, ydist;
    xdist = euclidean_distance(lvalue, rvalue, HORIZONTAL);
    ydist = euclidean_distance(lvalue, rvalue, VERTICAL);
    return (xdist * xdist) + (ydist * ydist);
  }

  struct y_r_sed2 : gtl_yes {};

  template <typename rectangle_type, typename rectangle_type_2>
  typename enable_if<
    typename gtl_and_3<y_r_sed2, typename is_rectangle_concept< typename geometry_concept<rectangle_type>::type>::type,
                                       typename is_rectangle_concept< typename geometry_concept<rectangle_type_2>::type>::type>::type,
    typename rectangle_difference_type<rectangle_type>::type>::type
  square_euclidean_distance(const rectangle_type& lvalue, const rectangle_type_2& rvalue) {
    typename coordinate_traits<typename rectangle_coordinate_type<rectangle_type>::type>::coordinate_difference xdist, ydist;
    xdist = euclidean_distance(lvalue, rvalue, HORIZONTAL);
    ydist = euclidean_distance(lvalue, rvalue, VERTICAL);
    return (xdist * xdist) + (ydist * ydist);
  }

  struct y_r_edist : gtl_yes {};

  template <typename rectangle_type, typename point_type>
  typename enable_if< typename gtl_and_3<y_r_edist, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type,
                                                          typename is_point_concept<typename geometry_concept<point_type>::type>::type>::type,
                       typename rectangle_distance_type<rectangle_type>::type>::type
  euclidean_distance(rectangle_type& lvalue, const point_type& rvalue) {
    return std::sqrt((double)(square_euclidean_distance(lvalue, rvalue)));
  }

  struct y_r_edist2 : gtl_yes {};

  template <typename rectangle_type, typename rectangle_type_2>
  typename enable_if< typename gtl_and_3<y_r_edist2, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type,
                                                          typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
                       typename rectangle_distance_type<rectangle_type>::type>::type
  euclidean_distance(const rectangle_type& lvalue, const rectangle_type_2& rvalue) {
    double val = (int)square_euclidean_distance(lvalue, rvalue);
    return std::sqrt(val);
  }

  struct y_r_mdist : gtl_yes {};

  template <typename rectangle_type, typename point_type>
  typename enable_if<
    typename gtl_and_3<y_r_mdist, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type,
                                       typename is_point_concept<typename geometry_concept<point_type>::type>::type>::type,
    typename rectangle_difference_type<rectangle_type>::type>::type
  manhattan_distance(rectangle_type& lvalue, const point_type& rvalue) {
    typename coordinate_traits<typename rectangle_coordinate_type<rectangle_type>::type>::coordinate_difference xdist, ydist;
    xdist = euclidean_distance(lvalue, rvalue, HORIZONTAL);
    ydist = euclidean_distance(lvalue, rvalue, VERTICAL);
    return xdist + ydist;
  }

  struct y_r_mdist2 : gtl_yes {};

  template <typename rectangle_type, typename rectangle_type_2>
  typename enable_if<
    typename gtl_and_3<y_r_mdist2, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type,
                                       typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
    typename rectangle_difference_type<rectangle_type>::type>::type
  manhattan_distance(const rectangle_type& lvalue, const rectangle_type_2& rvalue) {
    typename coordinate_traits<typename rectangle_coordinate_type<rectangle_type>::type>::coordinate_difference xdist, ydist;
    xdist = euclidean_distance(lvalue, rvalue, HORIZONTAL);
    ydist = euclidean_distance(lvalue, rvalue, VERTICAL);
    return xdist + ydist;
  }

  struct y_r_scale_up : gtl_yes {};

  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_scale_up, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                     rectangle_type>::type &
  scale_up(rectangle_type& rectangle,
           typename coordinate_traits<typename rectangle_coordinate_type<rectangle_type>::type>::unsigned_area_type factor) {
    typename rectangle_interval_type<rectangle_type>::type h = horizontal(rectangle);
    horizontal(rectangle, scale_up(h, factor));
    typename rectangle_interval_type<rectangle_type>::type v = vertical(rectangle);
    vertical(rectangle, scale_up(v, factor));
    return rectangle;
  }

  struct y_r_scale_down : gtl_yes {};

  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_scale_down, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                     rectangle_type>::type &
  scale_down(rectangle_type& rectangle,
             typename coordinate_traits<typename rectangle_coordinate_type<rectangle_type>::type>::unsigned_area_type factor) {
    typename rectangle_interval_type<rectangle_type>::type h = horizontal(rectangle);
    horizontal(rectangle, scale_down(h, factor));
    typename rectangle_interval_type<rectangle_type>::type v = vertical(rectangle);
    vertical(rectangle, scale_down(v, factor));
    return rectangle;
  }

  struct y_r_scale : gtl_yes {};

  template <typename rectangle_type, typename scaling_type>
  typename enable_if<typename gtl_and<y_r_scale, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                     rectangle_type>::type &
  scale(rectangle_type& rectangle, const scaling_type& scaling) {
    point_data<typename rectangle_coordinate_type<rectangle_type>::type> llp(xl(rectangle), yl(rectangle));
    point_data<typename rectangle_coordinate_type<rectangle_type>::type> urp(xl(rectangle), yl(rectangle));
    scale(llp, scaling);
    scale(urp, scaling);
    set_points(rectangle, llp, urp);
    return rectangle;
  }

  struct y_r_transform : gtl_yes {};

  template <typename rectangle_type, typename transformation_type>
  typename enable_if<typename gtl_and<y_r_transform, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                     rectangle_type>::type &
  transform(rectangle_type& rectangle, const transformation_type& transformation) {
    point_data<typename rectangle_coordinate_type<rectangle_type>::type> llp(xl(rectangle), yl(rectangle));
    point_data<typename rectangle_coordinate_type<rectangle_type>::type> urp(xh(rectangle), yh(rectangle));
    transform(llp, transformation);
    transform(urp, transformation);
    set_points(rectangle, llp, urp);
    return rectangle;
  }

  template <typename rectangle_type_1, typename rectangle_type_2>
  class less_rectangle_concept {
  private:
    orientation_2d orient_;
  public:
    inline less_rectangle_concept(orientation_2d orient = VERTICAL) : orient_(orient) {}
    typename enable_if<
      typename gtl_and< typename is_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
                        typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
      bool>::type
    operator () (const rectangle_type_1& a,
                 const rectangle_type_2& b) const {
      typedef typename rectangle_coordinate_type<rectangle_type_1>::type Unit;
      Unit vl1 = get(get(a, orient_), LOW);
      Unit vl2 = get(get(b, orient_), LOW);
      if(vl1 > vl2) return false;
      if(vl1 == vl2) {
        orientation_2d perp = orient_.get_perpendicular();
        Unit hl1 = get(get(a, perp), LOW);
        Unit hl2 = get(get(b, perp), LOW);
        if(hl1 > hl2) return false;
        if(hl1 == hl2) {
          Unit vh1 = get(get(a, orient_), HIGH);
          Unit vh2 = get(get(b, orient_), HIGH);
          if(vh1 > vh2) return false;
          if(vh1 == vh2) {
            Unit hh1 = get(get(a, perp), HIGH);
            Unit hh2 = get(get(b, perp), HIGH);
            return hh1 < hh2;
          }
        }
      }
      return true;
    }

  };

  template <typename T>
  template <typename interval_type_1>
  inline void rectangle_data<T>::set(orientation_2d orient, const interval_type_1& interval) {
    assign(ranges_[orient.to_int()], interval);
  }

  template <class T>
  template <class T2>
  rectangle_data<T>& rectangle_data<T>::operator=(const T2& rvalue) {
    assign(*this, rvalue);
    return *this;
  }

  template <class T>
  template <class T2>
  bool rectangle_data<T>::operator==(const T2& rvalue) const {
    return equivalence(*this, rvalue);
  }

  template <typename T>
  struct geometry_concept<rectangle_data<T> > {
    typedef rectangle_concept type;
  };
}
}
#endif

/* rectangle_concept.hpp
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
*/