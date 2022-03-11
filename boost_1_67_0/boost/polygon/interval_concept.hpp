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