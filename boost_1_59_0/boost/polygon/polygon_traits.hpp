/*
  Copyright 2008 Intel Corporation

  Use, modification and distribution are subject to the Boost Software License,
  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt).
*/
#ifndef BOOST_POLYGON_POLYGON_TRAITS_HPP
#define BOOST_POLYGON_POLYGON_TRAITS_HPP
namespace boost { namespace polygon{

  template <typename T, typename enable = gtl_yes>
  struct polygon_90_traits {
    typedef typename T::coordinate_type coordinate_type;
    typedef typename T::compact_iterator_type compact_iterator_type;

    // Get the begin iterator
    static inline compact_iterator_type begin_compact(const T& t) {
      return t.begin_compact();
    }

    // Get the end iterator
    static inline compact_iterator_type end_compact(const T& t) {
      return t.end_compact();
    }

    // Get the number of sides of the polygon
    static inline std::size_t size(const T& t) {
      return t.size();
    }

    // Get the winding direction of the polygon
    static inline winding_direction winding(const T&) {
      return unknown_winding;
    }
  };

  template <typename T>
  struct polygon_traits_general {
    typedef typename T::coordinate_type coordinate_type;
    typedef typename T::iterator_type iterator_type;
    typedef typename T::point_type point_type;

    // Get the begin iterator
    static inline iterator_type begin_points(const T& t) {
      return t.begin();
    }

    // Get the end iterator
    static inline iterator_type end_points(const T& t) {
      return t.end();
    }

    // Get the number of sides of the polygon
    static inline std::size_t size(const T& t) {
      return t.size();
    }

    // Get the winding direction of the polygon
    static inline winding_direction winding(const T&) {
      return unknown_winding;
    }
  };

  template <typename T>
  struct polygon_traits_90 {
    typedef typename polygon_90_traits<T>::coordinate_type coordinate_type;
    typedef iterator_compact_to_points<typename polygon_90_traits<T>::compact_iterator_type, point_data<coordinate_type> > iterator_type;
    typedef point_data<coordinate_type> point_type;

    // Get the begin iterator
    static inline iterator_type begin_points(const T& t) {
      return iterator_type(polygon_90_traits<T>::begin_compact(t),
                           polygon_90_traits<T>::end_compact(t));
    }

    // Get the end iterator
    static inline iterator_type end_points(const T& t) {
      return iterator_type(polygon_90_traits<T>::end_compact(t),
                           polygon_90_traits<T>::end_compact(t));
    }

    // Get the number of sides of the polygon
    static inline std::size_t size(const T& t) {
      return polygon_90_traits<T>::size(t);
    }

    // Get the winding direction of the polygon
    static inline winding_direction winding(const T& t) {
      return polygon_90_traits<T>::winding(t);
    }
  };

#ifndef BOOST_VERY_LITTLE_SFINAE

  template <typename T, typename enable = gtl_yes>
  struct polygon_traits {};

  template <typename T>
  struct polygon_traits<T,
                        typename gtl_or_4<
    typename gtl_same_type<typename geometry_concept<T>::type, polygon_concept>::type,
    typename gtl_same_type<typename geometry_concept<T>::type, polygon_45_concept>::type,
    typename gtl_same_type<typename geometry_concept<T>::type, polygon_with_holes_concept>::type,
    typename gtl_same_type<typename geometry_concept<T>::type, polygon_45_with_holes_concept>::type
  >::type> : public polygon_traits_general<T> {};

  template <typename T>
  struct polygon_traits< T,
                         typename gtl_or<
    typename gtl_same_type<typename geometry_concept<T>::type, polygon_90_concept>::type,
    typename gtl_same_type<typename geometry_concept<T>::type, polygon_90_with_holes_concept>::type
  >::type > : public polygon_traits_90<T> {};

#else

  template <typename T, typename T_IF, typename T_ELSE>
  struct gtl_ifelse {};
  template <typename T_IF, typename T_ELSE>
  struct gtl_ifelse<gtl_no, T_IF, T_ELSE> {
    typedef T_ELSE type;
  };
  template <typename T_IF, typename T_ELSE>
  struct gtl_ifelse<gtl_yes, T_IF, T_ELSE> {
    typedef T_IF type;
  };

  template <typename T, typename enable = gtl_yes>
  struct polygon_traits {};

  template <typename T>
  struct polygon_traits<T, typename gtl_or<typename gtl_or_4<
    typename gtl_same_type<typename geometry_concept<T>::type, polygon_concept>::type,
    typename gtl_same_type<typename geometry_concept<T>::type, polygon_45_concept>::type,
    typename gtl_same_type<typename geometry_concept<T>::type, polygon_with_holes_concept>::type,
    typename gtl_same_type<typename geometry_concept<T>::type, polygon_45_with_holes_concept>::type
  >::type, typename gtl_or<
    typename gtl_same_type<typename geometry_concept<T>::type, polygon_90_concept>::type,
    typename gtl_same_type<typename geometry_concept<T>::type, polygon_90_with_holes_concept>::type
  >::type>::type > : public gtl_ifelse<typename gtl_or<
    typename gtl_same_type<typename geometry_concept<T>::type, polygon_90_concept>::type,
    typename gtl_same_type<typename geometry_concept<T>::type, polygon_90_with_holes_concept>::type >::type,
      polygon_traits_90<T>,
      polygon_traits_general<T> >::type {
  };

#endif

  template <typename T, typename enable = void>
  struct polygon_with_holes_traits {
    typedef typename T::iterator_holes_type iterator_holes_type;
    typedef typename T::hole_type hole_type;

    // Get the begin iterator
    static inline iterator_holes_type begin_holes(const T& t) {
      return t.begin_holes();
    }

    // Get the end iterator
    static inline iterator_holes_type end_holes(const T& t) {
      return t.end_holes();
    }

    // Get the number of holes
    static inline std::size_t size_holes(const T& t) {
      return t.size_holes();
    }
  };

  template <typename T, typename enable = void>
  struct polygon_90_mutable_traits {

    // Set the data of a polygon with the unique coordinates in an iterator, starting with an x
    template <typename iT>
    static inline T& set_compact(T& t, iT input_begin, iT input_end) {
      t.set_compact(input_begin, input_end);
      return t;
    }

  };

  template <typename T, typename enable = void>
  struct polygon_mutable_traits {

    // Set the data of a polygon with the unique coordinates in an iterator, starting with an x
    template <typename iT>
    static inline T& set_points(T& t, iT input_begin, iT input_end) {
      t.set(input_begin, input_end);
      return t;
    }

  };

  template <typename T, typename enable = void>
  struct polygon_with_holes_mutable_traits {

    // Set the data of a polygon with the unique coordinates in an iterator, starting with an x
    template <typename iT>
    static inline T& set_holes(T& t, iT inputBegin, iT inputEnd) {
      t.set_holes(inputBegin, inputEnd);
      return t;
    }

  };
}
}
#include "isotropy.hpp"

//point
#include "point_data.hpp"
#include "point_traits.hpp"
#include "point_concept.hpp"

//interval
#include "interval_data.hpp"
#include "interval_traits.hpp"
#include "interval_concept.hpp"

//rectangle
#include "rectangle_data.hpp"
#include "rectangle_traits.hpp"
#include "rectangle_concept.hpp"

//algorithms needed by polygon types
#include "detail/iterator_points_to_compact.hpp"
#include "detail/iterator_compact_to_points.hpp"

//polygons
#include "polygon_45_data.hpp"
#include "polygon_data.hpp"
#include "polygon_90_data.hpp"
#include "polygon_90_with_holes_data.hpp"
#include "polygon_45_with_holes_data.hpp"
#include "polygon_with_holes_data.hpp"

namespace boost { namespace polygon{
  struct polygon_concept {};
  struct polygon_with_holes_concept {};
  struct polygon_45_concept {};
  struct polygon_45_with_holes_concept {};
  struct polygon_90_concept {};
  struct polygon_90_with_holes_concept {};


  template <typename T>
  struct is_polygon_90_type {
    typedef typename geometry_concept<T>::type GC;
    typedef typename gtl_same_type<polygon_90_concept, GC>::type type;
  };

  template <typename T>
  struct is_polygon_45_type {
    typedef typename geometry_concept<T>::type GC;
    typedef typename gtl_or<typename is_polygon_90_type<T>::type,
                            typename gtl_same_type<polygon_45_concept, GC>::type>::type type;
  };

  template <typename T>
  struct is_polygon_type {
    typedef typename geometry_concept<T>::type GC;
    typedef typename gtl_or<typename is_polygon_45_type<T>::type,
                            typename gtl_same_type<polygon_concept, GC>::type>::type type;
  };

  template <typename T>
  struct is_polygon_90_with_holes_type {
    typedef typename geometry_concept<T>::type GC;
    typedef typename gtl_or<typename is_polygon_90_type<T>::type,
                            typename gtl_same_type<polygon_90_with_holes_concept, GC>::type>::type type;
  };

  template <typename T>
  struct is_polygon_45_with_holes_type {
    typedef typename geometry_concept<T>::type GC;
    typedef typename gtl_or_3<typename is_polygon_90_with_holes_type<T>::type,
                              typename is_polygon_45_type<T>::type,
                              typename gtl_same_type<polygon_45_with_holes_concept, GC>::type>::type type;
  };

  template <typename T>
  struct is_polygon_with_holes_type {
    typedef typename geometry_concept<T>::type GC;
    typedef typename gtl_or_3<typename is_polygon_45_with_holes_type<T>::type,
                              typename is_polygon_type<T>::type,
                              typename gtl_same_type<polygon_with_holes_concept, GC>::type>::type type;
  };

