// Boost.Polygon library transform.hpp header file

// Copyright (c) Intel Corporation 2008.
// Copyright (c) 2008-2012 Simonson Lucanus.
// Copyright (c) 2012-2012 Andrii Sydorchuk.

// See http://www.boost.org for updates, documentation, and revision history.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_POLYGON_TRANSFORM_HPP
#define BOOST_POLYGON_TRANSFORM_HPP

#include "isotropy.hpp"

namespace boost {
namespace polygon {
// Transformation of Coordinate System.
// Enum meaning:
// Select which direction_2d to change the positive direction of each
// axis in the old coordinate system to map it to the new coordiante system.
// The first direction_2d listed for each enum is the direction to map the
// positive horizontal direction to.
// The second direction_2d listed for each enum is the direction to map the
// positive vertical direction to.
// The zero position bit (LSB) indicates whether the horizontal axis flips
// when transformed.
// The 1st postion bit indicates whether the vertical axis flips when
// transformed.
// The 2nd position bit indicates whether the horizontal and vertical axis
// swap positions when transformed.
// Enum Values:
//   000 EAST NORTH
//   001 WEST NORTH
//   010 EAST SOUTH
//   011 WEST SOUTH
//   100 NORTH EAST
//   101 SOUTH EAST
//   110 NORTH WEST
//   111 SOUTH WEST
class axis_transformation {
 public:
  enum ATR {
#ifdef BOOST_POLYGON_ENABLE_DEPRECATED
    EN = 0,
    WN = 1,
    ES = 2,
    WS = 3,
    NE = 4,
    SE = 5,
    NW = 6,
    SW = 7,
#endif
    NULL_TRANSFORM = 0,
    BEGIN_TRANSFORM = 0,
    EAST_NORTH = 0,
    WEST_NORTH = 1, FLIP_X       = 1,
    EAST_SOUTH = 2, FLIP_Y       = 2,
    WEST_SOUTH = 3, FLIP_XY      = 3,
    NORTH_EAST = 4, SWAP_XY      = 4,
    SOUTH_EAST = 5, ROTATE_LEFT  = 5,
    NORTH_WEST = 6, ROTATE_RIGHT = 6,
    SOUTH_WEST = 7, FLIP_SWAP_XY = 7,
    END_TRANSFORM = 7
  };

  // Individual axis enum values indicate which axis an implicit individual
  // axis will be mapped to.
  // The value of the enum paired with an axis provides the information
  // about what the axis will transform to.
  // Three individual axis values, one for each axis, are equivalent to one
  // ATR enum value, but easier to work with because they are independent.
  // Converting to and from the individual axis values from the ATR value
  // is a convenient way to implement tranformation related functionality.
  // Enum meanings:
  // PX: map to positive x axis
  // NX: map to negative x axis
  // PY: map to positive y axis
  // NY: map to negative y axis
  enum INDIVIDUAL_AXIS {
    PX = 0,
    NX = 1,
    PY = 2,
    NY = 3
  };

  axis_transformation() : atr_(NULL_TRANSFORM) {}
  explicit axis_transformation(ATR atr) : atr_(atr) {}
  axis_transformation(const axis_transformation& atr) : atr_(atr.atr_) {}

  explicit axis_transformation(const orientation_2d& orient) {
    const ATR tmp[2] = {
      NORTH_EAST,  // sort x, then y
      EAST_NORTH   // sort y, then x
    };
    atr_ = tmp[orient.to_int()];
  }

  explicit axis_transformation(const direction_2d& dir) {
    const ATR tmp[4] = {
      SOUTH_EAST,  // sort x, then y
      NORTH_EAST,  // sort x, then y
      EAST_SOUTH,  // sort y, then x
      EAST_NORTH   // sort y, then x
    };
    atr_ = tmp[dir.to_int()];
  }

  // assignment operator
  axis_transformation& operator=(const axis_transformation& a) {
    atr_ = a.atr_;
    return *this;
  }

  // assignment operator
  axis_transformation& operator=(const ATR& atr) {
    atr_ = atr;
    return *this;
  }

  // equivalence operator
  bool operator==(const axis_transformation& a) const {
    return atr_ == a.atr_;
  }

