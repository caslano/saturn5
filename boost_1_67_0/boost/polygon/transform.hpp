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