  template <typename T>
  struct is_mutable_polygon_90_type {
    typedef typename geometry_concept<T>::type GC;
    typedef typename gtl_same_type<polygon_90_concept, GC>::type type;
  };

  template <typename T>
  struct is_mutable_polygon_45_type {
    typedef typename geometry_concept<T>::type GC;
    typedef typename gtl_same_type<polygon_45_concept, GC>::type type;
  };

  template <typename T>
  struct is_mutable_polygon_type {
    typedef typename geometry_concept<T>::type GC;
    typedef typename gtl_same_type<polygon_concept, GC>::type type;
  };

  template <typename T>
  struct is_mutable_polygon_90_with_holes_type {
    typedef typename geometry_concept<T>::type GC;
    typedef typename gtl_same_type<polygon_90_with_holes_concept, GC>::type type;
  };

  template <typename T>
  struct is_mutable_polygon_45_with_holes_type {
    typedef typename geometry_concept<T>::type GC;
    typedef typename gtl_same_type<polygon_45_with_holes_concept, GC>::type type;
  };

  template <typename T>
  struct is_mutable_polygon_with_holes_type {
    typedef typename geometry_concept<T>::type GC;
    typedef typename gtl_same_type<polygon_with_holes_concept, GC>::type type;
  };

  template <typename T>
  struct is_any_mutable_polygon_with_holes_type {
    typedef typename gtl_or_3<typename is_mutable_polygon_90_with_holes_type<T>::type,
                              typename is_mutable_polygon_45_with_holes_type<T>::type,
                              typename is_mutable_polygon_with_holes_type<T>::type>::type type;
  };
  template <typename T>
  struct is_any_mutable_polygon_without_holes_type {
    typedef typename gtl_or_3<
      typename is_mutable_polygon_90_type<T>::type,
      typename is_mutable_polygon_45_type<T>::type,
      typename is_mutable_polygon_type<T>::type>::type type; };

  template <typename T>
  struct is_any_mutable_polygon_type {
    typedef typename gtl_or<typename is_any_mutable_polygon_with_holes_type<T>::type,
                            typename is_any_mutable_polygon_without_holes_type<T>::type>::type type;
  };

  template <typename T>
  struct polygon_from_polygon_with_holes_type {};
  template <>
  struct polygon_from_polygon_with_holes_type<polygon_with_holes_concept> { typedef polygon_concept type; };
  template <>
  struct polygon_from_polygon_with_holes_type<polygon_45_with_holes_concept> { typedef polygon_45_concept type; };
  template <>
  struct polygon_from_polygon_with_holes_type<polygon_90_with_holes_concept> { typedef polygon_90_concept type; };

  template <>
  struct geometry_domain<polygon_45_concept> { typedef forty_five_domain type; };
  template <>
  struct geometry_domain<polygon_45_with_holes_concept> { typedef forty_five_domain type; };
  template <>
  struct geometry_domain<polygon_90_concept> { typedef manhattan_domain type; };
  template <>
  struct geometry_domain<polygon_90_with_holes_concept> { typedef manhattan_domain type; };

  template <typename domain_type, typename coordinate_type>
  struct distance_type_by_domain { typedef typename coordinate_traits<coordinate_type>::coordinate_distance type; };
  template <typename coordinate_type>
  struct distance_type_by_domain<manhattan_domain, coordinate_type> {
    typedef typename coordinate_traits<coordinate_type>::coordinate_difference type; };

  // \brief Sets the boundary of the polygon to the points in the iterator range
  // \tparam T A type that models polygon_concept
  // \tparam iT Iterator type over objects that model point_concept
  // \param t The polygon to set
  // \param begin_points The start of the range of points
  // \param end_points The end of the range of points

  /// \relatesalso polygon_concept
  template <typename T, typename iT>
  typename enable_if <typename is_any_mutable_polygon_type<T>::type, T>::type &
  set_points(T& t, iT begin_points, iT end_points) {
    polygon_mutable_traits<T>::set_points(t, begin_points, end_points);
    return t;
  }

  // \brief Sets the boundary of the polygon to the non-redundant coordinates in the iterator range
  // \tparam T A type that models polygon_90_concept
  // \tparam iT Iterator type over objects that model coordinate_concept
  // \param t The polygon to set
  // \param begin_compact_coordinates The start of the range of coordinates
  // \param end_compact_coordinates The end of the range of coordinates

/// \relatesalso polygon_90_concept
  template <typename T, typename iT>
  typename enable_if <typename gtl_or<
    typename is_mutable_polygon_90_type<T>::type,
    typename is_mutable_polygon_90_with_holes_type<T>::type>::type, T>::type &
  set_compact(T& t, iT begin_compact_coordinates, iT end_compact_coordinates) {
    polygon_90_mutable_traits<T>::set_compact(t, begin_compact_coordinates, end_compact_coordinates);
    return t;
  }

/// \relatesalso polygon_with_holes_concept
  template <typename T, typename iT>
  typename enable_if< typename gtl_and <
    typename is_any_mutable_polygon_with_holes_type<T>::type,
    typename gtl_different_type<typename geometry_domain<typename geometry_concept<T>::type>::type,
                                manhattan_domain>::type>::type,
                       T>::type &
  set_compact(T& t, iT begin_compact_coordinates, iT end_compact_coordinates) {
    iterator_compact_to_points<iT, point_data<typename polygon_traits<T>::coordinate_type> >
      itrb(begin_compact_coordinates, end_compact_coordinates),
      itre(end_compact_coordinates, end_compact_coordinates);
    return set_points(t, itrb, itre);
  }

/// \relatesalso polygon_with_holes_concept
  template <typename T, typename iT>
  typename enable_if <typename is_any_mutable_polygon_with_holes_type<T>::type, T>::type &
  set_holes(T& t, iT begin_holes, iT end_holes) {
    polygon_with_holes_mutable_traits<T>::set_holes(t, begin_holes, end_holes);
    return t;
  }

/// \relatesalso polygon_90_concept
  template <typename T>
  typename polygon_90_traits<T>::compact_iterator_type
  begin_compact(const T& polygon,
    typename enable_if<
      typename gtl_and <typename is_polygon_with_holes_type<T>::type,
                        typename gtl_same_type<typename geometry_domain<typename geometry_concept<T>::type>::type,
                manhattan_domain>::type>::type>::type * = 0
  ) {
    return polygon_90_traits<T>::begin_compact(polygon);
  }

/// \relatesalso polygon_90_concept
  template <typename T>
  typename polygon_90_traits<T>::compact_iterator_type
  end_compact(const T& polygon,
    typename enable_if<
    typename gtl_and <typename is_polygon_with_holes_type<T>::type,
                      typename gtl_same_type<typename geometry_domain<typename geometry_concept<T>::type>::type,
              manhattan_domain>::type>::type>::type * = 0
  ) {
    return polygon_90_traits<T>::end_compact(polygon);
  }

  /// \relatesalso polygon_concept
  template <typename T>
  typename enable_if < typename gtl_if<
    typename is_polygon_with_holes_type<T>::type>::type,
                        typename polygon_traits<T>::iterator_type>::type
  begin_points(const T& polygon) {
    return polygon_traits<T>::begin_points(polygon);
  }

  /// \relatesalso polygon_concept
  template <typename T>
  typename enable_if < typename gtl_if<
    typename is_polygon_with_holes_type<T>::type>::type,
                        typename polygon_traits<T>::iterator_type>::type
  end_points(const T& polygon) {
    return polygon_traits<T>::end_points(polygon);
  }

  /// \relatesalso polygon_concept
  template <typename T>
  typename enable_if <typename is_polygon_with_holes_type<T>::type,
                       std::size_t>::type
  size(const T& polygon) {
    return polygon_traits<T>::size(polygon);
  }

/// \relatesalso polygon_with_holes_concept
  template <typename T>
  typename enable_if < typename gtl_if<
    typename is_polygon_with_holes_type<T>::type>::type,
                        typename polygon_with_holes_traits<T>::iterator_holes_type>::type
  begin_holes(const T& polygon) {
    return polygon_with_holes_traits<T>::begin_holes(polygon);
  }

/// \relatesalso polygon_with_holes_concept
  template <typename T>
  typename enable_if < typename gtl_if<
    typename is_polygon_with_holes_type<T>::type>::type,
                        typename polygon_with_holes_traits<T>::iterator_holes_type>::type
  end_holes(const T& polygon) {
    return polygon_with_holes_traits<T>::end_holes(polygon);
  }

/// \relatesalso polygon_with_holes_concept
  template <typename T>
  typename enable_if <typename is_polygon_with_holes_type<T>::type,
                       std::size_t>::type
  size_holes(const T& polygon) {
    return polygon_with_holes_traits<T>::size_holes(polygon);
  }

