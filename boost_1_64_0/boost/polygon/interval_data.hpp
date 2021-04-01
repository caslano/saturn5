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
ZlyXN/ZCbZzNQd0k0iZrhb+lna0mXcfDCk8iNsn7e1eLZpx6tR1ei+V5HjEycdFLntDQcV6lwbfrJ/VmlnQqy80RNF0q6VX1pucRBVn9+TwCc1TIBjm26eJASNWjmBmAx7dTM3/zMY7xIOy4LWtKQ6mzrVCBNnrWtlLLB8aF72LmpV9WzpzU8CZWLNNEdigFg7n8CXJF0sbLPRdWzL4XsYcrF4lK5WuoiPZFQ7SbPCv/lwzlU/e0CDa3adDHGNA8siE3JHZwK/ZRfGqwmanQUlyGmXzqyicvcRcmvrOJUuPqyyKMZpFz8YvcIQRTmmCof7nYev0GIZylsW8u4losuoG1yThXYpJ0TwIzpMmGhARfeNfWgg9S6JzUO4SLmHcy1pgUl/0JBOLnub7XUwkCXQkgHgA7SYEfiHWgORRk9K2aY66bwD70Yx2Wfvby2YX6F/xh4a99TYGI9yCZbJnMNx2+YfZgKacuIHAZk0BpPTM2Aduv9dElRcHEMY9Hi04h5AdN4nf5neT9RI3RAlG6UJ4thLVYLbyGC/V27PZC9G77J8DyRXm5TQV4Ww==
*/