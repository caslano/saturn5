/*
  Copyright 2008 Intel Corporation

  Use, modification and distribution are subject to the Boost Software License,
  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt).
*/

#ifndef BOOST_POLYGON_ISOTROPY_HPP
#define BOOST_POLYGON_ISOTROPY_HPP

//external
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <vector>
#include <deque>
#include <map>
#include <set>
#include <list>
//#include <iostream>
#include <algorithm>
#include <limits>
#include <iterator>
#include <string>

#ifndef BOOST_POLYGON_NO_DEPS

#include <boost/config.hpp>
#ifdef BOOST_MSVC
#define BOOST_POLYGON_MSVC
#endif
#ifdef BOOST_INTEL
#define BOOST_POLYGON_ICC
#endif
#ifdef BOOST_HAS_LONG_LONG
#define BOOST_POLYGON_USE_LONG_LONG
typedef boost::long_long_type polygon_long_long_type;
typedef boost::ulong_long_type polygon_ulong_long_type;
//typedef long long polygon_long_long_type;
//typedef unsigned long long polygon_ulong_long_type;
#endif
#else

#ifdef _WIN32
#define BOOST_POLYGON_MSVC
#endif
#ifdef __ICC
#define BOOST_POLYGON_ICC
#endif
#define BOOST_POLYGON_USE_LONG_LONG
typedef long long polygon_long_long_type;
typedef unsigned long long polygon_ulong_long_type;
#endif

namespace boost { namespace polygon{

  enum GEOMETRY_CONCEPT_ID {
    COORDINATE_CONCEPT,
    INTERVAL_CONCEPT,
    POINT_CONCEPT,
    POINT_3D_CONCEPT,
    RECTANGLE_CONCEPT,
    POLYGON_90_CONCEPT,
    POLYGON_90_WITH_HOLES_CONCEPT,
    POLYGON_45_CONCEPT,
    POLYGON_45_WITH_HOLES_CONCEPT,
    POLYGON_CONCEPT,
    POLYGON_WITH_HOLES_CONCEPT,
    POLYGON_90_SET_CONCEPT,
    POLYGON_45_SET_CONCEPT,
    POLYGON_SET_CONCEPT
  };

  struct undefined_concept {};

  template <typename T>
  struct geometry_concept { typedef undefined_concept type; };

  template <typename GCT, typename T>
  struct view_of {};

  template <typename T1, typename T2>
  view_of<T1, T2> view_as(const T2& obj) { return view_of<T1, T2>(obj); }

  template <typename T, bool /*enable*/ = true>
  struct coordinate_traits {};

  //used to override long double with an infinite precision datatype
  template <typename T>
  struct high_precision_type {
    typedef long double type;
  };

  template <typename T>
  T convert_high_precision_type(const typename high_precision_type<T>::type& v) {
    return T(v);
  }

  //used to override std::sort with an alternative (parallel) algorithm
  template <typename iter_type>
  void polygon_sort(iter_type _b_, iter_type _e_);

  template <typename iter_type, typename pred_type>
  void polygon_sort(iter_type _b_, iter_type _e_, const pred_type& _pred_);


  template <>
  struct coordinate_traits<int> {
    typedef int coordinate_type;
    typedef long double area_type;
#ifdef BOOST_POLYGON_USE_LONG_LONG
    typedef polygon_long_long_type manhattan_area_type;
    typedef polygon_ulong_long_type unsigned_area_type;
    typedef polygon_long_long_type coordinate_difference;
#else
    typedef long manhattan_area_type;
    typedef unsigned long unsigned_area_type;
    typedef long coordinate_difference;
#endif
    typedef long double coordinate_distance;
  };

  template<>
  struct coordinate_traits<long, sizeof(long) == sizeof(int)> {
    typedef coordinate_traits<int> cT_;
    typedef cT_::coordinate_type coordinate_type;
    typedef cT_::area_type area_type;
    typedef cT_::manhattan_area_type manhattan_area_type;
    typedef cT_::unsigned_area_type unsigned_area_type;
    typedef cT_::coordinate_difference coordinate_difference;
    typedef cT_::coordinate_distance coordinate_distance;
  };

#ifdef BOOST_POLYGON_USE_LONG_LONG
  template <>
  struct coordinate_traits<polygon_long_long_type> {
    typedef polygon_long_long_type coordinate_type;
    typedef long double area_type;
    typedef polygon_long_long_type manhattan_area_type;
    typedef polygon_ulong_long_type unsigned_area_type;
    typedef polygon_long_long_type coordinate_difference;
    typedef long double coordinate_distance;
  };