  // \relatesalso polygon_concept
  template <typename T1, typename T2>
  typename enable_if<
    typename gtl_and< typename is_mutable_polygon_type<T1>::type,
                      typename is_polygon_type<T2>::type>::type, T1>::type &
  assign(T1& lvalue, const T2& rvalue) {
    polygon_mutable_traits<T1>::set_points(lvalue, polygon_traits<T2>::begin_points(rvalue),
                                           polygon_traits<T2>::end_points(rvalue));
    return lvalue;
  }

// \relatesalso polygon_with_holes_concept
  template <typename T1, typename T2>
  typename enable_if<
    typename gtl_and< typename is_mutable_polygon_with_holes_type<T1>::type,
                      typename is_polygon_with_holes_type<T2>::type>::type, T1>::type &
  assign(T1& lvalue, const T2& rvalue) {
    polygon_mutable_traits<T1>::set_points(lvalue, polygon_traits<T2>::begin_points(rvalue),
                                           polygon_traits<T2>::end_points(rvalue));
    polygon_with_holes_mutable_traits<T1>::set_holes(lvalue, polygon_with_holes_traits<T2>::begin_holes(rvalue),
                                                     polygon_with_holes_traits<T2>::end_holes(rvalue));
    return lvalue;
  }

  // \relatesalso polygon_45_concept
  template <typename T1, typename T2>
  typename enable_if< typename gtl_and< typename is_mutable_polygon_45_type<T1>::type, typename is_polygon_45_type<T2>::type>::type, T1>::type &
  assign(T1& lvalue, const T2& rvalue) {
    polygon_mutable_traits<T1>::set_points(lvalue, polygon_traits<T2>::begin_points(rvalue),
                                           polygon_traits<T2>::end_points(rvalue));
    return lvalue;
  }

// \relatesalso polygon_45_with_holes_concept
  template <typename T1, typename T2>
  typename enable_if<
    typename gtl_and< typename is_mutable_polygon_45_with_holes_type<T1>::type,
                      typename is_polygon_45_with_holes_type<T2>::type>::type, T1>::type &
  assign(T1& lvalue, const T2& rvalue) {
    polygon_mutable_traits<T1>::set_points(lvalue, polygon_traits<T2>::begin_points(rvalue),
                                           polygon_traits<T2>::end_points(rvalue));
    polygon_with_holes_mutable_traits<T1>::set_holes(lvalue, polygon_with_holes_traits<T2>::begin_holes(rvalue),
                                                     polygon_with_holes_traits<T2>::end_holes(rvalue));
    return lvalue;
  }

  // \relatesalso polygon_90_concept
  template <typename T1, typename T2>
  typename enable_if<
    typename gtl_and< typename is_mutable_polygon_90_type<T1>::type,
                      typename is_polygon_90_type<T2>::type>::type, T1>::type &
  assign(T1& lvalue, const T2& rvalue) {
    polygon_90_mutable_traits<T1>::set_compact(lvalue, polygon_90_traits<T2>::begin_compact(rvalue),
                                               polygon_90_traits<T2>::end_compact(rvalue));
    return lvalue;
  }

// \relatesalso polygon_90_with_holes_concept
  template <typename T1, typename T2>
  typename enable_if<
    typename gtl_and< typename is_mutable_polygon_90_with_holes_type<T1>::type,
                      typename is_polygon_90_with_holes_type<T2>::type>::type, T1>::type &
  assign(T1& lvalue, const T2& rvalue) {
    polygon_90_mutable_traits<T1>::set_compact(lvalue, polygon_90_traits<T2>::begin_compact(rvalue),
                                               polygon_90_traits<T2>::end_compact(rvalue));
    polygon_with_holes_mutable_traits<T1>::set_holes(lvalue, polygon_with_holes_traits<T2>::begin_holes(rvalue),
                                                     polygon_with_holes_traits<T2>::end_holes(rvalue));
    return lvalue;
  }

  // \relatesalso polygon_90_concept
  template <typename T1, typename T2>
  typename enable_if<
    typename gtl_and< typename is_any_mutable_polygon_type<T1>::type,
                      typename is_rectangle_concept<typename geometry_concept<T2>::type>::type>::type, T1>::type &
  assign(T1& polygon, const T2& rect) {
    typedef point_data<typename polygon_traits<T1>::coordinate_type> PT;
    PT points[4] = {PT(xl(rect), yl(rect)), PT(xh(rect), yl(rect)), PT(xh(rect), yh(rect)), PT(xl(rect), yh(rect))};
    set_points(polygon, points, points+4);
    return polygon;
  }

/// \relatesalso polygon_90_concept
  template <typename polygon_type, typename point_type>
  typename enable_if< typename gtl_and< typename is_mutable_polygon_90_type<polygon_type>::type,
                                         typename is_point_concept<typename geometry_concept<point_type>::type>::type>::type,
                       polygon_type>::type &
  convolve(polygon_type& polygon, const point_type& point) {
    std::vector<typename polygon_90_traits<polygon_type>::coordinate_type> coords;
    coords.reserve(::boost::polygon::size(polygon));
    bool pingpong = true;
    for(typename polygon_90_traits<polygon_type>::compact_iterator_type iter = begin_compact(polygon);
        iter != end_compact(polygon); ++iter) {
      coords.push_back((*iter) + (pingpong ? x(point) : y(point)));
      pingpong = !pingpong;
    }
    polygon_90_mutable_traits<polygon_type>::set_compact(polygon, coords.begin(), coords.end());
    return polygon;
  }

/// \relatesalso polygon_concept
  template <typename polygon_type, typename point_type>
  typename enable_if< typename gtl_and< typename gtl_or<
    typename is_mutable_polygon_45_type<polygon_type>::type,
    typename is_mutable_polygon_type<polygon_type>::type>::type,
                                         typename is_point_concept<typename geometry_concept<point_type>::type>::type>::type,
                       polygon_type>::type &
  convolve(polygon_type& polygon, const point_type& point) {
    std::vector<typename std::iterator_traits<typename polygon_traits<polygon_type>::iterator_type>::value_type> points;
    points.reserve(::boost::polygon::size(polygon));
    for(typename polygon_traits<polygon_type>::iterator_type iter = begin_points(polygon);
        iter != end_points(polygon); ++iter) {
      points.push_back(*iter);
      convolve(points.back(), point);
    }
    polygon_mutable_traits<polygon_type>::set_points(polygon, points.begin(), points.end());
    return polygon;
  }

/// \relatesalso polygon_with_holes_concept
  template <typename polygon_type, typename point_type>
  typename enable_if<
    typename gtl_and< typename is_any_mutable_polygon_with_holes_type<polygon_type>::type,
                      typename is_point_concept<typename geometry_concept<point_type>::type>::type>::type,
    polygon_type>::type &
  convolve(polygon_type& polygon, const point_type& point) {
    typedef typename polygon_with_holes_traits<polygon_type>::hole_type hole_type;
    hole_type h;
    set_points(h, begin_points(polygon), end_points(polygon));
    convolve(h, point);
    std::vector<hole_type> holes;
    holes.reserve(size_holes(polygon));
    for(typename polygon_with_holes_traits<polygon_type>::iterator_holes_type itr = begin_holes(polygon);
        itr != end_holes(polygon); ++itr) {
      holes.push_back(*itr);
      convolve(holes.back(), point);
    }
    assign(polygon, h);
    set_holes(polygon, holes.begin(), holes.end());
    return polygon;
  }

/// \relatesalso polygon_concept
  template <typename T>
  typename enable_if< typename is_any_mutable_polygon_type<T>::type, T>::type &
  move(T& polygon, orientation_2d orient, typename polygon_traits<T>::coordinate_type displacement) {
    typedef typename polygon_traits<T>::coordinate_type Unit;
    if(orient == HORIZONTAL) return convolve(polygon, point_data<Unit>(displacement, Unit(0)));
    return convolve(polygon, point_data<Unit>(Unit(0), displacement));
  }

/// \relatesalso polygon_concept
/// \brief Applies a transformation to the polygon.
/// \tparam polygon_type A type that models polygon_concept
/// \tparam transform_type A type that may be either axis_transformation or transformation or that overloads point_concept::transform
/// \param polygon The polygon to transform
/// \param tr The transformation to apply
  template <typename polygon_type, typename transform_type>
  typename enable_if< typename is_any_mutable_polygon_without_holes_type<polygon_type>::type, polygon_type>::type &
  transform(polygon_type& polygon, const transform_type& tr) {
    std::vector<typename std::iterator_traits<typename polygon_traits<polygon_type>::iterator_type>::value_type> points;
    points.reserve(::boost::polygon::size(polygon));
    for(typename polygon_traits<polygon_type>::iterator_type iter = begin_points(polygon);
        iter != end_points(polygon); ++iter) {
      points.push_back(*iter);
      transform(points.back(), tr);
    }
    polygon_mutable_traits<polygon_type>::set_points(polygon, points.begin(), points.end());
    return polygon;
  }

/// \relatesalso polygon_with_holes_concept
  template <typename T, typename transform_type>
  typename enable_if< typename is_any_mutable_polygon_with_holes_type<T>::type, T>::type &
  transform(T& polygon, const transform_type& tr) {
    typedef typename polygon_with_holes_traits<T>::hole_type hole_type;
    hole_type h;
    set_points(h, begin_points(polygon), end_points(polygon));
    transform(h, tr);
    std::vector<hole_type> holes;
    holes.reserve(size_holes(polygon));
    for(typename polygon_with_holes_traits<T>::iterator_holes_type itr = begin_holes(polygon);
        itr != end_holes(polygon); ++itr) {
      holes.push_back(*itr);
      transform(holes.back(), tr);
    }
    assign(polygon, h);
    set_holes(polygon, holes.begin(), holes.end());
    return polygon;
  }

