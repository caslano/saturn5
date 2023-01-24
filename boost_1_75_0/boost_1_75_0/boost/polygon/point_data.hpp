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
/ibSmz5p5T65YlzqrQHnVwnbsGISzPgJ5WFHUULLQGEOVv871VX02VY6u1ZSlDxnHhLxntKSbiUpicf8iFMHXGp9tspRLHngng6EvlTKzbx0BWxoLd890Ioa3cwNxU6EdQjKt6SrZaXMo3x+fXq6tf2GLyaWMJJl3twcbCy+6uk/NXkRgF6nmnqzB35sldRbvF+KdDLaG9CQJdl5f+3p1ghbC8FikAaslWrr5yIro9IrANavalF5dnc3W059PpPwddwc9uVgHAAxr66FzYVgRNe/mqJeSpn7LfGLRJ0efDs0MooQNia+aySIwZcy5OMnLP2g5Q4zA4OJiKcAANR/e3J2UypNVNsdRtREgW2AUfAmIVFA9eY11JkZOD3tfIb5xLJ/fGV1h9CX+f7qCzlfGPSh/w7Q88saxRl1CmkKdQpliv7wGiskVqYAX2CMto9kS22Lc6szuLlvd2iJZ0Zuy7FPs2+hT8BE2AW7DukAFT4fEM+whLSEwvt3AiYNacVPtLYoTAYnelejnt+VC/AOe23l93UGCwYLhnQGd2oWehetY70lmkQoyXbGUTRu8JH9nfKTLebf6kjNn9mdn3Prn9o00BN+xs93rVqqP9GRp5/WP9UZ2k4Xdu1cihN8vuvad2Le9ohUqKpas3XNa/PkO8yK9rr+PmdFosTp5HWSID3RRnB8pc9BDendjKLj8FeuJecyV5KW72JeCYs5
*/