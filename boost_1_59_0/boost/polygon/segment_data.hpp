// Boost.Polygon library segment_data.hpp header file

// Copyright (c) Intel Corporation 2008.
// Copyright (c) 2008-2012 Simonson Lucanus.
// Copyright (c) 2012-2012 Andrii Sydorchuk.

// See http://www.boost.org for updates, documentation, and revision history.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_POLYGON_SEGMENT_DATA_HPP
#define BOOST_POLYGON_SEGMENT_DATA_HPP

#include "isotropy.hpp"
#include "segment_concept.hpp"

namespace boost {
namespace polygon {

template <typename T>
class segment_data {
 public:
  typedef T coordinate_type;
  typedef point_data<T> point_type;

  segment_data()
#ifndef BOOST_POLYGON_MSVC
    : points_()
#endif
  {}

  segment_data(const point_type& low, const point_type& high) {
    points_[LOW] = low;
    points_[HIGH] = high;
  }

  segment_data(const segment_data& that) {
    points_[0] = that.points_[0];
    points_[1] = that.points_[1];
  }

  segment_data& operator=(const segment_data& that) {
    points_[0] = that.points_[0];
    points_[1] = that.points_[1];
    return *this;
  }

  template <typename SegmentType>
  segment_data& operator=(const SegmentType& that) {
    assign(*this, that);
    return *this;
  }

  point_type get(direction_1d dir) const {
    return points_[dir.to_int()];
  }

  void set(direction_1d dir, const point_type& point) {
    points_[dir.to_int()] = point;
  }

  point_type low() const {
    return points_[LOW];
  }

  segment_data& low(const point_type& point) {
    points_[LOW] = point;
    return *this;
  }

  point_type high() const {
    return points_[HIGH];
  }

  segment_data& high(const point_type& point) {
    points_[HIGH] = point;
    return *this;
  }

  bool operator==(const segment_data& that) const {
    return (points_[0] == that.points_[0]) &&
           (points_[1] == that.points_[1]);
  }

  bool operator!=(const segment_data& that) const {
    return (points_[0] != that.points_[0]) ||
           (points_[1] != that.points_[1]);
  }

  bool operator<(const segment_data& that) const {
    if (points_[0] != that.points_[0]) {
      return points_[0] < that.points_[0];
    }
    return points_[1] < that.points_[1];
  }

  bool operator<=(const segment_data& that) const {
    return !(that < *this);
  }

  bool operator>(const segment_data& that) const {
    return that < *this;
  }

  bool operator>=(const segment_data& that) const {
    return !((*this) < that);
  }

 private:
  point_type points_[2];
};

template <typename CType>
struct geometry_concept<segment_data<CType> > {
  typedef segment_concept type;
};
}  // polygon
}  // boost

#endif  // BOOST_POLYGON_SEGMENT_DATA_HPP

/* segment_data.hpp
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
*/