  template <typename polygon_type>
  typename enable_if< typename is_any_mutable_polygon_without_holes_type<polygon_type>::type, polygon_type>::type &
  scale_up(polygon_type& polygon, typename coordinate_traits<typename polygon_traits<polygon_type>::coordinate_type>::unsigned_area_type factor) {
    std::vector<typename std::iterator_traits<typename polygon_traits<polygon_type>::iterator_type>::value_type> points;
    points.reserve(::boost::polygon::size(polygon));
    for(typename polygon_traits<polygon_type>::iterator_type iter = begin_points(polygon);
        iter != end_points(polygon); ++iter) {
      points.push_back(*iter);
      scale_up(points.back(), factor);
    }
    polygon_mutable_traits<polygon_type>::set_points(polygon, points.begin(), points.end());
    return polygon;
  }

  template <typename T>
  typename enable_if< typename is_any_mutable_polygon_with_holes_type<T>::type, T>::type &
  scale_up(T& polygon, typename coordinate_traits<typename polygon_traits<T>::coordinate_type>::unsigned_area_type factor) {
    typedef typename polygon_with_holes_traits<T>::hole_type hole_type;
    hole_type h;
    set_points(h, begin_points(polygon), end_points(polygon));
    scale_up(h, factor);
    std::vector<hole_type> holes;
    holes.reserve(size_holes(polygon));
    for(typename polygon_with_holes_traits<T>::iterator_holes_type itr = begin_holes(polygon);
        itr != end_holes(polygon); ++itr) {
      holes.push_back(*itr);
      scale_up(holes.back(), factor);
    }
    assign(polygon, h);
    set_holes(polygon, holes.begin(), holes.end());
    return polygon;
  }

  //scale non-45 down
  template <typename polygon_type>
  typename enable_if<
    typename gtl_and< typename is_any_mutable_polygon_without_holes_type<polygon_type>::type,
                      typename gtl_not<typename gtl_same_type
                                       < forty_five_domain,
                                         typename geometry_domain<typename geometry_concept<polygon_type>::type>::type>::type>::type>::type,
    polygon_type>::type &
  scale_down(polygon_type& polygon, typename coordinate_traits<typename polygon_traits<polygon_type>::coordinate_type>::unsigned_area_type factor) {
    std::vector<typename std::iterator_traits<typename polygon_traits<polygon_type>::iterator_type>::value_type> points;
    points.reserve(::boost::polygon::size(polygon));
    for(typename polygon_traits<polygon_type>::iterator_type iter = begin_points(polygon);
        iter != end_points(polygon); ++iter) {
      points.push_back(*iter);
      scale_down(points.back(), factor);
    }
    polygon_mutable_traits<polygon_type>::set_points(polygon, points.begin(), points.end());
    return polygon;
  }

  template <typename Unit>
  Unit local_abs(Unit value) { return value < 0 ? (Unit)-value : value; }

  template <typename Unit>
  void snap_point_vector_to_45(std::vector<point_data<Unit> >& pts) {
    typedef point_data<Unit> Point;
    if(pts.size() < 3) { pts.clear(); return; }
    typename std::vector<point_data<Unit> >::iterator endLocation = std::unique(pts.begin(), pts.end());
    if(endLocation != pts.end()){
      pts.resize(endLocation - pts.begin());
    }
    if(pts.back() == pts[0]) pts.pop_back();
    //iterate over point triplets
    int numPts = pts.size();
    bool wrap_around = false;
    for(int i = 0; i < numPts; ++i) {
      Point& pt1 = pts[i];
      Point& pt2 = pts[(i + 1) % numPts];
      Point& pt3 = pts[(i + 2) % numPts];
      //check if non-45 edge
      Unit deltax = x(pt2) - x(pt1);
      Unit deltay = y(pt2) - y(pt1);
      if(deltax && deltay &&
         local_abs(deltax) != local_abs(deltay)) {
        //adjust the middle point
        Unit ndx = x(pt3) - x(pt2);
        Unit ndy = y(pt3) - y(pt2);
        if(ndx && ndy) {
          Unit diff = local_abs(local_abs(deltax) - local_abs(deltay));
          Unit halfdiff = diff/2;
          if((deltax > 0 && deltay > 0) ||
             (deltax < 0 && deltay < 0)) {
            //previous edge is rising slope
            if(local_abs(deltax + halfdiff + (diff % 2)) ==
               local_abs(deltay - halfdiff)) {
              x(pt2, x(pt2) + halfdiff + (diff % 2));
              y(pt2, y(pt2) - halfdiff);
            } else if(local_abs(deltax - halfdiff - (diff % 2)) ==
                      local_abs(deltay + halfdiff)) {
              x(pt2, x(pt2) - halfdiff - (diff % 2));
              y(pt2, y(pt2) + halfdiff);
            } else{
              //std::cout << "fail1\n";
            }
          } else {
            //previous edge is falling slope
            if(local_abs(deltax + halfdiff + (diff % 2)) ==
               local_abs(deltay + halfdiff)) {
              x(pt2, x(pt2) + halfdiff + (diff % 2));
              y(pt2, y(pt2) + halfdiff);
            } else if(local_abs(deltax - halfdiff - (diff % 2)) ==
                      local_abs(deltay - halfdiff)) {
              x(pt2, x(pt2) - halfdiff - (diff % 2));
              y(pt2, y(pt2) - halfdiff);
            } else {
              //std::cout << "fail2\n";
            }
          }
          if(i == numPts - 1 && (diff % 2)) {
            //we have a wrap around effect
            if(!wrap_around) {
              wrap_around = true;
              i = -1;
            }
          }
        } else if(ndx) {
          //next edge is horizontal
          //find the x value for pt1 that would make the abs(deltax) == abs(deltay)
          Unit newDeltaX = local_abs(deltay);
          if(deltax < 0) newDeltaX *= -1;
          x(pt2, x(pt1) + newDeltaX);
        } else { //ndy
          //next edge is vertical
          //find the y value for pt1 that would make the abs(deltax) == abs(deltay)
          Unit newDeltaY = local_abs(deltax);
          if(deltay < 0) newDeltaY *= -1;
          y(pt2, y(pt1) + newDeltaY);
        }
      }
    }
  }

  template <typename polygon_type>
  typename enable_if< typename is_any_mutable_polygon_without_holes_type<polygon_type>::type, polygon_type>::type &
  snap_to_45(polygon_type& polygon) {
    std::vector<typename std::iterator_traits<typename polygon_traits<polygon_type>::iterator_type>::value_type> points;
    points.reserve(::boost::polygon::size(polygon));
    for(typename polygon_traits<polygon_type>::iterator_type iter = begin_points(polygon);
        iter != end_points(polygon); ++iter) {
      points.push_back(*iter);
    }
    snap_point_vector_to_45(points);
    polygon_mutable_traits<polygon_type>::set_points(polygon, points.begin(), points.end());
    return polygon;
  }

  template <typename polygon_type>
  typename enable_if< typename is_any_mutable_polygon_with_holes_type<polygon_type>::type, polygon_type>::type &
  snap_to_45(polygon_type& polygon) {
    typedef typename polygon_with_holes_traits<polygon_type>::hole_type hole_type;
    hole_type h;
    set_points(h, begin_points(polygon), end_points(polygon));
    snap_to_45(h);
    std::vector<hole_type> holes;
    holes.reserve(size_holes(polygon));
    for(typename polygon_with_holes_traits<polygon_type>::iterator_holes_type itr = begin_holes(polygon);
        itr != end_holes(polygon); ++itr) {
      holes.push_back(*itr);
      snap_to_45(holes.back());
    }
    assign(polygon, h);
    set_holes(polygon, holes.begin(), holes.end());
    return polygon;
  }

  //scale specifically 45 down
  template <typename polygon_type>
  typename enable_if<
    typename gtl_and< typename is_any_mutable_polygon_without_holes_type<polygon_type>::type,
                      typename gtl_same_type
                      < forty_five_domain,
                        typename geometry_domain<typename geometry_concept<polygon_type>::type>::type>::type>::type,
    polygon_type>::type &
  scale_down(polygon_type& polygon, typename coordinate_traits<typename polygon_traits<polygon_type>::coordinate_type>::unsigned_area_type factor) {
    std::vector<typename std::iterator_traits<typename polygon_traits<polygon_type>::iterator_type>::value_type> points;
    points.reserve(::boost::polygon::size(polygon));
    for(typename polygon_traits<polygon_type>::iterator_type iter = begin_points(polygon);
        iter != end_points(polygon); ++iter) {
      points.push_back(*iter);
      scale_down(points.back(), factor);
    }
    snap_point_vector_to_45(points);
    polygon_mutable_traits<polygon_type>::set_points(polygon, points.begin(), points.end());
    return polygon;
  }

  template <typename T>
  typename enable_if< typename is_any_mutable_polygon_with_holes_type<T>::type, T>::type &
  scale_down(T& polygon, typename coordinate_traits<typename polygon_traits<T>::coordinate_type>::unsigned_area_type factor) {
    typedef typename polygon_with_holes_traits<T>::hole_type hole_type;
    hole_type h;
    set_points(h, begin_points(polygon), end_points(polygon));
    scale_down(h, factor);
    std::vector<hole_type> holes;
    holes.reserve(size_holes(polygon));
    for(typename polygon_with_holes_traits<T>::iterator_holes_type itr = begin_holes(polygon);
        itr != end_holes(polygon); ++itr) {
      holes.push_back(*itr);
      scale_down(holes.back(), factor);
    }
    assign(polygon, h);
    set_holes(polygon, holes.begin(), holes.end());
    return polygon;
  }

