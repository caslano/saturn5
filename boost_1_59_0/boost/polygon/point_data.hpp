// Boost.Polygon library point_data.hpp header file

// Copyright (c) Intel Corporation 2008.
// Copyright (c) 2008-2012 Simonson Lucanus.
// Copyright (c) 2012-2012 Andrii Sydorchuk.

// See http://www.boost.org for updates, documentation, and revision history.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_POLYGON_POINT_DATA_HPP
#define BOOST_POLYGON_POINT_DATA_HPP

#include "isotropy.hpp"
#include "point_concept.hpp"

namespace boost {
namespace polygon {

template <typename T>
class point_data {
 public:
  typedef T coordinate_type;

  point_data()
#ifndef BOOST_POLYGON_MSVC
    : coords_()
#endif
  {}

  point_data(coordinate_type x, coordinate_type y) {
    coords_[HORIZONTAL] = x;
    coords_[VERTICAL] = y;
  }

  explicit point_data(const point_data& that) {
    coords_[0] = that.coords_[0];
    coords_[1] = that.coords_[1];
  }

  point_data& operator=(const point_data& that) {
    coords_[0] = that.coords_[0];
    coords_[1] = that.coords_[1];
    return *this;
  }

#if defined(__GNUC__) && __GNUC__ < 6
  // "explicit" to work around a bug in GCC < 6: https://gcc.gnu.org/bugzilla/show_bug.cgi?id=63356
  template <typename PointType>
  explicit point_data(const PointType& that) {
    *this = that;
  }
#else // __GNUC__ < 6
  template <typename PointType>
  point_data(const PointType& that) {
    *this = that;
  }
#endif // __GNUC__ < 6

  template <typename PointType>
  point_data& operator=(const PointType& that) {
    assign(*this, that);
    return *this;
  }

  // TODO(asydorchuk): Deprecated.
  template <typename CT>
  point_data(const point_data<CT>& that) {
    coords_[HORIZONTAL] = (coordinate_type)that.x();
    coords_[VERTICAL] = (coordinate_type)that.y();
  }

  coordinate_type get(orientation_2d orient) const {
    return coords_[orient.to_int()];
  }

  void set(orientation_2d orient, coordinate_type value) {
    coords_[orient.to_int()] = value;
  }

  coordinate_type x() const {
    return coords_[HORIZONTAL];
  }

  point_data& x(coordinate_type value) {
    coords_[HORIZONTAL] = value;
    return *this;
  }

  coordinate_type y() const {
    return coords_[VERTICAL];
  }

  point_data& y(coordinate_type value) {
    coords_[VERTICAL] = value;
    return *this;
  }

  bool operator==(const point_data& that) const {
    return (coords_[0] == that.coords_[0]) &&
      (coords_[1] == that.coords_[1]);
  }

  bool operator!=(const point_data& that) const {
    return !(*this == that);
  }

  bool operator<(const point_data& that) const {
    return (coords_[0] < that.coords_[0]) ||
      ((coords_[0] == that.coords_[0]) &&
       (coords_[1] < that.coords_[1]));
  }

  bool operator<=(const point_data& that) const {
    return !(that < *this);
  }

  bool operator>(const point_data& that) const {
    return that < *this;
  }

  bool operator>=(const point_data& that) const {
    return !(*this < that);
  }

 private:
  coordinate_type coords_[2];
};

template <typename CType>
struct geometry_concept< point_data<CType> > {
  typedef point_concept type;
};
}  // polygon
}  // boost

#endif  // BOOST_POLYGON_POINT_DATA_HPP

/* point_data.hpp
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
*/