  template<>
  struct coordinate_traits<long, sizeof(long) == sizeof(polygon_long_long_type)> {
    typedef coordinate_traits<polygon_long_long_type> cT_;
    typedef cT_::coordinate_type coordinate_type;
    typedef cT_::area_type area_type;
    typedef cT_::manhattan_area_type manhattan_area_type;
    typedef cT_::unsigned_area_type unsigned_area_type;
    typedef cT_::coordinate_difference coordinate_difference;
    typedef cT_::coordinate_distance coordinate_distance;
  };
#endif

  template <>
  struct coordinate_traits<float> {
    typedef float coordinate_type;
    typedef float area_type;
    typedef float manhattan_area_type;
    typedef float unsigned_area_type;
    typedef float coordinate_difference;
    typedef float coordinate_distance;
  };

  template <>
  struct coordinate_traits<double> {
    typedef double coordinate_type;
    typedef double area_type;
    typedef double manhattan_area_type;
    typedef double unsigned_area_type;
    typedef double coordinate_difference;
    typedef double coordinate_distance;
  };

  template <>
  struct coordinate_traits<long double> {
    typedef long double coordinate_type;
    typedef long double area_type;
    typedef long double manhattan_area_type;
    typedef long double unsigned_area_type;
    typedef long double coordinate_difference;
    typedef long double coordinate_distance;
  };

  template <typename T>
  struct scaling_policy {
    template <typename T2>
    static inline T round(T2 t2) {
      return (T)std::floor(t2+0.5);
    }

    static inline T round(T t2) {
      return t2;
    }
  };

  struct coordinate_concept {};

  template <>
  struct geometry_concept<int> { typedef coordinate_concept type; };
#ifdef BOOST_POLYGON_USE_LONG_LONG
  template <>
  struct geometry_concept<polygon_long_long_type> { typedef coordinate_concept type; };
#endif
  template <>
  struct geometry_concept<float> { typedef coordinate_concept type; };
  template <>
  struct geometry_concept<double> { typedef coordinate_concept type; };
  template <>
  struct geometry_concept<long double> { typedef coordinate_concept type; };

  struct gtl_no { static const bool value = false; };
  struct gtl_yes { typedef gtl_yes type;
    static const bool value = true; };

  template <bool T, bool T2>
  struct gtl_and_c { typedef gtl_no type; };
  template <>
  struct gtl_and_c<true, true> { typedef gtl_yes type; };

  template <typename T, typename T2>
  struct gtl_and : gtl_and_c<T::value, T2::value> {};
  template <typename T, typename T2, typename T3>
  struct gtl_and_3 { typedef typename gtl_and<
                       T, typename gtl_and<T2, T3>::type>::type type; };

  template <typename T, typename T2, typename T3, typename T4>
  struct gtl_and_4 { typedef typename gtl_and_3<
                       T, T2, typename gtl_and<T3, T4>::type>::type type; };
  template <typename T, typename T2>
  struct gtl_or { typedef gtl_yes type; };
  template <typename T>
  struct gtl_or<T, T> { typedef T type; };

  template <typename T, typename T2, typename T3>
  struct gtl_or_3 { typedef typename gtl_or<
                      T, typename gtl_or<T2, T3>::type>::type type; };

  template <typename T, typename T2, typename T3, typename T4>
  struct gtl_or_4 { typedef typename gtl_or<
                      T, typename gtl_or_3<T2, T3, T4>::type>::type type; };

  template <typename T>
  struct gtl_not { typedef gtl_no type; };
  template <>
  struct gtl_not<gtl_no> { typedef gtl_yes type; };

  template <typename T>
  struct gtl_if {
#ifdef BOOST_POLYGON_MSVC
    typedef gtl_no type;
#endif
  };
  template <>
  struct gtl_if<gtl_yes> { typedef gtl_yes type; };

  template <typename T, typename T2>
  struct gtl_same_type { typedef gtl_no type; };
  template <typename T>
  struct gtl_same_type<T, T> { typedef gtl_yes type; };
  template <typename T, typename T2>
  struct gtl_different_type { typedef typename gtl_not<typename gtl_same_type<T, T2>::type>::type type; };

  struct manhattan_domain {};
  struct forty_five_domain {};
  struct general_domain {};

  template <typename T>
  struct geometry_domain { typedef general_domain type; };

  template <typename domain_type, typename coordinate_type>
  struct area_type_by_domain { typedef typename coordinate_traits<coordinate_type>::area_type type; };
  template <typename coordinate_type>
  struct area_type_by_domain<manhattan_domain, coordinate_type> {
    typedef typename coordinate_traits<coordinate_type>::manhattan_area_type type; };

  template<bool E, class R = void>
  struct enable_if_ {
      typedef R type;
  };

  template<class R>
  struct enable_if_<false, R> { };

  template<class E, class R = void>
  struct enable_if
      : enable_if_<E::value, R> { };