  //scale non-45
  template <typename polygon_type>
  typename enable_if<
    typename gtl_and< typename is_any_mutable_polygon_without_holes_type<polygon_type>::type,
                      typename gtl_not<typename gtl_same_type
                                       < forty_five_domain,
                                         typename geometry_domain<typename geometry_concept<polygon_type>::type>::type>::type>::type>::type,
    polygon_type>::type &
  scale(polygon_type& polygon, double factor) {
    std::vector<typename std::iterator_traits<typename polygon_traits<polygon_type>::iterator_type>::value_type> points;
    points.reserve(::boost::polygon::size(polygon));
    for(typename polygon_traits<polygon_type>::iterator_type iter = begin_points(polygon);
        iter != end_points(polygon); ++iter) {
      points.push_back(*iter);
      scale(points.back(), anisotropic_scale_factor<double>(factor, factor));
    }
    polygon_mutable_traits<polygon_type>::set_points(polygon, points.begin(), points.end());
    return polygon;
  }

  //scale specifically 45
  template <typename polygon_type>
  polygon_type&
  scale(polygon_type& polygon, double factor,
    typename enable_if<
    typename gtl_and< typename is_any_mutable_polygon_without_holes_type<polygon_type>::type,
                      typename gtl_same_type
                      < forty_five_domain,
        typename geometry_domain<typename geometry_concept<polygon_type>::type>::type>::type>::type>::type * = 0
  ) {
    std::vector<typename std::iterator_traits<typename polygon_traits<polygon_type>::iterator_type>::value_type> points;
    points.reserve(::boost::polygon::size(polygon));
    for(typename polygon_traits<polygon_type>::iterator_type iter = begin_points(polygon);
        iter != end_points(polygon); ++iter) {
      points.push_back(*iter);
      scale(points.back(), anisotropic_scale_factor<double>(factor, factor));
    }
    snap_point_vector_to_45(points);
    polygon_mutable_traits<polygon_type>::set_points(polygon, points.begin(), points.end());
    return polygon;
  }

  template <typename T>
  T&
  scale(T& polygon, double factor,
  typename enable_if< typename is_any_mutable_polygon_with_holes_type<T>::type>::type * = 0
  ) {
    typedef typename polygon_with_holes_traits<T>::hole_type hole_type;
    hole_type h;
    set_points(h, begin_points(polygon), end_points(polygon));
    scale(h, factor);
    std::vector<hole_type> holes;
    holes.reserve(size_holes(polygon));
    for(typename polygon_with_holes_traits<T>::iterator_holes_type itr = begin_holes(polygon);
        itr != end_holes(polygon); ++itr) {
      holes.push_back(*itr);
      scale(holes.back(), factor);
    }
    assign(polygon, h);
    set_holes(polygon, holes.begin(), holes.end());
    return polygon;
  }

  template <typename iterator_type, typename area_type>
  static area_type
  point_sequence_area(iterator_type begin_range, iterator_type end_range) {
    typedef typename std::iterator_traits<iterator_type>::value_type point_type;
    if(begin_range == end_range) return area_type(0);
    point_type first = *begin_range;
    point_type previous = first;
    ++begin_range;
    // Initialize trapezoid base line
    area_type y_base = (area_type)y(first);
    // Initialize area accumulator

    area_type area(0);
    while (begin_range != end_range) {
      area_type x1 = (area_type)x(previous);
      area_type x2 = (area_type)x(*begin_range);
#ifdef BOOST_POLYGON_ICC
#pragma warning (push)
#pragma warning (disable:1572)
#endif
      if(x1 != x2) {
#ifdef BOOST_POLYGON_ICC
#pragma warning (pop)
#endif
        // do trapezoid area accumulation
        area += (x2 - x1) * (((area_type)y(*begin_range) - y_base) +
                             ((area_type)y(previous) - y_base)) / 2;
      }
      previous = *begin_range;
      // go to next point
      ++begin_range;
    }
    //wrap around to evaluate the edge between first and last if not closed
    if(!equivalence(first, previous)) {
      area_type x1 = (area_type)x(previous);
      area_type x2 = (area_type)x(first);
      area += (x2 - x1) * (((area_type)y(first) - y_base) +
                           ((area_type)y(previous) - y_base)) / 2;
    }
    return area;
  }

  template <typename T>
  typename enable_if<
    typename is_polygon_with_holes_type<T>::type,
                        typename area_type_by_domain< typename geometry_domain<typename geometry_concept<T>::type>::type,
                                                      typename polygon_traits<T>::coordinate_type>::type>::type
  area(const T& polygon) {
    typedef typename area_type_by_domain< typename geometry_domain<typename geometry_concept<T>::type>::type,
      typename polygon_traits<T>::coordinate_type>::type area_type;
    area_type retval = point_sequence_area<typename polygon_traits<T>::iterator_type, area_type>
      (begin_points(polygon), end_points(polygon));
    if(retval < 0) retval *= -1;
    for(typename polygon_with_holes_traits<T>::iterator_holes_type itr =
          polygon_with_holes_traits<T>::begin_holes(polygon);
        itr != polygon_with_holes_traits<T>::end_holes(polygon); ++itr) {
      area_type tmp_area = point_sequence_area
        <typename polygon_traits<typename polygon_with_holes_traits<T>::hole_type>::iterator_type, area_type>
        (begin_points(*itr), end_points(*itr));
      if(tmp_area < 0) tmp_area *= -1;
      retval -= tmp_area;
    }
    return retval;
  }

  template <typename iT>
  bool point_sequence_is_45(iT itr, iT itr_end) {
    typedef typename std::iterator_traits<iT>::value_type Point;
    typedef typename point_traits<Point>::coordinate_type Unit;
    if(itr == itr_end) return true;
    Point firstPt = *itr;
    Point prevPt = firstPt;
    ++itr;
    while(itr != itr_end) {
      Point pt = *itr;
      Unit deltax = x(pt) - x(prevPt);
      Unit deltay = y(pt) - y(prevPt);
      if(deltax && deltay &&
         local_abs(deltax) != local_abs(deltay))
        return false;
      prevPt = pt;
      ++itr;
    }
    Unit deltax = x(firstPt) - x(prevPt);
    Unit deltay = y(firstPt) - y(prevPt);
    if(deltax && deltay &&
       local_abs(deltax) != local_abs(deltay))
      return false;
    return true;
  }

  template <typename polygon_type>
  typename enable_if< typename is_polygon_with_holes_type<polygon_type>::type, bool>::type
  is_45(const polygon_type& polygon) {
    typename polygon_traits<polygon_type>::iterator_type itr = begin_points(polygon), itr_end = end_points(polygon);
    if(!point_sequence_is_45(itr, itr_end)) return false;
    typename polygon_with_holes_traits<polygon_type>::iterator_holes_type itrh = begin_holes(polygon), itrh_end = end_holes(polygon);
    typedef typename polygon_with_holes_traits<polygon_type>::hole_type hole_type;
    for(; itrh != itrh_end; ++ itrh) {
      typename polygon_traits<hole_type>::iterator_type itr1 = begin_points(polygon), itr1_end = end_points(polygon);
      if(!point_sequence_is_45(itr1, itr1_end)) return false;
    }
    return true;
  }

  template <typename distance_type, typename iterator_type>
  distance_type point_sequence_distance(iterator_type itr, iterator_type itr_end) {
    typedef distance_type Unit;
    typedef iterator_type iterator;
    typedef typename std::iterator_traits<iterator>::value_type point_type;
    Unit return_value = Unit(0);
    point_type previous_point, first_point;
    if(itr == itr_end) return return_value;
    previous_point = first_point = *itr;
    ++itr;
    for( ; itr != itr_end; ++itr) {
      point_type current_point = *itr;
      return_value += (Unit)euclidean_distance(current_point, previous_point);
      previous_point = current_point;
    }
    return_value += (Unit)euclidean_distance(previous_point, first_point);
    return return_value;
  }

  template <typename T>
  typename distance_type_by_domain
  <typename geometry_domain<typename geometry_concept<T>::type>::type, typename polygon_traits<T>::coordinate_type>::type
  perimeter(const T& polygon,
  typename enable_if<
      typename is_polygon_with_holes_type<T>::type>::type * = 0
  ) {
    typedef typename distance_type_by_domain
      <typename geometry_domain<typename geometry_concept<T>::type>::type, typename polygon_traits<T>::coordinate_type>::type Unit;
    typedef typename polygon_traits<T>::iterator_type iterator;
    iterator itr = begin_points(polygon);
    iterator itr_end = end_points(polygon);
    Unit return_value = point_sequence_distance<Unit, iterator>(itr, itr_end);
    for(typename polygon_with_holes_traits<T>::iterator_holes_type itr_holes = begin_holes(polygon);
        itr_holes != end_holes(polygon); ++itr_holes) {
      typedef typename polygon_traits<typename polygon_with_holes_traits<T>::hole_type>::iterator_type hitertype;
      return_value += point_sequence_distance<Unit, hitertype>(begin_points(*itr_holes), end_points(*itr_holes));
    }
    return return_value;
  }

  template <typename T>
  typename enable_if <typename is_polygon_with_holes_type<T>::type,
                       direction_1d>::type
  winding(const T& polygon) {
    winding_direction wd = polygon_traits<T>::winding(polygon);
    if(wd != unknown_winding) {
      return wd == clockwise_winding ? CLOCKWISE: COUNTERCLOCKWISE;
    }
    typedef typename area_type_by_domain< typename geometry_domain<typename geometry_concept<T>::type>::type,
      typename polygon_traits<T>::coordinate_type>::type area_type;
    return point_sequence_area<typename polygon_traits<T>::iterator_type, area_type>(begin_points(polygon), end_points(polygon)) < 0 ?
      COUNTERCLOCKWISE : CLOCKWISE;
  }