  // inequivalence operator
  bool operator!=(const axis_transformation& a) const {
    return !(*this == a);
  }

  // ordering
  bool operator<(const axis_transformation& a) const {
    return atr_ < a.atr_;
  }

  // concatenate this with that
  axis_transformation& operator+=(const axis_transformation& a) {
    bool abit2 = (a.atr_ & 4) != 0;
    bool abit1 = (a.atr_ & 2) != 0;
    bool abit0 = (a.atr_ & 1) != 0;
    bool bit2 = (atr_ & 4) != 0;
    bool bit1 = (atr_ & 2) != 0;
    bool bit0 = (atr_ & 1) != 0;
    int indexes[2][2] = {
      { (int)bit2, (int)(!bit2) },
      { (int)abit2, (int)(!abit2) }
    };
    int zero_bits[2][2] = {
      {bit0, bit1}, {abit0, abit1}
    };
    int nbit1 = zero_bits[0][1] ^ zero_bits[1][indexes[0][1]];
    int nbit0 = zero_bits[0][0] ^ zero_bits[1][indexes[0][0]];
    indexes[0][0] = indexes[1][indexes[0][0]];
    indexes[0][1] = indexes[1][indexes[0][1]];
    int nbit2 = indexes[0][0] & 1;  // swap xy
    atr_ = (ATR)((nbit2 << 2) + (nbit1 << 1) + nbit0);
    return *this;
  }

  // concatenation operator
  axis_transformation operator+(const axis_transformation& a) const {
    axis_transformation retval(*this);
    return retval+=a;
  }

  // populate_axis_array writes the three INDIVIDUAL_AXIS values that the
  // ATR enum value of 'this' represent into axis_array
  void populate_axis_array(INDIVIDUAL_AXIS axis_array[]) const {
    bool bit2 = (atr_ & 4) != 0;
    bool bit1 = (atr_ & 2) != 0;
    bool bit0 = (atr_ & 1) != 0;
    axis_array[1] = (INDIVIDUAL_AXIS)(((int)(!bit2) << 1) + bit1);
    axis_array[0] = (INDIVIDUAL_AXIS)(((int)(bit2) << 1) + bit0);
  }

  // it is recommended that the directions stored in an array
  // in the caller code for easier isotropic access by orientation value
  void get_directions(direction_2d& horizontal_dir,
                      direction_2d& vertical_dir) const {
    bool bit2 = (atr_ & 4) != 0;
    bool bit1 = (atr_ & 2) != 0;
    bool bit0 = (atr_ & 1) != 0;
    vertical_dir = direction_2d((direction_2d_enum)(((int)(!bit2) << 1) + !bit1));
    horizontal_dir = direction_2d((direction_2d_enum)(((int)(bit2) << 1) + !bit0));
  }

  // combine_axis_arrays concatenates this_array and that_array overwriting
  // the result into this_array
  static void combine_axis_arrays(INDIVIDUAL_AXIS this_array[],
                                  const INDIVIDUAL_AXIS that_array[]) {
    int indexes[2] = { this_array[0] >> 1, this_array[1] >> 1 };
    int zero_bits[2][2] = {
      { this_array[0] & 1, this_array[1] & 1 },
      { that_array[0] & 1, that_array[1] & 1 }
    };
    this_array[0] = (INDIVIDUAL_AXIS)((int)this_array[0] |
                                      ((int)zero_bits[0][0] ^
                                       (int)zero_bits[1][indexes[0]]));
    this_array[1] = (INDIVIDUAL_AXIS)((int)this_array[1] |
                                      ((int)zero_bits[0][1] ^
                                       (int)zero_bits[1][indexes[1]]));
  }

  // write_back_axis_array converts an array of three INDIVIDUAL_AXIS values
  // to the ATR enum value and sets 'this' to that value
  void write_back_axis_array(const INDIVIDUAL_AXIS this_array[]) {
    int bit2 = ((int)this_array[0] & 2) != 0;  // swap xy
    int bit1 = ((int)this_array[1] & 1);
    int bit0 = ((int)this_array[0] & 1);
    atr_ = ATR((bit2 << 2) + (bit1 << 1) + bit0);
  }