  struct y_c_edist : gtl_yes {};

  template <typename coordinate_type_1, typename coordinate_type_2>
    typename enable_if<
    typename gtl_and_3<y_c_edist, typename gtl_same_type<typename geometry_concept<coordinate_type_1>::type, coordinate_concept>::type,
                       typename gtl_same_type<typename geometry_concept<coordinate_type_1>::type, coordinate_concept>::type>::type,
    typename coordinate_traits<coordinate_type_1>::coordinate_difference>::type
  euclidean_distance(const coordinate_type_1& lvalue, const coordinate_type_2& rvalue) {
    typedef typename coordinate_traits<coordinate_type_1>::coordinate_difference Unit;
    return (lvalue < rvalue) ? (Unit)rvalue - (Unit)lvalue : (Unit)lvalue - (Unit)rvalue;
  }



  // predicated_swap swaps a and b if pred is true

  // predicated_swap is guarenteed to behave the same as
  // if(pred){
  //   T tmp = a;
  //   a = b;
  //   b = tmp;
  // }
  // but will not generate a branch instruction.
  // predicated_swap always creates a temp copy of a, but does not
  // create more than one temp copy of an input.
  // predicated_swap can be used to optimize away branch instructions in C++
  template <class T>
  inline bool predicated_swap(const bool& pred,
                              T& a,
                              T& b) {
    const T tmp = a;
    const T* input[2] = {&b, &tmp};
    a = *input[!pred];
    b = *input[pred];
    return pred;
  }

  enum direction_1d_enum { LOW = 0, HIGH = 1,
                           LEFT = 0, RIGHT = 1,
                           CLOCKWISE = 0, COUNTERCLOCKWISE = 1,
                           REVERSE = 0, FORWARD = 1,
                           NEGATIVE = 0, POSITIVE = 1 };
  enum orientation_2d_enum { HORIZONTAL = 0, VERTICAL = 1 };
  enum direction_2d_enum { WEST = 0, EAST = 1, SOUTH = 2, NORTH = 3 };
  enum orientation_3d_enum { PROXIMAL = 2 };
  enum direction_3d_enum { DOWN = 4, UP = 5 };
  enum winding_direction {
    clockwise_winding = 0,
    counterclockwise_winding = 1,
    unknown_winding = 2
  };

  class direction_2d;
  class direction_3d;
  class orientation_2d;

  class direction_1d {
  private:
    unsigned int val_;
    explicit direction_1d(int d);
  public:
    inline direction_1d() : val_(LOW) {}
    inline direction_1d(const direction_1d& that) : val_(that.val_) {}
    inline direction_1d(const direction_1d_enum val) : val_(val) {}
    explicit inline direction_1d(const direction_2d& that);
    explicit inline direction_1d(const direction_3d& that);
    inline direction_1d& operator = (const direction_1d& d) {
      val_ = d.val_; return * this; }
    inline bool operator==(direction_1d d) const { return (val_ == d.val_); }
    inline bool operator!=(direction_1d d) const { return !((*this) == d); }
    inline unsigned int to_int(void) const { return val_; }
    inline direction_1d& backward() { val_ ^= 1; return *this; }
    inline int get_sign() const { return val_ * 2 - 1; }
  };

  class direction_2d;

  class orientation_2d {
  private:
    unsigned int val_;
    explicit inline orientation_2d(int o);
  public:
    inline orientation_2d() : val_(HORIZONTAL) {}
    inline orientation_2d(const orientation_2d& ori) : val_(ori.val_) {}
    inline orientation_2d(const orientation_2d_enum val) : val_(val) {}
    explicit inline orientation_2d(const direction_2d& that);
    inline orientation_2d& operator=(const orientation_2d& ori) {
      val_ = ori.val_; return * this; }
    inline bool operator==(orientation_2d that) const { return (val_ == that.val_); }
    inline bool operator!=(orientation_2d that) const { return (val_ != that.val_); }
    inline unsigned int to_int() const { return (val_); }
    inline void turn_90() { val_ = val_^ 1; }
    inline orientation_2d get_perpendicular() const {
      orientation_2d retval = *this;
      retval.turn_90();
      return retval;
    }
    inline direction_2d get_direction(direction_1d dir) const;
  };

  class direction_2d {
  private:
    int val_;

  public:

    inline direction_2d() : val_(WEST) {}

    inline direction_2d(const direction_2d& that) : val_(that.val_) {}

    inline direction_2d(const direction_2d_enum val) : val_(val) {}

    inline direction_2d& operator=(const direction_2d& d) {
      val_ = d.val_;
      return * this;
    }

    inline ~direction_2d() { }