  template <typename T, typename input_point_type>
  typename enable_if<
    typename gtl_and<
      typename is_polygon_90_type<T>::type,
      typename gtl_same_type<
        typename geometry_concept<input_point_type>::type,
        point_concept
      >::type
    >::type,
    bool
  >::type contains(
      const T& polygon,
      const input_point_type& point,
      bool consider_touch = true) {
    typedef T polygon_type;
    typedef typename polygon_traits<polygon_type>::coordinate_type coordinate_type;
    typedef typename polygon_traits<polygon_type>::iterator_type iterator;
    typedef typename std::iterator_traits<iterator>::value_type point_type;
    coordinate_type point_x = x(point);
    coordinate_type point_y = y(point);
    // Check how many intersections has the ray extended from the given
    // point in the x-axis negative direction with the polygon edges.
    // If the number is odd the point is within the polygon, otherwise not.
    // We can safely ignore horizontal edges, however intersections with
    // end points of the vertical edges require special handling. We should
    // add one intersection in case horizontal edges that extend vertical edge
    // point in the same direction.
    int num_full_intersections = 0;
    int num_half_intersections = 0;
    for (iterator iter = begin_points(polygon); iter != end_points(polygon);) {
      point_type curr_point = *iter;
      ++iter;
      point_type next_point = (iter == end_points(polygon)) ? *begin_points(polygon) : *iter;
      if (x(curr_point) == x(next_point)) {
        if (x(curr_point) > point_x) {
          continue;
        }
        coordinate_type min_y = (std::min)(y(curr_point), y(next_point));
        coordinate_type max_y = (std::max)(y(curr_point), y(next_point));
        if (point_y > min_y && point_y < max_y) {
          if (x(curr_point) == point_x) {
            return consider_touch;
          }
          ++num_full_intersections;
        }
        if (point_y == min_y || point_y == max_y) {
          num_half_intersections += (y(curr_point) < y(next_point) ? 1 : -1);
        }
      } else {
        coordinate_type min_x = (std::min)(x(curr_point), x(next_point));
        coordinate_type max_x = (std::max)(x(curr_point), x(next_point));
        if (point_x >= min_x && point_x <= max_x) {
          if (y(curr_point) == point_y) {
            return consider_touch;
          }
        }
      }
    }
    int total_intersections = num_full_intersections + (num_half_intersections >> 1);
    return total_intersections & 1;
  }

  //TODO: refactor to expose as user APIs
  template <typename Unit>
  struct edge_utils {
    typedef point_data<Unit> Point;
    typedef std::pair<Point, Point> half_edge;

    class less_point {
    public:
      typedef Point first_argument_type;
      typedef Point second_argument_type;
      typedef bool result_type;
      inline less_point() {}
      inline bool operator () (const Point& pt1, const Point& pt2) const {
        if(pt1.get(HORIZONTAL) < pt2.get(HORIZONTAL)) return true;
        if(pt1.get(HORIZONTAL) == pt2.get(HORIZONTAL)) {
          if(pt1.get(VERTICAL) < pt2.get(VERTICAL)) return true;
        }
        return false;
      }
    };

    static inline bool between(Point pt, Point pt1, Point pt2) {
      less_point lp;
      if(lp(pt1, pt2))
        return lp(pt, pt2) && lp(pt1, pt);
      return lp(pt, pt1) && lp(pt2, pt);
    }

    template <typename area_type>
    static inline bool equal_slope(area_type dx1, area_type dy1, area_type dx2, area_type dy2) {
      typedef typename coordinate_traits<Unit>::unsigned_area_type unsigned_product_type;
      unsigned_product_type cross_1 = (unsigned_product_type)(dx2 < 0 ? -dx2 :dx2) * (unsigned_product_type)(dy1 < 0 ? -dy1 : dy1);
      unsigned_product_type cross_2 = (unsigned_product_type)(dx1 < 0 ? -dx1 :dx1) * (unsigned_product_type)(dy2 < 0 ? -dy2 : dy2);
      int dx1_sign = dx1 < 0 ? -1 : 1;
      int dx2_sign = dx2 < 0 ? -1 : 1;
      int dy1_sign = dy1 < 0 ? -1 : 1;
      int dy2_sign = dy2 < 0 ? -1 : 1;
      int cross_1_sign = dx2_sign * dy1_sign;
      int cross_2_sign = dx1_sign * dy2_sign;
      return cross_1 == cross_2 && (cross_1_sign == cross_2_sign || cross_1 == 0);
    }

    static inline bool equal_slope(const Unit& x, const Unit& y,
                                   const Point& pt1, const Point& pt2) {
      const Point* pts[2] = {&pt1, &pt2};
      typedef typename coordinate_traits<Unit>::manhattan_area_type at;
      at dy2 = (at)pts[1]->get(VERTICAL) - (at)y;
      at dy1 = (at)pts[0]->get(VERTICAL) - (at)y;
      at dx2 = (at)pts[1]->get(HORIZONTAL) - (at)x;
      at dx1 = (at)pts[0]->get(HORIZONTAL) - (at)x;
      return equal_slope(dx1, dy1, dx2, dy2);
    }

    template <typename area_type>
    static inline bool less_slope(area_type dx1, area_type dy1, area_type dx2, area_type dy2) {
      //reflext x and y slopes to right hand side half plane
      if(dx1 < 0) {
        dy1 *= -1;
        dx1 *= -1;
      } else if(dx1 == 0) {
        //if the first slope is vertical the first cannot be less
        return false;
      }
      if(dx2 < 0) {
        dy2 *= -1;
        dx2 *= -1;
      } else if(dx2 == 0) {
        //if the second slope is vertical the first is always less unless it is also vertical, in which case they are equal
        return dx1 != 0;
      }
      typedef typename coordinate_traits<Unit>::unsigned_area_type unsigned_product_type;
      unsigned_product_type cross_1 = (unsigned_product_type)(dx2 < 0 ? -dx2 :dx2) * (unsigned_product_type)(dy1 < 0 ? -dy1 : dy1);
      unsigned_product_type cross_2 = (unsigned_product_type)(dx1 < 0 ? -dx1 :dx1) * (unsigned_product_type)(dy2 < 0 ? -dy2 : dy2);
      int dx1_sign = dx1 < 0 ? -1 : 1;
      int dx2_sign = dx2 < 0 ? -1 : 1;
      int dy1_sign = dy1 < 0 ? -1 : 1;
      int dy2_sign = dy2 < 0 ? -1 : 1;
      int cross_1_sign = dx2_sign * dy1_sign;
      int cross_2_sign = dx1_sign * dy2_sign;
      if(cross_1_sign < cross_2_sign) return true;
      if(cross_2_sign < cross_1_sign) return false;
      if(cross_1_sign == -1) return cross_2 < cross_1;
      return cross_1 < cross_2;
    }

    static inline bool less_slope(const Unit& x, const Unit& y,
                                  const Point& pt1, const Point& pt2) {
      const Point* pts[2] = {&pt1, &pt2};
      //compute y value on edge from pt_ to pts[1] at the x value of pts[0]
      typedef typename coordinate_traits<Unit>::manhattan_area_type at;
      at dy2 = (at)pts[1]->get(VERTICAL) - (at)y;
      at dy1 = (at)pts[0]->get(VERTICAL) - (at)y;
      at dx2 = (at)pts[1]->get(HORIZONTAL) - (at)x;
      at dx1 = (at)pts[0]->get(HORIZONTAL) - (at)x;
      return less_slope(dx1, dy1, dx2, dy2);
    }

    //return -1 below, 0 on and 1 above line
    //assumes point is on x interval of segment
    static inline int on_above_or_below(Point pt, const half_edge& he) {
      if(pt == he.first || pt == he.second) return 0;
      if(equal_slope(pt.get(HORIZONTAL), pt.get(VERTICAL), he.first, he.second)) return 0;
      bool less_result = less_slope(pt.get(HORIZONTAL), pt.get(VERTICAL), he.first, he.second);
      int retval = less_result ? -1 : 1;
      less_point lp;
      if(lp(he.second, he.first)) retval *= -1;
      if(!between(pt, he.first, he.second)) retval *= -1;
      return retval;
    }
  };

  template <typename T, typename input_point_type>
  typename enable_if<
    typename gtl_and< typename is_any_mutable_polygon_with_holes_type<T>::type,
                      typename gtl_same_type<typename geometry_concept<input_point_type>::type, point_concept>::type>::type,
    bool>::type
  contains(const T& polygon, const input_point_type& point, bool consider_touch = true) {
    typedef typename polygon_with_holes_traits<T>::iterator_holes_type holes_iterator;
    bool isInside = contains( view_as< typename polygon_from_polygon_with_holes_type<
                              typename geometry_concept<T>::type>::type>( polygon ), point, consider_touch );
    if(!isInside) return false; //no need to check holes
    holes_iterator itH = begin_holes( polygon );
    while( itH != end_holes( polygon ) ) {
      if(  contains( *itH, point, !consider_touch )  ) {
        isInside = false;
        break;
      }
      ++itH;
    }
    return isInside;
  }