  // behavior is deterministic but undefined in the case where illegal
  // combinations of directions are passed in.
  axis_transformation& set_directions(const direction_2d& horizontal_dir,
                                      const direction_2d& vertical_dir) {
    int bit2 = (static_cast<orientation_2d>(horizontal_dir).to_int()) != 0;
    int bit1 = !(vertical_dir.to_int() & 1);
    int bit0 = !(horizontal_dir.to_int() & 1);
    atr_ = ATR((bit2 << 2) + (bit1 << 1) + bit0);
    return *this;
  }

  // transform the three coordinates by reference
  template <typename coordinate_type>
  void transform(coordinate_type& x, coordinate_type& y) const {
    int bit2 = (atr_ & 4) != 0;
    int bit1 = (atr_ & 2) != 0;
    int bit0 = (atr_ & 1) != 0;
    x *= -((bit0 << 1) - 1);
    y *= -((bit1 << 1) - 1);
    predicated_swap(bit2 != 0, x, y);
  }

  // invert this axis_transformation
  axis_transformation& invert() {
    int bit2 = ((atr_ & 4) != 0);
    int bit1 = ((atr_ & 2) != 0);
    int bit0 = ((atr_ & 1) != 0);
    // swap bit 0 and bit 1 if bit2 is 1
    predicated_swap(bit2 != 0, bit0, bit1);
    bit1 = bit1 << 1;
    atr_ = (ATR)(atr_ & (32+16+8+4));  // mask away bit0 and bit1
    atr_ = (ATR)(atr_ | bit0 | bit1);
    return *this;
  }

  // get the inverse axis_transformation of this
  axis_transformation inverse() const {
    axis_transformation retval(*this);
    return retval.invert();
  }

 private:
  ATR atr_;
};

// Scaling object to be used to store the scale factor for each axis.
// For use by the transformation object, in that context the scale factor
// is the amount that each axis scales by when transformed.
template <typename scale_factor_type>
class anisotropic_scale_factor {
 public:
  anisotropic_scale_factor() {
    scale_[0] = 1;
    scale_[1] = 1;
  }
  anisotropic_scale_factor(scale_factor_type xscale,
                           scale_factor_type yscale) {
    scale_[0] = xscale;
    scale_[1] = yscale;
  }

  // get a component of the anisotropic_scale_factor by orientation
  scale_factor_type get(orientation_2d orient) const {
    return scale_[orient.to_int()];
  }

  // set a component of the anisotropic_scale_factor by orientation
  void set(orientation_2d orient, scale_factor_type value) {
    scale_[orient.to_int()] = value;
  }

  scale_factor_type x() const {
    return scale_[HORIZONTAL];
  }

  scale_factor_type y() const {
    return scale_[VERTICAL];
  }

  void x(scale_factor_type value) {
    scale_[HORIZONTAL] = value;
  }

  void y(scale_factor_type value) {
    scale_[VERTICAL] = value;
  }

  // concatination operator (convolve scale factors)
  anisotropic_scale_factor operator+(const anisotropic_scale_factor& s) const {
    anisotropic_scale_factor<scale_factor_type> retval(*this);
    return retval += s;
  }

  // concatinate this with that
  const anisotropic_scale_factor& operator+=(
      const anisotropic_scale_factor& s) {
    scale_[0] *= s.scale_[0];
    scale_[1] *= s.scale_[1];
    return *this;
  }

  // transform this scale with an axis_transform
  anisotropic_scale_factor& transform(axis_transformation atr) {
    direction_2d dirs[2];
    atr.get_directions(dirs[0], dirs[1]);
    scale_factor_type tmp[2] = {scale_[0], scale_[1]};
    for (int i = 0; i < 2; ++i) {
      scale_[orientation_2d(dirs[i]).to_int()] = tmp[i];
    }
    return *this;
  }

  // scale the two coordinates
  template <typename coordinate_type>
  void scale(coordinate_type& x, coordinate_type& y) const {
    x = scaling_policy<coordinate_type>::round(
        (scale_factor_type)x * get(HORIZONTAL));
    y = scaling_policy<coordinate_type>::round(
        (scale_factor_type)y * get(HORIZONTAL));
  }

  // invert this scale factor to give the reverse scale factor
  anisotropic_scale_factor& invert() {
    x(1/x());
    y(1/y());
    return *this;
  }

