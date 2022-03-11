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