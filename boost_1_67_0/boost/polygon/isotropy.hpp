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