 private:
  scale_factor_type scale_[2];
};

// Transformation object, stores and provides services for transformations.
// Consits of axis transformation, scale factor and translation.
// The tranlation is the position of the origin of the new coordinate system of
// in the old system. Coordinates are scaled before they are transformed.
template <typename coordinate_type>
class transformation {
 public:
  transformation() : atr_(), p_(0, 0) {}
  explicit transformation(axis_transformation atr) : atr_(atr), p_(0, 0) {}
  explicit transformation(axis_transformation::ATR atr) : atr_(atr), p_(0, 0) {}
  transformation(const transformation& tr) : atr_(tr.atr_), p_(tr.p_) {}

  template <typename point_type>
  explicit transformation(const point_type& p) : atr_(), p_(0, 0) {
    set_translation(p);
  }

  template <typename point_type>
  transformation(axis_transformation atr,
                 const point_type& p) : atr_(atr), p_(0, 0) {
    set_translation(p);
  }

  template <typename point_type>
  transformation(axis_transformation atr,
                 const point_type& referencePt,
                 const point_type& destinationPt) : atr_(), p_(0, 0) {
    transformation<coordinate_type> tmp(referencePt);
    transformation<coordinate_type> rotRef(atr);
    transformation<coordinate_type> tmpInverse = tmp.inverse();
    point_type decon(referencePt);
    deconvolve(decon, destinationPt);
    transformation<coordinate_type> displacement(decon);
    tmp += rotRef;
    tmp += tmpInverse;
    tmp += displacement;
    (*this) = tmp;
  }

  // equivalence operator
  bool operator==(const transformation& tr) const {
    return (atr_ == tr.atr_) && (p_ == tr.p_);
  }

  // inequivalence operator
  bool operator!=(const transformation& tr) const {
    return !(*this == tr);
  }

  // ordering
  bool operator<(const transformation& tr) const {
    return (atr_ < tr.atr_) || ((atr_ == tr.atr_) && (p_ < tr.p_));
  }

  // concatenation operator
  transformation operator+(const transformation& tr) const {
    transformation<coordinate_type> retval(*this);
    return retval+=tr;
  }

  // concatenate this with that
  const transformation& operator+=(const transformation& tr) {
    coordinate_type x, y;
    transformation<coordinate_type> inv = inverse();
    inv.transform(x, y);
    p_.set(HORIZONTAL, p_.get(HORIZONTAL) + x);
    p_.set(VERTICAL, p_.get(VERTICAL) + y);
    // concatenate axis transforms
    atr_ += tr.atr_;
    return *this;
  }

  // get the axis_transformation portion of this
  axis_transformation get_axis_transformation() const {
    return atr_;
  }

  // set the axis_transformation portion of this
  void set_axis_transformation(const axis_transformation& atr) {
    atr_ = atr;
  }

  // get the translation
  template <typename point_type>
  void get_translation(point_type& p) const {
    assign(p, p_);
  }

  // set the translation
  template <typename point_type>
  void set_translation(const point_type& p) {
    assign(p_, p);
  }

  // apply the 2D portion of this transformation to the two coordinates given
  void transform(coordinate_type& x, coordinate_type& y) const {
    y -= p_.get(VERTICAL);
    x -= p_.get(HORIZONTAL);
    atr_.transform(x, y);
  }

  // invert this transformation
  transformation& invert() {
    coordinate_type x = p_.get(HORIZONTAL), y = p_.get(VERTICAL);
    atr_.transform(x, y);
    x *= -1;
    y *= -1;
    p_ = point_data<coordinate_type>(x, y);
    atr_.invert();
    return *this;
  }

  // get the inverse of this transformation
  transformation inverse() const {
    transformation<coordinate_type> ret_val(*this);
    return ret_val.invert();
  }

  void get_directions(direction_2d& horizontal_dir,
                      direction_2d& vertical_dir) const {
    return atr_.get_directions(horizontal_dir, vertical_dir);
  }

 private:
  axis_transformation atr_;
  point_data<coordinate_type> p_;
};
}  // polygon
}  // boost

#endif  // BOOST_POLYGON_TRANSFORM_HPP

/* transform.hpp
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
*/