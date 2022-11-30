// Boost.Polygon library interval_concept.hpp header file

// Copyright (c) Intel Corporation 2008.
// Copyright (c) 2008-2012 Simonson Lucanus.
// Copyright (c) 2012-2012 Andrii Sydorchuk.

// See http://www.boost.org for updates, documentation, and revision history.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_POLYGON_INTERVAL_CONCEPT_HPP
#define BOOST_POLYGON_INTERVAL_CONCEPT_HPP

#include "isotropy.hpp"
#include "interval_traits.hpp"

namespace boost {
namespace polygon {

struct interval_concept {};

template <typename ConceptType>
struct is_interval_concept {
  typedef gtl_no type;
};

template <>
struct is_interval_concept<interval_concept> {
  typedef gtl_yes type;
};

template <typename ConceptType>
struct is_mutable_interval_concept {
  typedef gtl_no type;
};

template <>
struct is_mutable_interval_concept<interval_concept> {
  typedef gtl_yes type;
};

template <typename GeometryType, typename BoolType>
struct interval_coordinate_type_by_concept {
  typedef void type;
};

template <typename GeometryType>
struct interval_coordinate_type_by_concept<GeometryType, gtl_yes> {
  typedef typename interval_traits<GeometryType>::coordinate_type type;
};

template <typename GeometryType>
struct interval_coordinate_type {
  typedef typename interval_coordinate_type_by_concept<
    GeometryType,
    typename is_interval_concept<
      typename geometry_concept<GeometryType>::type
    >::type
  >::type type;
};

template <typename GeometryType, typename BoolType>
struct interval_difference_type_by_concept {
  typedef void type;
};

template <typename GeometryType>
struct interval_difference_type_by_concept<GeometryType, gtl_yes> {
  typedef typename coordinate_traits<
    typename interval_traits<GeometryType>::coordinate_type
  >::coordinate_difference type;
};

template <typename GeometryType>
struct interval_difference_type {
  typedef typename interval_difference_type_by_concept<
    GeometryType,
    typename is_interval_concept<
      typename geometry_concept<GeometryType>::type
    >::type
  >::type type;
};

struct y_i_get : gtl_yes {};

template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_get,
    typename is_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  typename interval_coordinate_type<IntervalType>::type
>::type get(const IntervalType& interval, direction_1d dir) {
  return interval_traits<IntervalType>::get(interval, dir);
}

struct y_i_set : gtl_yes {};

template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_set,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  void
>::type set(IntervalType& interval, direction_1d dir,
    typename interval_mutable_traits<IntervalType>::coordinate_type value) {
  interval_mutable_traits<IntervalType>::set(interval, dir, value);
}

struct y_i_construct : gtl_yes {};

template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_construct,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type construct(
    typename interval_mutable_traits<IntervalType>::coordinate_type low,
    typename interval_mutable_traits<IntervalType>::coordinate_type high) {
  if (low > high) {
    (std::swap)(low, high);
  }
  return interval_mutable_traits<IntervalType>::construct(low, high);
}

struct y_i_copy_construct : gtl_yes {};

template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_copy_construct,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  IntervalType1
>::type copy_construct(const IntervalType2& interval) {
  return construct<IntervalType1>(get(interval, LOW), get(interval, HIGH));
}

struct y_i_assign : gtl_yes {};

template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_assign,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  IntervalType1
>::type& assign(IntervalType1& lvalue, const IntervalType2& rvalue) {
  set(lvalue, LOW, get(rvalue, LOW));
  set(lvalue, HIGH, get(rvalue, HIGH));
  return lvalue;
}

struct y_i_low : gtl_yes {};

template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_low,
    typename is_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  typename interval_coordinate_type<IntervalType>::type
>::type low(const IntervalType& interval) {
  return get(interval, LOW);
}

struct y_i_high : gtl_yes {};

template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_high,
    typename is_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  typename interval_coordinate_type<IntervalType>::type
>::type high(const IntervalType& interval) {
  return get(interval, HIGH);
}

struct y_i_low2 : gtl_yes {};

template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_low2,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  void
>::type low(IntervalType& interval,
    typename interval_mutable_traits<IntervalType>::coordinate_type value) {
  set(interval, LOW, value);
}

struct y_i_high2 : gtl_yes {};

template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_high2,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  void
>::type high(IntervalType& interval,
    typename interval_mutable_traits<IntervalType>::coordinate_type value) {
  set(interval, HIGH, value);
}

struct y_i_equivalence : gtl_yes {};

template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_equivalence,
    typename is_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  bool
>::type equivalence(
    const IntervalType1& interval1,
    const IntervalType2& interval2) {
  return (get(interval1, LOW) == get(interval2, LOW)) &&
         (get(interval1, HIGH) == get(interval2, HIGH));
}

struct y_i_contains : gtl_yes {};

template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_contains,
    typename is_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  bool
>::type contains(
    const IntervalType& interval,
    typename interval_coordinate_type<IntervalType>::type value,
    bool consider_touch = true ) {
  if (consider_touch) {
    return value <= high(interval) && value >= low(interval);
  } else {
    return value < high(interval) && value > low(interval);
  }
}

struct y_i_contains2 : gtl_yes {};

template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_contains2,
    typename is_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  bool
>::type contains(
    const IntervalType1& interval1,
    const IntervalType2& interval2,
    bool consider_touch = true) {
  return contains(interval1, get(interval2, LOW), consider_touch) &&
         contains(interval1, get(interval2, HIGH), consider_touch);
}

struct y_i_center : gtl_yes {};

template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_center,
    typename is_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  typename interval_coordinate_type<IntervalType>::type
>::type center(const IntervalType& interval) {
  return (high(interval) + low(interval)) / 2;
}

struct y_i_delta : gtl_yes {};

template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_delta,
    typename is_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  typename interval_difference_type<IntervalType>::type
>::type delta(const IntervalType& interval) {
  typedef typename interval_difference_type<IntervalType>::type diff_type;
  return static_cast<diff_type>(high(interval)) -
         static_cast<diff_type>(low(interval));
}

struct y_i_flip : gtl_yes {};

template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_flip,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
IntervalType>::type& flip(
    IntervalType& interval,
    typename interval_coordinate_type<IntervalType>::type axis = 0) {
  typename interval_coordinate_type<IntervalType>::type newLow, newHigh;
  newLow  = 2 * axis - high(interval);
  newHigh = 2 * axis - low(interval);
  low(interval, newLow);
  high(interval, newHigh);
  return interval;
}

struct y_i_scale_up : gtl_yes {};

template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_scale_up,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type& scale_up(
    IntervalType& interval,
    typename interval_coordinate_type<IntervalType>::type factor) {
  typename interval_coordinate_type<IntervalType>::type newHigh =
      high(interval) * factor;
  low(interval, low(interval) * factor);
  high(interval, (newHigh));
  return interval;
}

struct y_i_scale_down : gtl_yes {};

template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_scale_down,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type& scale_down(
    IntervalType& interval,
    typename interval_coordinate_type<IntervalType>::type factor) {
  typename interval_coordinate_type<IntervalType>::type newHigh =
      high(interval) / factor;
  low(interval, low(interval) / factor);
  high(interval, (newHigh));
  return interval;
}

// TODO(asydorchuk): Deprecated.
struct y_i_scale : gtl_yes {};

template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_scale,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type& scale(IntervalType& interval, double factor) {
  typedef typename interval_coordinate_type<IntervalType>::type Unit;
  Unit newHigh = scaling_policy<Unit>::round(
      static_cast<double>(high(interval)) * factor);
  low(interval, scaling_policy<Unit>::round(
      static_cast<double>(low(interval)) * factor));
  high(interval, (newHigh));
  return interval;
}

struct y_i_move : gtl_yes {};

template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_move,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type& move(
    IntervalType& interval,
    typename interval_difference_type<IntervalType>::type displacement) {
  typedef typename interval_coordinate_type<IntervalType>::type ctype;
  typedef typename coordinate_traits<ctype>::coordinate_difference Unit;
  low(interval, static_cast<ctype>(
      static_cast<Unit>(low(interval)) + displacement));
  high(interval, static_cast<ctype>(
      static_cast<Unit>(high(interval)) + displacement));
  return interval;
}

struct y_i_convolve : gtl_yes {};

template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_convolve,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type& convolve(
    IntervalType& interval,
    typename interval_coordinate_type<IntervalType>::type value) {
    typedef typename interval_coordinate_type<IntervalType>::type Unit;
  Unit newLow  = low(interval) + value;
  Unit newHigh = high(interval) + value;
  low(interval, newLow);
  high(interval, newHigh);
  return interval;
}

struct y_i_deconvolve : gtl_yes {};

template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_deconvolve,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type& deconvolve(
    IntervalType& interval,
    typename interval_coordinate_type<IntervalType>::type value) {
    typedef typename interval_coordinate_type<IntervalType>::type Unit;
  Unit newLow  = low(interval) - value;
  Unit newHigh = high(interval) - value;
  low(interval, newLow);
  high(interval, newHigh);
  return interval;
}

struct y_i_convolve2 : gtl_yes {};

template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_convolve2,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  IntervalType1
>::type& convolve(IntervalType1& lvalue, const IntervalType2& rvalue) {
  typedef typename interval_coordinate_type<IntervalType1>::type Unit;
  Unit newLow  = low(lvalue) + low(rvalue);
  Unit newHigh = high(lvalue) + high(rvalue);
  low(lvalue, newLow);
  high(lvalue, newHigh);
  return lvalue;
}

struct y_i_deconvolve2 : gtl_yes {};

template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_deconvolve2,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  IntervalType1
>::type& deconvolve(IntervalType1& lvalue, const IntervalType2& rvalue) {
  typedef typename interval_coordinate_type<IntervalType1>::type Unit;
  Unit newLow  = low(lvalue) - low(rvalue);
  Unit newHigh = high(lvalue) - high(rvalue);
  low(lvalue, newLow);
  high(lvalue, newHigh);
  return lvalue;
}

struct y_i_reconvolve : gtl_yes {};

template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_reconvolve,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  IntervalType1
>::type& reflected_convolve(
    IntervalType1& lvalue,
    const IntervalType2& rvalue) {
  typedef typename interval_coordinate_type<IntervalType1>::type Unit;
  Unit newLow  = low(lvalue) - high(rvalue);
  Unit newHigh = high(lvalue) - low(rvalue);
  low(lvalue, newLow);
  high(lvalue, newHigh);
  return lvalue;
}

struct y_i_redeconvolve : gtl_yes {};

template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_redeconvolve,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  IntervalType1
>::type& reflected_deconvolve(
    IntervalType1& lvalue,
    const IntervalType2& rvalue) {
  typedef typename interval_coordinate_type<IntervalType1>::type Unit;
  Unit newLow  = low(lvalue)  + high(rvalue);
  Unit newHigh = high(lvalue) + low(rvalue);
  low(lvalue, newLow);
  high(lvalue, newHigh);
  return lvalue;
}

struct y_i_e_dist1 : gtl_yes {};

template <typename IntervalType>
typename enable_if<
  typename gtl_and<y_i_e_dist1,
    typename is_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  typename interval_difference_type<IntervalType>::type
>::type euclidean_distance(
    const IntervalType& interval,
    typename interval_coordinate_type<IntervalType>::type position) {
  typedef typename interval_difference_type<IntervalType>::type Unit;
  Unit dist[3] = {
      0,
      (Unit)low(interval) - (Unit)position,
      (Unit)position - (Unit)high(interval)
  };
  return dist[(dist[1] > 0) + ((dist[2] > 0) << 1)];
}

struct y_i_e_dist2 : gtl_yes {};

template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_e_dist2,
    typename is_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  typename interval_difference_type<IntervalType1>::type
>::type euclidean_distance(
    const IntervalType1& interval1,
    const IntervalType2& interval2) {
  typedef typename interval_difference_type<IntervalType1>::type Unit;
  Unit dist[3] = {
      0,
      (Unit)low(interval1) - (Unit)high(interval2),
      (Unit)low(interval2) - (Unit)high(interval1)
  };
  return dist[(dist[1] > 0) + ((dist[2] > 0) << 1)];
}

struct y_i_e_intersects : gtl_yes {};

template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_e_intersects,
    typename is_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  bool
>::type intersects(
    const IntervalType1& interval1,
    const IntervalType2& interval2,
    bool consider_touch = true) {
  return consider_touch ?
      (low(interval1) <= high(interval2)) &&
      (high(interval1) >= low(interval2)) :
      (low(interval1) < high(interval2)) &&
      (high(interval1) > low(interval2));
}

struct y_i_e_bintersect : gtl_yes {};

template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_e_bintersect,
    typename is_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  bool
>::type boundaries_intersect(
    const IntervalType1& interval1,
    const IntervalType2& interval2,
    bool consider_touch = true) {
  return (contains(interval1, low(interval2), consider_touch) ||
          contains(interval1, high(interval2), consider_touch)) &&
         (contains(interval2, low(interval1), consider_touch) ||
          contains(interval2, high(interval1), consider_touch));
}

struct y_i_intersect : gtl_yes {};

template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_intersect,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  bool
>::type intersect(
    IntervalType1& lvalue,
    const IntervalType2& rvalue,
    bool consider_touch = true) {
  typedef typename interval_coordinate_type<IntervalType1>::type Unit;
  Unit lowVal = (std::max)(low(lvalue), low(rvalue));
  Unit highVal = (std::min)(high(lvalue), high(rvalue));
  bool valid = consider_touch ? lowVal <= highVal : lowVal < highVal;
  if (valid) {
    low(lvalue, lowVal);
    high(lvalue, highVal);
  }
  return valid;
}

struct y_i_g_intersect : gtl_yes {};

// TODO(asydorchuk): Deprecated.
template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_g_intersect,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  IntervalType1
>::type& generalized_intersect(
    IntervalType1& lvalue,
    const IntervalType2& rvalue) {
  typedef typename interval_coordinate_type<IntervalType1>::type Unit;
  Unit coords[4] = {low(lvalue), high(lvalue), low(rvalue), high(rvalue)};
  // TODO(asydorchuk): consider implementing faster sorting of small
  // fixed length range.
  polygon_sort(coords, coords+4);
  low(lvalue, coords[1]);
  high(lvalue, coords[2]);
  return lvalue;
}

struct y_i_abuts1 : gtl_yes {};

template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_abuts1,
    typename is_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  bool
>::type abuts(
    const IntervalType1& interval1,
    const IntervalType2& interval2,
    direction_1d dir) {
  return dir.to_int() ? low(interval2) == high(interval1) :
                        low(interval1) == high(interval2);
}

struct y_i_abuts2 : gtl_yes {};

template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_abuts2,
    typename is_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  bool
>::type abuts(
    const IntervalType1& interval1,
    const IntervalType2& interval2) {
  return abuts(interval1, interval2, HIGH) ||
         abuts(interval1, interval2, LOW);
}

struct y_i_bloat : gtl_yes {};

template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_bloat,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type& bloat(
    IntervalType& interval,
    typename interval_coordinate_type<IntervalType>::type bloating) {
  low(interval, low(interval) - bloating);
  high(interval, high(interval) + bloating);
  return interval;
}

struct y_i_bloat2 : gtl_yes {};

template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_bloat2,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type& bloat(
    IntervalType& interval,
    direction_1d dir,
    typename interval_coordinate_type<IntervalType>::type bloating) {
  set(interval, dir, get(interval, dir) + dir.get_sign() * bloating);
  return interval;
}

struct y_i_shrink : gtl_yes {};

template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_shrink,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type& shrink(
    IntervalType& interval,
    typename interval_coordinate_type<IntervalType>::type shrinking) {
  return bloat(interval, -shrinking);
}

struct y_i_shrink2 : gtl_yes {};

template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_shrink2,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type& shrink(
    IntervalType& interval,
    direction_1d dir,
    typename interval_coordinate_type<IntervalType>::type shrinking) {
  return bloat(interval, dir, -shrinking);
}

struct y_i_encompass : gtl_yes {};

template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_encompass,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  bool
>::type encompass(IntervalType1& interval1, const IntervalType2& interval2) {
  bool retval = !contains(interval1, interval2, true);
  low(interval1, (std::min)(low(interval1), low(interval2)));
  high(interval1, (std::max)(high(interval1), high(interval2)));
  return retval;
}

struct y_i_encompass2 : gtl_yes {};

template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_encompass2,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  bool
>::type encompass(
    IntervalType& interval,
    typename interval_coordinate_type<IntervalType>::type value) {
  bool retval = !contains(interval, value, true);
  low(interval, (std::min)(low(interval), value));
  high(interval, (std::max)(high(interval), value));
  return retval;
}

struct y_i_get_half : gtl_yes {};

template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_get_half,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type get_half(const IntervalType& interval, direction_1d dir) {
  typedef typename interval_coordinate_type<IntervalType>::type Unit;
  Unit c = (get(interval, LOW) + get(interval, HIGH)) / 2;
  return construct<IntervalType>(
      (dir == LOW) ? get(interval, LOW) : c,
      (dir == LOW) ? c : get(interval, HIGH));
}

struct y_i_join_with : gtl_yes {};

template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_join_with,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type>::type,
  bool
>::type join_with(IntervalType1& interval1, const IntervalType2& interval2) {
  if (abuts(interval1, interval2)) {
    encompass(interval1, interval2);
    return true;
  }
  return false;
}
}  // polygon
}  // boost

#endif  // BOOST_POLYGON_INTERVAL_CONCEPT_HPP

/* interval_concept.hpp
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
*/