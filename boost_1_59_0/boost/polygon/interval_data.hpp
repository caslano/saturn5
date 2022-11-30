// Boost.Polygon library interval_data.hpp header file

// Copyright (c) Intel Corporation 2008.
// Copyright (c) 2008-2012 Simonson Lucanus.
// Copyright (c) 2012-2012 Andrii Sydorchuk.

// See http://www.boost.org for updates, documentation, and revision history.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_POLYGON_INTERVAL_DATA_HPP
#define BOOST_POLYGON_INTERVAL_DATA_HPP

#include "isotropy.hpp"
#include "interval_concept.hpp"

namespace boost {
namespace polygon {

template <typename T>
class interval_data {
 public:
  typedef T coordinate_type;

  interval_data()
#ifndef BOOST_POLYGON_MSVC
    : coords_()
#endif
  {}

  interval_data(coordinate_type low, coordinate_type high) {
    coords_[LOW] = low;
    coords_[HIGH] = high;
  }

  interval_data(const interval_data& that) {
    coords_[0] = that.coords_[0];
    coords_[1] = that.coords_[1];
  }

  interval_data& operator=(const interval_data& that) {
    coords_[0] = that.coords_[0];
    coords_[1] = that.coords_[1];
    return *this;
  }

  template <typename IntervalType>
  interval_data& operator=(const IntervalType& that) {
    assign(*this, that);
    return *this;
  }

  coordinate_type get(direction_1d dir) const {
    return coords_[dir.to_int()];
  }

  void set(direction_1d dir, coordinate_type value) {
    coords_[dir.to_int()] = value;
  }

  coordinate_type low() const {
    return coords_[0];
  }

  interval_data& low(coordinate_type value) {
    coords_[LOW] = value;
    return *this;
  }

  coordinate_type high() const {
    return coords_[1];
  }

  interval_data& high(coordinate_type value) {
    coords_[HIGH] = value;
    return *this;
  }

  bool operator==(const interval_data& that) const {
    return low() == that.low() && high() == that.high();
  }

  bool operator!=(const interval_data& that) const {
    return low() != that.low() || high() != that.high();
  }

  bool operator<(const interval_data& that) const {
    if (coords_[0] != that.coords_[0]) {
      return coords_[0] < that.coords_[0];
    }
    return coords_[1] < that.coords_[1];
  }

  bool operator<=(const interval_data& that) const {
    return !(that < *this);
  }

  bool operator>(const interval_data& that) const {
    return that < *this;
  }

  bool operator>=(const interval_data& that) const {
    return !((*this) < that);
  }

 private:
  coordinate_type coords_[2];
};

template <typename CType>
struct geometry_concept< interval_data<CType> > {
  typedef interval_concept type;
};
}  // polygon
}  // boost

#endif  // BOOST_POLYGON_INTERVAL_DATA_HPP

/* interval_data.hpp
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
*/