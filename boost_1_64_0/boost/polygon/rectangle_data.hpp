/*
  Copyright 2008 Intel Corporation

  Use, modification and distribution are subject to the Boost Software License,
  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt).
*/
#ifndef BOOST_POLYGON_RECTANGLE_DATA_HPP
#define BOOST_POLYGON_RECTANGLE_DATA_HPP

#include "isotropy.hpp"
//interval
#include "interval_data.hpp"

namespace boost { namespace polygon{

template <typename T>
class rectangle_data {
public:
  typedef T coordinate_type;
  typedef interval_data<T> interval_type;
  inline rectangle_data():ranges_() {}
  inline rectangle_data(T xl, T yl, T xh, T yh):ranges_() {
    if(xl > xh) std::swap(xl, xh);
    if(yl > yh) std::swap(yl, yh);
    ranges_[HORIZONTAL] = interval_data<T>(xl, xh);
    ranges_[VERTICAL] = interval_data<T>(yl, yh);
  }
  template <typename interval_type_1, typename interval_type_2>
  inline rectangle_data(const interval_type_1& hrange,
                        const interval_type_2& vrange):ranges_() {
    set(HORIZONTAL, hrange); set(VERTICAL, vrange); }

  inline rectangle_data(const rectangle_data& that):ranges_() { (*this) = that; }
  inline rectangle_data& operator=(const rectangle_data& that) {
    ranges_[0] = that.ranges_[0]; ranges_[1] = that.ranges_[1]; return *this;
  }
  template <typename T2>
  inline rectangle_data& operator=(const T2& rvalue);

  template <typename T2>
  inline bool operator==(const T2& rvalue) const;
  template <typename T2>
  inline bool operator!=(const T2& rvalue) const { return !((*this) == rvalue); }

  inline interval_data<coordinate_type> get(orientation_2d orient) const {
    return ranges_[orient.to_int()]; }
  inline coordinate_type get(direction_2d dir) const {
    return ranges_[orientation_2d(dir).to_int()].get(direction_1d(dir));
  }
  inline void set(direction_2d dir, coordinate_type value) {
    return ranges_[orientation_2d(dir).to_int()].set(direction_1d(dir), value);
  }
  template <typename interval_type_1>
  inline void set(orientation_2d orient, const interval_type_1& interval);
private:
  interval_data<coordinate_type> ranges_[2];
};


}
}
#endif

/* rectangle_data.hpp
3AkPkcXLh0trW+HtVZEZMOHHBVXyYXqSD47+V6QLve2goGLF22uaImKz614Jfm50sjKQsdbe6rSTK6O/8qhIhxme71ldHYG9x31/j0pOfm2Pv0o9vbw0Q4yhhYqc8kjgoHGTE0GL9dNFdbsQGKZYv76f73dKZJZjKqtIrTz8mM4dJn5q4WeXJTdHSJFU/lpP5omYY0IGemnyBKH4jf8MVx9rgbBy+9L0X/2H9BOWpKhUlj8fIMoxFq96tIIq/3KUnFvehXHE/MZMoI0c8+D6OEixxV8RtMt6AMLU14SKLOmKZVq6v5ME3CEL4Bit3iG2Jye3NeMqmh6+7f4CDnC0S4SUQbkMv9RB4k8cU7hdY+J85XN0Krj+NSa9Rj9J8iW7tOVAE+BwuPC8QqlqSBXyaQj7SlhwyIc7UYqsDuLIBNqsjqf3BfJg9RXK/vvW06xoMkmPXqd7A4sFUFKKRP3Rg/gtmar+wn+7ITMLrQhRGqLGLeC3cJS+Fg+KwbnjCZROnUQ2J19+E+hH7ln27AvQCR69gCiVtzNatd53kglVPhyAoeIQtoIQyS0vIQ==
*/