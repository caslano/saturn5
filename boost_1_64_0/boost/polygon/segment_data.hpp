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
EeNIs2hvknK5V8ZSX4R2wNkQMLrZmfZpldeTordW9FaLXvqCCL16nyF3hlpGnT91qbHh3aRU0i2ktfSpFkMrOHJXNjY0cNmCmMy92D+pte8M0FXjtsWX0MNvf4DfMo/UOn4zdof6wdshXeaiYF3w97/k9/p+kXan97Wfd7G5TN+8i+LXF8dvqu1zAdn7p8XzH4vntxbPT6zt/nv2fnrx/NMSN0dQouY+sverjOcnmbi5rRI1h1Va3+D6NVMuHJtz8IXBD4264K2Tz9QOjufP2XZ/v7bObRXy6+sk7w/lvWIZZbyZfx+QwZV5EZpS4S44Aj4Hx8A9cBL8DpwFX4Dl8EVYAb8Pq+HLcA3cD++Er8AH4Q/ht+AB+CI8CH8LfwPfhb+F3TDqdzAV/gEOhX+E4+ARWAz/BBfBo9AP34S3wrfgg/Bt+Cj8C3wcvgP3whNwP/wQvgk/gu9BBoKmT3QAMBl2gr1gZzgAXgQnwy6wHCbDCngpXAH7wtthP3gXHADvhwPhd+FQ+Dd4OexOf7kC9oZXwYFwOLwOjoDTYCYsgFnQA0fDOjgBPgOvhQfhRPhLmAP/DXPhpdThDDgAzoJZsBi+C0tgN9rMfNgLlsHL4EJ4LSyHU+BSmA8dsBoug164HN4GvXAbrIVfhj74TbgSHoaN8AO4Cva5gLYLL4M3wU/BT8IvwSa4A34KvgvvgN3oF3fCXvBeeCX8HMyAm2A23Axz4QOwEn4RroAPwe1wO/wGfBTugl+Bz8OvwZfhM/AP8Fn4IdwN+9Df98By+B24Gu6FTfBFuAnug9+CL8PX4CtwEv3sR3AlfA0+DQ/CAYwHv4BXw1/B8fAQvB7+ATrgH+EN8Ai8G/4J3gP/DHfBN+BP4V/hG/Ad+A/4HpzaBd8AWAQ/gAvhv+Et8BS8D34Ed8GkjtgFO8PX4IXwL7ALPAmT4QXJnC/hCNgNToG9YC7sDefCS2EV7AtvhANhExwMN8Ch8D54FfwKHA6fgyPgD+FIeBhmwnfhOPghvA72YRyaBIfCKXAUnArHwelwJsyBFTAXroAz4adhPtwIZ0E1B1lzTniuuc7nJW6uuRY5brYc1zpX2lyZa64A9oOFcCC8Hl4Di+FoWGJ+11veu8KL5HjWObgmi51TYGc41Tpnm+zHcdnv7Oe888nxsInjnf2cd7ty45dThtiXKeWUJeU0RspprJTTOLFvWZK8rwR+Od6FsESO94zMvfOcHO95OBPugbPhd+FCuBc64ffgcvgirIf7LDrNp9H5s+i8KTpvi85fROe46LwrOu+JzgnR+bulvAfNtJb32c8JuCzO8aK/n54Kn5PjfUuO92053nescxbOtNbf2c8xeFyONyJ0vLObY5Djyfsxxhqb4w2U9jUI9oKDYR84BKbBy+GV8Apr+5fjjbE53iQ53mQ53hQ53jQ4CubALJgLZfyRd1JsEzpeYuZALEuS90ywTI5rnRPwq3Lcx+S4X5Pjfl2O+w04CX4TXg8fh6XwCcsci8351nZ05nMstshxuoSO07o5Fn2kw7LfXonH6AJdst9C6X+L4TC4DM6CTlgDK+Ea6IIbYDW8H3rg03A5fB7Wwj2wTuqrJUne2cAiiXNJDY4LovsliQP5Khwg5ToC7oQTpHzzpXzLpHyrpXz98El4O3wa3gufgY/A5+DT8Hm4T/rja9IP/wC/C9+FL8AP4T7YBfu+D3vDl+GVcD+cDH8I58AD5tyJ8v4GXibl2QmOtJnjsRu8AfaDq6EaD3fJ/stkf+t4eKOUyzrYC94k+38SjpdxYRq8BRbAW2E5vA0uhustOulz4+t8RnQ2iM7tonOn6GwUnc+Kzl2ic7foNIvObtIu0XFKPQc=
*/