  template <typename T, typename input_point_type>
  typename enable_if<
    typename gtl_and_3<
      typename is_polygon_type<T>::type,
      typename gtl_different_type<typename geometry_domain<typename geometry_concept<T>::type>::type, manhattan_domain>::type,
      typename gtl_same_type<typename geometry_concept<input_point_type>::type, point_concept>::type>::type,
    bool>::type
  contains(const T& polygon, const input_point_type& point, bool consider_touch = true) {
    typedef typename point_traits<input_point_type>::coordinate_type Unit;
    typedef point_data<Unit> Point;
    typedef std::pair<Point, Point> half_edge;
    typedef typename polygon_traits<T>::iterator_type iterator;
    iterator itr = begin_points(polygon);
    iterator itrEnd = end_points(polygon);
    half_edge he;
    if(itr == itrEnd) return false;
    assign(he.first, *itr);
    Point firstPt;
    assign(firstPt, *itr);
    ++itr;
    if(itr == itrEnd) return false;
    bool done = false;
    int above = 0;
    while(!done) {
      Point currentPt;
      if(itr == itrEnd) {
        done = true;
        currentPt = firstPt;
      } else {
        assign(currentPt, *itr);
        ++itr;
      }
      if(currentPt == he.first) {
        continue;
      } else {
        he.second = currentPt;
        if(equivalence(point, currentPt)) return consider_touch;
        Unit xmin = (std::min)(x(he.first), x(he.second));
        Unit xmax = (std::max)(x(he.first), x(he.second));
        if(x(point) >= xmin && x(point) < xmax) { //double counts if <= xmax
          Point tmppt;
          assign(tmppt, point);
          int oabedge = edge_utils<Unit>::on_above_or_below(tmppt, he);
          if(oabedge == 0) return consider_touch;
          if(oabedge == 1) ++above;
        } else if(x(point) == xmax) {
          if(x(point) == xmin) {
            Unit ymin = (std::min)(y(he.first), y(he.second));
            Unit ymax = (std::max)(y(he.first), y(he.second));
            Unit ypt = y(point);
            if(ypt <= ymax && ypt >= ymin)
              return consider_touch;
          } else {
            Point tmppt;
            assign(tmppt, point);
            if( edge_utils<Unit>::on_above_or_below(tmppt, he) == 0 ) {
              return consider_touch;
            }
          }
        }
      }
      he.first = he.second;
    }
    return above % 2 != 0; //if the point is above an odd number of edges is must be inside polygon
  }

  /*
  template <typename T, typename input_point_type>
  typename enable_if<
    typename gtl_and_3<
      typename is_polygon_with_holes_type<T>::type,
      typename gtl_different_type<typename geometry_domain<typename geometry_concept<T>::type>::type, manhattan_domain>::type,
      typename gtl_same_type<typename geometry_concept<input_point_type>::type, point_concept>::type>::type,
    bool>::type
  contains(const T& polygon, const input_point_type& point, bool consider_touch = true) {
    typedef typename point_traits<input_point_type>::coordinate_type Unit;
    typedef point_data<Unit> Point;
    typedef std::pair<Point, Point> half_edge;
    typedef typename polygon_traits<T>::iterator_type iterator;
    iterator itr = begin_points(polygon);
    iterator itrEnd = end_points(polygon);
    half_edge he;
    if(itr == itrEnd) return false;
    assign(he.first, *itr);
    Point firstPt;
    assign(firstPt, *itr);
    ++itr;
    if(itr == itrEnd) return false;
    bool done = false;
    int above = 0;
    while(!done) {
      Point currentPt;
      if(itr == itrEnd) {
        done = true;
        currentPt = firstPt;
      } else {
        assign(currentPt, *itr);
        ++itr;
      }
      if(currentPt == he.first) {
        continue;
      } else {
        he.second = currentPt;
        if(equivalence(point, currentPt)) return consider_touch;
        Unit xmin = (std::min)(x(he.first), x(he.second));
        Unit xmax = (std::max)(x(he.first), x(he.second));
        if(x(point) >= xmin && x(point) < xmax) { //double counts if <= xmax
          Point tmppt;
          assign(tmppt, point);
          int oabedge = edge_utils<Unit>::on_above_or_below(tmppt, he);
          if(oabedge == 0) return consider_touch;
          if(oabedge == 1) ++above;
        }
      }
      he.first = he.second;
    }
    return above % 2 != 0; //if the point is above an odd number of edges is must be inside polygon
  }
  */

  template <typename T1, typename T2>
  typename enable_if<
    typename gtl_and< typename is_mutable_rectangle_concept<typename geometry_concept<T1>::type>::type,
                      typename is_polygon_with_holes_type<T2>::type>::type,
    bool>::type
  extents(T1& bounding_box, const T2& polygon) {
    typedef typename polygon_traits<T2>::iterator_type iterator;
    bool first_iteration = true;
    iterator itr_end = end_points(polygon);
    for(iterator itr = begin_points(polygon); itr != itr_end; ++itr) {
      if(first_iteration) {
        set_points(bounding_box, *itr, *itr);
        first_iteration = false;
      } else {
        encompass(bounding_box, *itr);
      }
    }
    if(first_iteration) return false;
    return true;
  }

  template <typename T1, typename T2>
  typename enable_if<
    typename gtl_and< typename is_mutable_point_concept<typename geometry_concept<T1>::type>::type,
                      typename is_polygon_with_holes_type<T2>::type>::type,
    bool>::type
  center(T1& center_point, const T2& polygon) {
    typedef typename polygon_traits<T2>::coordinate_type coordinate_type;
    rectangle_data<coordinate_type> bbox;
    extents(bbox, polygon);
    return center(center_point, bbox);
  }

  template <class T>
  template <class T2>
  polygon_90_data<T>& polygon_90_data<T>::operator=(const T2& rvalue) {
    assign(*this, rvalue);
    return *this;
  }

  template <class T>
  template <class T2>
  polygon_45_data<T>& polygon_45_data<T>::operator=(const T2& rvalue) {
    assign(*this, rvalue);
    return *this;
  }

  template <class T>
  template <class T2>
  polygon_data<T>& polygon_data<T>::operator=(const T2& rvalue) {
    assign(*this, rvalue);
    return *this;
  }

  template <class T>
  template <class T2>
  polygon_90_with_holes_data<T>& polygon_90_with_holes_data<T>::operator=(const T2& rvalue) {
    assign(*this, rvalue);
    return *this;
  }

  template <class T>
  template <class T2>
  polygon_45_with_holes_data<T>& polygon_45_with_holes_data<T>::operator=(const T2& rvalue) {
    assign(*this, rvalue);
    return *this;
  }

  template <class T>
  template <class T2>
  polygon_with_holes_data<T>& polygon_with_holes_data<T>::operator=(const T2& rvalue) {
    assign(*this, rvalue);
    return *this;
  }

  template <typename T>
  struct geometry_concept<polygon_data<T> > {
    typedef polygon_concept type;
  };
  template <typename T>
  struct geometry_concept<polygon_45_data<T> > {
    typedef polygon_45_concept type;
  };
  template <typename T>
  struct geometry_concept<polygon_90_data<T> > {
    typedef polygon_90_concept type;
  };
  template <typename T>
  struct geometry_concept<polygon_with_holes_data<T> > {
    typedef polygon_with_holes_concept type;
  };
  template <typename T>
  struct geometry_concept<polygon_45_with_holes_data<T> > {
    typedef polygon_45_with_holes_concept type;
  };
  template <typename T>
  struct geometry_concept<polygon_90_with_holes_data<T> > {
    typedef polygon_90_with_holes_concept type;
  };

//   template <typename T> struct polygon_with_holes_traits<polygon_90_data<T> > {
//     typedef polygon_90_data<T> hole_type;
//     typedef const hole_type* iterator_holes_type;
//     static inline iterator_holes_type begin_holes(const hole_type& t) { return &t; }
//     static inline iterator_holes_type end_holes(const hole_type& t) { return &t; }
//     static inline std::size_t size_holes(const hole_type& t) { return 0; }
//   };
//   template <typename T> struct polygon_with_holes_traits<polygon_45_data<T> > {
//     typedef polygon_45_data<T> hole_type;
//     typedef const hole_type* iterator_holes_type;
//     static inline iterator_holes_type begin_holes(const hole_type& t) { return &t; }
//     static inline iterator_holes_type end_holes(const hole_type& t) { return &t; }
//     static inline std::size_t size_holes(const hole_type& t) { return 0; }
//   };
//   template <typename T> struct polygon_with_holes_traits<polygon_data<T> > {
//     typedef polygon_data<T> hole_type;
//     typedef const hole_type* iterator_holes_type;
//     static inline iterator_holes_type begin_holes(const hole_type& t) { return &t; }
//     static inline iterator_holes_type end_holes(const hole_type& t) { return &t; }
//     static inline std::size_t size_holes(const hole_type& t) { return 0; }
//   };
  template <typename T> struct get_void {};
  template <> struct get_void<gtl_yes> { typedef void type; };

  template <typename T> struct polygon_with_holes_traits<
    T, typename get_void<typename is_any_mutable_polygon_without_holes_type<T>::type>::type > {
    typedef T hole_type;
    typedef const hole_type* iterator_holes_type;
    static inline iterator_holes_type begin_holes(const hole_type& t) { return &t; }
    static inline iterator_holes_type end_holes(const hole_type& t) { return &t; }
  };