    inline bool operator==(direction_2d d) const { return (val_ == d.val_); }
    inline bool operator!=(direction_2d d) const { return !((*this) == d); }
    inline bool operator< (direction_2d d) const { return (val_ < d.val_); }
    inline bool operator<=(direction_2d d) const { return (val_ <= d.val_); }
    inline bool operator> (direction_2d d) const { return (val_ > d.val_); }
    inline bool operator>=(direction_2d d) const { return (val_ >= d.val_); }

    // Casting to int
    inline unsigned int to_int(void) const { return val_; }

    inline direction_2d backward() const {
      // flip the LSB, toggles 0 - 1   and 2 - 3
      return direction_2d(direction_2d_enum(val_ ^ 1));
    }

    // Returns a direction 90 degree left (LOW) or right(HIGH) to this one
    inline direction_2d turn(direction_1d t) const {
      return direction_2d(direction_2d_enum(val_ ^ 3 ^ (val_ >> 1) ^ t.to_int()));
    }

    // Returns a direction 90 degree left to this one
    inline direction_2d left() const {return turn(HIGH);}

    // Returns a direction 90 degree right to this one
    inline direction_2d right() const {return turn(LOW);}

    // N, E are positive, S, W are negative
    inline bool is_positive() const {return (val_ & 1);}
    inline bool is_negative() const {return !is_positive();}
    inline int get_sign() const {return ((is_positive()) << 1) -1;}

  };

  direction_1d::direction_1d(const direction_2d& that) : val_(that.to_int() & 1) {}

  orientation_2d::orientation_2d(const direction_2d& that) : val_(that.to_int() >> 1) {}

  direction_2d orientation_2d::get_direction(direction_1d dir) const {
    return direction_2d(direction_2d_enum((val_ << 1) + dir.to_int()));
  }

  class orientation_3d {
  private:
    unsigned int val_;
    explicit inline orientation_3d(int o);
  public:
    inline orientation_3d() : val_((int)HORIZONTAL) {}
    inline orientation_3d(const orientation_3d& ori) : val_(ori.val_) {}
    inline orientation_3d(orientation_2d ori) : val_(ori.to_int()) {}
    inline orientation_3d(const orientation_3d_enum val) : val_(val) {}
    explicit inline orientation_3d(const direction_2d& that);
    explicit inline orientation_3d(const direction_3d& that);
    inline ~orientation_3d() {  }
    inline orientation_3d& operator=(const orientation_3d& ori) {
      val_ = ori.val_; return * this; }
    inline bool operator==(orientation_3d that) const { return (val_ == that.val_); }
    inline bool operator!=(orientation_3d that) const { return (val_ != that.val_); }
    inline unsigned int to_int() const { return (val_); }
    inline direction_3d get_direction(direction_1d dir) const;
  };

  class direction_3d {
  private:
    int val_;

  public:

    inline direction_3d() : val_(WEST) {}

    inline direction_3d(direction_2d that) : val_(that.to_int()) {}
    inline direction_3d(const direction_3d& that) : val_(that.val_) {}

    inline direction_3d(const direction_2d_enum val) : val_(val) {}
    inline direction_3d(const direction_3d_enum val) : val_(val) {}

    inline direction_3d& operator=(direction_3d d) {
      val_ = d.val_;
      return * this;
    }

    inline ~direction_3d() { }

    inline bool operator==(direction_3d d) const { return (val_ == d.val_); }
    inline bool operator!=(direction_3d d) const { return !((*this) == d); }
    inline bool operator< (direction_3d d) const { return (val_ < d.val_); }
    inline bool operator<=(direction_3d d) const { return (val_ <= d.val_); }
    inline bool operator> (direction_3d d) const { return (val_ > d.val_); }
    inline bool operator>=(direction_3d d) const { return (val_ >= d.val_); }

    // Casting to int
    inline unsigned int to_int(void) const { return val_; }

    inline direction_3d backward() const {
      // flip the LSB, toggles 0 - 1   and 2 - 3 and 4 - 5
      return direction_2d(direction_2d_enum(val_ ^ 1));
    }

    // N, E, U are positive, S, W, D are negative
    inline bool is_positive() const {return (val_ & 1);}
    inline bool is_negative() const {return !is_positive();}
    inline int get_sign() const {return ((is_positive()) << 1) -1;}

  };

  direction_1d::direction_1d(const direction_3d& that) : val_(that.to_int() & 1) {}
  orientation_3d::orientation_3d(const direction_3d& that) : val_(that.to_int() >> 1) {}
  orientation_3d::orientation_3d(const direction_2d& that) : val_(that.to_int() >> 1) {}

  direction_3d orientation_3d::get_direction(direction_1d dir) const {
    return direction_3d(direction_3d_enum((val_ << 1) + dir.to_int()));
  }

}
}
#endif

/* isotropy.hpp
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
*/