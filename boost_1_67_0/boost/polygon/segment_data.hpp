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