  template <typename T>
  struct view_of<rectangle_concept, T> {
    typedef typename polygon_traits<T>::coordinate_type coordinate_type;
    typedef interval_data<coordinate_type> interval_type;
    rectangle_data<coordinate_type> rect;
    view_of(const T& obj) : rect() {
      point_data<coordinate_type> pts[2];
      typename polygon_traits<T>::iterator_type itr =
        begin_points(obj), itre = end_points(obj);
      if(itr == itre) return;
      assign(pts[0], *itr);
      ++itr;
      if(itr == itre) return;
      ++itr;
      if(itr == itre) return;
      assign(pts[1], *itr);
      set_points(rect, pts[0], pts[1]);
    }
    inline interval_type get(orientation_2d orient) const {
      return rect.get(orient); }
  };

  template <typename T>
  struct geometry_concept<view_of<rectangle_concept, T> > {
    typedef rectangle_concept type;
  };

  template <typename T>
  struct view_of<polygon_45_concept, T> {
    const T* t;
    view_of(const T& obj) : t(&obj) {}
    typedef typename polygon_traits<T>::coordinate_type coordinate_type;
    typedef typename polygon_traits<T>::iterator_type iterator_type;
    typedef typename polygon_traits<T>::point_type point_type;

    /// Get the begin iterator
    inline iterator_type begin() const {
      return polygon_traits<T>::begin_points(*t);
    }

    /// Get the end iterator
    inline iterator_type end() const {
      return polygon_traits<T>::end_points(*t);
    }

    /// Get the number of sides of the polygon
    inline std::size_t size() const {
      return polygon_traits<T>::size(*t);
    }

    /// Get the winding direction of the polygon
    inline winding_direction winding() const {
      return polygon_traits<T>::winding(*t);
    }
  };

  template <typename T>
  struct geometry_concept<view_of<polygon_45_concept, T> > {
    typedef polygon_45_concept type;
  };

  template <typename T>
  struct view_of<polygon_90_concept, T> {
    const T* t;
    view_of(const T& obj) : t(&obj) {}
    typedef typename polygon_traits<T>::coordinate_type coordinate_type;
    typedef typename polygon_traits<T>::iterator_type iterator_type;
    typedef typename polygon_traits<T>::point_type point_type;
    typedef iterator_points_to_compact<iterator_type, point_type> compact_iterator_type;

    /// Get the begin iterator
    inline compact_iterator_type begin_compact() const {
      return compact_iterator_type(polygon_traits<T>::begin_points(*t),
                                   polygon_traits<T>::end_points(*t));
    }

    /// Get the end iterator
    inline compact_iterator_type end_compact() const {
      return compact_iterator_type(polygon_traits<T>::end_points(*t),
                                   polygon_traits<T>::end_points(*t));
    }

    /// Get the number of sides of the polygon
    inline std::size_t size() const {
      return polygon_traits<T>::size(*t);
    }

    /// Get the winding direction of the polygon
    inline winding_direction winding() const {
      return polygon_traits<T>::winding(*t);
    }
  };

  template <typename T>
  struct geometry_concept<view_of<polygon_90_concept, T> > {
    typedef polygon_90_concept type;
  };

  template <typename T>
  struct view_of<polygon_45_with_holes_concept, T> {
    const T* t;
    view_of(const T& obj) : t(&obj) {}
    typedef typename polygon_traits<T>::coordinate_type coordinate_type;
    typedef typename polygon_traits<T>::iterator_type iterator_type;
    typedef typename polygon_traits<T>::point_type point_type;
    typedef view_of<polygon_45_concept, typename polygon_with_holes_traits<T>::hole_type> hole_type;
    struct iterator_holes_type {
      typedef std::forward_iterator_tag iterator_category;
      typedef hole_type value_type;
      typedef std::ptrdiff_t difference_type;
      typedef const hole_type* pointer; //immutable
      typedef const hole_type& reference; //immutable
      typedef typename polygon_with_holes_traits<T>::iterator_holes_type iht;
      iht internal_itr;
      iterator_holes_type() : internal_itr() {}
      iterator_holes_type(iht iht_in) : internal_itr(iht_in) {}
      inline iterator_holes_type& operator++() {
        ++internal_itr;
        return *this;
      }
      inline const iterator_holes_type operator++(int) {
        iterator_holes_type tmp(*this);
        ++(*this);
        return tmp;
      }
      inline bool operator==(const iterator_holes_type& that) const {
        return (internal_itr == that.internal_itr);
      }
      inline bool operator!=(const iterator_holes_type& that) const {
        return (internal_itr != that.internal_itr);
      }
      inline value_type operator*() const {
        return view_as<polygon_45_concept>(*internal_itr);
      }
    };

    /// Get the begin iterator
    inline iterator_type begin() const {
      return polygon_traits<T>::begin_points(*t);
    }

    /// Get the end iterator
    inline iterator_type end() const {
      return polygon_traits<T>::end_points(*t);
    }

    /// Get the number of sides of the polygon
    inline std::size_t size() const {
      return polygon_traits<T>::size(*t);
    }

    /// Get the winding direction of the polygon
    inline winding_direction winding() const {
      return polygon_traits<T>::winding(*t);
    }

    /// Get the begin iterator
    inline iterator_holes_type begin_holes() const {
      return polygon_with_holes_traits<T>::begin_holes(*t);
    }

    /// Get the end iterator
    inline iterator_holes_type end_holes() const {
      return polygon_with_holes_traits<T>::end_holes(*t);
    }

    /// Get the number of sides of the polygon
    inline std::size_t size_holes() const {
      return polygon_with_holes_traits<T>::size_holes(*t);
    }

  };

  template <typename T>
  struct geometry_concept<view_of<polygon_45_with_holes_concept, T> > {
    typedef polygon_45_with_holes_concept type;
  };

  template <typename T>
  struct view_of<polygon_90_with_holes_concept, T> {
    const T* t;
    view_of(const T& obj) : t(&obj) {}
    typedef typename polygon_traits<T>::coordinate_type coordinate_type;
    typedef typename polygon_traits<T>::iterator_type iterator_type;
    typedef typename polygon_traits<T>::point_type point_type;
    typedef iterator_points_to_compact<iterator_type, point_type> compact_iterator_type;
    typedef view_of<polygon_90_concept, typename polygon_with_holes_traits<T>::hole_type> hole_type;
    struct iterator_holes_type {
      typedef std::forward_iterator_tag iterator_category;
      typedef hole_type value_type;
      typedef std::ptrdiff_t difference_type;
      typedef const hole_type* pointer; //immutable
      typedef const hole_type& reference; //immutable
      typedef typename polygon_with_holes_traits<T>::iterator_holes_type iht;
      iht internal_itr;
      iterator_holes_type() : internal_itr() {}
      iterator_holes_type(iht iht_in) : internal_itr(iht_in) {}
      inline iterator_holes_type& operator++() {
        ++internal_itr;
        return *this;
      }
      inline const iterator_holes_type operator++(int) {
        iterator_holes_type tmp(*this);
        ++(*this);
        return tmp;
      }
      inline bool operator==(const iterator_holes_type& that) const {
        return (internal_itr == that.internal_itr);
      }
      inline bool operator!=(const iterator_holes_type& that) const {
        return (internal_itr != that.internal_itr);
      }
      inline value_type operator*() const {
        return view_as<polygon_90_concept>(*internal_itr);
      }
    };

    /// Get the begin iterator
    inline compact_iterator_type begin_compact() const {
      return compact_iterator_type(polygon_traits<T>::begin_points(*t),
                                   polygon_traits<T>::end_points(*t));
    }

    /// Get the end iterator
    inline compact_iterator_type end_compact() const {
      return compact_iterator_type(polygon_traits<T>::end_points(*t),
                                   polygon_traits<T>::end_points(*t));
    }

    /// Get the number of sides of the polygon
    inline std::size_t size() const {
      return polygon_traits<T>::size(*t);
    }

    /// Get the winding direction of the polygon
    inline winding_direction winding() const {
      return polygon_traits<T>::winding(*t);
    }

    /// Get the begin iterator
    inline iterator_holes_type begin_holes() const {
      return polygon_with_holes_traits<T>::begin_holes(*t);
    }

    /// Get the end iterator
    inline iterator_holes_type end_holes() const {
      return polygon_with_holes_traits<T>::end_holes(*t);
    }

    /// Get the number of sides of the polygon
    inline std::size_t size_holes() const {
      return polygon_with_holes_traits<T>::size_holes(*t);
    }

  };

  template <typename T>
  struct geometry_concept<view_of<polygon_90_with_holes_concept, T> > {
    typedef polygon_90_with_holes_concept type;
  };

  template <typename T>
  struct view_of<polygon_concept, T> {
    const T* t;
    view_of(const T& obj) : t(&obj) {}
    typedef typename polygon_traits<T>::coordinate_type coordinate_type;
    typedef typename polygon_traits<T>::iterator_type iterator_type;
    typedef typename polygon_traits<T>::point_type point_type;

    /// Get the begin iterator
    inline iterator_type begin() const {
      return polygon_traits<T>::begin_points(*t);
    }

    /// Get the end iterator
    inline iterator_type end() const {
      return polygon_traits<T>::end_points(*t);
    }

    /// Get the number of sides of the polygon
    inline std::size_t size() const {
      return polygon_traits<T>::size(*t);
    }

    /// Get the winding direction of the polygon
    inline winding_direction winding() const {
      return polygon_traits<T>::winding(*t);
    }
  };

  template <typename T>
  struct geometry_concept<view_of<polygon_concept, T> > {
    typedef polygon_concept type;
  };
}
}

#endif

/* polygon_traits.hpp
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
*/